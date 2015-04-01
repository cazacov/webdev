var sprintf = require(['sprintf']).sprintf;

require(['debugwriter', 'sensors', 'controllertd'], function (DebugWriter, Sensors, Controller3D) {

    $().ready(function () {
        var debugBox = $(document.getElementById('debugBox'));

        var debugWriter = new DebugWriter(debugBox);
        //var sensors = new Sensors(debugwriter, sprintf);

        var controller = new Controller3D(debugWriter, sprintf);
        controller.start();
    });
});