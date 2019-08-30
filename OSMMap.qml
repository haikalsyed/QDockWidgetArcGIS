import QtQuick 2.0
import QtQuick.Controls 1.1
import QtLocation 5.6
import QtPositioning 5.6

Item {

    Plugin {
        id: mapPlugin
        name: "osm"
    }

    Map {
            anchors.fill: parent
            plugin: mapPlugin
            center: QtPositioning.coordinate(1.26, 103.77) // Singapore
            zoomLevel: 14
    }
}
