#include "helper.h"

// Qt lib import
#include <QDebug>
#include <QJsonObject>
#include <QJsonDocument>
#include <QDateTime>

Helper::Helper():
    server_( "JQSpeed", QWebSocketServer::NonSecureMode )
{
    connect( &server_, &QWebSocketServer::newConnection, this, &Helper::onNewConnection );
}

bool Helper::init()
{
    return server_.listen( QHostAddress::Any, 51888 );
}

void Helper::onNewConnection()
{
    auto socket = server_.nextPendingConnection();

    qDebug() << "new connection:" << socket;

    connect( socket, &QWebSocket::disconnected, this, std::bind( &Helper::onDisconnected, this, socket ) );
    connect( socket, &QWebSocket::textMessageReceived, this, std::bind( &Helper::onTextMessageReceived, this, socket, std::placeholders::_1 ) );
    connect( socket, &QWebSocket::binaryMessageReceived, this, std::bind( &Helper::onBinaryMessageReceived, this, socket, std::placeholders::_1 ) );
}

void Helper::onDisconnected(QWebSocket *socket)
{
    qDebug() << "disconnected:" << socket;

    socket->deleteLater();
}

void Helper::onTextMessageReceived(QWebSocket *socket, const QString &message)
{
    // qDebug() << "text message received:" << socket << message.size();

    auto requestData = QJsonDocument::fromJson( message.toUtf8() ).object();
    if ( requestData.isEmpty() ) { return; }

    const auto action = requestData.value( "action" ).toString();
    if ( action.isEmpty() ) { return; }

    if ( action == "ping" )
    {
        QJsonObject replyData;
        replyData[ "action" ]     = "ping";
        replyData[ "serverTime" ] = QString::number( QDateTime::currentMSecsSinceEpoch() );
        replyData[ "clientTime" ] = requestData.value( "clientTime" );

        socket->sendTextMessage( QJsonDocument( replyData ).toJson( QJsonDocument::Compact ) );
    }
    else if ( action == "downloadSpeedTest" )
    {
        const auto dataBlockSize = 4 * 1024 * 1024;
        const auto sendCount     = 32;

        // 生成空数据
        QByteArray data;
        data.resize( dataBlockSize );

        for ( auto sendIndex = 0; sendIndex < sendCount; ++sendIndex )
        {
            socket->sendBinaryMessage( data );
        }

        QJsonObject replyData;
        replyData[ "action" ]     = "downloadSpeedTest";
        replyData[ "serverTime" ] = QString::number( QDateTime::currentMSecsSinceEpoch() );
        replyData[ "clientTime" ] = requestData.value( "clientTime" );
        replyData[ "byteCount" ]  = dataBlockSize * sendCount;

        socket->sendTextMessage( QJsonDocument( replyData ).toJson( QJsonDocument::Compact ) );
    }
    else if ( action == "uploadSpeedTest" )
    {
        QJsonObject replyData;
        replyData[ "action" ]     = "uploadSpeedTest";
        replyData[ "serverTime" ] = QString::number( QDateTime::currentMSecsSinceEpoch() );
        replyData[ "clientTime" ] = requestData.value( "clientTime" );
        replyData[ "byteCount" ]  = requestData.value( "byteCount" );

        socket->sendTextMessage( QJsonDocument( replyData ).toJson( QJsonDocument::Compact ) );
    }
}

void Helper::onBinaryMessageReceived(QWebSocket *socket, const QByteArray &message)
{
    Q_UNUSED( socket );
    Q_UNUSED( message );

    // qDebug() << "binary message received:" << socket << message.size();
}
