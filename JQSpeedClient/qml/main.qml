import QtQuick
import QtQuick.Controls
import QtQuick.Window

Window {
    id: window
    width: 640
    height: 480
    visible: true
    color: "#131a24"

    Rectangle {
        id: serverHostContains
        width: 300
        height: 85
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.verticalCenter: parent.verticalCenter
        anchors.verticalCenterOffset: -120
        color: "#00000000"
        border.width: 2
        border.color: ( Helper.isConnected ) ? ( "#4CAF50" ) : ( "#9E9E9E" )
        radius: 10

        Text {
            anchors.horizontalCenter: parent.horizontalCenter
            y: 20
            color: "#ffffff"
            font.pixelSize: 18
            text: Helper.serverHost
        }

        Text {
            anchors.horizontalCenter: parent.horizontalCenter
            y: 50
            color: serverHostContains.border.color
            font.pixelSize: 13
            text: ( Helper.isConnected ) ? ( "Connected" ) : ( "Connecting" )
        }
    }

    Column {
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.top: serverHostContains.bottom
        anchors.topMargin: 40
        spacing: 15

        Text {
            anchors.horizontalCenter: parent.horizontalCenter
            anchors.horizontalCenterOffset: 65
            width: 220
            color: "#ffffff"
            text: {
                if ( Helper.isConnected && ( Helper.latency >= 0 ) )
                {
                    if ( Helper.latency === 0 )
                    {
                        return "Latency: <1 ms";
                    }

                    return "Latency: " + Helper.latency + " ms";
                }
                else
                {
                    return "Latency: N/A";
                }
            }

            Image {
                anchors.verticalCenter: parent.verticalCenter
                anchors.right: parent.left
                anchors.rightMargin: 12
                source: "qrc:/images/Latency.png"
            }
        }

        Row {
            anchors.horizontalCenter: parent.horizontalCenter
            anchors.horizontalCenterOffset: 60
            spacing: 15

            Text {
                width: 220
                color: "#ffffff"
                text: {
                    if ( Helper.isConnected && ( Helper.downloadSpeed >= 0 ) )
                    {
                        return "Download: " + Helper.downloadSpeed.toFixed( 1 ) + " Mbps";
                    }
                    else
                    {
                        return "Download: N/A";
                    }
                }

                Image {
                    anchors.verticalCenter: parent.verticalCenter
                    anchors.right: parent.left
                    anchors.rightMargin: 12
                    source: "qrc:/images/Download.png"
                }
            }

            Text {
                width: 220
                color: "#ffffff"
                text: {
                    if ( Helper.isConnected && ( Helper.uploadSpeed >= 0 ) )
                    {
                        return "Upload: " + Helper.uploadSpeed.toFixed( 1 ) + " Mbps";
                    }
                    else
                    {
                        return "Upload: N/A";
                    }
                }

                Image {
                    anchors.verticalCenter: parent.verticalCenter
                    anchors.right: parent.left
                    anchors.rightMargin: 12
                    source: "qrc:/images/Upload.png"
                }
            }
        }

        Item {
           width: 1
           height: 10
        }

        MouseArea {
            anchors.horizontalCenter: parent.horizontalCenter
            width: 100
            height: 100
            enabled: Helper.isConnected && !Helper.isMeasuringSpeed

            onClicked: {
                Helper.startMeasureDownloadSpeed();
            }

            Rectangle {
                anchors.fill: parent
                color: "#00000000"
                border.width: 2
                radius: 50
                border.color: {
                    if ( !enabled ) { return "#9E9E9E"; }

                    if ( !Helper.isConnected )
                    {
                        return "#9E9E9E";
                    }

                    if ( Helper.isMeasuringSpeed )
                    {
                        return "#FFC107";
                    }
                    else
                    {
                        return "#4CAF50";
                    }
                }
            }

            Text {
                anchors.centerIn: parent
                color: ( Helper.isConnected ) ? ( "#ffffff" ) : ( "#9E9E9E" )
                text: "Test"
            }
        }
    }

    Item {
        id: progressColumn
        anchors.bottom: parent.bottom
        width: parent.width
        height: 20

        Item {
            width: progressColumn.width * Math.max( 0, Helper.downloadSpeedTestProgress )
            height: 10
            clip: true

            Image {
                width: progressColumn.width
                height: 10
                source: "qrc:/images/DownloadProgress.png"
            }
        }

        Item {
            y: 10
            width: progressColumn.width * Math.max( 0, Helper.uploadSpeedTestProgress )
            height: 10
            clip: true

            Image {
                width: progressColumn.width
                height: 10
                source: "qrc:/images/UploadProgress.png"
            }
        }
    }
}
