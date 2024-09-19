#ifndef HELPER_H_
#define HELPER_H_

// Qt lib import
#include <QDebug>
#include <QWebSocket>
#include <QTimer>

class Helper: public QObject
{
    Q_OBJECT

    Q_PROPERTY( QString serverHost READ serverHost WRITE setServerHost NOTIFY serverHostChanged )

    Q_PROPERTY( bool isConnected READ isConnected WRITE setIsConnected NOTIFY isConnectedChanged )
    Q_PROPERTY( int latency READ latency WRITE setLatency NOTIFY latencyChanged )

public:
    Helper();

    virtual ~Helper() override = default;

private:
    void onCheck();

    void sendJsonTextMessage(const QJsonObject &requestData);

    void onTextMessageReceived(const QString &message);

    void onBinaryMessageReceived(const QByteArray &message);

private:
    QTimer     checkTimer_;
    QWebSocket socket_;

    // Property statement code start
private: QString serverHost_;
public: inline QString serverHost() const;
public: inline void setServerHost(const QString &newValue);
    Q_SIGNAL void serverHostChanged(const QString serverHost);

private: bool isConnected_ = false;
public: inline bool isConnected() const;
public: inline void setIsConnected(const bool &newValue);
    Q_SIGNAL void isConnectedChanged(const bool isConnected);

private: int latency_ = -1;
public: inline int latency() const;
public: inline void setLatency(const int &newValue);
    Q_SIGNAL void latencyChanged(const int latency);
private:
    // Property statement code end
};

// Property accomplish code start
inline QString Helper::serverHost() const
{ return serverHost_; }
inline void Helper::setServerHost(const QString &newValue)
{ if ( newValue == serverHost_ ) { return; } serverHost_ = newValue; emit serverHostChanged( serverHost_ ); }

inline bool Helper::isConnected() const
{ return isConnected_; }
inline void Helper::setIsConnected(const bool &newValue)
{ if ( newValue == isConnected_ ) { return; } isConnected_ = newValue; emit isConnectedChanged( isConnected_ ); }

inline int Helper::latency() const
{ return latency_; }
inline void Helper::setLatency(const int &newValue)
{ if ( newValue == latency_ ) { return; } latency_ = newValue; emit latencyChanged( latency_ ); }
// Property accomplish code end

#endif//HELPER_H_
