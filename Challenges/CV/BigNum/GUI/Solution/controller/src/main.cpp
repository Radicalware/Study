#include<Windows.h>

#include <QGuiApplication>
#include "Core.h"
#include "Nexus.h"


int main(int argc, char *argv[])
{
    Nexus<>::Start();
    LPCWSTR dll = L"C:\\SourceGUI\\Build\\Windows\\Release\\Release\\bin\\qml\\QtQuick.2\\qtquick2plugin.dll";
    HMODULE qtquick2plugin_dll = LoadLibrary(dll);
    cout << qtquick2plugin_dll << endl;
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
