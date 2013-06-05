#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "customwidget.h"

#include <QtCore/qt_windows.h>
#include <QTimer>
#include <QTreeWidgetItem>
#include <QPixmap>
#include <QScreen>
#include <QGuiApplication>

#include <iostream>

// LeftClick function
void LeftClick()
{
  INPUT    Input={0};
  // left down
  Input.type      = INPUT_MOUSE;
  Input.mi.dwFlags  = MOUSEEVENTF_LEFTDOWN;
  ::SendInput(1,&Input,sizeof(INPUT));

  // left up
  ::ZeroMemory(&Input,sizeof(INPUT));
  Input.type      = INPUT_MOUSE;
  Input.mi.dwFlags  = MOUSEEVENTF_LEFTUP;
  ::SendInput(1,&Input,sizeof(INPUT));
}
// MouseMove function
void MouseMove(int x, int y )
{
    double fScreenWidth    = ::GetSystemMetrics( SM_CXSCREEN )-1;
    double fScreenHeight  = ::GetSystemMetrics( SM_CYSCREEN )-1;
    double fx = x*(65535.0f/fScreenWidth);
    double fy = y*(65535.0f/fScreenHeight);
    INPUT  Input={0};
    Input.type      = INPUT_MOUSE;
    Input.mi.dwFlags  = MOUSEEVENTF_MOVE|MOUSEEVENTF_ABSOLUTE;
    Input.mi.dx = fx;
    Input.mi.dy = fy;
    ::SendInput(1,&Input,sizeof(INPUT));
}

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent, Qt::WindowStaysOnTopHint),
    ui(new Ui::MainWindow),
    m_timer(new QTimer(parent)),
    m_isRecording(false),
    m_isPlaying(false),
    m_mouseFrameIndex(0)
{
    ui->setupUi(this);
    w = new CustomWidget;
    w->show();
    connect( m_timer, &QTimer::timeout, this, &MainWindow::onTimerTimeout );
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::onMouseClicked(int x, int y)
{
    ui->statusBar->showMessage(QString( "[%1,%2]").arg(x).arg(y) );
    w->move( x-w->width()/2, y-w->height()/2 );
    if( isRecording() )
    {
        addMouseClick(x, y);
    }
}

void MainWindow::on_pushButton_clicked()
{
    std::cout << "clicked dummy" << std::endl;
}

void MainWindow::on_actionQuit_triggered()
{
    qApp->quit();
}

void MainWindow::on_actionRecord_toggled(bool on)
{
    if( on )
    {
        ui->treeWidget->clear();
    }
    else
    {
        int itemCount = ui->treeWidget->topLevelItemCount();
        if( itemCount > 0 )
        {
            delete ui->treeWidget->topLevelItem( itemCount-1 );
        }
    }
    m_isRecording = on;
}

void MainWindow::on_actionPlay_toggled(bool on)
{
    m_isPlaying = on;
    if( m_isPlaying )
    {
        m_mouseFrameIndex = 0;
        m_timer->start(3000);
    }
    else
    {
        m_timer->stop();
        m_mouseFrameIndex = 0;
    }
}

void MainWindow::on_actionStop_triggered()
{
    ui->actionPlay->setChecked(false);
    ui->actionRecord->setChecked(false);
}

void MainWindow::on_actionClear_triggered()
{
    ui->treeWidget->clear();
}

void MainWindow::onTimerTimeout()
{
    if( m_mouseFrameIndex < ui->treeWidget->topLevelItemCount() )
    {
        const QVariant& v =
                ui->treeWidget->topLevelItem(m_mouseFrameIndex++)->data(0, Qt::UserRole);
        const MouseFrame& frame = v.value<MouseFrame>();
        w->move( frame.pos.x()-w->width()/2, frame.pos.y()-w->height()/2 );
        MouseMove( frame.pos.x(), frame.pos.y() );
        LeftClick();
    }
    if( m_mouseFrameIndex >= ui->treeWidget->topLevelItemCount() )
    {
        on_actionStop_triggered();
    }
}

void MainWindow::closeEvent(QCloseEvent*)
{
    on_actionQuit_triggered();
}

bool MainWindow::nativeEvent(const QByteArray &eventType, void *message, long *result)
{
    MSG* pMessage = (MSG*)message;
    if( pMessage->message ==  WM_USER+123 )
    {
        int x = (int)(short)LOWORD(pMessage->lParam);
        int y = (int)(short)HIWORD(pMessage->lParam);
        onMouseClicked( x, y );
        return true;
    }
    return QWidget::nativeEvent(eventType, message, result);
}

bool MainWindow::isRecording()
{
    return m_isRecording;
}

bool MainWindow::isPlaying()
{
    return m_isPlaying;
}

void MainWindow::addMouseClick(int x, int y)
{
    QScreen* screen = QGuiApplication::primaryScreen();
    QPixmap pixmap = screen->grabWindow(0, x, y, 10, 10);
    QTreeWidgetItem* item = new QTreeWidgetItem(ui->treeWidget);
    item->setData(0, Qt::DecorationRole, pixmap	);
    item->setText(1, QString("[%1,%2]").arg(x).arg(y));
    item->setData(0, Qt::UserRole, QVariant::fromValue(MouseFrame(x,y)));
}

void MainWindow::stop()
{
    m_isRecording = false;
    m_isPlaying = false;
}
