#include "property.h"


Properties * getNewDataStruct(){
     Properties * property = new Properties();
     return property;
}


Properties * setDataInStruct(Properties * property, const QString &SenderName, const QString &ReceiverName, const quint8 &idSender, const quint8 &idReceiver){
    property->clientName = SenderName;
    property->matricule = idSender;

    property->ReceiverName=ReceiverName;
    property->statusReceiver=idReceiver;

    return property;
}

Properties *SendInfo(Properties *property, const QString &SenderName, const QString &idSender){
    property->clientName = SenderName;
    property->matricule = idSender;
    return property;

}
