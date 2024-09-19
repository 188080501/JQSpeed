#include "helper.h"

// Qt lib import
#include <QDebug>
#include <QJsonObject>
#include <QJsonDocument>
#include <QUrl>

// WASM lib import
#ifdef Q_OS_WASM
#   include <emscripten.h>
#   include <emscripten/val.h>
#endif

Helper::Helper()
{
    connect( &checkTimer_, &QTimer::timeout, this, &Helper::onCheck );
    checkTimer_.start( 1000 );

    connect( &socket_, &QWebSocket::textMessageReceived, this, &Helper::onTextMessageReceived );
    connect( &socket_, &QWebSocket::binaryMessageReceived, this, &Helper::onBinaryMessageReceived );

    QTimer::singleShot( 0, this, &Helper::onCheck );

#ifdef Q_OS_WASM
    this->setServerHost( QUrl( emscripten::val::global( "location" )[ "href" ].as<std::string>().c_str() ).host() );
#else
    this->setServerHost( "127.0.0.1" );
#endif
}

void Helper::onCheck()
{
    if ( socket_.state() == QAbstractSocket::UnconnectedState )
    {
        socket_.open( QUrl( QString( "ws://%1:51888" ).arg( this->serverHost() ) ) );
    }
    else if ( socket_.state() == QAbstractSocket::ConnectedState )
    {
        QJsonObject requestData;
        requestData[ "action" ]     = "ping";
        requestData[ "clientTime" ] = QString::number( QDateTime::currentMSecsSinceEpoch() );

        this->sendJsonTextMessage( requestData );
    }

    if ( socket_.state() == QAbstractSocket::ConnectedState )
    {
        this->setIsConnected( true );
    }
    else
    {
        this->setIsConnected( false );
        this->setLatency( -1 );
    }
}

void Helper::sendJsonTextMessage(const QJsonObject &requestData)
{
    socket_.sendTextMessage( QJsonDocument( requestData ).toJson( QJsonDocument::Compact ) );
}

void Helper::onTextMessageReceived(const QString &message)
{
    // qDebug() << "onTextMessageReceived:" << message.toUtf8().constData();

    auto responseData = QJsonDocument::fromJson( message.toUtf8() ).object();
    if ( responseData.isEmpty() ) { return; }

    const auto action = responseData .value( "action" ).toString();
    if ( action.isEmpty() ) { return; }

    if ( action == "ping" )
    {
        const auto clientTime  = responseData.value( "clientTime" ).toString().toLongLong();
        const auto currentTime = QDateTime::currentMSecsSinceEpoch();
        const auto latency     = currentTime - clientTime;

        // qDebug() << "ping latency:" << latency;

        if ( ( latency < 0 ) || ( latency > 10000000 ) )
        {
            socket_.close();

            this->setIsConnected( false );
            this->setLatency( -1 );

            return;
        }

        this->setLatency( latency );
    }
}

void Helper::onBinaryMessageReceived(const QByteArray &message)
{
    qDebug() << "onBinaryMessageReceived:" << message.size();
}
