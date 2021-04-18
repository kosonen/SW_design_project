import QtQuick 2.14


Item {
    id: browser
    property ListModel modelToView: listModel
    property int heightOfElement: 30
    property string type: ""
    property string value: ""

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
                            Row{
                                spacing: 10
                                Text {
                                    text: name
                                    wrapMode: Text.WordWrap
                                }
                                Image {
                                    source: fileUrl
                                }
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
                    if(type === "weather")
                    {
                        setWeatherProperties(modelToView.get(list.currentIndex).name);
                    }
                    else if (type === "consumption")
                    {
                        setElectricityProperties(modelToView.get(list.currentIndex).name);
                    }

                    else
                    {
                        console.log("ei mihinkään")
                        setProperties(modelToView.get(list.currentIndex).name);

                    }

                    return list.currentIndex;

            }
    }



}
    function setWeatherProperties(prop)
    {
        browser.value = prop;
    }

    function setElectricityProperties(prop)
    {
        browser.value = prop;
    }

    function setProperties(prop)
    {
        browser.value = prop;
    }

    function initWeatherProperties(prop)
    {
        browser.value = prop;
    }

    function initElecticityProperties(prop)
    {
        browser.value = prop;
    }

    function initProperties(prop)
    {
        browser.value = prop;
    }

    Component.onCompleted: {
        console.log(modelToView.get(list.currentIndex).name + ' selected');
        if(type === "weather")
        {
            initWeatherProperties(modelToView.get(list.currentIndex).name);
        }
        else if(type === "consumption")
        {
            initElecticityProperties(modelToView.get(list.currentIndex).name);
        }

        else
        {
            initProperties(modelToView.get(list.currentIndex).name);
        }
    }

}

