import QtQuick 1.0

Rectangle {
    id: portraitView
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
        path: Path {
            startY: 0
            startX: view.width / 2
            PathAttribute { name: "scaleX"; value: 0.8 }
            PathAttribute { name: "scaleY"; value: 0.3 }
            PathAttribute { name: "opacity"; value: 0.5 }
            PathAttribute { name: "zvalue"; value: -1.0 }
            PathQuad {
                x: view.width / 2
                y: view.height / 2
                controlY: view.height * 0.1
                controlX: view.width / 2
            }
            PathAttribute { name: "scaleX"; value: 1.0 }
            PathAttribute { name: "scaleY"; value: 1.0 }
            PathAttribute { name: "opacity"; value: 1.0 }
            PathAttribute { name: "zvalue"; value: 1.0 }
            PathQuad {
                x: view.width / 2
                y: view.height
                controlY: view.height * 0.9
                controlX: view.width / 2
            }
            PathAttribute { name: "scaleX"; value: 0.8 }
            PathAttribute { name: "scaleY"; value: 0.3 }
            PathAttribute { name: "opacity"; value: 0.5 }
            PathAttribute { name: "zvalue"; value: -1.0 }
        }
        delegate: MenuItem {}
        model: itemModel
        onStartUrlChanged: {
            portraitView.open(startUrl)
        }
    }
}
