#include "matrix.h"
#include "ui_matrix.h"

void Matrix::mousePressEvent(QMouseEvent *e)
{
    if(e->button()==Qt::LeftButton)
        clickPos=e->pos();
}
void Matrix::mouseMoveEvent(QMouseEvent *e)
{
    if(e->buttons()&Qt::LeftButton  //左键点击并且移动
            )
    {
        move(e->pos()+pos()-clickPos);  //移动窗口
    }
}
Matrix::Matrix(QWidget *contentWidget, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Matrix)
{
    mSysTrayIcon = new QSystemTrayIcon(this);
        //新建托盘要显示的icon
    QIcon icon = QIcon(":/new/prefix1/calc.png");
        //将icon设到QSystemTrayIcon对象中
    mSysTrayIcon->setIcon(icon);
        //当鼠标移动到托盘上的图标时，会显示此处设置的内容
    mSysTrayIcon->setToolTip("calculate");

        //在系统托盘显示此对象
    connect(mSysTrayIcon,SIGNAL(activated(QSystemTrayIcon::ActivationReason)),this,SLOT(on_activatedSysTrayIcon(QSystemTrayIcon::ActivationReason)));

    setWindowFlags(Qt::Dialog | Qt::FramelessWindowHint);
    setAttribute(Qt::WA_TranslucentBackground, true);

    // 添加阴影
    QGraphicsDropShadowEffect *shadowEffect = new QGraphicsDropShadowEffect(contentWidget);
    shadowEffect->setColor(Qt::lightGray);
    shadowEffect->setBlurRadius(4); // 阴影的大小
    shadowEffect->setOffset(0, 0);
    contentWidget->setGraphicsEffect(shadowEffect);

    // 添加到窗口中
    QGridLayout *lo = new QGridLayout();
    lo->addWidget(contentWidget, 0, 0);
    lo->setContentsMargins(4, 4, 4, 4); // 注意和阴影大小的协调
    setLayout(lo);
    ui->setupUi(this);
}
Matrix::~Matrix()
{
    delete ui;
}
void Matrix::on_pushButton_clicked()
{
    emit sendsignal();
    this->close();
}
void Matrix::on_activatedSysTrayIcon(QSystemTrayIcon::ActivationReason reason)
{
    switch(reason){
    case QSystemTrayIcon::Trigger:
        //单击托盘图标
        break;
    case QSystemTrayIcon::DoubleClick:
        this->show();
        mSysTrayIcon->hide();
        break;
    default:
        break;
    }
}


void Matrix::on_smallButton_clicked()
{
    this->hide();
    mSysTrayIcon->show();
}


void Matrix::on_closeButton_clicked()
{
    QApplication::exit();
}


void Matrix::on_gaussButton_clicked()
{

}

