import QtQuick 2.12
import QtQuick.Controls 2.5
import QtQuick.Layouts 1.0
import Riot 1.0
import 'Components'
import 'Fonts'
import QtWebEngine 1.8
import Clipboard 1.0

MainWindow {
    id: window
    title: qsTr("OPGG Add-on (made by 청산가리중독자)")
    color: '#222222'
//    titleColor: '#88000000'
    minimumHeight: 850
    minimumWidth: 1350
    width: 1350
    height: 850
    borderColor: '#000000'
    borderWidth: 1

    property WebEngineView webView: null

    Fonts { id: fonts; }
    PushPopup { id: push; fontFamily: fonts.nanumR }

    Component.onCompleted: {
        if (!supportSsl)
            push.show('SSL 오류 발생', sslVersion, 10000)
    }

    titleItem: TitleBar {
        Clipboard { id:clip; }
        onClickedHome: webView.url = 'https://www.op.gg/'
        onClickedNext: webView.goForward()
        onClickedPrevious: webView.goBack()
        onClickedRefrash: webView.reload()
        onClickedSummoner: webView.url = 'https://www.op.gg/summoner/userName=' + name
        onClickedCopy: {
            clip.setText(String(webView.url))
            push.show(qsTr('링크 복사'),qsTr('현재 페이지의 링크가 클립보드에 복사되었습니다.\n\n(%1)').arg(String(webView.url)),3000)
        }
    }


    content: Item {
        Popup {
            id: info
            closePolicy: Popup.CloseOnReleaseOutside
            anchors.centerIn: parent
            width: 400
            height: 400
        }

        RowLayout {
            anchors.fill: parent
            spacing: 0
            ColumnLayout {
                visible: teams.champCount
                Layout.fillHeight: true
                Layout.maximumWidth: 220
                Layout.minimumWidth: 220
                Repeater {
                    id: teams
                    model: 2
                    property int champCount: {
                        let result = 0
                        for (var i = 0; i < count; ++i) { result += itemAt(i).count }
                        return result
                    }

                    function releaseChampSelectViews() { for (var i = 0; i < count; ++i) itemAt(i).releaseChampSelectView(); }
                    function releaseGameSessionViews() { for (var i = 0; i < count; ++i) itemAt(i).releaseGameSessionView(); }
                    function clearViews() { for (var i = 0; i < count; ++i) itemAt(i).clear(); }

                    ChampSelectView {
                        iconDirPath: dragon.getDataDragonPath() + '/' + dragon.version + '/img'
                        allChampInfos: dragon.allChampionsInfo
                        Layout.fillHeight: true
                        Layout.fillWidth: true
                        fontFamily: fonts.nanumR
                        riotLCU: lcu
                        team: index === 0 ? 'myTeam' : 'theirTeam'
                        onClickedChampIcon: webView.url = 'https://www.op.gg/champion/' + id.toLowerCase()
                        onClickedSummonerName: webView.url = 'https://www.op.gg/summoner/userName=' + name
                        onClickedMultySearch: {
                            webView.multiSearchNames = names
                            webView.url = 'https://www.op.gg/multi/query=' + names.join(',')
                        }
                    }
                }

                Timer {
                    running: challenge.currentGameflowState === LCU.ChampSelect; repeat: true; interval: 500
                    onTriggered: teams.releaseChampSelectViews()
                }
                Connections {
                    target: challenge
                    onCurrentGameflowStateChanged: {
                        switch(challenge.currentGameflowState) {
                        case LCU.ChampSelect:
                            teams.releaseChampSelectViews()
                            break;
                        case LCU.InProgress:
                            teams.releaseGameSessionViews()
                            break;
                        case LCU.Reconnect:
                            break;
                        case LCU.EndOfGame:
                            break;
                        case LCU.PreEndOfGame:
                            break;
                        case LCU.WaitingForStats:
                            break;
                        default:
                            teams.clearViews()
                            break;
                        }
                    }
                }
            }

            WebViewForOPGG {
                id: webView
                Layout.fillHeight: true
                Layout.fillWidth: true
                Component.onCompleted: window.webView = this
                fontFamily: fonts.nanumR
                eventPush: push
                onDownloadComplated: {
                    if (obs.isObserverFile(path)) {
                        obs.runProcess(path, function(exitCode){
                            if (exitCode !== 0) {
                                push.show(qsTr('오류'), qsTr('관전 파일 실행 실패'))
                            }
                            obs.removeFile(path)
                        })
                    }
                }

                Connections {
                    target: challenge
                    onCurrentGameflowStateChanged: {
                        switch(challenge.currentGameflowState) {
                        case LCU.ChampSelect:
                            lcu.getChampSelectSession(function(object, err, errStr){
                                if (object === null) return

                                var summonerIds = new Array

                                var allPlayers = object.myTeam.concat(object.theirTeam)

                                for (let i in allPlayers) {
                                    if (allPlayers[i] === null || allPlayers[i].summonerId === 0) continue
                                    summonerIds.push(allPlayers[i].summonerId)
                                }

                                if (summonerIds.length === 0) return

                                lcu.getSummonersByIds(summonerIds, function(array, err, errStr){
                                    if (array.length === 0) return

                                    var summonerNames = new Array

                                    for (let i in array)
                                        summonerNames.push(array[i].displayName)


                                    webView.multiSearchNames = summonerNames
                                    webView.url = 'https://www.op.gg/multi/query=' + summonerNames.join(',')
                                })
                            })
                            break;
                        case LCU.InProgress:
                            lcu.getGameSession(function(object, err, errStr){
                                if (object === null) return

                                var summonerNames = new Array
                                var reverse = false
                                var t2 = object.gameData.teamTwo
                                for (var i in t2) {
                                    if (challenge.currentSummoner.displayName !== undefined && t2[i].summonerName === challenge.currentSummoner.displayName) {
                                        reverse = true
                                        break
                                    }
                                }

                                var team = reverse ? object.gameData.teamOne : t2

                                for (var ii in team) {
                                    var player = team[ii]
                                    if (player.summonerInternalName.split('_')[0] === 'bot') continue
                                    summonerNames.push(player.summonerName)
                                }

                                if (summonerNames.length === 0) return

                                webView.multiSearchNames = summonerNames
                                webView.url = 'https://www.op.gg/multi/query=' + summonerNames.join(',')
                            })
                            break;
                        default:
                            break;
                        }
                    }
                }
            }
        }
    }
}
