import QtQuick 2.0
import QtGraphicalEffects 1.0
import QtQuick.Controls 2.12

Item {
    id: root

    property var champInfo
    property int radius: 0

    signal clicked(var id)


    width: 100
    height: 100

    ToolTip {
        visible: mouse.containsMouse
        text: champInfo.name
        background: Rectangle {
            color: '#ffffff'
        }
        delay: 200
    }

    MouseArea {
        id: mouse
        anchors.fill: parent
        hoverEnabled: true
        onClicked: {
            root.clicked(champInfo.id)
        }


        onPressedChanged: {
            if (pressed) {
                icon.scale = 0.9
            } else {
                icon.scale = 1
            }
        }


    }

    Image {
        id: icon

        Behavior on scale { NumberAnimation { duration: 50 } }
        source: applicationPath + '/DataDragon/' + champInfo.version + '/img/' + champInfo.image.group + '/' + champInfo.image.full
        anchors.fill: parent
        layer.enabled: radius ? true : false
        layer.effect: OpacityMask {
            maskSource: Item {
                width: icon.width
                height: icon.height
                Rectangle {
                    anchors.centerIn: parent
                    width: icon.adapt ? icon.width : Math.min(icon.width, icon.height)
                    height: icon.adapt ? icon.height : width
                    radius: Math.min(width, height)
                }
            }
        }
    }

}
