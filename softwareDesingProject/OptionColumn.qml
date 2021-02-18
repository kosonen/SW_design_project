import QtQuick 2.15
import QtQuick.Controls 2.15

Item {
    property int spacing: 2
    ButtonGroup{
        id: consumtionPredictionGroup
    }
    Rectangle{
        border.color: "black"
        width: parent.width
        height: parent.height
  Column{
      id: columElement
      spacing: 2

      RadioButton{
          ButtonGroup.group: consumtionPredictionGroup
          text: qsTr("Predicition")
      }
      RadioButton{
          ButtonGroup.group: consumtionPredictionGroup
          text: qsTr("Tentative")
      }

  }
    }

}
