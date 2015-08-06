/*Class that provides user interface*/

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QLabel>
#include "robotvision.h"
#include "Source.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    RobotVision robot;	 
	QThread *thread;
    Worker *worker;

    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
	//void servershow();


signals:
    //void SigUpdateTransmissionWindow(QLabel *l, Mat m);
	void SigUpdateTransmissionWindow();

	public slots:
			void onProgressChagned();

private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

    void on_pushButton_3_clicked();

    void on_horizontalSlider_valueChanged(int value);
	
    void on_horizontalSlider_2_valueChanged(int value);

    void on_pushButton_4_clicked();

    void on_pushButton_7_clicked();

    void on_lineEdit_editingFinished();

    void on_lineEdit_2_editingFinished();

    void on_mesuredWidthSlider_valueChanged(int value);

    void on_StartButton_clicked();

    void on_pushButton_5_clicked();



private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
