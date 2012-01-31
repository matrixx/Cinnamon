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
        id: hueexample
        anchors.fill: bg
        source: bg
        hue: 1.0
        saturation: 1.0
        lightness: 0.0
        ParallelAnimation {
            running: true
            SequentialAnimation {
                loops: Animation.Infinite
                NumberAnimation {
                    target: hueexample
                    property: "hue"
                    easing.type: Easing.Linear
                    to: 0.0
                    duration: 5000
                }
                NumberAnimation {
                    target: hueexample
                    property: "hue"
                    easing.type: Easing.Linear
                    to: 1.0
                    duration: 5000
                }
            }
            SequentialAnimation {
                loops: Animation.Infinite
                NumberAnimation {
                    target: hueexample
                    property: "saturation"
                    easing.type: Easing.Linear
                    to: 0.0
                    duration: 5000
                }
                PauseAnimation { duration: 1000 }
                NumberAnimation {
                    target: hueexample
                    property: "saturation"
                    easing.type: Easing.Linear
                    to: 1.0
                    duration: 5000
                }
                PauseAnimation { duration: 1000 }
            }
        }
    }
}
