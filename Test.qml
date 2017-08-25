import QtQuick 2.0
import QtQuick.Controls 2.1

ApplicationWindow {
    objectName: "TestPage"

//    flags: Qt.FramelessWindowHint | Qt.Window | Qt.WindowMinimizeButtonHint
    // 非主窗口可以采用此种方式
    Component.onCompleted: FramelessWindowHelper.addWindow(objectName)
    Rectangle {
        anchors.fill: parent
        color: 'red'
    }
}
