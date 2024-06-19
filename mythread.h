#ifndef MYTHREAD_H
#define MYTHREAD_H
#include <QThread>
extern int sharedData,locking ;

class MyThread:public QThread
{
public:
    MyThread(QString get_ip,int T);
public slots:
    void die();//开启子进程
protected:
    int data;
    int model;
    QString ip;
    void matching();
    void server();
    void client();
    void run();
};

#endif

