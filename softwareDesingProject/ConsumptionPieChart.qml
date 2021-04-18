import QtQuick 2.14
import QtCharts 2.14

Item {

    Timer{
        interval: 1000;
        running: true
        onTriggered: {
            hydroLabel.text = "Hydro: " + model.getHydroProduction();
            nucklearLabel.text = "Nuclear: " + model.getNuclearProduction();
            windLabel.text = "Wind: "+ model.getWindProduction();
            stop();
        }
    }

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
                onAdded: {
                    hydroLabel.text = "Hydro: " + model.getHydroProduction();
                    nucklearLabel.text = "Nuclear: " + model.getNuclearProduction();
                    windLabel.text = "Wind: "+ model.getWindProduction();
                }
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
            font.pointSize: 10
            id: hydroLabel
            anchors.fill: parent
            leftPadding: 2
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
            font.pointSize: 10
            id: nucklearLabel
            anchors.fill: parent
            leftPadding: 2
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
            font.pointSize: 10
            id: windLabel
            anchors.fill: parent
            leftPadding: 2
        }

    }

    Component.onCompleted: {
        model.pieSeries = pieseries;
        hydroLabel.text = "Hydro: " + model.getHydroProduction();
        nucklearLabel.text = "Nuclear: " + model.getNuclearProduction();
        windLabel.text = "Wind: "+ model.getWindProduction();
    }
}
