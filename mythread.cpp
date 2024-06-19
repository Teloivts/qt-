#include "mythread.h"
#include <QDebug>
#include"mynet.h"
#include<time.h>
int sharedData = 0;
int locking = 0;
MyThread::MyThread(QString get_ip,int T)
{
    ip = get_ip;
    model = T;
}
void MyThread::die(){
    qDebug()<<"die";
    exit(0);
}
void MyThread::matching(){
    locking = 1;
    char mes[100]={0};
    char temp[10]={0};
    qDebug()<<"begin";
    //127.0.0.1
    //81.68.213.251
    net_send s("81.68.213.251", 8000);
    s.put("name");
    s.get(mes);
    qDebug()<<mes;
    while(1){
        qDebug()<<"test";
        //locking = 1;
        net_send s("81.68.213.251", 8000);
        temp[0]=mes[0];temp[1]='a';temp[2]='a';temp[3]='a';
        s.put(temp);
        s.get(temp);
        if(sharedData>>10){
            qDebug()<<"kill";
            sharedData = 0;
            locking = 0;
            break;
        }
        if(temp[0]=='a'){
            continue;
        }
        if(temp[0]=='b'){
            sharedData = 0;
            sharedData += 1<<9;
            sharedData += (temp[2]-'a')<<4;
            sharedData += (temp[3]-'a');
            qDebug()<<temp[2];
            if((temp[2]-'a')==0xf&&(temp[3]-'a')==0xf){
                locking= 0;
                break;
                qDebug()<<"???";
            }
        }
        if(temp[0]=='c'){

            if(locking == 2){
                qDebug()<<"send!";
                temp[0]=mes[0];temp[1]='c';temp[2]='a'+(sharedData>>4);temp[3]='a'+(sharedData&0xf);
                s.put(temp);
                if(temp[2]==0xf&&temp[3]==0xf){
                    break;
                }
                locking = 1;
            }
            else{
                s.put("aaaa");
            }
            locking= 0;

        }
        Sleep(5);

    }

    qDebug()<<"end";
}
void MyThread::server(){

    net_recv recv(8000);
    string tem = recv.get();
    char temp[10]={0};
    qDebug()<<QString::fromStdString(tem);
    if(tem=="start")
    while(1){
        qDebug()<<"test";
        locking = 0;
        while(1){
            if(locking == 0){
                qDebug()<<"0";
            }
            Sleep(50);
            if(locking == 2){
                qDebug()<<"recv";
                sharedData &= 0xff;
                temp[0]='a'+(sharedData>>4);temp[1]='a'+(sharedData&0xf);
                break;
            }
        }
        locking = 1;
        qDebug()<<"try";
        recv.put(temp);
        tem = recv.get();
        qDebug()<<QString::fromStdString(tem);
        sharedData = 0;
        sharedData += (tem[0]-'a')<<4;
        sharedData += (tem[1]-'a');
        sharedData += 1<<9;
    }
}
void MyThread::client(){
    char temp[10]={0};
    string tem;
    net_send send(ip.toStdString(),8000);
    send.put("start");
    while(1){
        tem = send.get();
        qDebug()<<QString::fromStdString(tem);
        sharedData = 0;
        sharedData += (tem[0]-'a')<<4;
        sharedData += (tem[1]-'a');
        sharedData += 1<<9;
        locking = 0;
        while(1){
            Sleep(50);
            if(locking == 2){
                qDebug()<<"recv";
                sharedData &= 0xff;
                temp[0]='a'+(sharedData>>4);temp[1]='a'+(sharedData&0xf);
                break;
            }
        }
        locking = 1;
        send.put(temp);
    }
}
void MyThread::run()
{
    if(model==1)
        matching();
    if(model==2)
        server();
    if(model==3)
        client();
    qDebug()<<"结束";
}
