import QtQuick 2.0

Rectangle {
    id: root
    property string fontFamily
    property alias champInfo: champ.champInfo
    property alias iconDirPath: champ.iconDirPath
    property string position
    property string summonerName
    property bool summonerEnalbe: false
    property bool complate: false
    property bool inProgress: false
    property bool isAllyAction: false

    property var summonerChampsRateInfo: {
        if (root.summonerEnalbe) challenge.getChampRateByOPGG(root.summonerName, function(object){
            summonerChampsRateInfo = object
        })
        return null
    }
    property var champRateInfo: {
        if (champInfo === null || summonerChampsRateInfo === null || !summonerChampsRateInfo.success) return null
        for (var obj of summonerChampsRateInfo.data) {
            if (String(champInfo.id).toLowerCase() === String(obj.id).toLowerCase()) {
                return obj
            }
        }
        return null
    }
    property bool hasChampRate: champRateInfo !== null

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
                    color: summonerNameArea.containsMouse ? '#ff4444' : '#ffff44'
                    font.pixelSize: 14
                    style: Text.Outline
                    text: root.summonerName
                }
            }
            Text {
                id: champRate
                font.family: fontFamily
                color: {
                    if (summonerChampsRateInfo !== null && !summonerChampsRateInfo.success && summonerEnalbe) return '#ff4444'
                    else if (!hasChampRate) return '#ffffff'
                    else if (champRateInfo.win + champRateInfo.lose >= 10) {
                        var ratePer = Math.round(champRateInfo.win / (champRateInfo.win+champRateInfo.lose)*100)
                        var kda = Number(champRateInfo.kda)
                        if (ratePer <= 40 || kda < 2)
                            return '#ff4444'
                        else if (ratePer >= 60 || kda >= 4)
                            return '#ffff44';

                    }
                    return '#ffffff'
                }
                font.pixelSize: 12
                text: {
                    if (summonerChampsRateInfo !== null && !summonerChampsRateInfo.success && summonerEnalbe)
                        return qsTr('전적 조회 오류')
                    else if (hasChampRate) {
                        return qsTr('%1판/%2%/KDA(%3)')
                                .arg(champRateInfo.win + champRateInfo.lose)
                                .arg(Math.round(champRateInfo.win / (champRateInfo.win+champRateInfo.lose)*100))
                                .arg(champRateInfo.kda)

                    } else if (champInfo !== null) {
                        return qsTr('플레이 전적 없음')
                    }
                    return ''
                }
            }

        }
    }

}
