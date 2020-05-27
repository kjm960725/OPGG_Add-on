import QtQuick 2.12
import QtWebEngine 1.8
import QtQuick.Controls 2.12
import Riot 1.0
import Clipboard 1.0

WebEngineView {
    id: root
    property PushPopup eventPush: PushPopup { fontFamily: root.fontFamily }
    property string fontFamily: ''
    property var multiSearchNames: new Array


    signal downloadStarted(var path)
    signal downloadComplated(var path)

    function sortMultiSearchSummoner(summonerNames) {
        if (summonerNames.length < 1 || loading || !String(url).includes('www.op.gg/multi/query=')) return
        runJavaScript(challenge.readFile(':/WebScrapyScripts/MultiSearchSort.js.txt').replace("_sortNameArgs", JSON.stringify(summonerNames)), function(result){})
    }

    function getPerkPagesFromHtml(callback){
        runJavaScript(challenge.readFile(':/WebScrapyScripts/GetPerkPages.js.txt'), function(data){
            var result = new Array
            var array = JSON.parse(data)
            for (var object of array) {
                const nameArg = object.name.split(':')
                let typeName = nameArg[nameArg.length - 1]
                const priStyleId = Number(object.primaryStyleId)
                const priPerkId = Number(object.selectedPerkIds[0])
                for (var style of dragon.allRunesInfo) {
                    if (style.id === priStyleId) {
                        for (var rune of style.slots[0].runes) {
                            if (rune.id === priPerkId) {
                                const typeNameSplit = typeName.split('+')
                                typeName = rune.name.replace(/(\s)*/g,'') + '+' + typeNameSplit[1]
                                break;
                            }
                        }
                        break;
                    }
                }
                nameArg[nameArg.length - 1] = typeName
                object.name = nameArg.join(':')
                result.push(object)
            }
            callback(result)
        })
    }

    onNewViewRequested: { url = request.requestedUrl }
    onJavaScriptConsoleMessage: {} // disable web console output
    onLoadingChanged: {
        if (!loading) {
            const urlStr = url.toString()
            if (urlStr.includes('www.op.gg')) {
                if (urlStr.includes('multi/query=')) {
                    sortMultiSearchSummoner(multiSearchNames)
                }
            }

        }
    }
    url: "https://www.op.gg/"
    profile: WebEngineProfile {
        httpAcceptLanguage: 'ko-KR'
        onDownloadRequested: {
            download.accept()
            eventPush.show(qsTr('파일을 다운로드하고 있습니다.'), qsTr('다운로드 경로 : %1').arg(download.path), 10000)
            downloadStarted(download.path)
        }
        onDownloadFinished: {
            switch(download.state) {
            case WebEngineDownloadItem.DownloadCompleted :
                eventPush.show(qsTr('파일 다운로드 완료'), '', 10000)
                downloadComplated(download.path)
                break;
            default:
                break;
            }
        }
    }

    Shortcut { sequence: 'Ctrl+C';  onActivated: action(WebEngineView.Copy).trigger(); }
    Shortcut { sequence: 'F5'; onActivated: reload(); }
    Shortcut { sequences: [StandardKey.Back, 'Alt']; onActivated: goBack(); }
    Shortcut { sequences: [StandardKey.Forward, 'Alt']; onActivated: goForward(); }
    BusyIndicator {
        width: 70
        height: 70
        z: 1
        running: loading
        anchors.centerIn: parent
    }

    Row {
        Timer {
            id :getPerkRepeatTimer
            running: false
            repeat: true
            interval: 200
            triggeredOnStart: true
            onTriggered: {
                getPerkPagesFromHtml(function(array){
                    perkPageCopyItemLayout.perkPages = array
                    if (array.length > 0)
                        running = false
                })
            }
        }

        id: perkPageCopyItemLayout

        property var perkPages: new Array

        height: 70
        z: 1
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.bottom: parent.bottom
        anchors.bottomMargin: 5
        spacing: 5
        visible: {
            if (!loading){
                if (url.toString().search(/op.gg\/(champion|urf)\/[a-zA-Z]*\/statistics/g) > -1) {
                    perkPageCopyItemLayout.perkPages = []
                    getPerkRepeatTimer.start()
                    return true;
                }
            }
            return false
        }

        Repeater {
            model: perkPageCopyItemLayout.perkPages.length

            Item {
                Behavior on scale { NumberAnimation { duration: 50 } }
                id: perkPageCopyItem
                width: 180
                height: perkPageCopyItemLayout.height
                scale: perkPageCopyArea.pressed ? 0.9 : 1
                MouseArea {
                    id: perkPageCopyArea
                    anchors.fill: parent
                    hoverEnabled: true
                    onClicked: {
                        if (!lcu.isConnected) {
                            push.show(qsTr('[오류] 룬 복사 실패'), qsTr('먼저, 롤 클라이언트를 실행해주세요.'), 5000)
                            return
                        }

                        var object = perkPageCopyItemLayout.perkPages[index]
                        object['current'] = true
                        lcu.putPerkPage(object,function(err, errStr){
                            if (err === 0) {
                                push.show(qsTr('룬 복사 성공'),qsTr('"%1" 룬페이지가 클라이언트에 저장되었으며, 현재 룬페이지로 설정되었습니다.').arg(object.name), 3000)
                            } else {
                                if (err === 110) errStr = qsTr('룬 페이지가 꽉 차 있습니다. 페이지 하나를 비워주세요.')
                                push.show(qsTr('[오류] 룬 복사 실패'), errStr, 5000)
                            }
                        })
                    }
                }
                Rectangle {
                    Behavior on opacity { NumberAnimation { duration: 50 } }
                    id: perkPageCopyBg
                    opacity: perkPageCopyArea.containsMouse ? 1 : 0.9
                    anchors.fill: parent
                    radius: 5
                    color: '#444444'
                    border.width: 1
                    border.color: '#000000'
                }

                Text {
                    Behavior on opacity { NumberAnimation { duration: 50 } }
                    id: perkPageCopyText
                    opacity: 1
                    anchors.horizontalCenter: parent.horizontalCenter
                    anchors.verticalCenter: parent.verticalCenter
                    font.family: fontFamily
                    color: '#ffffff'
                    font.pixelSize: 16
                    style: Text.Outline
                    horizontalAlignment: Text.AlignHCenter
                    lineHeight: 1.3
                    text: {
                        const object = perkPageCopyItemLayout.perkPages[index]
                        const nameArg = object.name.split(':')
                        let typeName = nameArg[nameArg.length - 1]
                        return qsTr('%1번 룬복사\n%2').arg(index + 1).arg(typeName)
                    }
                }
            }
        }
    }
}
