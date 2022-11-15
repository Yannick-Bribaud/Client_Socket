#ifndef CLIENTGUI_H
#define CLIENTGUI_H

#include <QWidget>
#include <QTcpSocket>
#include "client.h"
#include "property.h"
#include "data.h"


QT_BEGIN_NAMESPACE
namespace Ui { class ClientGui; }
QT_END_NAMESPACE

class ClientGui : public QWidget
{
    Q_OBJECT

public:
    ClientGui(QWidget *parent = nullptr);
    ~ClientGui();

private slots:
    void connecte();
    void deconnecte();
    void donneesRecues();
    void on_connexionBtn_clicked();
    void on_Envoyer_clicked();
    void properties(QTcpSocket * client, Properties & properties);
    void handlerError(QAbstractSocket::SocketError erreur);

private:
    Ui::ClientGui *ui;

    quint16 tailleMessage;
    QTcpSocket * client;
    QVariant container;
    Properties property;
    Data *data;
};
#endif // CLIENTGUI_H
