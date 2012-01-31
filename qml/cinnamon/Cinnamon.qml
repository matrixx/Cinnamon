import QtQuick 1.0
import com.nokia.meego 1.0

Item {
    property bool landscape: width > height
    property bool fullscreen: platformWindow.viewMode == WindowState.Fullsize
    id: cinnamon

    function showItem(url) {
        menuLoader.visible = false
        itemViewer.showEffect(url)
        itemViewer.visible = true
    }

    function showMenu() {
        itemViewer.visible = false
        menuLoader.visible = true
    }

    Loader {
        id: menuLoader
        source: cinnamon.landscape ? "LandscapeView.qml" : "PortraitView.qml"
        anchors.fill: parent
        onLoaded: {
            item.open.connect(cinnamon.showItem)
        }
    }
    Viewer {
        id: itemViewer
        anchors.fill: parent
        visible: false
        Component.onCompleted: {
            itemViewer.back.connect(cinnamon.showMenu)
        }
    }
    onFullscreenChanged: {
        if (!fullscreen && itemViewer.visible) {
            itemViewer.goBack();
        }
    }
}
