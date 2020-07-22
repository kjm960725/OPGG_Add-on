import QtQuick 2.15

Loader {
    readonly property string nanumB: nanumB.name
    readonly property string nanumR: nanumR.name
    readonly property string nanumL: nanumL.name
    readonly property string nanumEB: nanumEB.name

    FontLoader {
        id: nanumB
        source: 'qrc:/Fonts/NanumSquareB.ttf'
    }
    FontLoader {
        id: nanumR
        source: 'qrc:/Fonts/NanumSquareR.ttf'
    }
    FontLoader {
        id: nanumL
        source: 'qrc:/Fonts/NanumSquareL.ttf'
    }
    FontLoader {
        id: nanumEB
        source: 'qrc:/Fonts/NanumSquareEB.ttf'
    }
}
