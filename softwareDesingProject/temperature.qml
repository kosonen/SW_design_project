import QtQuick 2.0
import QtCharts 2.15

Item{
    Rectangle{
        width: parent.width
        height: parent.height
        border.color: "black"

        ChartView{
            anchors.fill: parent
            antialiasing: true

            ValueAxis{id: customX}
            ValueAxis{id: customY}

            LineSeries{
                color: "red"
                name: "Lämpötila"
                //axisX: customX
                //axisY: customY
                XYPoint { x:0; y:3 }
                XYPoint { x:1; y:2 }
                XYPoint { x:2; y:4 }
                XYPoint { x:4; y:3 }

            }
        }
    }
}
