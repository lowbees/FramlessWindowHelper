#include "framelesswindowhelper.h"
#include "windowhandler.h"
#include <QQuickItem>

FramelessWindowHelper::FramelessWindowHelper(QObject *parent) :
    QObject(parent)
{
}

FramelessWindowHelper::~FramelessWindowHelper()
{
    QObjectList keys = windows.keys();
    foreach (QObject *obj, keys) {
        delete windows.value(obj);
    }
}

void FramelessWindowHelper::classBegin()
{

}

// 此段代码来自 https://github.com/qtdevs/FramelessHelper
void FramelessWindowHelper::componentComplete()
{
    auto obj = parent();
    while (Q_NULLPTR != obj) {
        if (obj->inherits("QQuickRootItem")) {
            if (auto rootItem = qobject_cast<QQuickItem *>(obj)) {
                if (auto window = rootItem->window()) {
                    if (!windows.contains(window)) {
                        window->installEventFilter(this);
                        windows.insert(window, new WindowHandler(window));
                    }
                    break;
                }
            }
        }

        obj = obj->parent();
    }
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
