var sprintf = require(['sprintf']).sprintf;

require(['debugwriter', 'sensors', 'controller3d'], function (DebugWriter, Sensors, Controller3D) {

    $().ready(function () {
        var debugBox = $(document.getElementById('debugBox'));

        var debugWriter = new DebugWriter(debugBox);

        var controller = new Controller3D(debugWriter, sprintf);
        controller.start();

        /*
        Test rotation
        var phi = 0;
        setInterval(function() {
            var rm = new THREE.Matrix4();
            rm.makeRotationZ(phi);
            controller.applyRotationMatrix(rm);
            phi += Math.PI / 180.0;
        }, 100);
        */
    });
});