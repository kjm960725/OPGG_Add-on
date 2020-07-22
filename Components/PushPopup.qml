import QtQuick 2.15
import QtQuick.Controls 2.15

Popup {
    property string fontFamily

    function show(headerText, contentText, msec = 10000) {
        header.text = headerText
        content.text = contentText
        closeTimer.interval = msec
        open()
    }

    Timer {
        id: closeTimer
        running: visible; repeat: false; interval: 1000
        onTriggered: close()
    }

    width: 400
    height: col.height + 30

    id: root
    closePolicy: Popup.NoAutoClose
    modal: false
    anchors.centerIn: parent
    background: Rectangle {
        radius: Math.min(root.width,root.height) / 10
        color: '#ee333333'
        border.width: 1
        border.color: '#000000'
    }
    Column {
        id: col
        anchors.verticalCenter: parent.verticalCenter
        anchors.left: parent.left
        anchors.right: parent.right
        anchors.leftMargin: 10
        anchors.rightMargin: 10
        spacing: 10
        Text {
            id: header
            visible: text.length > 0
            font.family: fontFamily
            color: '#bbbb00'
            style: Text.Outline
            font.pixelSize: 18
            anchors.left: parent.left
            anchors.right: parent.right
            wrapMode: Text.WrapAnywhere
            lineHeight: 1.2
            horizontalAlignment: Text.AlignHCenter
        }
        Text {
            id: content
            visible: text.length > 0
            font.family: fontFamily
            color: '#ffffff'
            font.pixelSize: 12
            anchors.left: parent.left
            anchors.right: parent.right
            wrapMode: Text.WrapAnywhere
            lineHeight: 1.2
        }
    }

}
