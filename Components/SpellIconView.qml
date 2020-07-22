import QtQuick 2.15

Row {
    id: root
    property var champInfo
    property string fontFamily
    property string imgDirPath

    signal clicked(var id)

    height: 50
    spacing: 5
    SpellIcon {
        spellInfo: champInfo.passive
        width: root.height
        height: root.height
        fontFamily: root.fontFamily
        imgDirPath: root.imgDirPath
        onClicked: root.clicked(id)
        hotkey: 'P'
    }
    Repeater {
        model: champInfo.spells.length
        SpellIcon {
            spellInfo: champInfo.spells[index]
            hotkey: {
                switch(index) {
                case 0: return 'Q'
                case 1: return 'W'
                case 2: return 'E'
                case 3: return 'R'
                default: return ''
                }
            }
            width: root.height
            height: root.height
            fontFamily: root.fontFamily
            imgDirPath: root.imgDirPath
            onClicked: root.clicked(id)
        }
    }
}

