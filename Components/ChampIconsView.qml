import QtQuick 2.15
import QtQuick.Controls 2.15

Item {
    id: root

    property var champInfos
    property int iconSize: 80
    property string fontFamily
    property string imgDirPath

    signal clicked(var id)

    QtObject {
        id: pri
        readonly property var champInfosKeys: {
            const result = new Array;
            let i = 0;
            for (let key in champInfos) result[i++] = key
            return result
        }
    }

    Flickable {
        id: flickable
        anchors.fill: parent
        ScrollBar.vertical: ScrollBar { id: scrollbar }
        contentHeight: champGrid.height

        Grid {
            id: champGrid
            anchors.horizontalCenter: parent.horizontalCenter
            anchors.top: parent.top
            columnSpacing: iconSize / 20
            rowSpacing: iconSize / 20
            columns: Math.floor((root.width + columnSpacing) / (iconSize + columnSpacing))

            Repeater {
                model: pri.champInfosKeys.length

                ChampIcon {
                    radius: iconSize/10
                    width: iconSize
                    height: iconSize
                    fontFamily: root.fontFamily
                    champInfo: champInfos[pri.champInfosKeys[index]]
                    onClicked: root.clicked(id)
                    iconDirPath: root.imgDirPath
                }
            }
        }
    }




}
