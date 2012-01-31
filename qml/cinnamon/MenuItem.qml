import QtQuick 1.0

Rectangle {
    id: wrapper
    width: 460
    height: width * 0.6
    opacity: PathView.opacity
    transform: Scale {
        origin.x: wrapper.width / 2
        origin.y: wrapper.height / 2
        xScale: wrapper.PathView.scaleX
        yScale: wrapper.PathView.scaleY
    }
    z: PathView.zvalue
    Image {
        anchors.margins: 5
        anchors.fill: parent
        sourceSize.width: width
        sourceSize.height: height
        source: imageurl
    }
    Rectangle {
        id: header
        color: "black"
        opacity: 0.5
        anchors.left: parent.left
        anchors.top: parent.top
        anchors.right: parent.right
        height: 50
    }
    Text {
        color: "white"
        text: name
        anchors.centerIn: header
        font.pixelSize: 36
    }
    MouseArea {
        anchors.fill: parent
        onClicked: wrapper.PathView.view.startUrl = starturl
    }
}
