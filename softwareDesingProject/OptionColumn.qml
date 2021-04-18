import QtQuick 2.14
import QtQuick.Controls 2.14

Item {
    property int spacing: 2
    id: optionItem
    ButtonGroup{
        id: dataProcessing
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
          ButtonGroup.group: dataProcessing
          text: qsTr("Consumed")
      }
      RadioButton{
          ButtonGroup.group: dataProcessing
          text: qsTr("Producted")
      }
      RadioButton{
          ButtonGroup.group: dataProcessing
          text: qsTr("Predicted consupmtion")
      }


  }
    }

}
