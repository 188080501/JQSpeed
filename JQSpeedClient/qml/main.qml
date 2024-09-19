import QtQuick
import QtQuick.Window

Window {
    id: window
    width: 640
    height: 480
    visible: true
    color: "#eaeaea"

    Column {
        anchors.centerIn: parent

        Text {
            width: 100
            text: "Server: " + Helper.serverHost
        }

        Text {
            width: 100
            text: ( Helper.isConnected ) ? ( "Connected" ) : ( "Connecting" )
        }

        Text {
            width: 100
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
    }
}
