import QtQuick 2.0
import QtGraphicalEffects 1.0
import Riot 1.0

Item {
    id: root
    signal clickedHome()
    signal clickedNext()
    signal clickedPrevious()
    signal clickedRefrash()
    signal clickedSummoner(var name);
    signal clickedCopy()

    Row {

        anchors.left: parent.left
        anchors.top: parent.top
        anchors.bottom: parent.bottom
        Rectangle {
            width: 50
            height: parent.height
            color: homeArea.containsMouse ? '#44ffffff' : '#00000000'
            Image {
                id: homeImage
                source: 'qrc:/ICons/HomeIcon.png'
                anchors.fill: parent
                fillMode: Image.PreserveAspectFit
            }
            MouseArea {
                id: homeArea
                anchors.fill: parent
                hoverEnabled: true
                onClicked: clickedHome()
            }
        }
        Rectangle {
            width: 50
            height: parent.height
            color: previousArea.containsMouse ? '#44ffffff' : '#00000000'
            Image {
                id: previousImage
                source: 'qrc:/ICons/LeftArrowIcon.png'
                anchors.fill: parent
                fillMode: Image.PreserveAspectFit
            }
            MouseArea {
                id: previousArea
                anchors.fill: parent
                hoverEnabled: true
                onClicked: clickedPrevious()
            }
        }
        Rectangle {
            width: 50
            height: parent.height
            color: nextArea.containsMouse ? '#44ffffff' : '#00000000'
            Image {
                id: nextImage
                source: 'qrc:/ICons/RightArrowIcon.png'
                anchors.fill: parent
                fillMode: Image.PreserveAspectFit
            }
            MouseArea {
                id: nextArea
                anchors.fill: parent
                hoverEnabled: true
                onClicked: clickedNext()
            }
        }
        Rectangle {
            width: 50
            height: parent.height
            color: refrashArea.containsMouse ? '#44ffffff' : '#00000000'
            Image {
                width: 16
                height: 16
                id: refrashImage
                source: 'qrc:/ICons/RefrashIcon.png'
                anchors.centerIn: parent
                fillMode: Image.PreserveAspectFit
            }
            MouseArea {
                id: refrashArea
                anchors.fill: parent
                hoverEnabled: true
                onClicked: clickedRefrash()
            }
        }
        Rectangle {
            width: 50
            height: parent.height
            color: copyArea.containsMouse ? '#44ffffff' : '#00000000'
            Image {
                width: 16
                height: 16
                id: copyImage
                source: 'qrc:/ICons/CopyIcon.png'
                anchors.centerIn: parent
                fillMode: Image.PreserveAspectFit
            }
            MouseArea {
                id: copyArea
                anchors.fill: parent
                hoverEnabled: true
                onClicked: clickedCopy()
            }
        }
    }

    Row {
        anchors.right: parent.right
        anchors.top: parent.top
        anchors.bottom: parent.bottom

        Text {
            id: commentText
            width: contentWidth + 20
            text: qsTr('이 프로그램은 OP.GG와 관련이 없는 개인 프로젝트입니다. (made by 청산가리중독자)\t버그제보/기타문의 : %1').arg('kjm960725@gmail.com')
            font.family: fonts.nanumR
            color: '#aaffffff'
            anchors.verticalCenter: parent.verticalCenter
            font.pixelSize: 12
        }

        Item {
            id: summonerNameItem
//            visible: false
            visible: summonerNameText.text.length > 0
            anchors.top: parent.top
            anchors.bottom: parent.bottom
            width: summonerNameText.contentWidth + summonerIconImg.width + 15

            Rectangle {
                id: summonerNameBg
                anchors.fill: parent
                color: summonerNameArea.containsMouse ? '#88ffffff' : '#00ffffff'
            }

            MouseArea {
                id: summonerNameArea
                anchors.fill: parent
                hoverEnabled: true
                onClicked: clickedSummoner(summonerNameText.text)
            }

            Image {
                id: summonerIconImg
                anchors.left: parent.left
                anchors.leftMargin: 5
                anchors.top: parent.top
                anchors.bottom: parent.bottom
                width: height
                source: challenge.currentSummoner.profileIconId !== undefined
                              ? dragon.getDataDragonPath() + '/' + dragon.version + '/img/profileicon/' + challenge.currentSummoner.profileIconId +'.png'
                              : ''
                layer.enabled: true
                layer.effect: OpacityMask {
                    maskSource: Item {
                        width: summonerIconImg.width
                        height: summonerIconImg.height
                        Rectangle {
                            anchors.centerIn: parent
                            width: summonerIconImg.adapt ? summonerIconImg.width : Math.min(summonerIconImg.width, summonerIconImg.height)
                            height: summonerIconImg.adapt ? summonerIconImg.height : width
                            radius: Math.min(width,height) / 2
                            border.width: 1
                        }
                    }
                }
            }

            Text {
                id: summonerNameText
                anchors.left: summonerIconImg.right
                anchors.leftMargin: 5
                anchors.verticalCenter: parent.verticalCenter
                text: challenge.currentSummoner.displayName !== undefined
                      ? challenge.currentSummoner.displayName
                      : ''
                font.family: fonts.nanumR
                style: Text.Outline
                color: '#ffffff'
                font.pixelSize: 12
            }
        }

        Item {
            id: gameStateItem
            anchors.top: parent.top
            anchors.bottom: parent.bottom
            width: gameStateText.contentWidth + 10
            visible: gameStateText.text.length > 0

            Text {
                id: gameStateText
                anchors.horizontalCenter: parent.horizontalCenter
                anchors.verticalCenter: parent.verticalCenter
                text: {
                    switch(challenge.currentGameflowState) {
                    case LCU.None:
                        if (lcu.isConnected)
                            return qsTr('온라인')
                        else
                            return qsTr('오프라인')
                    case LCU.Lobby:
                        return qsTr('로비')
                    case LCU.Matchmaking:
                        return qsTr('매칭중')
                    case LCU.ReadyCheck:
                        return qsTr('매칭완료')
                    case LCU.ChampSelect:
                        return qsTr('챔피언 선택중')
                    case LCU.InProgress:
                        return qsTr('게임중')
                    case LCU.Reconnect:
                        return qsTr('게임중')
                    case LCU.WaitingForStats:
                        return qsTr('점수 화면')
                    case LCU.EndOfGame:
                        return qsTr('점수 화면')
                    case LCU.PreEndOfGame:
                        return qsTr('점수 화면')
                    default:
                        return qsTr('undefined')
                    }
                }

                font.family: fonts.nanumR
                color: '#ffffff'
                font.pixelSize: 12
            }
        }
    }
}
