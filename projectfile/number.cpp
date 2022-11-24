#include "number.h"
#include "qtextcursor.h"
#include "ui_number.h"
#include "matrix.h"

void Number::mousePressEvent(QMouseEvent *e)
{
    if(e->button()==Qt::LeftButton)
        clickPos=e->pos();
}
void Number::mouseMoveEvent(QMouseEvent *e)
{
    if(e->buttons()&Qt::LeftButton  //左键点击并且移动
            )
    {
        move(e->pos()+pos()-clickPos);  //移动窗口
    }
}
Number::Number(QWidget *contentWidget, QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::Number)
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

Number::~Number()
{
    delete ui;
}


void Number::on_cosButton_clicked()
{
    QString QStr="cos()";
    ui->textEdit->insertPlainText(QStr);
}


void Number::on_sinButton_clicked()
{
    QString QStr="sin()";
    ui->textEdit->insertPlainText(QStr);
}


void Number::on_divButton_clicked()
{
    QString QStr="/";
    ui->textEdit->insertPlainText(QStr);
}


void Number::on_eButton_clicked()
{
    QString QStr="e";
    ui->textEdit->insertPlainText(QStr);
}


void Number::on_factorButton_clicked()
{
    QString QStr="!";
    ui->textEdit->insertPlainText(QStr);
}


void Number::on_eightButton_clicked()
{
    QString QStr="8";
    ui->textEdit->insertPlainText(QStr);
}


void Number::on_fiveButton_clicked()
{
    QString QStr="5";
    ui->textEdit->insertPlainText(QStr);
}

void Number::on_oneButton_clicked()
{
    QString QStr="1";
    ui->textEdit->insertPlainText(QStr);
}

void Number::on_twoButton_clicked()
{
    QString QStr="2";
    ui->textEdit->insertPlainText(QStr);
}

void Number::on_threeButton_clicked()
{
    QString QStr="3";
    ui->textEdit->insertPlainText(QStr);
}

void Number::on_fourButton_clicked()
{
    QString QStr="4";
    ui->textEdit->insertPlainText(QStr);
}

void Number::on_sixButton_clicked()
{
    QString QStr="6";
    ui->textEdit->insertPlainText(QStr);
}

void Number::on_sevenButton_clicked()
{
    QString QStr="7";
    ui->textEdit->insertPlainText(QStr);
}

void Number::on_nineButton_clicked()
{
    QString QStr="9";
    ui->textEdit->insertPlainText(QStr);
}

void Number::on_zeroButton_clicked()
{
    QString QStr="0";
    ui->textEdit->insertPlainText(QStr);
}

void Number::on_leftButton_clicked()
{
    QString QStr="(";
    ui->textEdit->insertPlainText(QStr);
}


void Number::on_lnButton_clicked()
{
    QString QStr="ln()";
    ui->textEdit->insertPlainText(QStr);
}


void Number::on_logButton_clicked()
{
    QString QStr="log()()";
    ui->textEdit->insertPlainText(QStr);
}


void Number::on_minusButton_clicked()
{
    QString QStr="-";
    ui->textEdit->insertPlainText(QStr);
}


void Number::on_modButton_clicked()
{
    QString QStr="%";
    ui->textEdit->insertPlainText(QStr);
}


void Number::on_piButton_clicked()
{
    QString QStr="pi";
    ui->textEdit->insertPlainText(QStr);
}


void Number::on_plusButton_clicked()
{
    QString QStr="+";
    ui->textEdit->insertPlainText(QStr);
}


void Number::on_pointButton_clicked()
{
    QString QStr=".";
    ui->textEdit->insertPlainText(QStr);
}


void Number::on_powerButton_clicked()
{
    QString QStr="()^()";
    ui->textEdit->insertPlainText(QStr);
}


void Number::on_rightButton_clicked()
{
    QString QStr=")";
    ui->textEdit->insertPlainText(QStr);
}


void Number::on_sqrtButton_clicked()
{
    QString QStr="sqrt()()";
    ui->textEdit->insertPlainText(QStr);
}


void Number::on_timesButton_clicked()
{
    QString QStr="*";
    ui->textEdit->insertPlainText(QStr);
}


void Number::on_cleanButton_clicked()
{
    ui->textEdit->clear();
}


void Number::on_packspace_clicked()
{
    QTextCursor cursor = ui->textEdit->textCursor();
    cursor.movePosition(QTextCursor::End);
    cursor.deletePreviousChar();
    ui->textEdit->setTextCursor(cursor);
    ui->textEdit->show();
}


void Number::on_tanButton_clicked()
{
    QString QStr="tan()";
    ui->textEdit->insertPlainText(QStr);
}


void Number::on_lgButton_clicked()
{
    QString QStr="lg()";
    ui->textEdit->insertPlainText(QStr);
}


void Number::on_absButton_clicked()
{
    QString QStr="abs()";
    ui->textEdit->insertPlainText(QStr);
}


void Number::on_closeButton_clicked()
{
    QApplication::exit();
}


void Number::on_smallButton_clicked()
{
    this->hide();
    mSysTrayIcon->show();

}
void Number::on_activatedSysTrayIcon(QSystemTrayIcon::ActivationReason reason)
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

void Number::reshow(){
    this->show();
}

void Number::on_pushButton_clicked()
{
    QWidget *contentWidget = new QWidget();
    contentWidget->setObjectName("contentWidget");
    contentWidget->setStyleSheet("#contentWidget{background: rgb(32, 32, 32); border-radius: 8px;}");
    Matrix *videodlg = new Matrix(contentWidget, this);//新建子界面
    connect(videodlg,SIGNAL(sendsignal()),this,SLOT(reshow()));//当点击子界面时，调用主界面的reshow()函数
    videodlg->show();//子界面出现
    this->hide();//主界面关闭


}

void Number::on_filebutton_clicked()
{
    QString fileName = QFileDialog::getOpenFileName(this,"Open File",QDir::currentPath());
        //qDebug()<<"文件名是："<<fileName;
        if(fileName.isEmpty()){
            return;
        }
        QFile *file = new QFile;
        file->setFileName(fileName);
        bool openFileOk = file->open(QIODevice::ReadOnly);
        if(openFileOk){
            //文件与文本流相关联
            QTextStream in(file);
            ui->textEdit->setText(in.readAll());
            file->close();
            delete file;
        }else{
            return;
        }
}


void Number::on_saveButton_clicked()
{
    QString fileName = QFileDialog::getSaveFileName(this,"Save File",QDir::currentPath());
    QFile file(fileName);//创建文件对象
    bool tag = file.open(QIODevice::WriteOnly);//写内容到文件中
    if(!tag)
    {
        return;
    }
    QString text = ui->textEdit->toPlainText();//文本框中的内容
    file.write(text.toUtf8());//将text内容转化为字节数组
    file.close();
}

