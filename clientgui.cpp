#include "clientgui.h"
#include "ui_clientgui.h"
#include <QMessageBox>

ClientGui::ClientGui(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::ClientGui)
{
    ui->setupUi(this);

    qRegisterMetaTypeStreamOperators<Properties>("Properties");
    qRegisterMetaTypeStreamOperators<Data>("Data");

    client = new Client(this);
    this->tailleMessage=0;

    connect(client, SIGNAL(readyRead()),this, SLOT(donneesRecues()));
    connect(client,SIGNAL(connected()),this, SLOT(connecte()));
    connect(ui->DeconnectBtn,SIGNAL(clicked()),this,SLOT(deconnecte()));

    connect(client, SIGNAL(error(QAbstractSocket::SocketError)), this,
    SLOT(handlerError(QAbstractSocket::SocketError)));

}

ClientGui::~ClientGui(){
    delete ui;
}

void ClientGui::connecte(){
    ui->ReponseMsg->append("Connexion reussi");
    properties(client,property);
}

void ClientGui::deconnecte(){
    ui->ReponseMsg->append("vous etes deconnecté");
    client->abort();
}

void ClientGui::donneesRecues(){

    QDataStream in(client);
    if(tailleMessage==0){
        if(client->bytesAvailable() <(int)sizeof(quint16)){
            return;
        }
    in >> tailleMessage;
    }
    if(client->bytesAvailable() < tailleMessage)
        return;

    QString messageRecu;
    in >> messageRecu;
    ui->ReponseMsg->append(messageRecu);
    tailleMessage=0;
}


void ClientGui::on_connexionBtn_clicked(){
    client->abort();
    client->connectToHost(ui->IPServeur->text(), ui->port->value());
}


void ClientGui::on_Envoyer_clicked(){

        QByteArray paquet; data = getNewData();
        QDataStream out(&paquet,QIODevice::WriteOnly);
        QString message= tr("<strong>")+ui->pseudo->text()+tr("</strong> : ")+ui->msg->text();

        data->message=message;
        data->sender=ui->pseudo->text();
        data->receiver=ui->Destinateur->text();
        container=QVariant::fromValue(*data);

        out <<(quint16)0;
        out <<(quint8)('M');
        out << container;
        out.device()->seek(0);
        out << (quint16) (paquet.size() - sizeof (quint16));
        client->write(paquet);
        ui->msg->clear();
        ui->msg->setFocus();
}


void ClientGui::properties(QTcpSocket * client, Properties &properties)
{
   QByteArray DataOnClient;   QVariant props;
   QDataStream out(&DataOnClient, QIODevice::WriteOnly);

    properties.clientName=ui->pseudo->text();
    properties.ReceiverName=ui->Destinateur->text();
    properties.statusReceiver='E';
    properties.matricule='E';
    properties.dateConnexion=QDate::currentDate();
    props=QVariant::fromValue(properties);

    out<<quint16(0)<<(quint8)('P')<<props;
    out.device()->seek(0);
    out <<quint16(DataOnClient.size() - sizeof(quint16));

    client->write(DataOnClient);

}

void ClientGui::handlerError(QAbstractSocket::SocketError erreur){

    switch (erreur) {
    case QAbstractSocket::HostNotFoundError: QMessageBox::critical(this,"ERREUR","le serveur n'a pas pu être trouvé.Vérifiez l'IP et le port");
        break;
    case QAbstractSocket::ConnectionRefusedError: QMessageBox::critical(this,"ERREUR","le serveur a refusé la connexion,veuillez redemarrer le programme ou serveur");
        break;
    case QAbstractSocket::RemoteHostClosedError: QMessageBox::critical(this,"ERREUR","le serveur a coupé la connexion");
        break;
    default:
        QMessageBox::critical(this,"ERREUR",client->errorString());
    }
}

