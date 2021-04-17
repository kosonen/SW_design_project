import QtQuick 2.0
import QtCharts 2.14

Item{

    Rectangle{
        width: parent.width
        height: parent.height
        border.color: "black"

        ChartView{
            anchors.fill: parent
            antialiasing: true

            DateTimeAxis{
                id: timeAxis
                min: model.startTime
                max: model.endTime
            }
            ValueAxis{
                id: weatherY
                min: model.weatherY.y
                max: model.weatherY.x
                titleText: getWeatherUnits()
            }

            ValueAxis{
                id: electricityY
                min: model.electricityY.y
                max: model.electricityY.x
            }


            LineSeries{
                id: weatherSeries
                color: getWeatherColor()
                name: getWeatherName()
                axisX: timeAxis
                axisY: weatherY
                width: 2

            }

            LineSeries{
                id: electricitySeries
                color: getElectricityColor()
                name: getElectricityName()
                axisX: timeAxis
                axisYRight: electricityY
                width: 2
            }

        }
    }


    Component.onCompleted:
    {
        model.weatherSeries = weatherSeries;
        model.elecrtricitySeries = electricitySeries;
    }

    function getWeatherColor()
    {
        var color;
        switch (model.weatherType){
            case "Temperature"      : color = "red" ; break;
            case "Wind speed"       : color = "cyan"; break;
            case "Humidity"         : color = "blue"; break;
            case "TotalCloudCover"  : color = "gray"; break;
        }
        return color;
    }

    function getWeatherName()
    {
        var name;
        switch (model.weatherType){
            case "Temperature"      : name = "Temperature"    ; break;
            case "Wind speed"       : name = "Wind speed"     ; break;
            case "Humidity"         : name = "Humidity"       ; break;
            case "TotalCloudCover"  : name = "Cloud Cover"    ; break;
        }
        return name;
    }

    function getWeatherUnits()
    {
        var unit;
        switch (model.weatherType){
            case "Temperature"      : unit = "°C"           ; break;
            case "Wind speed"       : unit = "M/S"          ; break;
            case "Humidity"         : unit = "%"            ; break;
            case "TotalCloudCover"  : unit = "Cloud Cover"  ; break;
        }
        return unit;
    }

    function getElectricityColor()
    {
        var color;
        switch (model.electricityType){
            case "Hydro power"  :   color = "darkblue"  ; break;
            case "Wind power"   :   color = "darkgreen" ; break;
            case "Nuclear power":   color = "darkcyan"  ; break;
        }
        return color;
    }

    function getElectricityName()
    {
        var name;
        switch (model.electricityType){
            case "Hydro power"  :   name = "Hydro power"    ; break;
            case "Wind power"   :   name = "Wind power"     ; break;
            case "Nuclear power":   name = "Nuclear power"  ; break;
        }
        return name;
    }

}

