#ifndef WELCOME_H
#define WELCOME_H
#include <QMainWindow>
#include <QMouseEvent>
#include <QPushButton>
#include"mainwindow.h"
#include "ui_first.h"
namespace Ui {
class Form;
}

class first : public QMainWindow
{
    Q_OBJECT

public:
    explicit first(QWidget *parent = nullptr);
    ~first();



private slots:
    void on_pushButton_clicked();

    void on_pushButton_3_clicked();

    void on_pushButton_2_clicked();

private:
    int t;
    Ui::Form *ui;

MainWindow w;
};
#endif // WELCOME_H
