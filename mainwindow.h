/*Class that provides user interface*/

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

//#include <QMainWindow>
#include <QtWidgets/QMainWindow>
//#include <QtGui>
//#include <QtGui>
#include "robotvision.h"


namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    RobotVision robot;

    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void sessionOpened();
    void readFortune();
    void requestNewFortune();

    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

    void on_pushButton_3_clicked();

    void on_horizontalSlider_valueChanged(int value);

    void on_pushButton_4_clicked();

    void on_pushButton_7_clicked();

    void on_lineEdit_editingFinished();

    void on_lineEdit_2_editingFinished();

    void on_mesuredWidthSlider_valueChanged(int value);

    void on_StartButton_clicked();

    void on_pushButton_5_clicked();

    void on_getFortuneButton_clicked();

private:
    Ui::MainWindow *ui;

    QTcpSocket *tcpSocket;
    QImage currentImage;
    QString currentFortune;
    quint32 blockSize;

    QNetworkSession *networkSession;
};

#endif // MAINWINDOW_H
