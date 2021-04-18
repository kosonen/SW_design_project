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
            }

            ValueAxis{
                id: electricityY
            }

            ValueAxis{
                id: savedY
            }


            LineSeries{
                id: weatherSeries
                axisX: timeAxis
                axisY: weatherY
                width: 2

            }

            LineSeries{
                id: electricitySeries
                axisX: timeAxis
                axisYRight: electricityY
                width: 2
            }

            LineSeries{
                id: savedSeries
                axisX: timeAxis
                width: 2
                axisYRight: savedY
            }

        }
    }


    Component.onCompleted:
    {
        model.weatherSeries = weatherSeries;
        model.elecrtricitySeries = electricitySeries;
        model.savedSeries = savedSeries;

        model.weatherY = weatherY;
        model.electricityY = electricityY;
        model.savedY = savedY;
    }

}

