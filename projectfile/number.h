#ifndef NUMBER_H
#define NUMBER_H

#include <QDialog>
#include <QMainWindow>
#include <QFileDialog>
#include <QMessageBox>
#include <QMainWindow>
#include <QMouseEvent>
#include <windows.h>        //注意头文件
#include <windowsx.h>
#include <QSystemTrayIcon>
#include <QDebug>


namespace Ui {
class Number;
}

class Number : public QDialog
{
    Q_OBJECT

public:
    Number(QWidget *contentWidget, QWidget *parent = 0);
    ~Number();

private slots:

    void on_cosButton_clicked();

    void on_sinButton_clicked();

    void on_divButton_clicked();

    void on_eButton_clicked();

    void on_factorButton_clicked();

    void on_eightButton_clicked();

    void on_fiveButton_clicked();

    void on_oneButton_clicked();

    void on_twoButton_clicked();

    void on_threeButton_clicked();

    void on_fourButton_clicked();

    void on_sixButton_clicked();

    void on_sevenButton_clicked();

    void on_nineButton_clicked();

    void on_zeroButton_clicked();



    void on_leftButton_clicked();

    void on_lnButton_clicked();

    void on_logButton_clicked();

    void on_minusButton_clicked();

    void on_modButton_clicked();

    void on_piButton_clicked();

    void on_plusButton_clicked();

    void on_pointButton_clicked();

    void on_powerButton_clicked();

    void on_rightButton_clicked();

    void on_sqrtButton_clicked();

    void on_timesButton_clicked();

    void on_cleanButton_clicked();

    void on_packspace_clicked();

    void on_tanButton_clicked();

    void on_lgButton_clicked();

    void on_absButton_clicked();

    void on_closeButton_clicked();

    void on_smallButton_clicked();

    void on_activatedSysTrayIcon(QSystemTrayIcon::ActivationReason reason);

    void on_pushButton_clicked();

    void reshow();

    void on_filebutton_clicked();

    void on_saveButton_clicked();

private:
    Ui::Number *ui;
protected:
    void mousePressEvent(QMouseEvent *e);
    void mouseMoveEvent(QMouseEvent *e);
private:
    int boundaryWidth;
    QPoint clickPos;
    QSystemTrayIcon *mSysTrayIcon;
};

#endif // NUMBER_H
