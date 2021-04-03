import QtQuick 2.14
import QtCharts 2.14

Item {
    Rectangle{
        width: parent.width
        height: parent.height
        border.color: "black"

        ChartView{
            id: chart
            title: "Electricity production forms in finland"
            anchors.fill: parent
            legend.alignment: Qt.AlignTop
            antialiasing: true
            PieSeries{
                id: serie
                PieSlice{ label: "Wind"; value: 15 }
                PieSlice{ label: "Nuclear"; value: 30 }
                PieSlice{ label: "Hydro"; value: 25}
                PieSlice{ label: "Other"; value: 28}

            }
        }
    }
}
