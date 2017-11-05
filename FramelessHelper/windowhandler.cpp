#include "windowhandler.h"
#include <QQuickWindow>
#include <QEvent>
#include <QMouseEvent>
#include <QPoint>
#include <QGuiApplication>

WindowHandler::WindowHandler(QQuickWindow *w) :
    _edgeSize(5), window(w)
{
    if (w) w->setFlags(w->flags() | Qt::FramelessWindowHint);
}

void WindowHandler::handleEvent(QEvent *e)
{
    switch (e->type()) {
    case QEvent::MouseButtonPress:
        handleMousePressEvent(static_cast<QMouseEvent*>(e));
        break;
    case QEvent::MouseMove:
        handleMouseMoveEvent(static_cast<QMouseEvent*>(e));
        break;
    case QEvent::MouseButtonRelease:
        handleMouseReleaseEvent(static_cast<QMouseEvent*>(e));
        break;
    default:
        break;
    }
}

void WindowHandler::checkOnEdges(const QPoint &pos)
{
    if (!window)
        return;
    int x = pos.x();
    int y = pos.y();
    int width = window->width();
    int height = window->height();

    onLeft = (x >= 0 && x <= _edgeSize);
    onTop = (y >= 0 && y <= _edgeSize);
    onRight = (x >= width - _edgeSize && x <= width);
    onBottom = (y >= height - _edgeSize && y <= height);

    onTopLeft = onTop && onLeft;
    onTopRight = onTop && onRight;
    onBottomLeft = onBottom && onLeft;
    onBottomRight = onBottom && onRight;
    onEdges = onTop || onLeft || onRight || onBottom;

}

void WindowHandler::updateCursorShape(const QPoint &pos)
{
    if (!window)
        return;
    if (window->visibility() == QQuickWindow::FullScreen
            || window->visibility() == QQuickWindow::Maximized) {
        while (QGuiApplication::overrideCursor())
            QGuiApplication::restoreOverrideCursor();
        return;
    }

    checkOnEdges(pos);
    if (onTopLeft || onBottomRight) {
        QGuiApplication::setOverrideCursor(Qt::SizeFDiagCursor);
    }
    else if (onTopRight || onBottomLeft) {
        QGuiApplication::setOverrideCursor(Qt::SizeBDiagCursor);
    }
    else if (onLeft || onRight) {
        QGuiApplication::setOverrideCursor(Qt::SizeHorCursor);
    }
    else if (onTop || onBottom) {
        QGuiApplication::setOverrideCursor(Qt::SizeVerCursor);
    }
    else {
        // 将鼠标形状恢复
        while (QGuiApplication::overrideCursor())
            QGuiApplication::restoreOverrideCursor();
    }
}

void WindowHandler::resizeWindow(const QPoint &pos)
{
    if (!window)
        return;

    const QPoint gPos = window->mapToGlobal(pos);
    int x = gPos.x();
    int y = gPos.y();

    QRect frameRect = window->frameGeometry();
    int minWidth = window->minimumWidth();
    int minHeight = window->minimumHeight();
    int maxWidth = window->maximumWidth();
    int maxHeight = window->maximumHeight();

    int left, top, right, bottom;
    frameRect.getCoords(&left, &top, &right, &bottom);

    if (onTopLeft) {
        left = x;
        top = y;
    }
    else if (onTopRight) {
        right = x;
        top = y;
    }
    else if (onBottomLeft) {
        left = x;
        bottom = y;
    }
    else if (onBottomRight) {
        right = x;
        bottom = y;
    }
    else if (onLeft) {
        left = x;
    }
    else if (onTop) {
        top = y;
    }
    else if (onRight) {
        right = x;
    }
    else if (onBottom) {
        bottom = y;
    }

    QRect newRect(QPoint(left, top), QPoint(right, bottom));
    if (newRect.isValid()) {
        if (minWidth > newRect.width() || maxWidth < newRect.width()) {
            if (left != frameRect.left())
                newRect.setLeft(frameRect.left());
            else
                newRect.setRight(frameRect.right());
        }
        if (minHeight > newRect.height() || maxHeight < newRect.height()) {
            if (top != frameRect.top())
                newRect.setTop(frameRect.top());
            else
                newRect.setBottom(frameRect.bottom());
        }
        window->setGeometry(newRect);
        // 解决界面刷新不及时的问题, requestUpdate() 不知道为什么不管用
        qreal opacity = window->opacity();
        window->setOpacity(opacity - 0.01);
        window->setOpacity(opacity);
    }
}

void WindowHandler::handleMousePressEvent(QMouseEvent *e)
{
    if (e->button() == Qt::LeftButton) {
        leftButtonPress = true;
        checkOnEdges(e->pos());
    }
}

void WindowHandler::handleMouseMoveEvent(QMouseEvent *e)
{
    if (window && window->visibility() == QWindow::Maximized)
        return;
    if (leftButtonPress) {
        if (onEdges) {
            resizing = true;
            resizeWindow(e->pos());
        }
    }
    else {
        updateCursorShape(e->pos());
    }
}

void WindowHandler::handleMouseReleaseEvent(QMouseEvent *e)
{
    Q_UNUSED(e)
    leftButtonPress = false;
    resizing = false;
}
