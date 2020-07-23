import QtQuick 2.12
import QtQuick.Controls 2.15
import QtQuick.Layouts 1.15
import Riot 1.0
import 'Components'
import 'Fonts'
import 'Pages'
import QtWebEngine 1.10
import Clipboard 1.0
import Qt.labs.settings 1.1

MainWindow {
    id: window

    Connections {
        target: challenge
        function onCurrentSummonerChanged() {
            if (Object.keys(challenge.currentSummoner).length)
                lcu.getClientRegion(function(object,err,errStr){
                    if (err === 0)
                        if (JSON.stringify(settings.region) !== JSON.stringify(object)) {
                            settings.region = object
                        }
                })
        }
    }

    Connections {
        target: lcu
        function onErrorOccurred() {
            switch(lcu.error) {
            case LCU.NotRunningLeagueClient:
                push.show(qsTr('LOL 클라이언트가 실행중이 아닙니다.'), qsTr('LOL 클라이언트가 실행되었나요?.'), 5000)
                break;
            case LCU.LackOfAuthority:
                askPopup.askRestartAdministrator()
                break;
            case LCU.NotFoundLockfile:
                push.show(qsTr('[오류:101] NotFoundLockFile'), qsTr('클라이언트와 연동이 안된다면 개발자에게 문의하여주세요.'), 15000)
                break;
            case LCU.LockfileOpenFailed:
                push.show(qsTr('[오류:102] LockfileOpenFailed'), qsTr('클라이언트와 연동이 안된다면 개발자에게 문의하여주세요.'), 15000)
                break;
            case LCU.LockfileParseError:
                push.show(qsTr('[오류:103] LockfileParseError'), qsTr('클라이언트와 연동이 안된다면 개발자에게 문의하여주세요.'), 15000)
                break;
            }
        }
    }

    Connections {
        target: updateTool
        function onHasUpdateChanged(hasUpdate) {
            if (hasUpdate) askPopup.askUpdate()
        }
    }

    readonly property string opggURL: {
        var webRegion = settings.region === undefined ? 'www' : settings.region.webRegion
        return 'https://' + webRegion + '.op.gg'
    }

    onOpggURLChanged: {
        webView.url = opggURL
        console.log('OPGG URL Changed :', opggURL)
    }
    title: qsTr("OPGG Add-on (made by 청산가리중독자)")
    color: '#222222'
//    titleColor: '#88000000'
    minimumHeight: 600
    minimumWidth: 1000
    width: 1200
    height: 800
    borderColor: '#000000'
    borderWidth: 1

    property Item titlew: null
    property Repeater teams: null
    property WebEngineView webView: null
    property SettingsPopup settingsPopup: null
    property Settings settings: null

    Fonts { id: fonts; }
    PushPopup { id: push; fontFamily: fonts.nanumR }
    AskPopup {
        id: askPopup
        width: 500
        function askUpdate() {
            acceptButton.text = qsTr('업데이트')
            acceptButton.contentItem.color = '#ff0000'
            acceptButton.background.border.color = '#ff0000'
            closeButton.text = qsTr('나중에')
            show(qsTr('새로운 업데이트가 있습니다.'),
                 qsTr('지금 업데이트 하시겠습니까?\n[설정] > [업데이트]에서 수동 업데이트도 가능합니다.'),
                 function(accept){
                     if (accept) updateTool.startUpdate()
                 })
        }

        function askRestartAdministrator() {
            acceptButton.text = qsTr('재시작')
            acceptButton.contentItem.color = '#ff0000'
            acceptButton.background.border.color = '#ff0000'
            closeButton.text = qsTr('아니오')
            show(qsTr('관리자 권한으로 실행'),
                 qsTr('LOL 클라이언트가 관리자 권한으로 실행되었기 때문에 이 프로그램도 관리자 권한으로 실행되어야 원활한 동작이 가능합니다.'),
                 function(accept){
                     if (accept) challenge.restartAdministrator()
                 })
        }
        Component.onCompleted: {

        }
    }

    titleItem: TitleBar {
        id: title
        Component.onCompleted: {
            window.titlew = this
        }

        Clipboard { id:clip; }
        onClickedHome: webView.url = opggURL
        onClickedNext: webView.goForward()
        onClickedPrevious: webView.goBack()
        onClickedRefrash: webView.reload()
        onClickedSummoner: webView.url = opggURL + '/summoner/userName=' + name
        onClickedSetting: settingsPopup.open()
        onClickedCopy: {
            clip.setText(String(webView.url))
            push.show(qsTr('링크 복사'),qsTr('현재 페이지의 링크가 클립보드에 복사되었습니다.\n\n(%1)').arg(String(webView.url)),3000)
        }
    }

    content: Item {
        SettingsPopup {
            id: settingsPopup
            Component.onCompleted: window.settingsPopup = this
            Settings {
                id: settings
                property bool inChampSessionAction: true // true:픽창 진입시 아군 멀티서치
                property bool inGameSessionAction: true // true:인게임 진입시 적군 멀티서치
                property bool selectionChampAction: false // true:챔피언 선택시 OP.GG 챔피언 페이지로 이동
                property var region
                onRegionChanged: {
                    console.info('Region Chagned :', JSON.stringify(region))
                }
                Component.onCompleted: window.settings = this
            }
        }
        Shortcut { sequence: 'F1'; onActivated: {
                var view = teams.itemAt(0)
                if (view.count > 0) {
                    webView.multiSearch(view.getEnableSummonerNames())
                }
            }
        }
        Shortcut { sequence: 'F2'; onActivated: {
                var view = teams.itemAt(1)
                if (view.count > 0) {
                    webView.multiSearch(view.getEnableSummonerNames())
                }
            }
        }
        Shortcut { sequence: 'F3'; onActivated:  webView.url = opggURL+ '/summoner/userName=' + challenge.currentSummoner.displayName }
        Shortcut { sequence: 'F4'; onActivated:  { // 자신이 픽창으로 선택한 챔피언 분석 페이지로 이동
                var view = teams.itemAt(0)
                for (var i = 0; i < view.count; ++i) {
                    var element = view.itemAt(i)
                    if (element.summonerName === challenge.currentSummoner.displayName && element.champInfo !== null) {
                        webView.url = opggURL + '/champion/' + element.champInfo.id.toLowerCase()
                        break;
                    }
                }
            }
        }

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
            Rectangle {
                id: champViewBg
                Layout.alignment: Qt.AlignTop
                Layout.fillHeight: true
                Layout.preferredWidth: 230
                visible: teams.champCount
                color: '#303030'
                Rectangle { anchors.right: parent.right; height: parent.height; width: 1; color: '#000000'; }
                Column {
                    anchors.top: parent.top
                    anchors.left: parent.left
                    anchors.right: parent.right
                    id: champViewLayout
                    spacing: 20
                    Repeater {
                        Component.onCompleted: window.teams = this
                        id: teams
                        model: 2

                        readonly property int champCount: {
                            let result = 0
                            for (var i = 0; i < count; ++i) { result += itemAt(i).count }
                            return result
                        }



                        function releaseChampSelectViews() { for (var i = 0; i < count; ++i) itemAt(i).releaseChampSelectView(); }
                        function releaseGameSessionViews() { for (var i = 0; i < count; ++i) itemAt(i).releaseGameSessionView(); }
                        function clearViews() { for (var i = 0; i < count; ++i) itemAt(i).clear(); }

                        ChampSelectView {
                            iconDirPath: {
                                if (dragon == null) return ''
                                return dragon.getDataDragonPath() + '/' + dragon.version + '/img'
                            }
                            allChampInfos: {
                                if (dragon == null) return []
                                dragon.allChampionsInfo
                            }
                            anchors.left: parent.left
                            anchors.right: parent.right
                            fontFamily: fonts.nanumR
                            riotLCU: lcu
                            team: index === 0 ? 'myTeam' : 'theirTeam'
                            onClickedChampIcon: webView.url = opggURL + '/champion/' + id.toLowerCase()
                            onClickedSummonerName: webView.url = opggURL + '/summoner/userName=' + name
                            onClickedMultySearch: webView.multiSearch(names)
                            onComplateChanged: {
                                if (!settings.selectionChampAction)
                                    return
                                if (element.summonerName === challenge.currentSummoner.displayName && element.champInfo !== null && element.complate) {
                                    webView.url = opggURL + '/champion/' + element.champInfo.id.toLowerCase()
                                }
                            }
                            onContentHeightChanged: {
                                let sum = 0
                                for (var i = 0; i < teams.count; ++i) {
                                    const item = teams.itemAt(i)
                                    sum += item === null ? 0 : item.contentHeight
                                }
                                const maximum = Math.max(window.minimumHeight, sum + 100, window.height)
                                window.height = maximum
                            }
                        }
                    }

                    Timer {
                        running: {
                            if (challenge == null) return false
                            return challenge.currentGameflowState === LCU.ChampSelect;
                        }
                        repeat: true; interval: 1000
                        onTriggered: {
                            if (challenge == null) return
                            switch(challenge.currentGameflowState) {
                            case LCU.ChampSelect:
                                teams.releaseChampSelectViews()
                                break;
                            case LCU.InProgress:

                                break;
                            default:
                                break;
                            }

                        }
                    }
                    Connections {
                        target: challenge
                        function onCurrentGameflowStateChanged() {
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
            }


            WebViewForOPGG {
                id: webView
//                visible: false
                zoomFactor: 0.9
                Layout.fillHeight: true
                Layout.fillWidth: true
                Component.onCompleted: {
                    window.webView = this
                    url = opggURL
                }
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
                    function onCurrentGameflowStateChanged() {
                        switch(challenge.currentGameflowState) {
                        case LCU.ChampSelect:
                            if (!settings.inChampSessionAction) break;
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

                                    webView.multiSearch(summonerNames)
                                })
                            })
                            break;
                        case LCU.InProgress:
                            if (!settings.inGameSessionAction) break;
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

                                webView.multiSearch(summonerNames)
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
