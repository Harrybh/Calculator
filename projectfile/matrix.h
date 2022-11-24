#ifndef MATRIX_H
#define MATRIX_H

#include <QDialog>
#include <QMouseEvent>
#include <windows.h>        //注意头文件
#include <windowsx.h>
#include <QSystemTrayIcon>
#include <QGraphicsDropShadowEffect>
#include <QGridLayout>

namespace Ui {
class Matrix;
}

class Matrix : public QDialog
{
    Q_OBJECT

public:
    explicit Matrix(QWidget *contentWidget, QWidget *parent = nullptr);
    ~Matrix();

private slots:
    void on_pushButton_clicked();
    void on_activatedSysTrayIcon(QSystemTrayIcon::ActivationReason reason);

    void on_smallButton_clicked();

    void on_closeButton_clicked();

    void on_gaussButton_clicked();

signals:
    void sendsignal();

private:
    Ui::Matrix *ui;
protected:
    void mousePressEvent(QMouseEvent *e);
    void mouseMoveEvent(QMouseEvent *e);
private:
    int boundaryWidth;
    QPoint clickPos;
    QSystemTrayIcon *mSysTrayIcon;
};

#endif // MATRIX_H
