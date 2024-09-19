// Qt lib import
#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include <QQuickStyle>

// Project lib import
#include "jqwebcommon.h"
#include "helper.h"

int main(int argc, char **argv)
{
    QGuiApplication app( argc, argv );

    JQWebCommon::init( &app );

    Helper helper;
    if ( !helper.init() )
    {
        qDebug() << "init error";
        return -1;
    }

    qDebug() << "server init succeed";

    return app.exec();
}
