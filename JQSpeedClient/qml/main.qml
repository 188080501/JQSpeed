import QtQuick
import QtQuick.Controls
import QtQuick.Window

Window {
    id: window
    width: 640
    height: 480
    visible: true
    color: "#131a24"

    Column {
        anchors.centerIn: parent

        Text {
            width: 100
            color: "#ffffff"
            text: "Server: " + Helper.serverHost
        }

        Text {
            width: 100
            color: "#ffffff"
            text: ( Helper.isConnected ) ? ( "Connected" ) : ( "Connecting" )
        }

        Text {
            width: 100
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
        }

        Text {
            width: 100
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
        }

        Text {
            width: 100
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
        }

        Item {
           width: 1
           height: 10
        }

        Button {
            anchors.horizontalCenter: parent.horizontalCenter
            width: 100
            height: 40
            text: "Test"
            enabled: Helper.isConnected && !Helper.isMeasuringSpeed

            onClicked: {
                Helper.startMeasureDownloadSpeed();
            }
        }
    }
}
