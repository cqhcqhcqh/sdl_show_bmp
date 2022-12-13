#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "showthread.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);


}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_startPlayButton_clicked()
{
#ifdef Q_OS_MAC
    ShowThread::showYuv();
#else
    ShowThread *thread = new ShowThread();
    thread->start();
#endif

}

