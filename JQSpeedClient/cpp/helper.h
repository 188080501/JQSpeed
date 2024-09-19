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
    Q_PROPERTY( bool isMeasuringSpeed READ isMeasuringSpeed WRITE setIsMeasuringSpeed NOTIFY isMeasuringSpeedChanged )

    Q_PROPERTY( int latency READ latency WRITE setLatency NOTIFY latencyChanged )
    Q_PROPERTY( float downloadSpeed READ downloadSpeed WRITE setDownloadSpeed NOTIFY downloadSpeedChanged )
    Q_PROPERTY( float uploadSpeed READ uploadSpeed WRITE setUploadSpeed NOTIFY uploadSpeedChanged )

public:
    Helper();

    virtual ~Helper() override = default;

public slots:
    void startMeasureDownloadSpeed();

    void startMeasureUploadSpeed();

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

private: bool isMeasuringSpeed_ = false;
public: inline bool isMeasuringSpeed() const;
public: inline void setIsMeasuringSpeed(const bool &newValue);
    Q_SIGNAL void isMeasuringSpeedChanged(const bool isMeasuringSpeed);

private: int latency_ = -1;
public: inline int latency() const;
public: inline void setLatency(const int &newValue);
    Q_SIGNAL void latencyChanged(const int latency);

private: float downloadSpeed_ = -1.0f;
public: inline float downloadSpeed() const;
public: inline void setDownloadSpeed(const float &newValue);
    Q_SIGNAL void downloadSpeedChanged(const float downloadSpeed);

private: float uploadSpeed_ = -1.0f;
public: inline float uploadSpeed() const;
public: inline void setUploadSpeed(const float &newValue);
    Q_SIGNAL void uploadSpeedChanged(const float uploadSpeed);
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

inline bool Helper::isMeasuringSpeed() const
{ return isMeasuringSpeed_; }
inline void Helper::setIsMeasuringSpeed(const bool &newValue)
{ if ( newValue == isMeasuringSpeed_ ) { return; } isMeasuringSpeed_ = newValue; emit isMeasuringSpeedChanged( isMeasuringSpeed_ ); }

inline int Helper::latency() const
{ return latency_; }
inline void Helper::setLatency(const int &newValue)
{ if ( newValue == latency_ ) { return; } latency_ = newValue; emit latencyChanged( latency_ ); }

inline float Helper::downloadSpeed() const
{ return downloadSpeed_; }
inline void Helper::setDownloadSpeed(const float &newValue)
{ if ( qAbs( newValue - downloadSpeed_ ) < 0.000001 ) { return; } downloadSpeed_ = newValue; emit downloadSpeedChanged( downloadSpeed_ ); }

inline float Helper::uploadSpeed() const
{ return uploadSpeed_; }
inline void Helper::setUploadSpeed(const float &newValue)
{ if ( qAbs( newValue - uploadSpeed_ ) < 0.000001 ) { return; } uploadSpeed_ = newValue; emit uploadSpeedChanged( uploadSpeed_ ); }
// Property accomplish code end

#endif//HELPER_H_
