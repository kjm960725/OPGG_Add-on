import QtQuick 2.12
import QtQuick.Controls 2.3
import QtQuick.Layouts 1.12
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

//    signal accepted()
//    modal: false
//    closePolicy: Popup.CloseOnEscape


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
                    name: qsTr('일반')
                    trriger: function() {
                        settingPageLoader.source = 'qrc:/Pages/GeneralSettingsPage.qml'
                    }
                }
//                ListElement {
//                    name: qsTr('단축키')
//                    trriger: function() {

//                    }
//                }

//                ListElement {
//                    name: qsTr('자주 묻는 질문')
//                    trriger: function() {

//                    }
//                }

//                ListElement {
//                    name: qsTr('프로그램 정보')
//                    trriger: function() {

//                    }
//                }
            }
            delegate: ItemDelegate {
                id: delegate
                Behavior on scale { NumberAnimation { duration: 20 } }
                text: name
                anchors.left: parent.left
                anchors.right: parent.right
                font.family: fonts.nanumB
                onClicked: {
                    trriger()
                }

                scale: pressed ? 0.95 : 1
                background: Rectangle {
                    color: delegate.hovered ? '#aaaaaaaa' : '#00000000'
                    radius: 5
                }
                Binding {
                    target: contentItem
                    property: "color"
                    value: delegate.hovered ? '#000000' : "#ffffff"
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

        Page {
            background: Rectangle {
                color: '#00000000'
            }
            height: parent.height
            width: settingPageLoader.width

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
}

/*##^##
Designer {
    D{i:0;autoSize:true;height:480;width:640}
}
##^##*/
