import QtQuick 2.6
import QtQuick.Window 2.2
import QtQuick.Controls 2.1

Window {
    id: root
    visible: true
    minimumWidth: 600
    minimumHeight: 400
    maximumWidth: 1000
    maximumHeight: 700
    width: 640
    height: 480
    title: qsTr("Hello World")
    objectName: "MainWindow"

    flags: Qt.FramelessWindowHint | Qt.Window | Qt.WindowMinimizeButtonHint

    Rectangle {
        id: titleBar
        color: 'blue'
        width: parent.width
        height: closeButton.height
        objectName: "titleBar"

        MouseArea {
            anchors.fill: parent
            cursorShape: Qt.BusyCursor
            property point pressPos
            onPressed: pressPos = Qt.point(mouse.x, mouse.y)
            onPositionChanged: {
                root.x += mouse.x - pressPos.x
                root.y += mouse.y - pressPos.y
            }
            onDoubleClicked: maxButton.clicked()
        }

        Row {
            spacing: 6
            anchors.right: parent.right
            anchors.rightMargin: 6
            Rectangle {
                color: 'yellow'
                width: 100
                height: parent.height
                MouseArea {
                    anchors.fill: parent
                    cursorShape: Qt.ArrowCursor
                }
            }

            Button {
                text: "最小化"
                onClicked: root.visibility = Window.Minimized
            }

            Button {
                id: maxButton
                text: root.visibility == Window.Windowed ? "最大化" : "恢复"
                onClicked: root.visibility = root.visibility == Window.Windowed ?
                               Window.Maximized : Window.Windowed
            }
            Button {
                id: closeButton
                text: "关闭"
                onClicked: root.close()
            }
        }


    }


    Rectangle {
        anchors.fill: parent
        anchors.margins: 5
        color: 'transparent'
        border.color: 'red'
        border.width: 1
    }

    Button {
        anchors.centerIn: parent
        onClicked: testLoader.source = "Test.qml"
    }

    Loader {
        id: testLoader
        onStatusChanged: if (status == Loader.Ready) item.show()
    }
}
