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
        smooth: true
        fillMode: Image.PreserveAspectCrop
        visible: true
    }

    Colorize {
        id: saturationexample
        anchors.fill: bg
        source: bg
        hue: 0.5
        saturation: 1.0
        lightness: 0.0

        SequentialAnimation on lightness {
            id: ratioAnimation
            running: true
            loops: Animation.Infinite
            NumberAnimation {
                easing.type: Easing.Linear
                to: -1.0
                duration: 3000
            }
            NumberAnimation {
                easing.type: Easing.Linear
                to: 1.0
                duration: 3000
            }
        }
    }
}
