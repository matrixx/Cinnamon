import QtQuick 1.0

Rectangle {
    id: landscapeView
    signal open(url startUrl)

    anchors.fill: parent

    gradient: Gradient {
        GradientStop { position: 0.0; color: "black" }
        GradientStop { position: 0.5; color: "grey" }
        GradientStop { position: 1.0; color: "black" }
    }

    PathView {
        id: view
        property url startUrl: ""
        anchors.rightMargin: 10
        anchors.leftMargin: 10
        anchors.bottomMargin: 10
        anchors.topMargin: 10
        anchors.fill: parent
        pathItemCount: 8
        clip: true
        path: Path {
            startY: -30
            startX: view.width / 5
            PathAttribute { name: "scaleX"; value: 0.2 }
            PathAttribute { name: "scaleY"; value: 0.2 }
            PathAttribute { name: "opacity"; value: 0.3 }
            PathAttribute { name: "zvalue"; value: -1.0 }
            PathQuad {
                x: view.width / 3 * 2
                y: view.height / 2
                controlY: view.height / 4
                controlX: view.width / 2
            }
            PathPercent { value: 0.35 }
            PathAttribute { name: "scaleX"; value: 1.0 }
            PathAttribute { name: "scaleY"; value: 1.0 }
            PathAttribute { name: "opacity"; value: 1.0 }
            PathAttribute { name: "zvalue"; value: 1.0 }
            PathQuad {
                x: view.width / 2
                y: view.height / 4 * 3
                controlY: view.height / 4 * 3
                controlX: view.width / 4 * 3
            }

            PathPercent { value: 0.60 }
            PathAttribute { name: "scaleX"; value: 0.6 }
            PathAttribute { name: "scaleY"; value: 0.6 }
            PathAttribute { name: "opacity"; value: 0.6 }
            PathAttribute { name: "zvalue"; value: -0.5 }
            PathQuad {
                x: view.width / 3
                y: view.height / 3.5
                controlY: view.height / 3 * 2
                controlX: 0
            }
            PathPercent { value: 1.0 }
            PathAttribute { name: "scaleX"; value: 0.1 }
            PathAttribute { name: "scaleY"; value: 0.1 }
            PathAttribute { name: "opacity"; value: 0.2 }
            PathAttribute { name: "zvalue"; value: -2.0 }
        }
        delegate: MenuItem {}
        model: itemModel
        onStartUrlChanged: {
            landscapeView.open(startUrl)
        }
    }
}
