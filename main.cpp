#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include "startup.h"

int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);

    Startup startup(&app, app);

    return app.exec();
}
