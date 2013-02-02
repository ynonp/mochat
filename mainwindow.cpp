#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "messagereceiver.h"

using namespace mongo;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

   m_conn.connect("ds031957.mongolab.com:31957");
   std::string err;
   m_conn.auth("demo", "ynon", "123456", err);

    QObject::connect( ui->btnSend, SIGNAL(clicked()),
                       this, SLOT(addMessage()) );
    QObject::connect( ui->edtMessage, SIGNAL(editingFinished()),
                      this, SLOT(addMessage()));

    MessageReceiver *r = new MessageReceiver();

    QObject::connect(r, SIGNAL(newMessage(QString)),
                     this, SLOT(gotNewMessage(QString)));
    r->start();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::addMessage()
{
    QString text = ui->edtMessage->text();
    m_conn.insert("demo.chat",
                  BSONObjBuilder().
                  append("text", text.toStdString()).
                  obj() );
    ui->edtMessage->clear();
}

void MainWindow::gotNewMessage(const QString &text)
{
    ui->lstChat->addItem(text);
}
