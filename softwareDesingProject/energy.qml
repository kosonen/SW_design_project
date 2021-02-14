import QtQuick 2.0
import QtCharts 2.15

Item {

    Rectangle{
        width: parent.width
        height: parent.height
        border.color: "black"

        ChartView{
            title: "Enegy Production Sources"
            anchors.fill: parent
            antialiasing: true

            ValueAxis {
                id: time
                min: 0
                max: 24
                tickCount: 24
                labelFormat: "‰.0f"
            }

            AreaSeries{
                name: "Solar"
                axisX: ValueAxis
                upperSeries: LineSeries{
                    XYPoint { x: 0; y: 1 }
                    XYPoint { x: 1; y: 1 }
                    XYPoint { x: 2; y: 1 }
                    XYPoint { x: 3; y: 1 }
                }
            }

            AreaSeries{
                name: "Wind"
            }

            AreaSeries{
                name: "Hydro"
            }

        }

    }

}
