
#include <winsock2.h>
#include <stdio.h>
#include <windows.h>
#include "Ws2tcpip.h"
#pragma comment(lib, "WS2_32") // 链接到WS2_32.lib
class CInitSock
{
public:
	CInitSock(BYTE minorVer = 2, BYTE majorVer = 2)
	{
		// 初始化WS2_32.dll
		WSADATA wsaData;
		WORD sockVersion = MAKEWORD(minorVer, majorVer);
		if (::WSAStartup(sockVersion, &wsaData) != 0)
			return;
	}
	~CInitSock()
	{
		::WSACleanup();
	}
};

CInitSock theSock;

typedef struct _IP_HEADER
{
	char m_cVersionAndHeaderLen; //版本信息(前4位)，头长度(后4位)
	char m_cTypeOfService;			 //服务类型8位
	short m_sTotalLenOfPacket;	 //数据包长度
	short m_sPacketID;					 //数据包标识
	short m_sSliceinfo;					 //分片使用
	char m_cTTL;								 //存活时间
	char m_cTypeOfProtocol;			 //协议类型
	short m_sCheckSum;					 //校验和
	unsigned int m_uiSourIp;		 //源ip
	unsigned int m_uiDestIp;		 //目的ip
} ip_hdr;

typedef struct icmp_hdr
{
	unsigned char icmp_type;			// 消息类型
	unsigned char icmp_code;			// 代码
	unsigned short icmp_checksum; // 校验和
																// 下面是回显头
	unsigned short icmp_id;				// 用来惟一标识此请求的ID号，通常设置为进程ID
	unsigned short icmp_sequence; // 序列号
	unsigned long icmp_timestamp; // 时间戳
} ICMP_HDR, *PICMP_HDR;

USHORT checksum(USHORT *buff, int size);
BOOL SetTTL(SOCKET s, int nValue);
BOOL SetTimeout(SOCKET s, int nTime, BOOL bRecv = TRUE);

USHORT checksum(USHORT *buff, int size)
{
	unsigned long cksum = 0;
	while (size > 1)
	{
		cksum += *buff++;
		size -= sizeof(USHORT);
	}
	// 是奇数
	if (size)
	{
		cksum += *(UCHAR *)buff;
	}
	// 将32位的chsum高16位和低16位相加，然后取反
	cksum = (cksum >> 16) + (cksum & 0xffff);
	cksum += (cksum >> 16);
	return (USHORT)(~cksum);
}

BOOL SetTTL(SOCKET s, int nValue)
{
	int ret = ::setsockopt(s, IPPROTO_IP, IP_TTL, (char *)&nValue, sizeof(nValue));
	return ret != SOCKET_ERROR;
}

BOOL SetTimeout(SOCKET s, int nTime, BOOL bRecv)
{
	int ret = ::setsockopt(s, SOL_SOCKET,
												 bRecv ? SO_RCVTIMEO : SO_SNDTIMEO, (char *)&nTime, sizeof(nTime));
	return ret != SOCKET_ERROR;
}

int main()
{
	// 目的IP地址，即要Ping的IP地址
	char szDestIp[] = "192.168.1.1"; // 127.0.0.1
	ip_hdr IPHeader;

	// 创建原始套节字
	SOCKET sRaw = ::socket(AF_INET, SOCK_RAW, IPPROTO_ICMP);

	// 设置接收超时
	SetTimeout(sRaw, 1000, TRUE);

	// 设置目的地址
	SOCKADDR_IN dest;
	dest.sin_family = AF_INET;
	dest.sin_port = htons(0);
	dest.sin_addr.S_un.S_addr = inet_addr(szDestIp);

	// 创建ICMP封包
	char buff[sizeof(ICMP_HDR) + 32];
	ICMP_HDR *pIcmp = (ICMP_HDR *)buff;

	// 填写ICMP封包数据
	pIcmp->icmp_type = 8; // 请求一个ICMP回显
	pIcmp->icmp_code = 0;
	pIcmp->icmp_id = (USHORT)::GetCurrentProcessId();
	pIcmp->icmp_checksum = 0;
	pIcmp->icmp_sequence = 0;

	// 填充数据部分，可以为任意
	memset(&buff[sizeof(ICMP_HDR)], '1', 32);

	// 开始发送和接收ICMP封包
	USHORT nSeq = 0;
	char recvBuf[1024];
	SOCKADDR_IN from;
	int nLen = sizeof(from);
	while (TRUE)
	{
		static int nCount = 0;
		int nRet;
		if (nCount++ == 4)
			break;
		pIcmp->icmp_checksum = 0;
		pIcmp->icmp_timestamp = ::GetTickCount();
		pIcmp->icmp_sequence = nSeq++;
		pIcmp->icmp_checksum = checksum((USHORT *)buff, sizeof(ICMP_HDR) + 32);
		nRet = ::sendto(sRaw, buff, sizeof(ICMP_HDR) + 32, 0, (SOCKADDR *)&dest, sizeof(dest));
		if (nRet == SOCKET_ERROR)
		{
			printf(" sendto() failed: %d \n", ::WSAGetLastError());
			return -1;
		}
		nRet = ::recvfrom(sRaw, recvBuf, 1024, 0, (sockaddr *)&from, &nLen);
		if (nRet == SOCKET_ERROR)
		{
			if (::WSAGetLastError() == WSAETIMEDOUT)
			{
				printf(" timed out\n");
				continue;
			}
			printf(" recvfrom() failed: %d\n", ::WSAGetLastError());
			return -1;
		}

		// 下面开始解析接收到的ICMP封包
		int nTick = ::GetTickCount();
		if (nRet < sizeof(IPHeader) + sizeof(ICMP_HDR))
		{
			printf(" Too few bytes from %s \n", ::inet_ntoa(from.sin_addr));
		}
		// 接收到的数据中包含IP头，IP头大小为20个字节，所以加20得到ICMP头
		ICMP_HDR *pRecvIcmp = (ICMP_HDR *)(recvBuf + 20); // (ICMP_HDR*)(recvBuf + sizeof(IPHeader));
		if (pRecvIcmp->icmp_type != 0)										// 回显
		{
			printf(" nonecho type %d recvd \n", pRecvIcmp->icmp_type);
			return -1;
		}

		if (pRecvIcmp->icmp_id != ::GetCurrentProcessId())
		{
			printf(" someone else's packet! \n");
			return -1;
		}

		printf(" %d bytes from %s:", nRet, inet_ntoa(from.sin_addr));
		printf(" icmp_seq = %d. ", pRecvIcmp->icmp_sequence);
		printf(" time: %d ms", nTick - pRecvIcmp->icmp_timestamp);
		printf(" \n");

		::Sleep(1000);
	}

	return 0;
}