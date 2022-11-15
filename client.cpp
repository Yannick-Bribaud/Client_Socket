#include "client.h"

Client::Client(QObject * parent) : QTcpSocket(parent){
     this->setObjectName("Client 1");

}
