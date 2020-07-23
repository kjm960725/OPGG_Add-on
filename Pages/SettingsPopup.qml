import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Layouts 1.15
Popup {
    id: root
    width: col.width + (padding * 2)
    anchors.centerIn: parent
    height: 500
    background: Rectangle {
        color: '#444444'
        radius: 10
        border.width: 1
        border.color: '#aaaaaa'
    }
    onOpened: settingPageLoader.source = 'qrc:/Pages/GeneralSettingsPage.qml'

    Row {
        id: col
        height: parent.height
        spacing: root.padding

        ListView {
            height: parent.height
            width: 150
            interactive: false // disable scroll
            model: ListModel {
                ListElement {
                    name: qsTr('프로그램 업데이트')
                    type: 'Update'
                    trriger: function() {
                        settingPageLoader.source = 'qrc:/Pages/UpdatePage.qml'
//                        updateTool.startUpdate()
//                        Qt.quit()
                    }
                }
                ListElement { type: 'Update Spacer'}
                ListElement {
                    name: qsTr('일반')
                    type: 'General'
                    trriger: function() {
                        settingPageLoader.source = 'qrc:/Pages/GeneralSettingsPage.qml'
                    }
                }
                ListElement {
                    name: qsTr('자주 묻는 질문')
                    type: 'General'
                    trriger: function() {
                        settingPageLoader.source = 'qrc:/Pages/QnAPage.qml'
                    }
                }
            }
            delegate: ItemDelegate {
                id: delegate
                Behavior on scale { NumberAnimation { duration: 20 } }
                text: name
                enabled: String(type).includes('Spacer') ? false : true
                anchors.left: parent.left
                anchors.right: parent.right
                font.family: fonts.nanumB
                onClicked: {
                    trriger()
                }
                height: {
                    if (visible) {
                        return String(type).includes('Spacer') ? 15 : 40
                    }
                    return 0
                }
                visible: {
                    if (updateTool == null) return false
                    return String(type).includes('Update') ? updateTool.hasUpdate : true
                }

                scale: pressed ? 0.95 : 1
                background: Rectangle {
                    color: delegate.hovered ? '#aaaaaaaa' : '#00000000'
                    radius: 5
                }
                Binding {
                    target: contentItem
                    property: "color"
                    value: {
                        if (String(type).includes('Update'))
                            return delegate.hovered ? '#000000' : "#ffff00"
                        return delegate.hovered ? '#000000' : "#ffffff"
                    }
                }
            }
            focus: true
        }

        Rectangle {
            color: '#ffffff'
            width: 1
            height: parent.height
            anchors.verticalCenter: parent.verticalCenter
        }

        ScrollView {
            height: parent.height
            width: settingPageLoader.width
            contentHeight: settingPageLoader.height
            clip: true
            Loader {
                id: settingPageLoader
                source: 'qrc:/Pages/GeneralSettingsPage.qml'
            }
        }

    }
}

/*##^##
Designer {
    D{i:0;autoSize:true;height:480;width:640}
}
##^##*/
