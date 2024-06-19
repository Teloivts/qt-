
#ifndef MYNET_H
#define MYNET_H

#include<WINSOCK2.H>
#include<iostream>
#include<cstring>
#include<string.h>
#include<QDebug>
using namespace std;
class net_send
{
protected:
    WSADATA data;
    SOCKET sclient;
    SOCKADDR_IN server;
public:
    net_send(string ser, int port)
    {
        WSAStartup(0x0202, &data);//创建套节字
        sclient = socket(AF_INET /* 使用 TCP/IP 协议簇 */, SOCK_STREAM, IPPROTO_TCP);
        memset(&server, 0, sizeof(server)); //初始化套节字

        server.sin_family = PF_INET; // 使用 TCP/IP 协议簇

        server.sin_port = htons(port); //服务器端口号
        server.sin_addr.s_addr = inet_addr(ser.c_str()); // 指向 客户端 的 IP 地址

        int connectf = -1;

        while (connectf == -1)
            connectf = connect(sclient, (struct sockaddr*)&server, sizeof(SOCKADDR_IN));
    }
    void put(const char* message){
        send(sclient, message, strlen(message), 0); // 发送
    }
    string get(){
        char message[1025];
        int len = recv(sclient, message, 1028 /* 缓冲区大小 */, 0);
        message[len] = 0;
        string temp(message);
        return message;
    }
    void get(char *mes){
        recv(sclient, mes, 1028 /* 缓冲区大小 */, 0);
    }
    ~net_send()
    {
        closesocket(sclient);  // 释放连接

        WSACleanup();
    }
};
class net_recv{
protected:

    int port = 5150; //端口号
    WSADATA data;
    SOCKADDR_IN server;
    SOCKADDR client;
    SOCKET slisten = socket(AF_INET /* 使用 TCP/IP 协议簇 */, SOCK_STREAM, IPPROTO_TCP);
    SOCKET sclient = accept(slisten, (struct sockaddr*)&client, &sizes); // 等待连接
    int sizes;
public:
    net_recv(int x)
    {
        port = x;
        WSAStartup(0x0202, &data);

        //创建套节字

        server.sin_family = AF_INET; // 使用 TCP/IP 协议簇

        server.sin_port = htons(port); //服务器端口号

        server.sin_addr.s_addr = htonl(INADDR_ANY); // 指向 客户端 的 IP 地址

        sizes = sizeof(SOCKADDR_IN);

        slisten = socket(AF_INET /* 使用 TCP/IP 协议簇 */, SOCK_STREAM, IPPROTO_TCP);

        bind(slisten, (struct sockaddr*)&server, sizeof(SOCKADDR_IN));

        listen(slisten, 1);
        sclient = accept(slisten, (struct sockaddr*)&client, &sizes); // 等待连接
    }
    string get()
    {
        char message[1025];
        int len = recv(sclient, message, 1024 /* 缓冲区大小 */, 0);
        message[len] = 0;
        string temp(message);
        return message;
    }
    void put(const char* message){
        send(sclient, message, strlen(message), 0); // 发送
    }
    ~net_recv()
    {
        closesocket(sclient);  // 释放连接
        WSACleanup();
    }
};

#endif // MYNET_H
