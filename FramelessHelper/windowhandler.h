#ifndef WINDOWHANDLER_H
#define WINDOWHANDLER_H

class QQuickWindow;
class QEvent;
class QMouseEvent;
class QPoint;

class WindowHandler
{
public:

    WindowHandler(QQuickWindow *w);

    // 事件转发
    void handleEvent(QEvent *e);

    bool isResizing() const { return resizing; }
    int edgeSize() const { return _edgeSize; }
    void setEdgeSize(int size) {
        if (size > 0 && size != _edgeSize)
            _edgeSize = size;
    }

private:
    // 是否在边界可拉伸区域
    void checkOnEdges(const QPoint &pos);
    // 更新鼠标样式
    void updateCursorShape(const QPoint &pos);
    // 更改窗口大小和位置
    void resizeWindow(const QPoint &pos);
    // 处理鼠标按下事件
    void handleMousePressEvent(QMouseEvent *e);
    // 处理鼠标移动事件
    void handleMouseMoveEvent(QMouseEvent *e);
    // 处理鼠标释放事件
    void handleMouseReleaseEvent(QMouseEvent *e);

private:
    bool onLeft;
    bool onTop;
    bool onRight;
    bool onBottom;
    bool onTopLeft;
    bool onTopRight;
    bool onBottomLeft;
    bool onBottomRight;
    bool onEdges;
    bool leftButtonPress;
    bool resizing;
    int _edgeSize;
    QQuickWindow *window;
};

#endif // WINDOWHANDLER_H
