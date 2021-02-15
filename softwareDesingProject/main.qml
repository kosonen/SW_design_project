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

        WeatherListModel
        {
            id: weatherModel
        }
        ConsumptionListModel
        {
            id: consumptionModel
        }

        DataBrowser
        {
            id: consumptionBrowser
            width: parent.width / 10
            height: parent.height
            anchors.left: parent.left
            modelToView: consumptionModel
        }
        DataBrowser
        {
            id: weatherBrowser
            width: parent.width / 10
            height: parent.height
            anchors.right: parent.right
            modelToView: weatherModel
        }

        Loader{
            id: energy
            source: "energy.qml"
            height: parent.height/2.5

            anchors.left: consumptionBrowser.right
            anchors.top: parent.top
            anchors.right: weatherBrowser.left

            anchors.topMargin: 150
            anchors.leftMargin: 200
            anchors.rightMargin: 200

        }

        Loader{

            source: "temperature.qml"
            height: parent.height/6
            width: parent.width/4

            anchors.left: consumptionBrowser.right
            anchors.top: energy.bottom
            anchors.right: weatherBrowser.left

            anchors.topMargin: 150
            anchors.leftMargin: 200
            anchors.rightMargin: 200

        }

    }



}
