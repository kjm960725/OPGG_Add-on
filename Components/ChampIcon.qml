import QtQuick 2.15
import QtGraphicalEffects 1.0
import QtQuick.Controls 2.15

Item {
    id: root

    property var champInfo
    property int radius: Math.min(width,height) / 10
    property string nullText
    property string fontFamily
    property string iconDirPath

    signal clicked(var id)


    width: 100
    height: 100

    MouseArea {
        id: mouse
        enabled: !(champInfo === undefined || champInfo === null)
        anchors.fill: parent
        onClicked: {
            root.clicked(champInfo.id)
        }
        hoverEnabled: true

        onPressedChanged: {
            if (pressed) {
                champ.scale = 0.9
            } else {
                champ.scale = 1
            }
        }
    }

    Item {
        Behavior on scale { NumberAnimation { duration: 50 } }
        id: champ
        anchors.fill: parent

        Item {
            id: layerItem
            anchors.fill: parent
            clip: true
            layer.enabled: true
            layer.effect: OpacityMask {
                maskSource: Item {
                    width: layerItem.width
                    height: layerItem.height
                    Rectangle {
                        anchors.centerIn: parent
                        width: layerItem.adapt ? layerItem.width : Math.min(layerItem.width, layerItem.height)
                        height: layerItem.adapt ? layerItem.height : width
                        radius: root.radius
                        border.width: 5
                    }
                }
            }

            Image {
                id: icon
                source: champInfo === undefined || champInfo === null ? '' : iconDirPath + '/champion/' + champInfo.image.full
                anchors.centerIn: parent
                width: parent.width * 1.1
                height: parent.height * 1.1

                clip: true
                Rectangle {
                    id: champNameBg
                    Behavior on opacity { NumberAnimation { duration: 100 } }
                    anchors.centerIn: parent
                    width: parent.width / 1.1
                    height: parent.height / 1.1
                    color: '#aa000000'
                    opacity: mouse.containsMouse || !mouse.enabled ? 1 : 0

                    Text {
                        id: champName
                        text: champInfo === undefined || champInfo === null ? nullText : champInfo.name
                        font.family: fontFamily
                        font.pixelSize: 14
                        anchors.fill: parent
                        color: '#ffffff'
                        horizontalAlignment: Text.AlignHCenter
                        verticalAlignment: Text.AlignVCenter
                        wrapMode: Text.WordWrap
                        style: Text.Outline
                    }
                }

                Rectangle {
                    id:border
                    anchors.centerIn: parent
                    width: parent.width / 1.1
                    height: parent.height / 1.1
                    color: '#00000000'
                    border.width: 1
                    border.color: '#888888'
                    radius: root.radius
                }
            }
        }

    }

}
