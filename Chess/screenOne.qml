import QtQuick 2.0
import QtQuick.Window 2.2
import QtQuick.Controls 1.3
import Chesspieces 1.0
import Screenloader 1.0

Window {
    id : wd
    width : 550
    height: 550
    visible: true

    ScreenLoader {
        id: screenLoader
    }

    Button {
        x: 175
        y: 250
        text: "Start game"
        onClicked: {screenLoader.load("../Chess/screenTwo.qml")
        wd.visible = false}
    }
    Button {
        text: "Load game"
        onClicked:{screenLoader.load("../Chess/screenThree.qml")
        wd.visible = false}
        x: 275
        y: 250
    }
}

