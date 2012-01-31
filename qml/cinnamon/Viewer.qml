import QtQuick 1.0

Item {
    id: main
    signal back
    function showEffect(url) {
        exampleLoader.source = url
        toolbar.visible = true
    }

    function goBack() {
        exampleLoader.source = ""
        toolbar.visible = false
        back()
    }

    anchors.fill: parent
    Loader {
        id: exampleLoader
        source: ""
        anchors.fill: parent
    }
    Rectangle {
        id: toolbar
        color: "black"
        opacity: 0.3
        anchors.left: parent.left
        anchors.bottom: parent.bottom
        anchors.right: parent.right
        height: 80
    }
    Image {
        id: arrow
        source: "images/back.png"
        width: 60
        height: 60
        smooth: true
        anchors.left: toolbar.left
        anchors.leftMargin: 15
        anchors.bottomMargin: 10
        anchors.bottom: toolbar.bottom
        MouseArea {
            anchors.fill: parent
            onClicked: main.goBack()
        }
    }
}
