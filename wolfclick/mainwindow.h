#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

namespace Ui {
class MainWindow;
}
class QBytreArray;

class MainWindow : public QMainWindow
{
    Q_OBJECT
    
public:
    explicit MainWindow(QWidget *parent = 0);
    virtual ~MainWindow();
    
public slots:
    void onMouseClicked( int x, int y );
    void on_pushButton_clicked();
private:
    virtual bool nativeEvent(const QByteArray &eventType, void *message, long *result);
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
