import QtQuick 2.4
import Riot 1.0
Item {
    id: root
    property var session: null
    property var inGameSession: null
    property var allChampInfos: null
    property string fontFamily
    property string iconDirPath
    property string team: 'myTeam'
    property LCU riotLCU: null
    readonly property int count: teamRepeater.count
    readonly property int contentHeight: col.height
    property Component background: null

    Loader {
        anchors.fill: parent
        sourceComponent: background
    }

    property var gameSessionTeamMap: {
        'myTeam'    : 'teamOne',
        'theirTeam' : 'teamTwo'
    }

    signal clickedSummonerName(var name)
    signal clickedChampIcon(var id)
    signal clickedMultySearch(var names)

    // Element Signals
    signal complateChanged(var element)
    signal inProgressChanged(var element)
    signal champInfoChanged(var element)

    width: 220
    height: contentHeight
    visible: count > 0

    function itemAt(index) { return teamRepeater.itemAt(index) }

    function clear() {
        session = null
        inGameSession = null
    }

    function getEnableSummonerNames() {
        var result = new Array
        for (var i = 0; i < count; ++i) {
            var item = teamRepeater.itemAt(i)
            if (item.summonerEnalbe)
                result.push(item.summonerName)
        }
        return result
    }

    function releaseChampSelectView() {
        riotLCU.getChampSelectSession(function(object, err, errStr){
            if (err === 0) {
                root.inGameSession = null

                if (JSON.stringify(root.session) !== JSON.stringify(object))
                    root.session = object
            }
        })
    }
    function releaseGameSessionView() {
        riotLCU.getGameSession(function(object, err, errStr) {
            if (err === 0) {
                var reverse = false
                var t2 = object.gameData.teamTwo
                for (var i in t2) {
                    if (challenge.currentSummoner.displayName !== undefined && t2[i].summonerName === challenge.currentSummoner.displayName) {
                        reverse = true
                        break
                    }
                }
                root.session = null
                gameSessionTeamMap = {
                    'myTeam'    : reverse ? 'teamTwo' : 'teamOne',
                    'theirTeam' : reverse ? 'teamOne' : 'teamTwo'
                }
                root.inGameSession = object.gameData
            }
        })
    }

    function findPickAction(cellId) {
        var actionsCol = session.actions
        for (var col in actionsCol) {
            var actionsRow = actionsCol[col]
            for (var row in actionsRow) {
                var action = actionsRow[row]
                if (action.type === 'pick' && action.actorCellId === cellId)
                    return action
            }
        }
        return null
    }
    Column {
        id: col
        anchors.left: parent.left
        anchors.right: parent.right
        spacing: 1

        Item {
            anchors.left: parent.left
            anchors.right: parent.right
            height: 30
            id: teamItem
            MouseArea {
                id: teamArea
                anchors.fill: parent
                hoverEnabled: true
                onClicked: {
                    root.clickedMultySearch(getEnableSummonerNames())
                }
            }

            Rectangle {
                id: teamBg
                anchors.fill: parent
                color: teamArea.containsMouse ? '#88ffffff' : '#00ffffff'
                border.width: 0
            }

            Text {
                id: teamText
                anchors.verticalCenter: parent.verticalCenter
                anchors.horizontalCenter: parent.horizontalCenter
                font.family: fontFamily
                font.pixelSize: 18
                color: '#ffffff'
                style: Text.Outline
                text: team === 'myTeam' ? qsTr('아군 팀') : qsTr('상대 팀')
                scale: teamArea.pressed ? 0.9 : 1
                Behavior on scale { NumberAnimation { duration: 50 } }
            }
        }

        Repeater {
            id: teamRepeater
            model: session !== null && session[team] !== null
                        ? session[team].length
                        : inGameSession !== null && inGameSession[gameSessionTeamMap[team]] !== null
                                ? inGameSession[gameSessionTeamMap[team]].length
                                : 0

            ChampSelectElement {
                anchors.left: parent.left
                anchors.right: parent.right
                anchors.leftMargin: 10
                anchors.rightMargin: 10
                fontFamily: root.fontFamily
                iconDirPath: root.iconDirPath
                radius: 10
                border.width: !complate && inProgress ? 1 : 0
                champInfo: {
                    var selectChampId = 0;
                    if (session !== null && session[team] !== null) {
                        var cellId = session[team][index].cellId
                        var action = findPickAction(cellId)
                        selectChampId = action === null ? session[team][index].championId : action.championId

                    } else if (inGameSession !== null && inGameSession[gameSessionTeamMap[team]] !== null) {
                        var teamObj = inGameSession[gameSessionTeamMap[team]]
                        var split = teamObj[index].summonerInternalName.split('_')
                        if (split.length === 3 && split[0] === 'bot') {
                            selectChampId = allChampInfos[split[1]].key
                        } else {
                            var champSelections = inGameSession.playerChampionSelections
                            for (var i = 0; i < champSelections.length; ++i) {
                                if (champSelections[i].summonerInternalName === teamObj[index].summonerInternalName) {
                                    selectChampId = champSelections[i].championId
                                    break
                                }
                            }
                        }
                    }
                    if (selectChampId === 0) return null
                    const champKeys = Object.keys(allChampInfos)
                    for (var key in allChampInfos) {
                        if (Number(allChampInfos[key].key) === Number(selectChampId)) {
                            return allChampInfos[key]
                        }
                    }
                    return null
                }
                onChampInfoChanged: root.champInfoChanged(this)
                complate: {
                    if (session !== null && session[team] !== null) {
                        var action = findPickAction(session[team][index].cellId)
                        return action === null ? true : action.completed
                    }
                    return true
                }
                onComplateChanged: root.complateChanged(this)
                inProgress: {
                    if (session !== null && session[team] !== null) {
                        var action = findPickAction(session[team][index].cellId)
                        return action === null ? false : action.isInProgress
                    }
                    return false
                }
                onInProgressChanged: root.inProgressChanged(this)
                isAllyAction: {
                    if (session !== null && session[team] !== null) {
                        var action = findPickAction(session[team][index].cellId)
                        return action === null ? false : action.isAllyAction
                    }
                    return false
                }

                position: {
                    var posi
                    if (session !== null && session[team] !== null) {
                        posi = session[team][index].assignedPosition

                    } else if (inGameSession !== null && inGameSession[gameSessionTeamMap[team]] !== null) {
                        posi = inGameSession[gameSessionTeamMap[team]][index].selectedPosition
                    }
                    if (posi === null || posi === undefined) return ''
                    switch (posi.toLowerCase()) {
                    case 'jungle': return qsTr('정글')
                    case 'middle': return qsTr('미드')
                    case 'bottom': return qsTr('원딜')
                    case 'top': return qsTr('탑')
                    case 'utility': return qsTr('서포터')
                    default: return ''
                    }
                }
                Component.onCompleted:  {
                    if (session !== null && session[team] !== null) {
                        if (Number(session[team][index].summonerId) === 0) {
                            teamRepeater.itemAt(index).summonerName = qsTr('소환사 %1').arg(index+1)
                            teamRepeater.itemAt(index).summonerEnalbe = false
                        } else {
                            var ids = new Array
                            ids.push(session[team][index].summonerId)
                            riotLCU.getSummonersByIds(ids, function(array, err, errStr){
                                if (array.length === 0) return
                                teamRepeater.itemAt(index).summonerName = array[0].displayName
                                teamRepeater.itemAt(index).summonerEnalbe = true
                            })
                        }

                    } else if (inGameSession !== null && inGameSession[gameSessionTeamMap[team]] !== null) {
                        if (inGameSession[gameSessionTeamMap[team]][index].summonerId === undefined) {
                            teamRepeater.itemAt(index).summonerName = qsTr('%1 봇').arg(allChampInfos[inGameSession[gameSessionTeamMap[team]][index].summonerInternalName.split('_')[1]].name)
                            teamRepeater.itemAt(index).summonerEnalbe = false
                        } else {
                            teamRepeater.itemAt(index).summonerName = inGameSession[gameSessionTeamMap[team]][index].summonerName;
                            teamRepeater.itemAt(index).summonerEnalbe = true
                        }
                    }
                }

                onClickedChampIcon: root.clickedChampIcon(id)
                onClickedSummonerName: root.clickedSummonerName(name)
            }
        }
    }

}
