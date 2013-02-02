#ifndef MESSAGERECEIVER_H
#define MESSAGERECEIVER_H

#include <QObject>
#include <QThread>
#include <mongo/client/dbclient.h>

class MessageReceiver : public QThread
{
    Q_OBJECT

protected:
    void run();

private:
    void tail(mongo::DBClientBase& conn, const char *ns);

signals:
    void newMessage(const QString &text);

public slots:
    
};

#endif // MESSAGERECEIVER_H
