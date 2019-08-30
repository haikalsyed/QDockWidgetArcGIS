import QtQuick 2.6
import QtQuick.Controls 2.2
import QtLocation 5.6
import Esri.ArcGISRuntime 100.5


Rectangle {
    MapView
    {
        id : mapView
        anchors.fill: parent

        Map
        {
            id: map
            BasemapDarkGrayCanvasVector{}

            ViewpointCenter
            {
                    center: Point
                    {
                        x: 103.77 //-118.80543                                        // Longitude
                        y: 1.26   //34.02700                                          // Latitude
                        spatialReference: SpatialReference { wkid: 3414 }    // WGS84
                    }
                    targetScale: 300000
            }
        }
    }
}
