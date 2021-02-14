import QtQuick 2.12
import QtQuick.Window 2.12


Window {
    width: screen.width
    height: screen.height
    visible: true
    title: qsTr("Hello World")

    Rectangle{
        width: parent.width
        height: parent.height
        color: "darkcyan"

       Loader{
            id: dataBrowser
            source: "dataBrowser.qml"
            width: parent.width / 10
            height: parent.height
            anchors.left: parent.left
        }

        Loader{
            id: energy
            source: "energy.qml"
            height: parent.height/2.5

            anchors.left: dataBrowser.right
            anchors.top: parent.top
            anchors.right: parent.right

            anchors.topMargin: 150
            anchors.leftMargin: 200
            anchors.rightMargin: 200

        }

        Loader{

            source: "temperature.qml"
            height: parent.height/6
            width: parent.width/4

            anchors.left: dataBrowser.right
            anchors.top: energy.bottom

            anchors.topMargin: 150
            anchors.leftMargin: 200

        }

    }



}
