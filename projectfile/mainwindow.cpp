#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include "number.h"
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{

    setWindowFlags(Qt::FramelessWindowHint);
    setAttribute(Qt::WA_TranslucentBackground, true);
    ui->setupUi(this);
    QWidget *contentWidget = new QWidget();
    contentWidget->setObjectName("contentWidget");
    contentWidget->setStyleSheet("#contentWidget{background: rgb(32, 32, 32); border-radius: 16px;}");
    Number *Vide = new Number(contentWidget, this);//新建子界面
    Vide->show();//子界面出现
    setVisible(false);

}

MainWindow::~MainWindow()
{
    delete ui;
}
