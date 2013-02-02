#include "messagereceiver.h"
using namespace mongo;

void MessageReceiver::run()
{
    mongo::DBClientConnection conn;
    conn.connect("ds031957.mongolab.com:31957");
    std::string err;
    conn.auth("demo", "ynon", "123456", err);

    tail( conn, "demo.chat" );
}

void MessageReceiver::tail(DBClientBase& conn, const char *ns) {

    BSONElement lastValue = minKey.firstElement();

    Query query = Query().hint( BSON( "$natural" << 1 ) );

    while ( 1 ) {
        auto_ptr<DBClientCursor> c =
            conn.query(ns, query, 0, 0, 0,
                       QueryOption_CursorTailable | QueryOption_AwaitData );

        while ( 1 ) {
            if ( !c->more() ) {

                if ( c->isDead() ) {
                    break;
                }

                continue;
            }

            BSONObj o = c->next();
            lastValue = o["insertDate"];
            cout << o.toString() << endl;
            emit newMessage(o.getStringField("text") );
        }

        query = QUERY( "insertDate" << GT << lastValue ).hint( BSON( "$natural" << 1 ) );
    }
}
