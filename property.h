#ifndef PROPERTY_H
#define PROPERTY_H
#include <QString>
#include <QMetaType>
#include <QDate>

typedef struct properties
{
    QDate dateConnexion;
    QString clientName;
    QString matricule;
    QString ReceiverName;
    QString statusReceiver;
    QDate dateDeconnexion;

    friend QDataStream &operator<<(QDataStream & out, const properties & properties){
        out << properties.dateConnexion;
        out << properties.clientName;
        out << properties.ReceiverName;
        out << properties.matricule;
        out << properties.statusReceiver;
        out << properties.dateDeconnexion;
        return  out;
    }

    friend QDataStream &operator>>(QDataStream & in, properties & properties){
        in >> properties.dateConnexion;
        in >> properties.clientName;
        in >> properties.ReceiverName;
        in >> properties.matricule;
        in >> properties.statusReceiver;
        in >> properties.dateDeconnexion;
        return  in;
    }

}Properties;

Q_DECLARE_METATYPE (Properties)

Properties * getNewDataStruct();
Properties * setDataInStruct(Properties * dataOfSocket,const QString & SenderName, const QString &ReceiverName,
                                         const QString & idSender, const QString & idReceiver);
Properties * SendInfo(Properties * dataOfSocket,const QString & SenderName, const QString & idSender);


#endif // PROPERTY_H
