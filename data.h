#ifndef DATA_H
#define DATA_H
#include <QString>
#include <QMetaType>

typedef struct data{

  QString sender;
  QString message;
  QString receiver;

      friend QDataStream &operator<<(QDataStream & out, const data & data){
          out << data.sender;
          out << data.message;
          out << data.receiver;
          return  out;
      }

      friend QDataStream &operator>>(QDataStream & in, data & data){
          in >> data.sender;
          in >> data.message;
          in >> data.receiver;
          return  in;
      }

} Data;

Q_DECLARE_METATYPE(Data);

Data * getNewData();

#endif // DATA_H
