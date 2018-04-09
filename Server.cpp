#include "Server.h"

Server::Server(QObject *parent) : QObject(parent)
{
    m_pServer = NULL;
    m_pSocket = NULL;
    m_LocalTag = "87654321";

    m_pServer = new QLocalServer(this);

    if( !m_pServer->listen(m_LocalTag)){
        m_pServer->close();
        m_pServer->deleteLater();
        //先移出socket name
        m_pServer->removeServer(m_LocalTag);
        //后删除指针重新实例化
        delete m_pServer;
        m_pServer = new QLocalServer(this);

        if( !m_pServer->listen(m_LocalTag)){
          qDebug() << m_pServer->errorString();
        }
        else
        {
            qDebug() << " The server has been initialized. !!! 2 " << m_pServer->serverName();
        }
    }
    else
    {
        qDebug() << " The server has been initialized. !!! 1 " << m_pServer->serverName();
    }
    connect(m_pServer,SIGNAL(newConnection()), this,SLOT(onNewConnection()));

}

Server::~Server()
{
    if(m_pServer != NULL){
        m_pServer->close();
        m_pServer->deleteLater();
        m_pServer->removeServer(m_LocalTag);
        delete m_pServer;
        m_pServer = NULL;
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


