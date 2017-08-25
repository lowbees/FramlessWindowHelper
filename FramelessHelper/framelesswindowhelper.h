#ifndef FRAMELESSWINDOWHELPER_H
#define FRAMELESSWINDOWHELPER_H

#include <QObject>
#include <QQuickWindow>

class QQmlApplicationEngine;
class WindowHandler;

class FramelessWindowHelper : public QObject
{
    Q_OBJECT
public:
    explicit FramelessWindowHelper(QQmlApplicationEngine *eg, QObject *parent = 0);

signals:

public slots:
    void addWindow(const QString &objName);
    void addWindow(QObject *obj);
    // QObject interface
public:
    bool eventFilter(QObject *watched, QEvent *event) Q_DECL_OVERRIDE;

private:
    QQmlApplicationEngine *engine;
    QHash<QObject*, WindowHandler*> windows;
};

#endif // FRAMELESSWINDOWHELPER_H
