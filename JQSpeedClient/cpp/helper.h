#ifndef HELPER_H_
#define HELPER_H_

// Qt lib import
#include <QDebug>
#include <QDateTime>

class Helper: public QObject
{
    Q_OBJECT

public:
    Helper() = default;

    virtual ~Helper() override = default;
};

#endif//HELPER_H_
