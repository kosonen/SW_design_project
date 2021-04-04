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
                id: tempSeries
                color: "red"
                name: "Temperature"
                axisX: timeAxis
                axisY: customY

            }
        }
    }
    Component.onCompleted:
    {
        model.tempSeries = tempSeries;
    }
}
