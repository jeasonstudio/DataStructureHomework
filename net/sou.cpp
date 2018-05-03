#define HAVE_REMOTE  
#define WPCAP  
#include <stdio.h>  
#include <stdlib.h>  
#include <pcap.h> 
#pragma comment(lib, "wpcap.lib")
#pragma comment(lib, "wsock32.lib")
#pragma comment(lib, "ws2_32.lib")
#define ETH_ARP         0x0806  //以太网帧类型表示后面数据的类型，对于ARP请求或应答来说，该字段的值为x0806
#define ARP_HARDWARE    1  //硬件类型字段值为表示以太网地址
#define ETH_IP          0x0800  //协议类型字段表示要映射的协议地址类型值为x0800表示IP地址
#define ARP_REQUEST     1   //ARP请求
#define ARP_REPLY       2      //ARP应答
#define HOSTNUM         16  //主机数量
#pragma pack(1)  //按一个字节内存对齐 
#define LOCALIP "10.18.138.36"
#define LOCALMASK "255.255.255.0"

struct IpAddress//IP地址格式
{
    u_char byte1;
    u_char byte2;
    u_char byte3;
    u_char byte4;
};

struct EthernetHeader//帧头部结构体，共14字节
{
    u_char DestMAC[6];    //目的MAC地址 6字节
    u_char SourMAC[6];   //源MAC地址 6字节
    u_short EthType;         //上一层协议类型，如0x0800代表上一层是IP协议，0x0806为arp  2字节
};

struct Arpheader {                         //28字节ARP帧结构
	unsigned short HardwareType; //硬件类型
	unsigned short ProtocolType; //协议类型
	unsigned char HardwareAddLen; //硬件地址长度
	unsigned char ProtocolAddLen; //协议地址长度
	unsigned short OperationField; //操作字段
	unsigned char SourceMacAdd[6]; //源mac地址
	unsigned long SourceIpAdd; //源ip地址
	unsigned char DestMacAdd[6]; //目的mac地址
	unsigned long DestIpAdd; //目的ip地址
};

//arp包结构
struct ArpPacket {
	EthernetHeader ed;
	Arpheader ah;
	char padding[18];
};

#define IPTOSBUFFERS   12 

// TODO:
char *iptos(u_long input)  
{   static char output[IPTOSBUFFERS][3*4+3+1];  
    static short which;  
    u_char *p;  
    p = (u_char *)&input;  
    which = (which + 1 == IPTOSBUFFERS ? 0 : which + 1);  
    printf("%d.%d.%d.%d", p[0], p[1], p[2], p[3]);   
	return output[which]; 	
}  

void getIP(pcap_if_t *d, char *ip_addr, char *ip_netmask) //获取IP和子网掩码赋值为ip_addr和ip_netmask
{   pcap_addr_t *a;//遍历所有的地址
	for (a = d->addresses; a; a = a->next) {
		switch (a->addr->sa_family) {
		case AF_INET:  //sa_family ：是2字节的地址家族，一般都是“AF_xxx”的形式。通常用的都是AF_INET。代表IPV4
			if (a->addr) 
			{   char *ipstr;
				printf("适配器信息:\nIP地址:");
			    ipstr=iptos(((struct sockaddr_in *) a->addr)->sin_addr.s_addr); 
				printf("\n");
				memcpy(ip_addr, ipstr, 16);
			}
			if (a->netmask) {
				char *netmaskstr;
				printf("网络掩码:");
				netmaskstr = iptos(((struct sockaddr_in *) a->netmask)->sin_addr.s_addr);
				printf("\n");
				memcpy(ip_netmask, netmaskstr, 16);
			}
		case AF_INET6:
			break;
		}
	}
}

int GetSelfMac(pcap_t *adhandle, const char *ip_addr, unsigned char *ip_mac) // 获取自己主机的MAC地址
{
	unsigned char sendbuf[42]; //arp包结构大小
	int i = -1;
	int res;
	EthernetHeader eh; //以太网帧头
	Arpheader ah;  //ARP帧头
	struct pcap_pkthdr * pkt_header; //数据包的头部
	const u_char * pkt_data;//数据包的内容
	memset(eh.DestMAC, 0xff, 6); //目的地址为全为广播地址
	memset(eh.SourMAC, 0x0f, 6);
	memset(ah.DestMacAdd, 0x0f, 6);
	memset(ah.SourceMacAdd, 0x00, 6);	
	eh.EthType = htons(ETH_ARP);//htons将一个无符号短整型的主机数值转换为网络字节顺序
	ah.HardwareType= htons(ARP_HARDWARE);
	ah.ProtocolType = htons(ETH_IP);
	ah.HardwareAddLen = 6;
	ah.ProtocolAddLen = 4;
	ah.SourceIpAdd = inet_addr("100.100.100.100"); //随便设的请求方ip
	ah.OperationField = htons(ARP_REQUEST);//ARP请求报文
	ah.DestIpAdd = inet_addr(LOCALIP);//将一个点分十进制的IP转换成一个长整数型数
	memset(sendbuf, 0, sizeof(sendbuf));
	memcpy(sendbuf, &eh, sizeof(eh));
	memcpy(sendbuf + sizeof(eh), &ah, sizeof(ah));	
	if (pcap_sendpacket(adhandle, sendbuf, 42) == 0) {
		printf("\n正在获取MAC地址。。。。\n");
	} else {
		printf("获取失败！ ");
		return 0;
	}
	//从interface或离线记录文件获取一个报文
	 while ((res = pcap_next_ex(adhandle, &pkt_header, &pkt_data)) >= 0) 
	 {
		if (*(unsigned short *) (pkt_data + 12) == htons(ETH_ARP)
				&& *(unsigned short*) (pkt_data + 20) == htons(ARP_REPLY)
				&& *(unsigned long*) (pkt_data + 38)
						== inet_addr("100.100.100.100")) {
			for (i = 0; i < 6; i++) {
				ip_mac[i] = *(unsigned char *) (pkt_data + 22 + i);
			} 
			printf("获取自己主机的MAC地址成功!\n");
			printf("MAC地址:%02x-%02x-%02x-%02x-%02x-%02x\n", ip_mac[0], ip_mac[1], ip_mac[2],
			ip_mac[3], ip_mac[4], ip_mac[5]);
			break;
		}
	}
	if (i == 6) {
		return 1;
	} else {
		return 0;
	}
   
}

/* 分析截留的数据包获取活动的主机MAC地址 */
DWORD WINAPI GetLivePC(pcap_t *adhandle,int j)
{
	unsigned char Mac[6];
	struct pcap_pkthdr * pkt_header;
	const u_char * pkt_data;
	pcap_next_ex(adhandle, &pkt_header, &pkt_data);//从interface或离线记录文件获取一个报文
    ArpPacket *recv = (ArpPacket *) pkt_data;
	if (*(unsigned short *) (pkt_data + 20) == htons(ARP_REPLY))
			{
					printf("-------------------------------------------\n");
					printf("IP地址:%d.%d.%d.%d   MAC地址:",
						     recv->ah.SourceIpAdd & 255,
							 recv->ah.SourceIpAdd >> 8 & 255,
							 recv->ah.SourceIpAdd >> 16 & 255,
							 recv->ah.SourceIpAdd >> 24 & 255);
					for (int i = 0; i < 6; i++) 
					{
						Mac[i] = *(unsigned char *) (pkt_data + 22 + i);
						printf("%02x", Mac[i]);
					}
					printf("\n");
					j++;
			}  		
		Sleep(10);
	return 0;
}

DWORD WINAPI SendArpPacket(pcap_t *adhandle,char *ip,unsigned char *mac,char *netmask)
{
	unsigned char sendbuf[42]; 
	//arp包结构大小
	EthernetHeader eh;
	Arpheader ah;
	//帧头部
	memset(eh.DestMAC, 0xff, 6);      
	//目的地址为全为广播地址
	memcpy(eh.SourMAC, mac, 6);  
	//源地址是本机的MAC地址	
	eh.EthType = htons(ETH_ARP);  
    //ARP头部
	ah.HardwareType = htons(ARP_HARDWARE);
	//0001表示以太网的地址
	ah.ProtocolType = htons(ETH_IP);
	//协议类型字段表示要映射的协议地址类型值为x0800表示IP地址
    ah.HardwareAddLen = 6;
	//硬件地址长度
	ah.ProtocolAddLen = 4;
	//协议地址长度
    ah.OperationField = htons(ARP_REQUEST);
	//0001为ARP请求报文
	memcpy(ah.SourceMacAdd, mac, 6);    
	//源MAC地址
    ah.SourceIpAdd = inet_addr(LOCALIP); 
	//请求方的IP地址为自身的IP地址
	memset(ah.DestMacAdd, 0x00, 6);   
	//目标MAC地址全0
	//目的IP，向局域网内广播发送arp包
	unsigned long myip = inet_addr(LOCALIP);
	unsigned long mynetmask = inet_addr(LOCALMASK);
	unsigned long hisip = htonl((myip & mynetmask));
	printf("正在发送ARP请求报文。。。。\n");
	for (int i = 0; i < HOSTNUM; i++) {//向HOSTNUM个主机发送
		ah.DestIpAdd = htonl(hisip + i);
		memset(sendbuf, 0, sizeof(sendbuf));
		memcpy(sendbuf, &eh, sizeof(eh));
		memcpy(sendbuf + sizeof(eh), &ah, sizeof(ah));	
		//如果发送成功
		if (pcap_sendpacket(adhandle, sendbuf, 42) == 0) {
		} else {
			printf("PacketSendPacket in getmine Error: %d\n", GetLastError());
		}
		Sleep(50);
	}
	printf("发送成功!");
	Sleep(1000);
	printf("\n解析收到的ARP回应报文。。。\n");
	return 0;
}



int main()
{
	char *ip_addr;//IP地址  
	char *ip_netmask;//子网掩码  
	unsigned char *ip_mac;//本机MAC地址  
	pcap_if_t  * alldevs;//所有网络适配器
	pcap_if_t  *d;//选中的网络适配器
	char errbuf[PCAP_ERRBUF_SIZE];//错误缓冲区,大小为256
	pcap_t *adhandle;//捕捉实例,是pcap_open返回的对象
	int i = 0;//适配器计数变量
    ip_addr = (char *) malloc(sizeof(char) * 16);  
    if (ip_addr == NULL)  
    {   printf("申请内存存放IP地址失败!\n");  
        return -1;  
    }  
    ip_netmask = (char *) malloc(sizeof(char) * 16); 
    if (ip_netmask == NULL)  
    {   printf("申请内存存放NETMASK地址失败!\n");  
        return -1;  
    }  
    ip_mac = (unsigned char *) malloc(sizeof(unsigned char) * 6);  
    if (ip_mac == NULL)  
    {  
        printf("申请内存存放MAC地址失败!\n");  
        return -1;  
    }  
	if(pcap_findalldevs_ex(PCAP_SRC_IF_STRING,NULL,&alldevs,errbuf) == -1)//获取本地适配器列表
	{
		//结果为-1代表出现获取适配器列表失败
		fprintf(stderr,"Error in pcap_findalldevs_ex:\n",errbuf);
		//exit(0)代表正常退出,exit(other)为非正常退出,这个值会传给操作系统
		exit(1);	
	}
	for(d = alldevs;d !=NULL;d = d->next)
	{
		printf("-----------------------------------------------------------------\nnumber:%d\nname:%s\n",++i,d->name);
		if(d->description){	//打印适配器的描述信息
        printf("description:%s\n",d->description);
		}else{
			printf("description:%s","no description\n");
		}
		
		 /**
		 pcap_addr结构如下
		 pcap_addr *  next     指向下一个地址的指针
		 sockaddr *  addr       IP地址
		 sockaddr *  netmask  子网掩码
		 sockaddr *  broadaddr   广播地址
		 sockaddr *  dstaddr        目的地址
		 */
		 pcap_addr_t *a; //网络适配器的地址用来存储变量
		 for(a = d->addresses;a;a = a->next)
		 {    switch (a->addr->sa_family)//sa_family代表了地址的类型,是IPV4地址类型还是IPV6地址类型
		 {
				 case AF_INET:  //代表IPV4类型地址
					 printf("Address Family Name:AF_INET\n");
					 if(a->addr){
						 //->的优先级等同于括号,高于强制类型转换,因为addr为sockaddr类型，对其进行操作须转换为sockaddr_in类型
						 printf("Address:");
						 iptos(((struct sockaddr_in *)a->addr)->sin_addr.s_addr);
						 printf("\n");
					 }
					if (a->netmask){
						printf("Netmask:");
						printf("%s\n",iptos(((struct sockaddr_in *)a->netmask)->sin_addr.s_addr));
					}
					if (a->broadaddr){
						printf("Broadcast Address:"); 
						printf("%s\n",iptos(((struct sockaddr_in *)a->broadaddr)->sin_addr.s_addr));
					 }
					 if (a->dstaddr){
						   printf("\tDestination Address: %s\n",iptos(((struct sockaddr_in *)a->dstaddr)->sin_addr.s_addr));
					 }
        			 break;
				 case AF_INET6: //代表IPV6类型地址
					 printf("Address Family Name:AF_INET6\n");
					 printf("this is an IPV6 address\n");
					 break;
				 default:
					 break;
			 }
		 }
	}
	if(i == 0)//i为0代表上述循环未进入,即没有找到适配器
	{
		printf("interface not found,please check winpcap installation");
	}

	int num;
	printf("Enter the interface number(1-%d):",i);
	//让用户选择选择哪个适配器进行抓包
	scanf("%d",&num);
	printf("\n");

	//用户输入的数字超出合理范围
	if(num<1||num>i){
		printf("number out of range\n");
		pcap_freealldevs(alldevs);
		return -1;
	}
	//跳转到选中的适配器
	for(d=alldevs, i=0; i< num-1 ; d=d->next, i++);

	//运行到此处说明用户的输入是合法的
	if((adhandle = pcap_open(d->name,		//设备名称
														65535,       //存放数据包的内容长度
														PCAP_OPENFLAG_PROMISCUOUS,  //混杂模式
														1000,           //超时时间
														NULL,          //远程验证
														errbuf         //错误缓冲
														)) == NULL){
        //打开适配器失败,打印错误并释放适配器列表
		fprintf(stderr,"\nUnable to open the adapter. %s is not supported by WinPcap\n", d->name);
        // 释放设备列表 
        pcap_freealldevs(alldevs);
        return -1;
	}
  getIP(d, ip_addr, ip_netmask); //获取所选网卡的基本信息--掩码--IP地址  
  GetSelfMac(adhandle, ip_addr, ip_mac);  //获取本地主机的MAC地址  
  char *spip =LOCALIP;
  unsigned char *spmac = ip_mac;
  char *spnetmask =LOCALMASK;
  SendArpPacket(adhandle, spip,spmac,spnetmask);//广播发送ARP报文
  int j=100;
  while (j>0)
 {
	GetLivePC(adhandle,j);
	 j--;
 }
}
