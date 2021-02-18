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

        Rectangle{
            id: titleConsumption
            width: consumptionBrowser.width
            height: 25
            anchors.top: parent.top
            anchors.left: parent.left
            border.color: "black"
            Text{
                id: titleText
                text: qsTr("Consumption Options")

            }

        }

        DataBrowser
        {
            id: consumptionBrowser
            width: parent.width / 10
            height: consumptionBrowser.heightOfElement * consumptionModel.rowCount()
            anchors.top: titleConsumption.bottom
            modelToView: consumptionModel
        }
        OptionColumn{
            id: optionColumn
            width: consumptionBrowser.width
            height: consumptionBrowser.height
            anchors.top: consumptionBrowser.bottom
        }

        Rectangle{
            id: titleWeather
            width: weatherBrowser.width
            height: 25
            anchors.top: optionColumn.bottom
            anchors.topMargin: 5
            border.color: "black"
            Text{
                id: titleweatherText
                text: qsTr("Weather Options")

            }

        }

        DataBrowser
        {
            id: weatherBrowser
            width: parent.width / 10
            height: weatherBrowser.heightOfElement * weatherModel.rowCount()
            anchors.top: titleWeather.bottom
            modelToView: weatherModel
        }

        Loader{
            id: energy
            source: "energy.qml"
            height: parent.height/2.5

            anchors.left: consumptionBrowser.right
            anchors.top: parent.top
            anchors.right: parent.right

            anchors.topMargin: 150
            anchors.leftMargin: 200
            anchors.rightMargin: 600


        }

        Loader{

            source: "temperature.qml"
            height: parent.height/6
            width: parent.width/4

            anchors.left: consumptionBrowser.right
            anchors.top: energy.bottom
            anchors.right: parent.right

            anchors.topMargin: 150
            anchors.leftMargin: 200
            anchors.rightMargin: 600

        }

        ConsumptionPieChart{
            id: consumptionChart
            height: energy.height
            width: energy.height

            anchors.left: energy.right
            anchors.top: parent.top
            anchors.topMargin: 150
            anchors.leftMargin: 50
        }

    }



}
