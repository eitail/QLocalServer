#ifndef SERVER_H
#define SERVER_H

#include <QObject>
#include <QLocalServer>
#include <QLocalSocket>

class Server : public QObject
{
    Q_OBJECT
public:
    explicit Server(QObject *parent = nullptr);
    ~Server();

private:
    QLocalServer *      m_pServer;
    QLocalSocket *      m_pSocket;
    QString             m_LocalTag;

public:

private:
    bool writeInfoToUi(QString infors);

signals:

public slots:
    void onNewConnection();
    void onConnectionDisconnected();
    void onReadyRead();

};

#endif // SERVER_H
