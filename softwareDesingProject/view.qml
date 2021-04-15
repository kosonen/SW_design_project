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
                min: 0
                max: 100
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
        if (model.weatherType === "Temperature")
        {
            color = "red";
        }
        if (model.weatherType === "Wind speed")
        {
            color = "gray";
        }
        if (model.weatherType === "Humidity")
        {
            color = "blue";
        }
        return color;
    }

    function getName()
    {
        var name;
        if (model.weatherType === "Temperature")
        {
            name = "Temperature";
        }
        if (model.weatherType === "Wind speed")
        {
            name = "Wind";
        }
        if (model.weatherType === "Humidity")
        {
            name = "Humidity";
        }
        return name;
    }

    function getUnits()
    {
        var unit;
        if (model.weatherType === "Temperature")
        {
            unit = "°C";
        }
        if (model.weatherType === "Wind speed")
        {
            unit = "M/S";
        }
        if (model.weatherType === "Humidity")
        {
            unit = "%";
        }
        return unit;
    }
}

