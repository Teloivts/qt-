#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include"mythread.h"
QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    int turn_time;
    int time_limit;
    void setMainUi(QWidget *parent);
private:
    Ui::MainWindow *ui;
protected:
   // MyThread *t;
    QWidget *par;
    QMenu *pMenu;
    MyThread *t;
    QString ip;
    int T;//回合
    int model;//游戏模式
    int end;//游戏是否结束
    int start;
    int record_x[1000],record_y[1000],record_time;
    int head;

    int board[25][25];
    QString b_text="白子";
    void ai();
    void paintEvent(QPaintEvent *event);//绘制界面
    void mouseMoveEvent(QMouseEvent *event);//追踪鼠标
    void mousePressEvent(QMouseEvent *event);
    void check();
    void reset();
    QPoint point;
    QPoint orgPoint;
signals:
    void Sig_check();
private slots:
    void prog_start(int x=1);//开启子进程
    void on_pushButton_clicked();
    void on_MainWindow_customContextMenuRequested(const QPoint &pos);
    void message();
    void re();
    void on_action_1_triggered();
    void on_action_2_triggered();
    void on_action_3_triggered();
    void on_action_5_triggered();
    void on_action_4_triggered();
};
#endif // MAINWINDOW_H
