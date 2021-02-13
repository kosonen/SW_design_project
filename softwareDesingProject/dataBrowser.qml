import QtQuick 2.0

Item {
    id: browser
   // width: parent.width /5
   // height: parent.height

    ListModel {
            id: model

            ListElement {
                name:'Solar Power'

            }
            ListElement {
                name:'Wind Power'
            }
            ListElement {
                name:'Hydro Power'
            }
        }

    Rectangle{
        id: borders
        width: parent.width
        height: parent.height
        border.color: "black"

            ListView {
                id: list
                anchors.fill: parent
                model: model
                delegate: Component {
                    Item{
                            width: parent.width
                            height: 30

                            Column{
                                Text { text: name
                                wrapMode: Text.WordWrap}
                            }
                            MouseArea {
                                anchors.fill: parent
                                onClicked: list.currentIndex = index
                            }
                        }
                }
                highlight: Rectangle {
                    color: 'grey'

                }
                focus: true
                onCurrentItemChanged: console.log(model.get(list.currentIndex).name + ' selected')

            }
    }



}
