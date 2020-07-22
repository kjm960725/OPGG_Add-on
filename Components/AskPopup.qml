import QtQuick 2.15
import QtQuick.Controls 2.15

Popup {
    property string fontFamily
    property alias acceptButton: acceptButton
    property alias closeButton: closeButton
    property bool accepted: false

    function show(headerText, contentText, callback) {
        accepted = false
        header.text = headerText
        content.text = contentText
        function f(){
            callback(accepted)
            closed.disconnect(f)
        }
        closed.connect(f)
        open()
    }

    width: 300
    height: col.height + 30

    id: root
    closePolicy: Popup.NoAutoClose
    modal: true
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
            font.family: fonts.nanumEB
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
            font.family: fonts.nanumR
            color: '#ffffff'
            font.pixelSize: 12
            anchors.left: parent.left
            anchors.right: parent.right
            wrapMode: Text.WrapAnywhere
            lineHeight: 1.2
        }

        Row {
            spacing: 15
            anchors.horizontalCenter: parent.horizontalCenter

            Button {
                id: acceptButton
                text: qsTr('예')
                width: 100
                height: 40
                font.family: fonts.nanumB
                font.pixelSize: 14

                onClicked: {
                    accepted = true
                    close()
                }
                contentItem: Text {
                    text: parent.text
                    font: parent.font
                    color: '#000000'
                    horizontalAlignment: Text.AlignHCenter
                    verticalAlignment: Text.AlignVCenter
                    elide: Text.ElideRight
                }

                background: Rectangle {
                    radius: height / 2
                    border.width: 1
                    border.color: '#ffffff'
                }
            }

            Button {
                id: closeButton
                text: qsTr('아니오')
                width: 100
                height: 40
                font.family: fonts.nanumB
                font.pixelSize: 14
                onClicked: {
                    accepted = false
                    close()
                }
                contentItem: Text {
                    text: parent.text
                    font: parent.font
                    color: '#000000'
                    horizontalAlignment: Text.AlignHCenter
                    verticalAlignment: Text.AlignVCenter
                    elide: Text.ElideRight
                }

                background: Rectangle {
                    radius: height / 2
                    border.width: 1
                    border.color: '#ffffff'
                }
            }

        }
    }

}
