/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   main.c
 * Author: Mr Mahaitao
 *
 * Created on March 7, 2018, 2:23 AM
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <errno.h>
#include <sys/types.h>
#define PORT 8888

/*
 * 
 */
int main(int argc, char** argv) {
    int sockfd;
    int i = 0;
    int z;
    char buf[80], strl[80];
    struct sockaddr_in adr_srvr;
    FILE *fp;

    printf("打开文件......\n");
    /*以只读的方式打开liu文件*/
    fp = fopen("liu.txt", "r");
    if (fp == NULL) {
        perror("打开文件失败 ");
        exit(1);
    }

    printf("连接服务器...\n");
    /*建立IP地址*/
    adr_srvr.sin_family = AF_INET;
    adr_srvr.sin_addr.s_addr = htonl(INADDR_ANY);
    adr_srvr.sin_port = PORT;
    bzero(&(adr_srvr.sin_zero), 8);
    sockfd = socket(AF_INET, SOCK_DGRAM, 0);
    if (sockfd == -1) {
        perror("socket 失败");
        exit(1);
    }
    printf("发送文件....\n");
    /*读取三行数据，传给udpserver*/
    for (i = 0; i < 3; i++) {
        fgets(strl, 80, fp);
        printf("%d:%s", i, strl);
        sprintf(buf, "%d:%s", i, strl);
        z = sendto(sockfd, buf, sizeof (buf), 0, (struct sockaddr*) &adr_srvr, sizeof (adr_srvr));
        if (z < 0) {
            perror("sendto 失败");
            exit(1);
        }
    }
    printf("发送....\n");
    sprintf(buf, "stop\n");
    z = sendto(sockfd, buf, sizeof (buf), 0, (struct sockaddr*) &adr_srvr, sizeof (adr_srvr));
    if (z < 0) {
        perror("sendto \"stop\" 失败");
        exit(1);
    }

    fclose(fp);
    close(sockfd);
    exit(0);



    return (EXIT_SUCCESS);
}

