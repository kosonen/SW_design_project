import QtQuick 2.14


Item {
    id: browser
    property ListModel modelToView: listModel
    property int heightOfElement: 30
    property string type: ""
    property string value: ""
    //signal optionChanged;

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

                    console.log(modelToView.get(list.currentIndex).name + ' selected');
                    if(type === "weather")
                    {
                        setWeatherProperties(modelToView.get(list.currentIndex).name);

                    }
                    else
                    {
                        setProperties(modelToView.get(list.currentIndex).name);

                    }

                    return list.currentIndex;

            }
    }



}
    function setWeatherProperties(prop)
    {
        console.log("current index " + prop);
        //model.setWeatherType(String(prop));
        viewController.setWeatherType(String(prop));
        browser.value = prop;
        //viewController.setDataSources([String(prop)]);
        viewController.requestData();
        //optionChanged();
    }

    function setProperties(prop)
    {
        console.log("current index " + prop);
        browser.value = prop;
        //viewController.setDataSources([String(prop)]);
        viewController.requestData();
        //optionChanged();

    }

    function initWeatherProperties(prop)
    {
        console.log("current index " + prop);
        //model.setWeatherType(String(prop));
        viewController.setWeatherType(String(prop));
        browser.value = prop;
        //viewController.setDataSources([String(prop)]);
        //viewController.requestData();
        //optionChanged();
    }

    function initProperties(prop)
    {
        console.log("current index " + prop);
        //viewController.setDataSources([String(prop)]);
        browser.value = prop;
        //viewController.requestData();
        //optionChanged();
    }

    Component.onCompleted: {
        console.log(modelToView.get(list.currentIndex).name + ' selected');
        if(type === "weather")
        {
            initWeatherProperties(modelToView.get(list.currentIndex).name )
        }
        else // TÄMÄ ON KESKEN, TEE LOPPUUN!!!!
        {
            initProperties(modelToView.get(list.currentIndex).name);
        }
    }

}

