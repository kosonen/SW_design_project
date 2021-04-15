import QtQuick 2.14

ListModel{
    id: weatherModel
    ListElement {
        name:'Temperature'
        fileUrl: "g3943.png"

    }
    ListElement {
        name:'Wind speed'
        fileUrl: "g3882.png"
    }
    ListElement {
        name:'Humidity'
        fileUrl: "drop.png"
    }
    ListElement{
        name: "Cloudiness"
        fileUrl: "cloud.png"
    }
}


