import QtQuick 1.1
import Qt.labs.shaders 1.0
import QtGraphicalEffects 1.0

Item {
    id: main
    anchors.fill: parent
    Image {
        id: bg
        anchors.fill: parent
        source: "images/colorize.jpg"
        fillMode: Image.PreserveAspectCrop
        smooth: true
        visible: true
    }

    Colorize {
        id: hueexample
        anchors.fill: bg
        source: bg
        hue: 1.0
        saturation: 1.0
        lightness: 0.0

        SequentialAnimation on hue {
            id: ratioAnimation
            running: true
            loops: Animation.Infinite
            NumberAnimation {
                easing.type: Easing.Linear
                to: 0.0
                duration: 5000
            }
            NumberAnimation {
                easing.type: Easing.Linear
                to: 1.0
                duration: 5000
            }
        }
    }
}
