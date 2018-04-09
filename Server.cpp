#include "Server.h"

Server::Server(QObject *parent) : QObject(parent)
{
    m_pServer = NULL;
    m_pSocket = NULL;
    m_LocalTag = "445566778899";

    m_pServer = new QLocalServer(this);
    if( m_pServer->isListening() ){
        m_pServer->close();
        m_pServer->deleteLater();
    }

    if( !m_pServer->listen(m_LocalTag)){
        m_pServer->close();
        m_pServer->deleteLater();
        delete m_pServer;
        m_pServer = new QLocalServer(this);
        if( !m_pServer->listen(m_LocalTag)){
          qDebug() << m_pServer->errorString();
        }
    }
    connect(m_pServer,SIGNAL(newConnection()), this,SLOT(onNewConnection()));
    qDebug() << " The server has been initialized. !!! ";
}

Server::~Server()
{
    if(m_pServer != NULL){
        m_pServer->close();
        m_pServer->deleteLater();
        delete m_pServer;
    }
}

//新的链接
void Server::onNewConnection()
{
    QLocalSocket *  socket = m_pServer->nextPendingConnection();//设置监听
    m_pSocket = socket;
    connect(socket, SIGNAL(readyRead()) ,this , SLOT(onReadyRead()));
    connect(socket, SIGNAL(disconnected()), this, SLOT(onConnectionDisconnected()));
}

void Server::onConnectionDisconnected()
{
    qDebug() << "client disconnect!";
}

//接受发送来的数据,并返回给ui界面
void Server::onReadyRead()
{
    QString msg = m_pSocket->readAll();
    qDebug() << msg;
    writeInfoToUi("AAA");
}

//发送给Form内容
bool Server::writeInfoToUi(QString infors)
{
   m_pSocket->write(infors.toUtf8());
   return true;
}


