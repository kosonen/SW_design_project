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
                titleText: getUnits()
            }

            ValueAxis{
                id: electricityY
                min: model.electricityY.y
                max: model.electricityY.x
            }


            LineSeries{
                id: weatherSeries
                color: getColor()
                name: getName()
                axisX: timeAxis
                axisY: weatherY

            }

            LineSeries{
                id: electricitySeries
                //color: "black"
                name: "electricity placeholder"
                axisX: timeAxis
                axisYRight: electricityY
            }

        }
    }


    Component.onCompleted:
    {
        model.weatherSeries = weatherSeries;
        model.elecrtricitySeries = electricitySeries;
    }

    function getColor()
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

    function getName()
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

    function getUnits()
    {
        var unit;
        switch (model.weatherType){
            case "Temperature"      : unit = "°C"   ; break;
            case "Wind speed"       : unit = "M/S"  ; break;
            case "Humidity"         : unit = "%"    ; break;
            case "TotalCloudCover"  : unit = ""     ; break;
        }
        return unit;
    }
}

