import QtQuick 2.12
import QtQuick.Window 2.12

Window {
    width: screen.width
    height: screen.height
    visible: true
    title: qsTr("Hello World")

<<<<<<< HEAD

    Loader{
        source: "dataBrowser.qml"
        width: parent.width / 10
        height: parent.height
        anchors.left: parent.left

=======
    Loader{
        source: "background.qml"
        width: parent.width
        height: parent.height
    }

    Loader{
>>>>>>> added background and energy modules

    }

}
