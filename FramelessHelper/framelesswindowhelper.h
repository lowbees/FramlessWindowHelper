#ifndef FRAMELESSWINDOWHELPER_H
#define FRAMELESSWINDOWHELPER_H

#include <QObject>
#include <QQuickWindow>
#include <QQmlParserStatus>

class WindowHandler;

class FramelessWindowHelper : public QObject, public QQmlParserStatus
{
    Q_OBJECT
    Q_INTERFACES(QQmlParserStatus)
public:
    explicit FramelessWindowHelper(QObject *parent = 0);
    ~FramelessWindowHelper();
    
public:
    void classBegin() Q_DECL_FINAL;
    void componentComplete() Q_DECL_FINAL;    
    // QObject interface
public:
    bool eventFilter(QObject *watched, QEvent *event) Q_DECL_OVERRIDE;

private:
    QHash<QObject*, WindowHandler*> windows;
};

#endif // FRAMELESSWINDOWHELPER_H
