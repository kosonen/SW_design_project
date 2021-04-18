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
                        console.log("sää muuttuu")
                        setWeatherProperties(modelToView.get(list.currentIndex).name);
                        //parent.parent.requestData();
                        //viewController.setDataSources(modelToView.get(list.currentIndex).name)
                        //viewController.requestData();


                    }
                    else if (type === "consumption")
                    {
                        console.log("sähkö muuttuu")
                        setElectricityProperties(modelToView.get(list.currentIndex).name);
                        //parent.parent.requestData();
                        //viewController.setDataSources(modelToView.get(list.currentIndex).name)
                        //viewController.requestData();
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
        console.log("current index " + prop);
        browser.value = prop;
        //viewController.requestData();
    }

    function setElectricityProperties(prop)
    {
        console.log("current index " + prop);
        browser.value = prop;
        //viewController.requestData();
    }

    function setProperties(prop)
    {
        console.log("current index " + prop);
        browser.value = prop;
        //viewController.requestData();


    }

    function initWeatherProperties(prop)
    {
        console.log("current index " + prop);
        browser.value = prop;

    }

    function initElecticityProperties(prop)
    {
        console.log("current index " + prop);
        browser.value = prop;
    }

    function initProperties(prop)
    {
        console.log("current index " + prop);

        browser.value = prop;

    }

    Component.onCompleted: {
        console.log(modelToView.get(list.currentIndex).name + ' selected');
        if(type === "weather")
        {
            console.log("weather initialized");
            initWeatherProperties(modelToView.get(list.currentIndex).name);
        }
        else if(type === "consumption")
        {
            console.log("electricity initialized");
            initElecticityProperties(modelToView.get(list.currentIndex).name);
        }

        else // TÄMÄ ON KESKEN, TEE LOPPUUN!!!!
        {
            initProperties(modelToView.get(list.currentIndex).name);
        }
    }

}

