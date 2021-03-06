#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <fcntl.h>
#include <linux/in.h>
#include <stdlib.h>
/**
广播服务器端代码
**/
#define IP_FOUND "client"
#define IP_FOUND_ACK "server"
#define PORT 9999
int main(int argc,char*argv[]){
    int ret=-1;
    int sock;
    struct sockaddr_in server_addr;//服务器端地址
    struct sockaddr_in from_addr;//客户端地址
    int from_len=sizeof(struct sockaddr_in);
    int count=-1;
    fd_set readfd;//读文件描述符集合
    char buffer[1024];
    struct timeval timeout;
    timeout.tv_sec=2;
    timeout.tv_usec=0;
    sock=socket(AF_INET,SOCK_DGRAM,0);//建立数据报套接字
    if(sock<0){
        perror("sock error");
        return;
    }

    memset((void*)&server_addr,0,sizeof(struct sockaddr_in));
    server_addr.sin_family=AF_INET;
    server_addr.sin_addr.s_addr=htons(INADDR_ANY);
    server_addr.sin_port=htons(PORT);
    //将地址结构绑定到套接字上./
    ret=bind(sock,(struct sockaddr*)&server_addr,sizeof(server_addr));
    if(ret<0){
        perror("bind error");
        return;
    }

    while(1){
        timeout.tv_sec=2;
        timeout.tv_usec=0;
        //文件描述符集合清0
        FD_ZERO(&readfd);
        //将套接字描述符加入到文件描述符集合
        FD_SET(sock,&readfd);
        //select侦听是否有数据到来
        ret=select(sock+1,&readfd,NULL,NULL,&timeout);//侦听是否可读
        printf("ret=%d\n",ret);
        switch(ret){
            case -1://发生错误
				printf("Error\n");
                break;
            case 0://超时
                printf("Timeout\n");
                break;
            default:
				printf("Receive msg... \n ");
                if(FD_ISSET(sock,&readfd)){
                    count = recvfrom(sock,buffer,1024,0, (struct sockaddr*)&from_addr,&from_len);//接收客户端发送的数据
                    printf("Receive : %s \n",buffer);
                    //from_addr保存客户端的地址结构
                    if(strstr(buffer,IP_FOUND)){
                        //响应客户端请求
                        //打印客户端的IP地址
                        printf("Client IP: %s\n",inet_ntoa(from_addr.sin_addr));
                        //打印客户端的端口号
                        printf("Client Port: %d\n",ntohs(from_addr.sin_port));
                        char *msg = "I am server";
                        memcpy(buffer,msg,strlen(msg)+1);

                        printf("Send client msg: %s\n", buffer);
                        count = sendto(sock, buffer, strlen(buffer), 0, (struct sockaddr*)&from_addr,from_len);
                        //将数据发送给客户端
                    }
                }
                break;
        }
    }//end while
    return;
}
