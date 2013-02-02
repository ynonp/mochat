#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <mongo/client/dbclient.h>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT
    
public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();


private slots:
    void addMessage();
    void gotNewMessage(const QString &text);
private:
    Ui::MainWindow *ui;
    mongo::DBClientConnection m_conn;
};

#endif // MAINWINDOW_H
