#include "framelesswindowhelper.h"
#include "windowhandler.h"

#include <QQmlApplicationEngine>
#include <QQmlContext>
#include <QDebug>

FramelessWindowHelper::FramelessWindowHelper(QQmlApplicationEngine *eg, QObject *parent) :
    QObject(parent), engine(eg)
{
    if (eg) eg->rootContext()->setContextProperty("FramelessWindowHelper", this);
}

FramelessWindowHelper::~FramelessWindowHelper()
{
    QObjectList keys = windows.keys();
    foreach (QObject *obj, keys) {
        delete windows.value(obj);
    }
}

void FramelessWindowHelper::addWindow(const QString &objName)
{
    if (!engine || engine->rootObjects().isEmpty() || objName.isEmpty())
        return;

    for (int i = 0; i < engine->rootObjects().size(); ++i) {
        QObject *rootObj = engine->rootObjects()[i];

        if (rootObj) {
            if (rootObj->isWindowType() && !windows.contains(rootObj)) {
                windows.insert(rootObj, new WindowHandler(qobject_cast<QQuickWindow*>(rootObj)));
                rootObj->installEventFilter(this);
            }

            QObjectList objs = rootObj->findChildren<QObject*>(objName);
            for (int j = 0; j < objs.size(); ++j) {
                if (objs[j]->isWindowType() && !windows.contains(objs[j])) {
                    windows.insert(objs[j], new WindowHandler(qobject_cast<QQuickWindow*>(objs[j])));
                    objs[j]->installEventFilter(this);
                }
            }
        }
    }
}

void FramelessWindowHelper::addWindow(QObject *obj)
{
    if (obj) addWindow(obj->objectName());
}


bool FramelessWindowHelper::eventFilter(QObject *watched, QEvent *event)
{
    switch (event->type()) {
    case QEvent::MouseButtonPress:
    case QEvent::MouseMove:
    case QEvent::MouseButtonRelease:
    {
        WindowHandler *handler = windows.value(watched);
        if (handler) {
            handler->handleEvent(event);
            if (handler->isResizing())
                return true;
        }
    }
        break;
    default:
        break;
    }
    return QObject::eventFilter(watched, event);
}
