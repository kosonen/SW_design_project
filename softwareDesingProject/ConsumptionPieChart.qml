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
                id: pieseries
            }

        }
    }

    Rectangle{
        id: hydroRect
        height: 25
        width: parent.width/3
        anchors.bottom: parent.top
        anchors.left: parent.left
        border.color: "black"
        border.width: 2
        Text{
            id: hydroLabel
            anchors.fill: parent
        }

    }

    Rectangle{
        id: nucklearRect
        height: 25
        width: parent.width/3
        anchors.bottom: parent.top
        anchors.left: hydroRect.right
        border.color: "black"
        border.width: 2
        Text{
            id: nucklearLabel
            anchors.fill: parent
        }

    }

    Rectangle{
        id: windRect
        height: 25
        width: parent.width/3
        anchors.bottom: parent.top
        anchors.left: nucklearRect.right
        border.color: "black"
        border.width: 2
        Text {
            id: windLabel
            anchors.fill: parent
        }

    }

    Component.onCompleted: {
        model.pieSeries = pieseries;
    }
}
