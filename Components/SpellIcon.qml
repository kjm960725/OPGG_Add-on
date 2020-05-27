import QtQuick 2.12
import QtQuick.Controls 2.12
import QtGraphicalEffects 1.0

Item {
    id: root
    property string imgDirPath
    property var spellInfo
    property string fontFamily
    property int radius: Math.min(width,height) / 10
    property string hotkey

    signal clicked(var id)

    width: 50
    height: 50

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
            id: spellImage
            anchors.fill: parent
            source:  imgDirPath + (spellInfo.id === undefined ? '/passive/' : '/spell/') + spellInfo.image.full
            clip: true
            Rectangle {
                id: hotKeyBg
                Behavior on opacity { NumberAnimation { duration: 100 } }
                anchors.fill: parent
                color: '#aa000000'
                opacity: spellArea.containsMouse ? 1 : 0

                Text {
                    id: hoyKeyName
                    text: hotkey
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
                anchors.fill: parent
                color: '#00000000'
                border.width: 1
                border.color: '#000000'
                radius: root.radius
            }
        }
    }

    MouseArea {
        id: spellArea
        anchors.fill: parent
        hoverEnabled: true
        onClicked: root.clicked(spellInfo.id === undefined ? spellInfo.image.full.split('_')[0] + 'Q' : spellInfo.id)
    }

    ToolTip{
        id: tooltip
        visible: spellArea.containsMouse
        width: 300
        x: - (width / 2) + root.width / 2
        y: root.width + 10
        background: Rectangle {
            color: '#ee000000'
            radius: 10
            border.width: 0
            border.color: '#ffffff'
        }

        contentItem : Item {
            Column {
                id: col
                anchors.left: parent.left
                anchors.right: parent.right
                spacing: 10
                Item { height: 1; width: 1; }
                Text{
                    id: spellName
                    anchors.left: parent.left
                    anchors.right: parent.right
                    anchors.leftMargin: 10
                    anchors.rightMargin: 10
                    wrapMode: Text.WordWrap
                    text: spellInfo.name
                    font.family: fontFamily
                    font.pixelSize: 18
                    lineHeight: 1.2
                    color: '#ffff00'
                }
                Column {
                    visible: spellInfo.id !== undefined
                    anchors.left: parent.left
                    anchors.right: parent.right
                    spacing: 5
                    Text{
                        id: cooldownText
                        anchors.left: parent.left
                        anchors.right: parent.right
                        anchors.leftMargin: 10
                        anchors.rightMargin: 10
                        wrapMode: Text.WordWrap
                        text: qsTr('쿨타임 : %1').arg(spellInfo.cooldownBurn)
                        font.family: fontFamily
                        font.pixelSize: 12
                        color: '#aaaaaa'
                    }
                    Text{
                        id: costText
                        anchors.left: parent.left
                        anchors.right: parent.right
                        anchors.leftMargin: 10
                        anchors.rightMargin: 10
                        wrapMode: Text.WordWrap
                        text: qsTr('소모') + ': ' + spellInfo.costBurn
                        font.family: fontFamily
                        font.pixelSize: 12
                        color: '#aaaaaa'
                    }
                    Text{
                        id: rangeText
                        anchors.left: parent.left
                        anchors.right: parent.right
                        anchors.leftMargin: 10
                        anchors.rightMargin: 10
                        wrapMode: Text.WordWrap
                        text: qsTr('범위') + ': ' + spellInfo.rangeBurn
                        font.family: fontFamily
                        font.pixelSize: 12
                        color: '#aaaaaa'
                    }
                }
                Item { height: 1; width: 1; }

                Text{
                    id: tooltipText
                    anchors.left: parent.left
                    anchors.right: parent.right
                    anchors.leftMargin: 10
                    anchors.rightMargin: 10
                    wrapMode: Text.WordWrap
                    text: spellInfo.description
                    font.family: fontFamily
                    font.pixelSize: 12
                    lineHeight: 1.2
                    color: '#ffffff'
                }
                Item { height: 5; width: 1 }
            }
        }
    }
}
