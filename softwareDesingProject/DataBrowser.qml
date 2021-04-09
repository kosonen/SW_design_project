import QtQuick 2.14


Item {
    id: browser
    property ListModel modelToView: listModel
    property int heightOfElement: 30
    property string type: ""

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
                onCurrentItemChanged: {

                    console.log(modelToView.get(list.currentIndex).name + ' selected');
                    if(type === "weather")
                    {
                        setWeatherProperties(modelToView.get(list.currentIndex).name )
                    }

                    return list.currentIndex;

            }
    }



}
    function setWeatherProperties(prop)
    {
        console.log("current index " + prop);
        model.setWeatherType(String(prop));
    }

}

