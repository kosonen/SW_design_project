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
                id: customY
                min: model.weatherY.y
                max: model.weatherY.x
            }


            LineSeries{
                id: weatherSeries
                color: getColor()
                name: getName()
                axisX: timeAxis
                axisY: customY

            }
        }
    }


    Component.onCompleted:
    {
        model.weatherSeries = weatherSeries;
    }

    function getColor()
    {
        var color;
        if (model.weatherType === "temperature")
        {
            color = "red";
        }
        if (model.weatherType === "wind")
        {
            color = "gray";
        }
        if (model.weatherType === "humidity")
        {
            color = "blue";
        }
        return color;
    }

    function getName()
    {
        var name;
        if (model.weatherType === "temperature")
        {
            name = "Temperature";
        }
        if (model.weatherType === "wind")
        {
            name = "Wind";
        }
        if (model.weatherType === "humidity")
        {
            name = "Humidity";
        }
        return name;
    }

}

