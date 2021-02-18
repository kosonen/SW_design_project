import QtQuick 2.15
import QtQuick.Controls 2.15

Item {
    property int spacing: 2
    id: optionItem
    ButtonGroup{
        id: consumtionPredictionGroup
        buttons: columElement.children
    }
    Rectangle{
        id:boundingrect
        border.color: "black"
        width: parent.width
        height: parent.height
  Column{
      id: columElement
      spacing: 2

      RadioButton{
          ButtonGroup.group: consumtionPredictionGroup
          text: qsTr("Consumed")
      }
      RadioButton{
          ButtonGroup.group: consumtionPredictionGroup
          text: qsTr("Producted")
      }
      RadioButton{
          ButtonGroup.group: consumtionPredictionGroup
          text: qsTr("Predicted consupmtion")
      }
      RadioButton{
          ButtonGroup.group: consumtionPredictionGroup
          text: qsTr("Tentative production")
      }


  }
    }

}
