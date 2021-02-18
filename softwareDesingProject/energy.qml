import QtQuick 2.0
import QtCharts 2.15

Item {

    Rectangle{
        width: parent.width
        height: parent.height
        border.color: "black"

        ChartView{
            title: "Energiatuotanto"
            anchors.fill: parent
            antialiasing: true

            ValueAxis{id: customX}
            ValueAxis{id: customY}

            LineSeries{
                name: "*energiamuoto*"
                //axisX: customX
                //axisY: customY
                XYPoint { x:0; y:0 }
                XYPoint { x:1; y:3 }
                XYPoint { x:2; y:2 }
                XYPoint { x:4; y:6 }

            }
        }



    }

}
