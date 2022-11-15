#ifndef CLIENT_H
#define CLIENT_H

#include <QTcpSocket>
#include "property.h"


class Client : public QTcpSocket
{
public:
    explicit Client(QObject *parent);

private:
    QTcpSocket * clients;

};

#endif // CLIENT_H
