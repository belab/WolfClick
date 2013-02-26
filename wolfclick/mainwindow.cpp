#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <tchar.h>
#include <iostream>

#include <string>

#include <QtCore/qt_windows.h>


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    this->setWindowTitle("WolfClick");
//    setWindowFlags(Qt::WindowStaysOnTopHint);
    ui->setupUi(this);
//    connect( &Hooks::getInstance(), SIGNAL( mouseClicked(int, int) ), this, SLOT(onMouseClicked(int,int) ), Qt::QueuedConnection );
    std::cout << "Hello world" << std::endl;
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::onMouseClicked(int x, int y)
{
    ui->label->setText( QString( "[%1,%2]").arg(x).arg(y) );
}

void MainWindow::on_pushButton_clicked()
{
    std::wcout << L"Hello world" << std::endl;
}

#ifndef GET_X_LPARAM
#define GET_X_LPARAM(lp) ((int)(short)LOWORD(lp))
#endif
#ifndef GET_Y_LPARAM
#define GET_Y_LPARAM(lp) ((int)(short)HIWORD(lp))
#endif

bool MainWindow::nativeEvent(const QByteArray &eventType, void *message, long *result)
{
    MSG* pMessage = (MSG*)message;

    if( pMessage->message ==  WM_USER+123 )
    {
        POINT p;
        //pMessage->hwnd
        p.x = GET_X_LPARAM(pMessage->lParam);
        p.y = GET_Y_LPARAM(pMessage->lParam);
        onMouseClicked( p.x, p.y );
        std::cout << "got message" << std::endl;
//        DrawColor( p, hwnd );
    }
    else
    {
        return QWidget::nativeEvent(eventType, message, result);
    }

    return true;
}
