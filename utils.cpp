#include "utils.h"
#include <QDebug>

Utils::Utils()
{

}

void Utils::DestructorMsg(const QString &value)
{
    qDebug() << QStringLiteral("Running the %1 destructor").arg(value);
}

void Utils::DestructorMsg(const QObject * const object)
{
    DestructorMsg(object->metaObject()->className());
    qDebug() << Qt::endl;
}


