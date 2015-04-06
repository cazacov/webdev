var sprintf = require(['sprintf']).sprintf;

require(['debugwriter', 'sensors', 'controller3d'], function (DebugWriter, Sensors, Controller3D) {

    var debugWriter, controller;

    $().ready(function () {
        var debugBox = $(document.getElementById('debugBox'));

        debugWriter = new DebugWriter(debugBox);

        controller = new Controller3D(debugWriter, sprintf);
        controller.start();

        setTimeout(getSensors(), 200);
    });

    function getSensors() {
        $.get("/sensors", function(data, status) {
            //controller.useSensorData(data);
            debugWriter.show("AJAX ", "OK");
        })
        .fail(function(err) {
            debugWriter.show("AJAX ", "Error: ");
            console.log(err);
        })
        .always(function() {
            setTimeout(getSensors, 5);
        });
    }
});