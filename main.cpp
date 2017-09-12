#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include "framelesshelper/framelesswindowhelper.h"

int main(int argc, char *argv[])
{
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
    QCoreApplication::setAttribute(Qt::AA_UseSoftwareOpenGL);
    QGuiApplication app(argc, argv);

    qmlRegisterType<FramelessWindowHelper>("FramelessWindowHelper", 1, 0, "FramelessWindowHelper");
    QQmlApplicationEngine engine;
    engine.load(QUrl(QStringLiteral("qrc:/main.qml")));

    if (engine.rootObjects().isEmpty())
        return -1;

    return app.exec();
}
