import QtQuick 2.15

Item {
    id: browser
    property ListModel modelToView: model
    property int heightOfElement: 30

    Rectangle{
        id: borders
        width: parent.width
        height: parent.height
        border.color: "black"

            ListView {
                id: list
                anchors.fill: parent
                model: modelToView
                delegate: Component {
                    Item{
                            width: parent.width
                            height: heightOfElement

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
