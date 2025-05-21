import QtQuick 2.15
import QtQuick.Controls 2.15

Item {
    id: root
    width: 100
    height: 100

    required property int boxIndex
    property string mark: ""

    signal clicked(int index)

    Rectangle {
        anchors.fill: parent
        color: "lightyellow"
        border.color: "black"
        border.width: 1

        Text {
            anchors.centerIn: parent
            text: root.mark
            font.pixelSize: 40
            color: "black"
            font.bold: true
        }

        MouseArea {
            anchors.fill: parent
            onClicked: root.clicked(root.boxIndex)
        }
    }
}
