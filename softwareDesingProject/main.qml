import QtQuick 2.12
import QtQuick.Window 2.12
import QtQuick.Controls 2.14
import QtQml 2.14
//import controller 1.0

Window {
    width: screen.width
    height: screen.height
    visible: true
    title: qsTr("Hello World")

  /*  QtObject{
        id: dateObj
        property var locale: Qt.locale()
        property date currentTime: new Date()
        property string timeString: timeString

        Component.onCompleted: {
            console.log("timeString " << timeString);
            timeString = currentTime.toLocaleTimeString(locale, Locale.ShortFormat);
            console.log("timeString " << timeString);
        }
    }*/

    Rectangle{
        width: parent.width
        height: parent.height
        color: "darkcyan"

        Rectangle{
            id: locationInfoBoudningRect
            width: weatherBrowser.width
            height: 25
            border.color: "black"
            anchors.top: weatherBrowser.bottom
            anchors.left: parent.left

            Text {
                id: infotext
                text: "Location"
                leftPadding: 70
                anchors.top: locationInfoBoudningRect.top

            }
        }
        Rectangle{
            id: locationInputBoundingRect
            width: weatherBrowser.width
            height: 25
            border.color: "black"
            border.width: 2
            anchors.top: locationInfoBoudningRect.bottom
            anchors.left: parent.left
            TextInput
            {
                id: inputInfo
                width: locationInputBoundingRect.width
                height: locationInputBoundingRect.height
                text: "Viitasaari"
                leftPadding: 4
            }
        }

        Rectangle{
            id: startDateBoundingRect
            width: weatherBrowser.width
            height: 25
            border.color: "black"
            anchors.top: locationInputBoundingRect.bottom
            anchors.left: parent.left

            Text {
                id: dayInfo
                text: "Starting Date"
                leftPadding: 5
                anchors.top: startDateBoundingRect.top

            }
        }

        Rectangle{
            id: startDayBoundingRect
            width: weatherBrowser.width/2
            height: 25
            border.color: "black"
            anchors.top: startDateBoundingRect.bottom
            anchors.left: parent.left

            Text {
                id: startDayInfo
                text: "Day"
                anchors.top: locationInputBoundingRect.bottom

            }
        }
        Rectangle{
            id: startDayInputBoundingRect
            width: weatherBrowser.width/2
            height: 25
            border.color: "black"
            border.width: 2
            anchors.top: startDateBoundingRect.bottom
            anchors.left: startDayBoundingRect.right
            TextInput
            {
                id: startDayInput
                width: startDayInputBoundingRect.width
                height: startDayInputBoundingRect.height
                text: getCurrentDate().getDate()
                leftPadding: 4
            }
        }

        Rectangle{
            id: startMonthBoundingRect
            width: weatherBrowser.width/2
            height: 25
            border.color: "black"
            anchors.top: startDayInputBoundingRect.bottom
            anchors.left: parent.left

            Text {
                id: startMonthInfo
                text: "Month"
                anchors.fill: parent

            }
        }
        Rectangle{
            id: startMonthInputBoundingRect
            width: weatherBrowser.width/2
            height: 25
            border.color: "black"
            border.width: 2
            anchors.top: startDayBoundingRect.bottom
            anchors.left: startMonthBoundingRect.right
            TextInput
            {
                id: startMonthInput
                width: startMonthInputBoundingRect.width
                height: startMonthInputBoundingRect.height
                anchors.fill: parent
                text: getCurrentDate().getMonth() +1
                leftPadding: 4
            }
        }

        Rectangle{
            id: startYearBoundingRect
            width: weatherBrowser.width/2
            height: 25
            border.color: "black"
            anchors.top: startMonthInputBoundingRect.bottom
            anchors.left: parent.left

            Text {
                id: startYearInfo
                text: "Year"
                anchors.fill: parent

            }
        }
        Rectangle{
            id: startYearInputBoundingRect
            width: weatherBrowser.width/2
            height: 25
            border.color: "black"
            border.width: 2
            anchors.top: startMonthInputBoundingRect.bottom
            anchors.left: startYearBoundingRect.right
            TextInput
            {
                id: startYearInput
                width: startMonthInputBoundingRect.width
                height: startMonthInputBoundingRect.height
                anchors.fill: parent
                text: getCurrentDate().getFullYear()
                leftPadding: 4
            }
        }

        Rectangle{
            id: startTimeBoundingRect
            width: weatherBrowser.width/2
            height: 25
            border.color: "black"
            anchors.top: startYearInputBoundingRect.bottom
            anchors.left: parent.left

            Text {
                id: startTimeInfo
                text: "Time (hh:mm:ss)"
                anchors.fill: parent

            }
        }
        Rectangle{
            id: startTimeInputBoundingRect
            width: weatherBrowser.width/2
            height: 25
            border.color: "black"
            border.width: 2
            anchors.top: startYearInputBoundingRect.bottom
            anchors.left: startTimeBoundingRect.right
            TextInput
            {
                id: startTimeInput
                width: startMonthInputBoundingRect.width
                height: startMonthInputBoundingRect.height
                anchors.fill: parent
                text: getCurrentDate().getHours() + ":" + getCurrentDate().getMinutes() + ":" + "00"
                leftPadding: 4
            }
        }

        Rectangle{
            id: endDateBoundingRect
            width: weatherBrowser.width
            height: 25
            border.color: "black"
            anchors.top: startTimeInputBoundingRect.bottom
            anchors.left: parent.left

            Text {
                id: endDayInfo
                text: "End Date"
                leftPadding: 5
                anchors.fill: parent
            }
        }

        Rectangle{
            id: endDayBoundingRect
            width: weatherBrowser.width/2
            height: 25
            border.color: "black"
            anchors.top: endDateBoundingRect.bottom
            anchors.left: parent.left

            Text {
                id: endDayInputInfo
                text: "Day"
                anchors.fill: parent

            }
        }
        Rectangle{
            id: endDayInputBoundingRect
            width: weatherBrowser.width/2
            height: 25
            border.color: "black"
            border.width: 2
            anchors.top: endDateBoundingRect.bottom
            anchors.left: endDayBoundingRect.right
            TextInput
            {
                id: endDayInput
                width: endDayInputBoundingRect.width
                height: endDayInputBoundingRect.height
                text: getTomorrow().getDate()
                leftPadding: 4
            }
        }

        Rectangle{
            id: endMonthBoundingRect
            width: weatherBrowser.width/2
            height: 25
            border.color: "black"
            anchors.top: endDayInputBoundingRect.bottom
            anchors.left: parent.left

            Text {
                id: endMonthInfo
                text: "Month"
                anchors.fill: parent

            }
        }
        Rectangle{
            id: endMonthInputBoundingRect
            width: weatherBrowser.width/2
            height: 25
            border.color: "black"
            border.width: 2
            anchors.top: endDayBoundingRect.bottom
            anchors.left: endMonthBoundingRect.right
            TextInput
            {
                id: endMonthInput
                width: endMonthInputBoundingRect.width
                height: endMonthInputBoundingRect.height
                anchors.fill: parent
                text: getTomorrow().getMonth() +1
                leftPadding: 4
            }
        }

        Rectangle{
            id: endYearBoundingRect
            width: weatherBrowser.width/2
            height: 25
            border.color: "black"
            anchors.top: endMonthInputBoundingRect.bottom
            anchors.left: parent.left

            Text {
                id: endYearInfo
                text: "Year"
                anchors.fill: parent

            }
        }
        Rectangle{
            id: endYearInputBoundingRect
            width: weatherBrowser.width/2
            height: 25
            border.color: "black"
            border.width: 2
            anchors.top: endMonthInputBoundingRect.bottom
            anchors.left: endYearBoundingRect.right
            TextInput
            {
                id: endYearInput
                width: endMonthInputBoundingRect.width
                height: endMonthInputBoundingRect.height
                anchors.fill: parent
                text: getTomorrow().getFullYear()
                leftPadding: 4
            }
        }

        Rectangle{
            id: endTimeBoundingRect
            width: weatherBrowser.width/2
            height: 25
            border.color: "black"
            anchors.top: endYearInputBoundingRect.bottom
            anchors.left: parent.left

            Text {
                id: endTimeInfo
                text: "Time (hh:mm:ss)"
                anchors.fill: parent

            }
        }
        Rectangle{
            id: endTimeInputBoundingRect
            width: weatherBrowser.width/2
            height: 25
            border.color: "black"
            border.width: 2
            anchors.top: endYearInputBoundingRect.bottom
            anchors.left: endTimeBoundingRect.right
            TextInput
            {
                id: endTimeInput
                width: startMonthInputBoundingRect.width
                height: startMonthInputBoundingRect.height
                anchors.fill: parent
                text: getTomorrow().getHours() + ":" + getTomorrow().getMinutes() + ":" + "00"
                leftPadding: 4
            }
        }


        Button{
            id: requestDataButton
            text: "Request Data"
            width: weatherBrowser.width
            height: 50
            anchors.bottom: parent.bottom
            anchors.left: parent.left
            onClicked: {
                viewController.setLocation(inputInfo.text);
                viewController.setDataSources(["solar", "temperature"])
                var startTime = startYearInput.text + "-" + startMonthInput.text + "-" +
                startDayInput.text + "T" + startTimeInput.text +"Z";
                var endTime = endYearInput.text + "-" + endMonthInput.text + "-" +
                endDayInput.text + "T" + endTimeInput.text +"Z";
                viewController.setTimeWindow(startTime, endTime);
                viewController.requestData();
            }
        }

        WeatherListModel
        {
            id: weatherModel

        }
        ConsumptionListModel
        {
            id: consumptionModel

        }

//        Controller{
//            id: viewController
//        }
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
            height: 170
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

        /*Loader{
            id: energy
            source: "energy.qml"
            height: parent.height/2.5

            anchors.left: consumptionBrowser.right
            anchors.top: parent.top
            anchors.right: parent.right

            anchors.topMargin: 150
            anchors.leftMargin: 200
            anchors.rightMargin: 600


        }*/

        Loader{

            id: view
            source: "view.qml"
            height: parent.height/1.25
            width: parent.width

            anchors.left: consumptionBrowser.right
            anchors.top: parent.top
            anchors.right: parent.right

            anchors.topMargin: 150
            anchors.leftMargin: 200
            anchors.rightMargin: 600

        }

        ConsumptionPieChart{
            id: consumptionChart
            height: view.height/2
            width: view.height/2

            anchors.left: view.right
            anchors.top: view.top
            anchors.topMargin: 50
            anchors.leftMargin: 50
        }

    }

function getCurrentDate(){
    var today = new Date();
    return  today;
}

function getTomorrow()
{
    var tomorrow = new Date();
    tomorrow.setDate(tomorrow.getDate() +1);
    return tomorrow;
}

}
