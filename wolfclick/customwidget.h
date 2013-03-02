#pragma once

#include <QWidget>

class CustomWidget : public QWidget
{
    Q_OBJECT

public:
    CustomWidget(QWidget *parent = 0);
    QSize sizeHint() const;

protected:
    void paintEvent(QPaintEvent *event);
    void resizeEvent(QResizeEvent *event);

private:
    QPoint dragPosition;
};

