import QtQuick 2.12
import QtQuick.Window 2.12
import QtQuick.Controls 2.14
import QtQml 2.14
//import controller 1.0

Window {
    width: screen.height * 4/3
    height: screen.height
    visible: true
    title: qsTr("Hello World")

    Rectangle{
        id: viewBounds
        width: parent.width
        height: parent.height
        color: "cyan"

        Rectangle{
            id: locationInfoBoudningRect
            width: weatherBrowser.width
            height: 25
            border.color: "black"
            anchors.top: weatherBrowser.bottom
            anchors.left: parent.left
            radius: 5
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
                onEditingFinished: {
                    requestData()
                }
            }
        }

        Rectangle{
            id: startDateBoundingRect
            width: weatherBrowser.width
            height: 25
            border.color: "black"
            anchors.top: locationInputBoundingRect.bottom
            anchors.left: parent.left
            radius: 5
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
            radius: 2
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
                text: {
                    if(getCurrentDate().getDate() < 10)
                    {
                        startDayInput.text = "0" + getCurrentDate().getDate() - 1;
                    }
                    else
                    {
                        startDayInput.text = getCurrentDate().getDate() -1;
                    }
                }
                onEditingFinished: {
                    requestData()
                }
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
            radius: 2
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
                text: {
                    if(getCurrentDate().getMonth() + 1 < 10)
                    {
                        var input =  getCurrentDate().getMonth() +1;
                        startMonthInput.text = "0" + input;
                    }
                    else
                    {
                        var inputUnderTen =  getCurrentDate().getMonth() +1;
                        startMonthInput.text = inputUnderTen;
                    }
                }
                onEditingFinished: {
                    requestData()
                }
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
            radius: 2
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
                onEditingFinished: {
                    requestData()
                }
            }
        }

        Rectangle{
            id: startTimeBoundingRect
            width: weatherBrowser.width/2
            height: 25
            border.color: "black"
            anchors.top: startYearInputBoundingRect.bottom
            anchors.left: parent.left
            radius: 2
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
                text: {
                    var retString = "";
                    if(getCurrentDate().getHours() < 10)
                    {
                        retString += "0"+ getCurrentDate().getHours();
                    }
                    else
                    {
                        retString  += getCurrentDate().getHours();
                    }
                    retString += ":";
                    if(getCurrentDate().getMinutes() < 10)
                    {
                        retString += "0" + getCurrentDate().getMinutes();
                    }
                    else{
                        retString += getCurrentDate().getMinutes();
                    }
                    retString += ":00";
                    startTimeInput.text = retString;
                }
                onEditingFinished: {
                    requestData()
                }
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
            radius: 5
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
            radius: 2
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
                text: {
                    if(getTomorrow().getDate() < 10)
                    {
                        endDayInput.text = "0" + getTomorrow().getDate();
                    }
                    else
                    {
                        endDayInput.text = getTomorrow().getDate();
                    }
                }
                leftPadding: 4
                onEditingFinished: {
                    requestData()
                }
            }
        }

        Rectangle{
            id: endMonthBoundingRect
            width: weatherBrowser.width/2
            height: 25
            border.color: "black"
            anchors.top: endDayInputBoundingRect.bottom
            anchors.left: parent.left
            radius: 2

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
                text: {
                    if(getTomorrow().getMonth() + 1< 10)
                    {
                        var input = getTomorrow().getMonth() + 1;
                        endMonthInput.text = "0" + input;
                    }
                    else
                    {
                        endMonthInput.text = getTomorrow().getMonth() + 1;
                    }
                }
                leftPadding: 4
                onEditingFinished: {
                    requestData()
                }
            }
        }

        Rectangle{
            id: endYearBoundingRect
            width: weatherBrowser.width/2
            height: 25
            border.color: "black"
            anchors.top: endMonthInputBoundingRect.bottom
            anchors.left: parent.left
            radius: 2
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
                onEditingFinished: {
                    requestData()
                }
            }
        }

        Rectangle{
            id: endTimeBoundingRect
            width: weatherBrowser.width/2
            height: 25
            border.color: "black"
            anchors.top: endYearInputBoundingRect.bottom
            anchors.left: parent.left
            radius: 2
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
               // text: getTomorrow().getHours() + "." + getTomorrow().getMinutes() + "." + "00"
                text: {
                    var retString = "";
                    if(getTomorrow().getHours() < 10)
                    {
                        retString += "0"+ getTomorrow().getHours();
                    }
                    else
                    {
                        retString  += getTomorrow().getHours();
                    }
                    retString += ":";
                    if(getTomorrow().getMinutes() < 10)
                    {
                        retString += "0" + getTomorrow().getMinutes();
                    }
                    else{
                        retString += getTomorrow().getMinutes();
                    }
                    retString += ":00";
                    endTimeInput.text = retString;
                }
                onEditingFinished: {
                    requestData()
                }

                leftPadding: 4
            }
        }


        RoundButton{
            id: requestDataButton
            text: "Request Data"
            contentItem: Text {
                text: requestDataButton.text
                color: "cyan"
                horizontalAlignment: Text.AlignHCenter
                verticalAlignment: Text.AlignVCenter
            }
            width: weatherBrowser.width
            height: 50
            anchors.bottom: parent.bottom
            anchors.left: parent.left
            background: Rectangle{
                color: "#e6004c"
                radius: 5
            }

            radius: 5
            onClicked: {
                requestData();
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

        Rectangle{
            id: titleConsumption
            width: consumptionBrowser.width
            height: 25
            anchors.top: parent.top
            anchors.left: parent.left
            border.color: "black"
            radius: 5
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
            type: "consumption"
            //optionChanged.
        }

        Rectangle{
            id: titleWeather
            width: weatherBrowser.width
            height: 25
            anchors.top: consumptionBrowser.bottom
            border.color: "black"
            radius: 5
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
            type: "weather"
        }


        Loader{

            id: view
            source: "view.qml"
            height: parent.height/2
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
            height: 4*view.height/5
            width: 4*view.height/5

            anchors.left: view.right
            anchors.bottom: view.bottom
            anchors.leftMargin: 25
        }

        SaveLoad{
            width: consumptionBrowser.width
            height: 25
            anchors.top:parent.top
            anchors.right: parent.right
        }

        Popup{
            id: invalidSettingsPopup
            //width: 600
           // height: 200
            anchors.centerIn: viewBounds
            background: Rectangle{
                id: popupBackground
                width: 600
                height: 200
                color: "red"
                radius: 5
                anchors.centerIn: viewBounds
                RoundButton{
                    id: closeButton
                    text: qsTr("Close popup");
                    anchors.bottom: popupBackground.bottom
                    anchors.horizontalCenter:  popupBackground.horizontalCenter
                    width: weatherBrowser.width
                    height: 50
                    anchors.bottomMargin: 10
                    radius: 5
                    onClicked: invalidSettingsPopup.close();
                }
            }

            focus: true
            modal: true
            contentItem: Text {
                id: popupText
                text: qsTr("text")
                color: "black"
                anchors.horizontalCenter: popupBackground.horizontalCenter
                anchors.verticalCenter: popupBackground.verticalCenter
            }


        }

        Rectangle{
            id: dataProcessingRect
            border.color: "black"
            width: consumptionBrowser.width
            height: 130
            anchors.left: parent.left
            anchors.top: endTimeInputBoundingRect.bottom
                Column{
                    id: columElement
                    spacing: 2
                    RadioButton{
                        id: avgButton
                        checked: true
                        text: "AVG"
                        onCheckedChanged: {
                            if(avgButton.checked)
                            {
                                viewController.setDataProcessing("AVG")
                            }
                        }
                    }
                    RadioButton{
                        id: maxButton
                        checked: false
                        text: "MAX"
                        onCheckedChanged: {
                            if(maxButton.checked)
                            {
                                viewController.setDataProcessing("MAX")
                            }
                        }
                    }
                    RadioButton{
                        id: minButton
                        checked: false
                        text: "MIN"
                        onCheckedChanged: {
                            if(minButton.checked)
                            {
                                viewController.setDataProcessing("MIN")
                            }
                        }
                    }

                }
            }


    }

    Component.onCompleted:{
        viewController.setDataProcessing("AVG");
        requestData();
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


function requestData()
{
    viewController.setLocation(inputInfo.text);
    console.log(" weather browser value: " + weatherBrowser.value + ", consumption browser value: " + consumptionBrowser.value)
    viewController.setDataSources([weatherBrowser.value, consumptionBrowser.value])


    var startTime = startYearInput.text + "-" + startMonthInput.text + "-" +
    startDayInput.text + "T" + startTimeInput.text +"Z";
    var endTime = endYearInput.text + "-" + endMonthInput.text + "-" +
    endDayInput.text + "T" + endTimeInput.text +"Z";
    viewController.setTimeWindow(startTime, endTime);
    viewController.requestData();
    var errMsg = viewController.getPopupError();
    console.log("request error " + errMsg);
    if(errMsg !== "")
    {
        showPopup(errMsg);
    }
}

function showPopup(msg)
{
    console.log("show Popup " << msg);
    popupText.text = msg;
    invalidSettingsPopup.open();
}

}

