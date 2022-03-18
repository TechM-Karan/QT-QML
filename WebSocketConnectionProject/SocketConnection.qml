import QtQuick 2.0
import QtQuick.Controls 2.12
import QtWebSockets 1.0

Item {
    id:connectionPage
    anchors.fill: parent

    Component.onCompleted: {
        socket.active = true
    }

    WebSocket {
        id: socket
        url: "wss://demo.piesocket.com/v3/channel_1?api_key=oCdCMcMPQpbvNjUIzqtvF1d2X2okWpDQj4AwARJuAgtjhzKxVEjQU6IdCjwm&notify_self"
        onTextMessageReceived: {
            respModel.insert(0, {msg: message});
        }
        onStatusChanged: if (socket.status == WebSocket.Error) {
                             console.log("Error: " + socket.errorString)
                         } else if (socket.status == WebSocket.Open) {
                             socket.sendTextMessage("Wel come")
                         } else if (socket.status == WebSocket.Closed) {

                         }
        active: false
    }
    Column{
        anchors.fill: parent

        Rectangle{
            id:header
            width: parent.width
            height: parent.height*.1
            color: "#00796b"
            Text{
                anchors.centerIn: parent
                text: "Web Socket Connection"
                font.pointSize: 24
                font.bold: true
                color: "white"
            }
        }

        Rectangle{
            width: parent.width
            height: parent.height*.08
            color: "#f2f2f2"
            Row{
                anchors.fill: parent
                spacing: 2
                Rectangle{
                    id:tab1Container
                    width: parent.width/2
                    height: parent.height
                    color: "#48a999"
                    Text{
                        anchors.centerIn: parent
                        text:"Server"
                        font.pointSize: 20
                        color: "white"
                    }
                }

                Rectangle{
                    id:tab2Container
                    width: parent.width/2
                    height: parent.height
                    color: "#48a999"
                    Text{
                        anchors.centerIn: parent
                        text:"Client"
                        font.pointSize: 20
                        color: "white"
                    }
                }
            }
        }

        Item{
            width: parent.width
            height: parent.height*.82
            Row{
                anchors.fill: parent
                Rectangle{
                    width: parent.width/2
                    height: parent.height
                    color: "#3E497A"
                    Column{
                        anchors.top: parent.top
                        anchors.topMargin: 50
                        anchors.horizontalCenter: parent.horizontalCenter
                        spacing: 10
                        TextField{
                            id:sendData
                            width: parent.parent.width*.8
                            height: 50
                            anchors.horizontalCenter: parent.horizontalCenter
                            placeholderText: "Send Message"
                        }
                        Button{
                            width: 100
                            height: 40
                            anchors.horizontalCenter: parent.horizontalCenter
                            text: "Send"
                            onClicked: {
                                socket.sendTextMessage(sendData.text.trim());
                                sendData.text = "";
                            }
                        }
                    }
                }

                Rectangle{
                    width: parent.width/2
                    height: parent.height
                    color: "#21325E"
                    ListModel{
                        id:respModel
                    }

                    ListView{
                        id:responseList
                        anchors.fill: parent
                        model: respModel
                        delegate: clientDelegate
                        clip: true
                    }
                    Component{
                        id:clientDelegate
                        Rectangle{
                            width: responseList.width
                            height: responseList.height*.1
                            Text{
                                width: parent.width
                                horizontalAlignment: Text.AlignHCenter
                                anchors.centerIn: parent
                                text: msg
                                font.pointSize: 20
                                wrapMode: Text.WordWrap
                            }
                            Rectangle{
                                width: parent.width
                                height: 1
                                anchors.bottom: parent.bottom
                                color: "black"
                            }
                        }
                    }
                }
            }
        }
    }
}
