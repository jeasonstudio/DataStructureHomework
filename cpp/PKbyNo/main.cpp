#include <vector>
#include <string>
#include <fstream>
#include <iostream>
using namespace std;
#define MAXSIZE 1024
int buffer[MAXSIZE*2];
typedef struct rnode{
    int n;
    struct rnode* next;
}rnode,*rlink;

rlink CreatRing(int m){
    int i;
    rlink head = NULL,tail = NULL;
    for(i = 1;i <= m;i++){
        if(i == 1)
            head = tail = (rlink)malloc(sizeof(rnode));
        else{
            tail -> next = (rlink)malloc(sizeof(rnode));
            tail = tail -> next;
        }
        tail -> n = i;
        tail -> next = NULL;
    }
    tail -> next = head;
    return head;
}

rlink Delete(rlink s){
    rlink p = s;
    while(p ->next != s)
        p = p -> next;
    p -> next = s -> next;
    free(s);
    return p -> next;
}

void ReadFile(string infilename){

    ifstream infile(infilename);
    int i = 0;
    if(!infile.is_open())
        cout<<"fail to open the file"<<endl;
    while(!infile.eof()){
        infile>>buffer[i];
        cout<<buffer[i++]<<endl;
    }
    infile.close();
}

void WriteFile(string outfilename,int* p,int m){
    int i;
    ofstream outfile(outfilename,ios::app);
    if(!outfile.is_open())
        cout<<"fail to open the file"<<endl;
    for(i = 0;i < m;i++)
        outfile<<p[i]<<' ';
    outfile<<endl;
}

void PKbyNo(string outfilename,rlink p,int m,int n){
    int i,j;
    int buff[m];
    for(i = 0;i < m;i++){
        for(j = 1;j < n;j++)
            p = p -> next;
        buff[i] = p -> n;
        p = Delete(p);
    }
    WriteFile(outfilename, buff,m);
}
int main(int argc, const char * argv[]) {
    string infilename = "./in.txt";
    string outfilename = "./out.txt";
    ReadFile(infilename);
    int m = 3,n = 2,i = 0;
    rlink head;
    while(i < MAXSIZE){
        if(i % 2 == 0)
            m = buffer[i];
        else {
            n = buffer[i];
            head = CreatRing(m);
            PKbyNo(outfilename,head,m,n);
        }
        i++;
    }
    return 0;
}

