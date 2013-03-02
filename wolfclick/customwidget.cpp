#include "customwidget.h"

#include <QWidget>
#include <QAction>
#include <QApplication>
#include <QTime>
#include <QPainter>


CustomWidget::CustomWidget(QWidget *parent)
    : QWidget(parent,
              Qt::FramelessWindowHint |
              Qt::WindowSystemMenuHint |
              Qt::WindowDoesNotAcceptFocus |
              Qt::WindowTransparentForInput |
              Qt::WindowStaysOnTopHint )
{
    // |
//    QTimer *timer = new QTimer(this);
//    connect(timer, SIGNAL(timeout()), this, SLOT(update()));
//    timer->start(1000);
//    setAttribute(Qt::WA_TransparentForMouseEvents);
    setAttribute( Qt::WA_TranslucentBackground );
}

void CustomWidget::paintEvent(QPaintEvent *)
{
    QColor hourColor(127, 0, 127, 20);
    QPainter painter(this);
    painter.setBackground(QColor(50,12,0,34));
    painter.setBackgroundMode( Qt::TransparentMode );
    painter.setRenderHint(QPainter::Antialiasing);
    painter.setPen(Qt::NoPen);
    painter.setBrush(hourColor);
    painter.fillRect(0, 0, 100, 100, hourColor);

}

void CustomWidget::resizeEvent(QResizeEvent * /* event */)
{
    QRegion maskedRegion(rect());
    setMask(maskedRegion);
}

QSize CustomWidget::sizeHint() const
{
    return QSize(100, 100);
}

