import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Layouts 1.15

Item {
    width: 800
    height: 600

    ListView {

        id: listView
        anchors.fill: parent
        header: Column {
            width: parent.width
            spacing: 10
            Text {
                text: qsTr('자주 묻는 질문')
                width: parent.width
                height: contentHeight + 10
                verticalAlignment: Text.AlignVCenter
                horizontalAlignment: Text.AlignHCenter
                wrapMode: Text.WrapAnywhere
                font.family: fonts.nanumB
                font.pixelSize: 28
                color: '#eeeeee'
            }
            Rectangle {
                width: parent.width
                height: 1
                color: '#ffffff'
            }
        }

        delegate: Item {
            anchors.left: parent.left
            anchors.right: parent.right
            height: layout.height
            property bool showAnswer: false

            Rectangle {
                Behavior on opacity { NumberAnimation { duration: 40 } }
                opacity: {
                    if (mouseArea.containsPress) {
                        return 0.6
                    } else if (mouseArea.containsMouse || showAnswer) {
                        return 0.3
                    } else {
                        const isEven = index % 2 == 0
                        return isEven ? 0.1 : 0
                    }
                }
                color: '#ffffff';
                anchors.fill: parent
            }

            MouseArea {
                id: mouseArea
                hoverEnabled: true
                anchors.fill: parent
                onClicked: showAnswer = showAnswer ? false : true
            }

            Column {
                id: layout
                anchors.left: parent.left
                anchors.right: parent.right
                spacing: 0
                Text {
                    text: question
                    width: parent.width
                    height: contentHeight + 30
                    verticalAlignment: Text.AlignVCenter
                    wrapMode: Text.WrapAnywhere
                    font.family: fonts.nanumB
                    font.pixelSize: 18
                    color: '#eeeeee'
                    leftPadding: 10
                }
                Rectangle {
                    Behavior on height { NumberAnimation { duration: 100 } }
                    width: parent.width
                    height: an.height
                    color: '#88ffffff'
                    clip: true
                    Text {
                        id: an
                        text: answer
                        anchors.verticalCenter: parent.verticalCenter
                        width: parent.width
                        height: showAnswer ? an.contentHeight + 20 : 0
                        verticalAlignment: Text.AlignVCenter
                        wrapMode: Text.WrapAnywhere
                        font.family: fonts.nanumB
                        lineHeight: 1.2
                        font.pixelSize: 14
                        color: '#000000'
                        leftPadding: 15
                        onLinkActivated: Qt.openUrlExternally(link)
                    }
                }

                Rectangle {
                    width: parent.width
                    height: 1
                    color: '#ffffff'
                }
            }
        }
        Component.onCompleted: {
            model.append({'question': qsTr("이 프로그램으로 인해 제제를 받을 수 있나요?"),
                          'answer': qsTr("이 프로그램은 롤 공식 API를 사용 사용했으며, 유사한 프로그램인 Blitz와 동일한 방식입니다. 이 프로그램이 정지먹었다면, Blitz를 사용하는 수 많은 전세계 유저들은 진작에 대량으로 정지먹고도 남았습니다.")})
            model.append({'question': qsTr("칼바람/우르프도 연동이 되나요?"),
                          'answer': qsTr("둘다 연동이 되지만, 최적화되어 있지는 않습니다. 일반게임, 랭크게임에 초점이 맞추어져 있습니다.")})
            model.append({'question': qsTr("향후 TFT 연동 계획이 있나요?"),
                          'answer': qsTr("계획은 있지만 우선 순위는 낮아 향후 지원될 예정입니다.")})
            model.append({'question': qsTr("해외 서버도 연동이 되나요?"),
                          'answer':  qsTr("네. 롤 로그인시, 서버 지역을 감지하여 OP.GG와 자동 연동됩니다.")})
            model.append({'question': qsTr("단축키 목록"),
                          'answer':  qsTr('F1: 아군 팀 [멀티 서치]\nF2: 적군 팀 [멀티 서치]\nF3: 자기 자신 [전적 검색]\nF4: 픽한 [챔피언 분석] 페이지로 이동')})
            model.append({'question': qsTr("업데이트는 어떻게하나요?"),
                          'answer':  qsTr('새로운 업데이트가 있을경우 자동으로 감지후 업데이트 여부를 확인합니다.')})
            model.append({'question': qsTr("이 프로그램은 어떤방식으로 작동하나요?"),
                          'answer':  qsTr('롤에서 공식적으로 지원하는 클라이언트 연동 API 및 OP.GG 크롤링 방식으로 연동됩니다. 자세한 내용은 <a href="https://github.com/kjm960725/OPGG_Add-on#opgg_add-on">[소스코드 링크]</a>를 참조하세요.')})
        }

        model: ListModel {
        }
    }
}
