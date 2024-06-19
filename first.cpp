#include "first.h"
#include "ui_first.h"
#include <QInputDialog>
first::first(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Form)
{

    ui->setupUi(this);
    this->setWindowTitle("五子棋");
    qreal a = 95;
    //setWindowFlags(Qt::FramelessWindowHint);
    this->setWindowOpacity(a/100);
    QPalette palette(this->palette());
    //this->setFixedSize(400,1.41*400);
    palette.setColor(QPalette::Background, QColor(0x1A334D));
    t = 0;
    this->setPalette(palette);
    w.setMainUi(this);
    //this->setFixedSize(400,1.41*400);

}
first::~first()
{
    delete ui;
}


void first::on_pushButton_clicked()
{
    close();
}

void first::on_pushButton_3_clicked()
{

    this->hide();
    w.time_limit = t;
    w.turn_time = clock();
    w.show();
}

void first::on_pushButton_2_clicked()
{
    bool ok;
    int i = QInputDialog::getInt(this, "时间设置", "请输入每一步的时间限制(0~180s)，0为不限时", 0, 0, 180, 1, &ok);
    if(ok){
        t = i;
    }
}
