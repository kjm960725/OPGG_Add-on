import QtQuick 2.0

Rectangle {
    id: root
    property string fontFamily
    property alias champInfo: champ.champInfo
    property alias iconDirPath: champ.iconDirPath
    property string position
    property string summonerName
    property bool summonerEnalbe: true
    property bool complate: false
    property bool inProgress: false
    property bool isAllyAction: false

    property var summonorInfo: null
//    {
//        'champPlayCount' : 0,
//        'winRate' : 0.00,
//    }


    signal clickedSummonerName(var name)
    signal clickedChampIcon(var id)


    color: '#00000000'
    border.width: !complate && inProgress ? 2 : 1
    border.color: !complate && inProgress ? '#ffff00' : '#ffffff'
    width: 200
    height: 70
    radius: 10

    Row {
        anchors.verticalCenter: parent.verticalCenter
        anchors.left: parent.left
        anchors.leftMargin: 10
        anchors.right: parent.right
        anchors.rightMargin: 10
        spacing: 10
        ChampIcon {
            id: champ
            width: height
            height: root.height * 0.9
            radius: Math.min(width, height) / 2
            fontFamily: root.fontFamily
            nullText: (!complate) && inProgress ? qsTr('선택중') : String()
            onClicked: clickedChampIcon(id)
        }

        Column {
            anchors.verticalCenter: parent.verticalCenter
            spacing: 5
            Text {
                id: position
                font.family: fontFamily
                color: "#ffffff"
                font.pixelSize: 12
                text: root.position
            }
            Item {
                Behavior on scale { NumberAnimation { duration: 50 } }
                id: summonerName
                width: summonerNameText.width
                height: summonerNameText.height
                scale: summonerNameArea.pressed ? 0.9 : 1
                visible: summonerNameText.text.length > 0
                MouseArea {
                    id: summonerNameArea
                    anchors.fill: parent
                    hoverEnabled: true
                    onClicked: clickedSummonerName(summonerNameText.text)
                    enabled: summonerEnalbe
                }

                Text {
                    id: summonerNameText
                    font.family: fontFamily
                    color: summonerNameArea.containsMouse ? '#ff2222' : '#ffffff'
                    font.pixelSize: 14
                    style: Text.Outline
                    text: root.summonerName
                }
            }
            Text {
                id: notice
                font.family: fontFamily
                color: !complate && inProgress ? '#ffff00' : '#ffffff'
                font.pixelSize: 12
                text: !complate && inProgress ? qsTr('선택중...') : ''
            }

        }
    }

}
