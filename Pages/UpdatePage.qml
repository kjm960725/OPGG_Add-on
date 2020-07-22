import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Layouts 1.15

Item {
    width: 550
    height: 400

    ColumnLayout {
        spacing: 25
        anchors.verticalCenter: parent.verticalCenter
        anchors.right: parent.right
        anchors.left: parent.left

        Text {
            id: hasUpdateText
            text: updateTool.hasUpdate ? qsTr('새로운 업데이트가 있습니다.') : qsTr('업데이트가 없습니다.')
            Layout.fillWidth: false
            Layout.alignment: Qt.AlignHCenter | Qt.AlignVCenter
            font.family: fonts.nanumB
            font.pixelSize: 24
            color: updateTool.hasUpdate ? '#ffff00' : '#ffffff'
            horizontalAlignment: Text.AlignHCenter
        }

        Button {
            text: qsTr('프로그램 업데이트')
            font.family: fonts.nanumR
            font.pixelSize: 18
            Layout.alignment: Qt.AlignHCenter | Qt.AlignVCenter
            onClicked: {
                updateTool.startUpdate()
                Qt.quit()
            }
        }
    }
}
