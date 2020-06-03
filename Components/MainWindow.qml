import QtQuick 2.12
import QtQuick.Window 2.12
import QtQuick.Controls 2.3

Window {
    id: mainWindow
    visible: true
    width: 1200
    height: 800
    minimumHeight: 600
    minimumWidth: 800
    flags: Qt.Window | Qt.FramelessWindowHint /*| Qt.WindowStaysOnTopHint*/

    color: '#222222'
    property color titleColor: '#00000000'
    property color borderColor: '#000000'
    property int borderWidth: 1
    property Component content
    property Component titleItem

    onMinimumHeightChanged: if (height < minimumHeight) height = minimumHeight
    onMinimumWidthChanged: if (width < minimumWidth) width = minimumWidth

    Rectangle {
        id: background
        color: mainWindow.color
        border.color: mainWindow.borderColor
        border.width: mainWindow.borderWidth
        anchors.fill: parent
    }

    Loader {
        id: contentLoader
        sourceComponent: content
        anchors.fill: parent
        anchors.topMargin: titleBar.height + 1
        anchors.bottomMargin: 1
        anchors.leftMargin: 1
        anchors.rightMargin: 1
        clip: true
    }

    property int previousNomalX: 0
    property int previousNomalY: 0
    function windowMaximize() {
        if (mainWindow.visibility === 4 || mainWindow.visibility === 5) {
            mainWindow.showNormal()
            mainWindow.setX(previousNomalX)
            mainWindow.setY(previousNomalY)
        } else {
            previousNomalX = mainWindow.x
            previousNomalY = mainWindow.y
            mainWindow.showMaximized();
        }
    }

    Rectangle {
        id: titleBar
        anchors.top: parent.top
        anchors.left: parent.left
        anchors.right: parent.right
        color: titleColor
        border.width: background.border.width
        height: 30
        border.color: background.border.color


        MouseArea {
            Timer {
                id: nomalVisibilityTimer
                running: mainWindow.visibility === 2
                interval: 50
                repeat: false
            }
            Timer {
                id: maxVisibilityTimer
                running: mainWindow.visibility === 4 || mainWindow.visibility === 5
                interval: 50
                repeat: false
            }

            anchors.fill: parent
            onPressed: {
                previousX = mouseX
                previousY = mouseY
            }
            onMouseXChanged: {
                if (nomalVisibilityTimer.running || maxVisibilityTimer.running) return
                var dx = mouseX - previousX
                if (mainWindow.visibility === 4 || mainWindow.visibility === 5) {
                    if (dx < 10 && dx > -10) return
                    const beforeLocation = mouseX / mainWindow.width
                    mainWindow.showNormal()
                    previousX = mainWindow.width * beforeLocation
                } else {
                    mainWindow.setX(mainWindow.x + dx)
                }

            }
            onMouseYChanged: {
                if ( nomalVisibilityTimer.running || maxVisibilityTimer.running) return
                var dy = mouseY - previousY
                if (mainWindow.visibility === 4 || mainWindow.visibility === 5) {
                    if (dy < 10 && dy > -10) return
                    const beforeLocation = mouseX / mainWindow.width
                    mainWindow.showNormal()
                    previousX = mainWindow.width * beforeLocation
                } else {
                    mainWindow.setY(mainWindow.y + dy)
                }
            }

            onDoubleClicked: windowMaximize()
        }


        Loader {
            id: titleItemLoader
            sourceComponent: titleItem
            anchors.left: parent.left
            anchors.top: parent.top
            anchors.bottom: parent.bottom
            anchors.right: windowIcons.left
            anchors.leftMargin: 1
            anchors.topMargin: 1
            anchors.bottomMargin: 1
            clip: true
        }


        Row {
            id: windowIcons
            anchors.right: parent.right
            anchors.top: parent.top
            anchors.bottom: parent.bottom
            anchors.topMargin: 1
            anchors.rightMargin: 1
            anchors.bottomMargin: 1

            Rectangle {
                width: 50
                anchors.top: parent.top
                anchors.bottom: parent.bottom
                color: minimizeArea.containsMouse ? '#44ffffff' : '#00000000'
                Image {
                    anchors.fill: parent
                    fillMode: Image.PreserveAspectFit
                    source: 'qrc:/ICons/MinimizeIcon.png'
                    MouseArea {
                        id: minimizeArea
                        hoverEnabled: true
                        anchors.fill: parent
                        onClicked: mainWindow.showMinimized()
                    }
                }
            }

            Rectangle {
                width: 50
                anchors.top: parent.top
                anchors.bottom: parent.bottom
                color: maxWinArea.containsMouse ? '#44ffffff' : '#00000000'
                Image {
                    anchors.fill: parent
                    fillMode: Image.PreserveAspectFit
                    source: mainWindow.visibility === 4 || mainWindow.visibility === 5 ? 'qrc:/ICons/WindowIcon.png' : 'qrc:/ICons/MaximizeIcon.png'
                    MouseArea {
                        id: maxWinArea
                        hoverEnabled: true
                        anchors.fill: parent
                        onClicked: windowMaximize()
                    }
                }
            }

            Rectangle {
                width: 50
                anchors.top: parent.top
                anchors.bottom: parent.bottom
                color: quitArea.containsMouse ? '#44ffffff' : '#00000000'
                Image {
                    anchors.fill: parent
                    source: 'qrc:/ICons/QuitIcon.png'
                    fillMode: Image.PreserveAspectFit
                    MouseArea {
                        id: quitArea
                        hoverEnabled: true
                        anchors.fill: parent
                        onClicked: Qt.quit()
                    }
                }
            }
        }


    }

    property int previousX
    property int previousY
    MouseArea {
        id: topArea
        height: 5
        anchors {
            top: parent.top
            left: parent.left
            right: parent.right
        }
        enabled: visibility !== 4 && visibility !== 5
        // We set the shape of the cursor so that it is clear that this resizing
        cursorShape: Qt.SizeVerCursor
        onPressed: {
            // We memorize the position along the Y axis
            previousY = mouseY
        }
        // When changing a position, we recalculate the position of the window, and its height
        onMouseYChanged: {
            var dy = mouseY - previousY
            if (mainWindow.height - dy < mainWindow.minimumHeight)
                dy = mainWindow.height - mainWindow.minimumHeight
            mainWindow.setGeometry(mainWindow.x, mainWindow.y + dy, mainWindow.width, mainWindow.height - dy)
        }
    }
    // Similar calculations for the remaining three areas of resize
    MouseArea {
        id: bottomArea
        height: 5
        anchors {
            bottom: parent.bottom
            left: leftBottomArea.right
            right: parent.right
        }
        enabled: visibility !== 4 && visibility !== 5
        cursorShape: Qt.SizeVerCursor
        onPressed: {
            previousY = mouseY
        }
        onMouseYChanged: {
            var dy = mouseY - previousY
            mainWindow.setHeight(Math.max(mainWindow.height + dy, mainWindow.minimumHeight))
        }
    }
    MouseArea {
        id: leftArea
        width: 5
        anchors {
            top: topArea.bottom
            bottom: bottomArea.top
            left: parent.left
        }
        enabled: visibility !== 4 && visibility !== 5
        cursorShape: Qt.SizeHorCursor
        onPressed: {
            previousX = mouseX
        }
        onMouseXChanged: {
            var dx = mouseX - previousX
            if (mainWindow.width - dx < mainWindow.minimumWidth)
                dx = mainWindow.width - mainWindow.minimumWidth
            mainWindow.setGeometry(mainWindow.x + dx, mainWindow.y, mainWindow.width - dx, mainWindow.height)
        }
    }
    MouseArea {
        id: rightArea
        width: 5
        anchors {
            top: topArea.bottom
            bottom: bottomArea.top
            right: parent.right
        }
        enabled: visibility !== 4 && visibility !== 5
        cursorShape:  Qt.SizeHorCursor
        onPressed: {
            previousX = mouseX
        }
        onMouseXChanged: {
            var dx = mouseX - previousX
            mainWindow.setWidth(Math.max(mainWindow.width + dx, mainWindow.minimumWidth))
        }
    }
    MouseArea {
        id: leftBottomArea
        width: 5
        height: 5
        anchors {
            bottom: parent.bottom
            left: parent.left
        }
        enabled: visibility !== 4 && visibility !== 5
        cursorShape: Qt.SizeBDiagCursor
        onPressed: {
            previousX = mouseX
            previousY = mouseY
        }
        onMouseYChanged: {
            var dy = mouseY - previousY
            mainWindow.setHeight(Math.max(mainWindow.height + dy, mainWindow.minimumHeight))
        }
        onMouseXChanged: {
            var dx = mouseX - previousX
            if (mainWindow.width - dx < mainWindow.minimumWidth)
                dx = mainWindow.width - mainWindow.minimumWidth
            mainWindow.setGeometry(mainWindow.x + dx, mainWindow.y, mainWindow.width - dx, mainWindow.height)
        }
    }
    MouseArea {
        id: rightBottomArea
        width: 5
        height: 5
        anchors {
            bottom: parent.bottom
            right: parent.right
        }
        enabled: visibility !== 4 && visibility !== 5
        cursorShape: Qt.SizeFDiagCursor
        onPressed: {
            previousX = mouseX
            previousY = mouseY
        }
        onMouseXChanged: {
            var dx = mouseX - previousX
            mainWindow.setWidth(Math.max(mainWindow.width + dx, mainWindow.minimumWidth))
        }
        onMouseYChanged: {
            var dy = mouseY - previousY
            mainWindow.setHeight(Math.max(mainWindow.height + dy, mainWindow.minimumHeight))
        }
    }
    MouseArea {
        id: leftTopArea
        width: 5
        height: 5
        anchors {
            left: parent.left
            top: parent.top
        }
        enabled: visibility !== 4 && visibility !== 5
        cursorShape: Qt.SizeFDiagCursor
        onPressed: {
            previousX = mouseX
            previousY = mouseY
        }
        onMouseXChanged: {
            var dx = mouseX - previousX
            if (mainWindow.width - dx < mainWindow.minimumWidth)
                dx = mainWindow.width - mainWindow.minimumWidth
            mainWindow.setGeometry(mainWindow.x + dx, mainWindow.y, mainWindow.width - dx, mainWindow.height)
        }
        onMouseYChanged: {
            var dy = mouseY - previousY
            if (mainWindow.height - dy < mainWindow.minimumHeight)
                dy = mainWindow.height - mainWindow.minimumHeight
            mainWindow.setGeometry(mainWindow.x, mainWindow.y + dy, mainWindow.width, mainWindow.height - dy)
        }
    }
    MouseArea {
        id: rightTopArea
        width: 5
        height: 5
        anchors {
            right: parent.right
            top: parent.top
        }
        enabled: visibility !== 4 && visibility !== 5
        cursorShape: Qt.SizeBDiagCursor
        onPressed: {
            previousX = mouseX
            previousY = mouseY
        }
        onMouseXChanged: {
            var dx = mouseX - previousX
            mainWindow.setWidth(Math.max(mainWindow.width + dx, mainWindow.minimumWidth))
        }
        onMouseYChanged: {
            var dy = mouseY - previousY
            if (mainWindow.height - dy < mainWindow.minimumHeight)
                dy = mainWindow.height - mainWindow.minimumHeight
            mainWindow.setGeometry(mainWindow.x, mainWindow.y + dy, mainWindow.width, mainWindow.height - dy)
        }
    }
}
