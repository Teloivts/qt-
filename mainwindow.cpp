#include "mainwindow.h"
#include "ui_mainwindow.h"
 #include <QMouseEvent>
#include <QColorDialog>
#include <QDialog>
#include <QColor>
#include <QRgb>
#include <QMessageBox>
#include <QFileDialog>
#include <QFontDialog>
#include <QDebug>
#include <QInputDialog>
#include <QMessageBox>
#include <QProgressDialog>
#include <QErrorMessage>
#include <QCoreApplication>
#include <QWizard>
#include <qpainter.h>
#include <QPainter>
#include <QColor>
#include <QFont>
#include<WINSOCK2.H>
#include<iostream>
#include<cstring>
#include<string.h>
#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<windows.h>
#include<QMouseEvent>
#include<time.h>
#include <QMainWindow>
#include"mynet.h"
using namespace std;
double len = 600;
QPoint P;
QPoint Get_Point(int x){
    QPoint orgPoint = P;
    double temp=0,temp_x=0,temp_y=0;
    if(orgPoint.x()<0.08*len){
        orgPoint.setX(0.08*len);
    }
    if(orgPoint.x()>0.92*len){
        orgPoint.setX(0.92*len);
    }
    if(orgPoint.y()>1.04*len){
        orgPoint.setY(1.04*len);
    }
    if(orgPoint.y()<0.2*len){
        orgPoint.setY(0.2*len);
    }
    if(orgPoint.x()-0.08*len-int((orgPoint.x()-0.08*len)/(0.9*len/15))*(0.9*len/15)<0.03*len)
        temp_x=int((orgPoint.x()-0.08*len)/(0.9*len/15));
    else
        temp_x=int((orgPoint.x()-0.08*len)/(0.9*len/15)+1);
    if(orgPoint.y()-0.2*len-int((orgPoint.y()-0.2*len)/(0.9*len/15))*(0.9*len/15)<0.03*len)
        temp_y=int((orgPoint.y()-0.2*len)/(0.9*len/15));
    else
        temp_y=int((orgPoint.y()-0.2*len)/(0.9*len/15)+1);
    orgPoint=QPoint(temp_x*(0.9*len/15)+0.08*len,temp_y*(0.9*len/15)+0.2*len);
    if(x==1)
        return orgPoint;
    if(x==2)
        return QPoint(temp_x,temp_y);
}
void MainWindow::ai(){
    int person_chess = 0;
    int ai_chess = 0;
    int null_chess = 0;
    int value[15][15];
    for(int a=0;a<15;a++)
        for(int b=0;b<15;b++){
            value[a][b]=0;
        }
    for(int a=0;a<15;a++){
        for(int b=0;b<15;b++){//遍历棋盘
            if(board[a][b]==0){//只考虑能下的点
                for(int c=-1;c<=1;c++){
                    for(int d=-1;d<=1;d++){//遍历8个方向
                        person_chess = ai_chess = null_chess = 0;
                        if(!(c==0&&d==0)){//落点本身不算方向
                            for(int e=1;e<=4;e++){
                                if(a+e*c>=0&&a+e*c<15&&b+e*d>=0&&b+e*d<15&&board[a+e*c][b+e*d]==-T){
                                    person_chess++;
                                }
                                else if(a+e*c>=0&&a+e*c<15&&b+e*d>=0&&b+e*d<15&&board[a+e*c][b+e*d]==0){
                                    null_chess++;
                                    break;
                                }
                                else{
                                    break;
                                }
                            }
                            for(int e=1;e<=4;e++){
                                if(a-e*c>=0&&a-e*c<15&&b-e*d>=0&&b-e*d<15&&board[a-e*c][b-e*d]==-T){
                                    person_chess++;
                                }
                                else if(a-e*c>=0&&a-e*c<15&&b-e*d>=0&&b-e*d<15&&board[a+e*c][b+e*d]==0){
                                    null_chess++;
                                    break;
                                }
                                else{
                                    break;
                                }
                            }
                            if(person_chess == 1){                 //杀2
                                qDebug()<<"person";
                                value[a][b]+=10;
                            }else if(person_chess == 2){           //杀3
                                if(null_chess == 1)
                                    value[a][b]+=30;
                                else if(null_chess == 2)
                                    value[a][b]+=40;
                            }else if(person_chess == 3){           //杀4
                                //量变空位不一样，优先級不一样
                                if(null_chess == 1)
                                    value[a][b]+=60;
                                else if(null_chess == 2)
                                    value[a][b]+=110;
                            }else if(person_chess == 4){           //杀5
                                value[a][b]+=10100;
                            }

                            //进行一次清空
                            null_chess = 0;
                            for(int e=1;e<=4;e++){
                                if(a+e*c>=0&&a+e*c<15&&b+e*d>=0&&b+e*d<15&&board[a+e*c][b+e*d]==T){
                                    ai_chess++;
                                }
                                else if(a+e*c>=0&&a+e*c<15&&b+e*d>=0&&b+e*d<15&&board[a+e*c][b+e*d]==0){
                                    null_chess++;
                                    break;
                                }
                                else{
                                    break;
                                }
                            }
                            for(int e=1;e<=4;e++){
                                if(a-e*c>=0&&a-e*c<15&&b-e*d>=0&&b-e*d<15&&board[a-e*c][b-e*d]==T){
                                    ai_chess++;
                                }
                                else if(a-e*c>=0&&a-e*c<15&&b-e*d>=0&&b-e*d<15&&board[a-e*c][b-e*d]==0){
                                    null_chess++;
                                    break;
                                }
                                else{
                                    break;
                                }
                            }
                            if(ai_chess == 0){
                                value[a][b]+=5;  //活1
                            }else if(ai_chess == 1){
                                value[a][b]+=10; //活2
                            }else if(ai_chess == 2){         //活3
                                if(null_chess == 1)
                                    value[a][b]+=25;
                                else if(null_chess == 2)
                                    value[a][b]+=50;
                            }else if(ai_chess == 3){         //活4
                                if(null_chess == 1)
                                    value[a][b]+=55;
                                else if(null_chess == 2)
                                    value[a][b]+=100;
                            }else if(ai_chess >= 4){         //活5
                                value[a][b]+=20000;
                            }
                        }
                    }
                }
            }
        }
    }
    int choose_x[300],choose_y[300],choose;
    int head=0;
    int max_value = 0;
    for(int a=0;a<15;a++){
        for(int b=0;b<15;b++){
            if(value[a][b]>max_value){
                max_value = value[a][b];
                head = 0;
                choose_x[head] = a;
                choose_y[head] = b;
                head++;
            }
            if(value[a][b]==max_value){
                choose_x[head] = a;
                choose_y[head] = b;
                head++;
            }
        }
    }
    srand(clock());
    choose = rand()%head;
    board[choose_x[choose]][choose_y[choose]] = T;
    T = -T;

}
void MainWindow::setMainUi(QWidget *parent)
{
    par = parent;
}
void MainWindow::check(){
    int A=0,B=0,C=0,D=0;
    for(int a=0;a<15;a++){
        for(int b=0;b<15;b++){
                if(board[a][b]==1||board[a][b]==-1){
                    for(int c=0;c<5;c++){
                        A += board[a+c][b+c];
                        B += board[a][b+c];
                        C += board[a+c][b];
                    }
                if(b>=4){
                    for(int c=0;c<5;c++){
                        D += board[a+c][b-c];
                    }
                }
                if(A==board[a][b]*5||B==board[a][b]*5||C==board[a][b]*5||D==board[a][b]*5){
                    if(board[a][b]*5==-5){
                        if(!end){
                            end = 1;//改变end值的位置不对会出错
                            QMessageBox::information(this,"info", "黑方胜，游戏结束");
                            if(t!=0){
                                sharedData = 1<<10;
                                model = 1;
                                //t ->quit();//退出线程请求
                                //t ->wait();
                            }
                        }

                    }
                    else{
                        if(!end){
                            end = 1;//改变end值的位置不对会出错
                            QMessageBox::information(this,"info", "白方胜，游戏结束");
                            if(t!=0){
                                sharedData = 1<<10;
                                model = 1;
                                //t ->quit();//退出线程请求
                                //t ->wait();
                            }
                        }

                    }
                    //return board[a][b]*5;
                }
                A=B=C=D=0;
            }
        }
    }
//    if(check()==-5){
//        if(!end){
//            QMessageBox::information(this,"info", "黑方胜，游戏结束");
//            end = 1;
//            qDebug()<<"test";
//        }

//    }
//    if(check()==5){
//        if(!end){
//            QMessageBox::information(this,"info", "白方胜，游戏结束");
//            end = 1;
//        }
//    }
//    return 0;
}
void MainWindow::prog_start(int x)
{
    if(time_limit>0){
        time_limit = 0;
    }
    if(t!=0){
        sharedData = 1<<10;
        Sleep(200);
//        t ->quit();//退出线程请求
//        t ->wait();
//        t->~MyThread();
        sharedData = 0;
        t = 0;
    }
    t=new MyThread(ip,x);
    t->start();
    //sleep(20);
}
void MainWindow::paintEvent(QPaintEvent *event){
    if(sharedData>>9==1){
        int temp_x,temp_y;
        sharedData -= 1<<9;
        temp_x = sharedData&0xf;
        temp_y = sharedData>>4;
        if(temp_x==15&&temp_y==15){
            on_pushButton_clicked();

        }
        else if(board[temp_x][temp_y]==0){
            board[temp_x][temp_y]=T;
            record_x[head]=temp_x;
            record_y[head]=temp_y;
            head++;
            T = -T;
        }
        sharedData = 0;
    }
    QPainter painter(this);
    QPen pen ;
    orgPoint = P;
    double temp=0,temp_x=0,temp_y=0;
    pen.setWidth(2);//改变线宽
    pen.setColor(QColor(255,255,255));
    painter.setPen(pen);
    for(int a=0;a<15;a++){//画棋盘
        temp = 0.9*len*a/15;
        painter.drawLine(QPoint(0.08*len, 0.2*len+temp), QPoint(0.92*len, 0.2*len+temp));
        painter.drawLine(QPoint(0.08*len+temp, 0.2*len), QPoint(0.08*len+temp, 0.2*len+0.84*len));
    }
    if(orgPoint.y()>0.13*len){//画瞄准框
        orgPoint=Get_Point(1);
        pen.setWidth(4);//改变线宽
        pen.setColor(QColor(255,0,0));
        painter.setPen(pen);
        painter.drawLine(QPoint(orgPoint.x()+0.02*len,orgPoint.y()+0.02*len), QPoint(orgPoint.x()+0.02*len,orgPoint.y()+0.01*len));
        painter.drawLine(QPoint(orgPoint.x()+0.02*len,orgPoint.y()+0.02*len), QPoint(orgPoint.x()+0.01*len,orgPoint.y()+0.02*len));
        painter.drawLine(QPoint(orgPoint.x()-0.02*len,orgPoint.y()-0.02*len), QPoint(orgPoint.x()-0.02*len,orgPoint.y()-0.01*len));
        painter.drawLine(QPoint(orgPoint.x()-0.02*len,orgPoint.y()-0.02*len), QPoint(orgPoint.x()-0.01*len,orgPoint.y()-0.02*len));
        painter.drawLine(QPoint(orgPoint.x()+0.02*len,orgPoint.y()-0.02*len), QPoint(orgPoint.x()+0.02*len,orgPoint.y()-0.01*len));
        painter.drawLine(QPoint(orgPoint.x()+0.02*len,orgPoint.y()-0.02*len), QPoint(orgPoint.x()+0.01*len,orgPoint.y()-0.02*len));
        painter.drawLine(QPoint(orgPoint.x()-0.02*len,orgPoint.y()+0.02*len), QPoint(orgPoint.x()-0.02*len,orgPoint.y()+0.01*len));
        painter.drawLine(QPoint(orgPoint.x()-0.02*len,orgPoint.y()+0.02*len), QPoint(orgPoint.x()-0.01*len,orgPoint.y()+0.02*len));
        //setCursor(Qt::BlankCursor);   //隐藏鼠标
    }
    for(int a=0;a<15;a++){//画棋子
        for(int b=0;b<15;b++){
            if(board[a][b]!=0){
                pen.setWidth(4);//改变线宽
                painter.setPen(pen);
                temp_x = 0.9*len*a/15;
                temp_y = 0.9*len*b/15;
                if(board[a][b]==-1){
                    pen.setColor(QColor(0,0,0));
                    QBrush brush(QColor(0,0,0));
                    painter.setBrush(brush);
                }
                if(board[a][b]==1){
                    pen.setColor(QColor(255,255,255));
                    QBrush brush(QColor(0xFF,0xFF,0xFF));
                    painter.setBrush(brush);
                }

                painter.setPen(pen);
                QPainterPath path;
                path.addEllipse(0.08*len+temp_x-0.025*len,0.2*len+temp_y-0.025*len,0.05*len,0.05*len);

                painter.drawPath(path);
            }
        }
    }
    pen.setWidth(4);//改变线宽
    QBrush brush;
    QPainterPath path;
    QColor color;
    if(T==-1){
        painter.setBrush(QBrush(Qt::NoBrush));
        pen.setColor(QColor(0,0,0));
        painter.setPen(pen);
        path.addRect(0.6*len,0.1*len,0.3*len,0.05*len);
        painter.drawPath(path);
        painter.setBrush(QBrush(QColor(0,0,0)));

    }
    else{
        painter.setBrush(QBrush(Qt::NoBrush));
        pen.setColor(QColor(0xFF,0xFF,0xFF));
        painter.setPen(pen);
        path.addRect(0.6*len,0.1*len,0.3*len,0.05*len);
        painter.drawPath(path);
        painter.setBrush(QBrush(QColor(0xFF,0xFF,0xFF)));
    }
    path = QPainterPath();
    if(!end){
        record_time = clock();
        if(time_limit>0){
            if((time_limit-(clock()-turn_time)/1000.0)>0){
                path.addRect(0.6*len,0.1*len,(time_limit-(record_time-turn_time)/1000.0)/time_limit*0.3*len,0.05*len);
            }
            else{
                on_pushButton_clicked();
            }
        }
        else{
            path.addRect(0.6*len,0.1*len,0.3*len,0.05*len);
        }
    }
    painter.drawPath(path);
        //setCursor(Qt::ArrowCursor);  //显示正常鼠标
    painter.end();
    //painter.drawLine(orgPoint, QPoint(0.5*len, 0.1*len));
    //棋盘长度为
    if(!end){

        check();
    }
    update();
}
void MainWindow::message(){
    reset();
    record_x[head]=0-record_x[head];
    //QMessageBox::information(this,"info", "信息");
}
void MainWindow::on_MainWindow_customContextMenuRequested(const QPoint &pos){
 //直接触发窗口的close函数
    /* 在鼠标右键处显示菜单 */
    pMenu->exec(cursor().pos());
    record_x[head]=0-record_x[head];
    /* 释放内存 */


}
void MainWindow::reset(){
    qDebug()<<"reset";
    if(t!=0){
        sharedData = 1<<10;
        model = 1;
    }
    locking = 0;
    for(int a=0;a<15;a++)
        for(int b=0;b<15;b++)
            board[a][b]=0;
    T = -1;
    end = 0;
    turn_time = clock();
}
void MainWindow::re(){
    if(end){
        QMessageBox::information(this,"info", "游戏结束，无法悔棋");
        return;
    }
    if(model==2){
        QMessageBox::information(this,"info", "联网对战禁止悔棋");
        return;
    }

    if(head>0){

        head--;
        board[record_x[head]][record_y[head]]=0;
        record_x[head]=-1;
        T=-T;
    }
}
MainWindow::MainWindow(QWidget *parent): QMainWindow(parent), ui(new Ui::MainWindow){
    ip = "81.68.213.251";
    time_limit = 0;
    turn_time = 0;
    t = NULL;
    for(int a=0;a<1000;a++){
        record_x[a] = record_y[a] = 0;
    }
    head=0;
    for(int a=0;a<25;a++)
        for(int b=0;b<25;b++)
            board[a][b]=0;
    b_text="黑子";
    T = -1;
    model = 1;
    end = 0;
    this->setContextMenuPolicy(Qt::CustomContextMenu);

    //this->setStyleSheet("QMenuBar{background-color:rgb(200,200,200);}");
    ui->setupUi(this);
    this->ui->menu->menuAction()->setVisible(false);//去掉“关于”
    this->setWindowTitle("五子棋");
    this->setMouseTracking(true);
    this->setFixedSize(len,1.1*len);//调整窗口大小
    //resize(900,900);
    qreal a = 95;
    //setWindowFlags(Qt::FramelessWindowHint);
    this->setWindowOpacity(a/100);
    QPalette palette(this->palette());//半透明效果

    palette.setColor(QPalette::Background, QColor(0x1A334D));//棋盘背景颜色

    this->setPalette(palette);

    pMenu = new QMenu(this);
    QAction *mes = new QAction(tr("重新开始"), this);
    QAction *redo = new QAction(tr("悔棋"), this);
    QAction *quit = new QAction(tr("退出"), this);
    /* 添加菜单项 */
    pMenu->addAction(mes);
    pMenu->addAction(redo);
    pMenu->addAction(quit);

    /* 连接槽函数 */
    connect(this,&MainWindow::Sig_check,this,&MainWindow::check);
    connect(mes, SIGNAL(triggered()), this, SLOT(message()));
    connect(redo, SIGNAL(triggered()), this, SLOT(re()));
    connect(quit, SIGNAL(triggered()), this, SLOT(close()));
    //this->setAttribute(Qt::WA_TranslucentBackground,true);
    //this->setAttribute(Qt::WA_TranslucentBackground,true);

}
MainWindow::~MainWindow(){
    delete ui;
    QList<QAction*> list = pMenu->actions();//释放内存
    foreach (QAction* pAction, list) delete pAction;
    delete pMenu;
}
void MainWindow::mousePressEvent(QMouseEvent *event){
    if(model==1){
        qDebug()<<"1";
    }
    if(model==2){
        qDebug()<<"2";
    }
    if(model==3){
        qDebug()<<"3";
    }
    if(model==4){
        qDebug()<<"4";
    }
    if(end)
        return;
    if(record_x[head]==-1){
        record_x[head]=0;
    }
    else
        if(event->button()==Qt::LeftButton&&P.y()>0.13*len&&!locking){
            QPoint orgPoint = Get_Point(2);
            int temp_x=orgPoint.x(),temp_y=orgPoint.y();
            if(board[temp_x][temp_y]==0){
                board[temp_x][temp_y]=T;
                record_x[head]=temp_x;
                record_y[head]=temp_y;
                head++;
                T = -T;
                turn_time = clock();
                if(model==2||model==4){
                    sharedData = (record_y[head-1]<<4)+(record_x[head-1]);

                    locking = 2;
                    qDebug()<<"2";
                }
                if(model==3){
                    check();
                    if(!end)
                        ai();
                }
            }

        }
}
void MainWindow::mouseMoveEvent(QMouseEvent *event){

    P.setX(event->x());
    P.setY(event->y());


}
void MainWindow::on_pushButton_clicked(){


        if(!end){
            end = 1;//改变end值的位置不对会出错
            if(t!=NULL){
                sharedData = 0;
                sharedData += 0xff;
                locking = 2;
                Sleep(200);//500
                sharedData = 1<<10;
                Sleep(50);
                //t ->quit();//退出线程请求
                //t ->wait();
                model = 1;
            }
            if(T==-1){
                QMessageBox::information(this,"info", "白方胜，游戏结束");
            }
            else{
                QMessageBox::information(this,"info", "黑方胜，游戏结束");
            }

        }


}
void MainWindow::on_action_1_triggered(){
    reset();
    model = 1;
}
void MainWindow::on_action_2_triggered()
{
    if(model!=2){
//        re();
        reset();
        model = 2;
        prog_start();
    }

}
void MainWindow::on_action_3_triggered(){
    reset();
    model = 3;
}
void MainWindow::on_action_4_triggered(){
    if(model!=4){
        reset();
        model = 4;
        bool ok;
        QString get_ip = QInputDialog::getText(this, "用户名", "请输入目标ip（输入0.0.0.0代表被动监听）", QLineEdit::Normal, "0.0.0.0", &ok);
        if(ok){
            QRegExp regExpIp("((2[0-4]\\d|25[0-5]|[01]?\\d\\d?)\\.){3}(2[0-4]\\d|25[0-5]|[01]?\\d\\d?)");
            if (!regExpIp.exactMatch(get_ip)) {
                QMessageBox::information(this, "提示", "ip格式错误");
                return;
            }
            if(get_ip=="0.0.0.0"){
                prog_start(2);
            }
            else{
                ip = get_ip;
                prog_start(3);
            }
        }



    }
}
void MainWindow::on_action_5_triggered()
{
    bool ok;
    int i = QInputDialog::getInt(this, "时间设置", "请输入每一步的时间限制，0为不限时", 0, 0, 200, 1, &ok);
    if(ok){
        time_limit = i;
        turn_time = clock();
    }

}

