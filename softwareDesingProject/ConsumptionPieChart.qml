import QtQuick 2.15
import QtCharts 2.15

Item {
    Rectangle{
        width: parent.width
        height: parent.height
        border.color: "black"

        ChartView{
            id: chart
            title: "Energy production forms in finland"
            anchors.fill: parent
            legend.alignment: Qt.AlignTop
            antialiasing: true
            PieSeries{
                id: serie
                PieSlice{ label: "Solar power"; value: 15 }
                PieSlice{ label: "Nuclear"; value: 30 }
                PieSlice{ label: "Hydro power"; value: 25}

            }
        }
    }
}
