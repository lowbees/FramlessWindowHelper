import QtQuick 2.0
import QtQuick.Controls 2.1
import FramelessWindowHelper 1.0

ApplicationWindow {
    objectName: "TestPage"

//    flags: Qt.FramelessWindowHint | Qt.Window | Qt.WindowMinimizeButtonHint
    FramelessWindowHelper {

    }
    Rectangle {
        anchors.fill: parent
        color: 'red'
    }
}
