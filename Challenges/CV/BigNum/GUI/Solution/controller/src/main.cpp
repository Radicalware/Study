#include<Windows.h>

#include <QGuiApplication>
#include <type_traits>
#include "Core.h"
#include "Nexus.h"


int main(int argc, char *argv[])
{
    Nexus<>::Start();
    
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
    QGuiApplication app(argc, argv);

    Core core;
    int retValue = 0;

    if (core.initialize())
        retValue = app.exec();
    else
        int retValue = -1;

    Nexus<>::Stop();
    return retValue;
}
