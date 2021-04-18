import QtQuick 2.12
import QtQuick.Controls 2.12

Rectangle{
    id: titlerect
    width: 10
    height: 10
    radius: 5
    border.color: "black"
    Text {
        id: title
        text: qsTr("File name")
    }
    Rectangle{
        id: fileInputRect
        width: titlerect.width
        height: titlerect.height
        anchors.top: titlerect.bottom
        border.width: 2
        border.color: "black"
        radius: 2
        TextInput{
            id:fileInput
            anchors.fill: parent
            leftPadding: 4
        }
    }
    Rectangle{
        id: sourceRect
        width: titlerect.width
        height: titlerect.height*3
        anchors.top: fileInputRect.bottom
        border.width: 2
        border.color: "black"
        radius: 2
        Column{
            RadioButton{
                id: weatherRadioButton
                text: qsTr("Weather")
                width: sourceRect.width
                height: sourceRect.height/2
                checked: true
            }
            RadioButton{
                id:electricityRadioButton
                text: qsTr("Electricity")
                width: sourceRect.width
                height: sourceRect.height/2
            }
        }
    }
    RoundButton{
        id: saveButton
        width: titlerect.width
        height: titlerect.height
        anchors.top: sourceRect.bottom
        background: Rectangle{
            color: "#e6004c"
            radius: 5
            border.width: 2
            border.color: "black"
        }
        text: qsTr("Save file")
        contentItem: Text {
            text: saveButton.text
            horizontalAlignment: Text.AlignHCenter
            verticalAlignment: Text.AlignVCenter
        }
        onClicked: {
            var filepath = fileInput.text;
            var source;
            if(weatherRadioButton.checked)
            {
                source = "weather"        
            }
            else if(electricityRadioButton.checked)
            {
                source = "electricity"
            }
            if( filepath !== "" && source !== "")
            {
                if(viewController.saveData(filepath,source))
                {
                    popupText.text = "Saved " + source + " data to file " + filepath;
                    invalidSettingsPopup.open();
                }
                else{
                    popupText.text = "Failed to save " + source + " data to file " + filepath;
                    invalidSettingsPopup.open();
                }
            }
            else{
                popupText.text = "Invalid file name or source";
                invalidSettingsPopup.open();
            }
        }
    }
    RoundButton{
        id: loadButton
        width: titlerect.width
        height: titlerect.height
        anchors.top: saveButton.bottom
        text: qsTr("Load file")
        background: Rectangle{
            color: "#e6004c"
            radius: 5
            border.width: 2
            border.color: "black"
        }
        contentItem: Text {
            text: loadButton.text
            horizontalAlignment: Text.AlignHCenter
            verticalAlignment: Text.AlignVCenter
        }
        onClicked: {
            var filepath = fileInput.text;
            if( filepath !== "")
            {
                if(viewController.loadData(filepath))
                {
                    popupText.text = "Loaded data from " + filepath;
                    invalidSettingsPopup.open();
                }
                else{
                    popupText.text = "Failed to load data from " + filepath;
                    invalidSettingsPopup.open();
                }
            }
        }

    }


}
