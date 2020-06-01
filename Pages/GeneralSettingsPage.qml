import QtQuick 2.12
import QtQuick.Controls 2.12
import QtQuick.Layouts 1.0

Item {
    width: 400
    height: 400

    ColumnLayout {
        spacing: 12
        anchors.right: parent.right
        anchors.left: parent.left

        Text {
            id: title
            text: qsTr("일반 설정")
            Layout.fillWidth: false
            Layout.alignment: Qt.AlignHCenter | Qt.AlignVCenter
            font.family: fonts.nanumB
            font.pixelSize: 24
            color: '#ffffff'
            horizontalAlignment: Text.AlignHCenter
        }

        Rectangle {
            id: rectangle
            color: "#ffffff"
            Layout.fillWidth: true
            Layout.preferredHeight: 1
        }

        CheckBox {
            id: inChampSessionAction
            text: qsTr("챔피언 픽창 진입시 아군 멀티서치")
            font.family: fonts.nanumR
            font.pixelSize: 14
            checked: settings.inChampSessionAction
            onCheckedChanged: settings.inChampSessionAction = checked
            contentItem: Text {
                text: parent.text
                font: parent.font
                opacity: enabled ? 1.0 : 0.3
                color: "#ffffff"
                verticalAlignment: Text.AlignVCenter
                leftPadding: parent.indicator.width + parent.spacing + 5
            }
        }

        CheckBox {
            id: inGameSessionAction
            text: qsTr("인게임 진입시 적군 멀티서치")
            font.family: fonts.nanumR
            font.pixelSize: 14
            checked: settings.inGameSessionAction
            onCheckedChanged: settings.inGameSessionAction = checked
            contentItem: Text {
                text: parent.text
                font: parent.font
                opacity: enabled ? 1.0 : 0.3
                color: "#ffffff"
                verticalAlignment: Text.AlignVCenter
                leftPadding: parent.indicator.width + parent.spacing + 5
            }
        }

        CheckBox {
            id: selectionChampAction
            text: qsTr("챔피언 선택시 챔피언 분석페이지 이동")
            font.family: fonts.nanumR
            font.pixelSize: 14
            checked: settings.selectionChampAction
            onCheckedChanged: settings.selectionChampAction = checked
            contentItem: Text {
                text: parent.text
                font: parent.font
                opacity: enabled ? 1.0 : 0.3
                color: "#ffffff"
                verticalAlignment: Text.AlignVCenter
                leftPadding: parent.indicator.width + parent.spacing + 5
            }
        }
    }

}
