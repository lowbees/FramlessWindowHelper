#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include "framelesshelper/framelesswindowhelper.h"

int main(int argc, char *argv[])
{
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
    QCoreApplication::setAttribute(Qt::AA_UseSoftwareOpenGL);
    QGuiApplication app(argc, argv);

    QQmlApplicationEngine engine;
    engine.load(QUrl(QStringLiteral("qrc:/main.qml")));

    if (engine.rootObjects().isEmpty())
        return -1;
    FramelessWindowHelper helper(&engine);

    // 主窗口必须以这种方式
    helper.addWindow("MainWindow");
    return app.exec();
}
