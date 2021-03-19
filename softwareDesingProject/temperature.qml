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

            ValueAxis{
                id: customX
                min: -10
                max: 10
            }
            ValueAxis{
                id: customY
                min: -10
                max: 10
            }

            LineSeries{
                id: tempSeries
                color: "red"
                name: "Temperature"
                axisX: customX
                axisY: customY
                /*
                XYPoint { x:0; y:3 }
                XYPoint { x:1; y:2 }
                XYPoint { x:2; y:4 }
                XYPoint { x:4; y:3 }*/

            }
        }
    }
    Component.onCompleted:
    {
        model.tempSeries = tempSeries;
        model.populateTempSeries();
    }
}
