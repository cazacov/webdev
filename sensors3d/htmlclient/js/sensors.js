/**
 * Created by Victor on 28.03.2015.
 */
define(function () {

    var that;

    function Sensors(debugWriter, sprintf) {
        that = this;
        this.debugWriter = debugWriter;
        this.sprintf = sprintf;

        if (!(this instanceof Sensors)) {
            throw new TypeError("Sensors constructor cannot be called as a function.");
        }

        if (window.DeviceMotionEvent) {
            // Listen for the event and handle DeviceOrientationEvent object
            window.addEventListener('devicemotion', deviceMotionHandler, false);
        }
        else {
            this.debugWriter.accelerometer("Not supported");
        }


        if (window.DeviceOrientationEvent) {
            // Listen for the event and handle DeviceOrientationEvent object
            window.addEventListener('deviceorientation', deviceOrientationHandler, false);
        }
        else {
            this.debugWriter.compass("Not supported");
        }
    }

    Sensors.prototype = {
        constructor: Sensors
    };

    function deviceMotionHandler(eventData) {
        var xyz = "[X, Y, Z]";

        // Grab the acceleration including gravity from the results
        acceleration = eventData.accelerationIncludingGravity;
        info = xyz.replace("X", acceleration.x);
        info = info.replace("Y", acceleration.y);
        info = info.replace("Z", acceleration.z);
        info = that.sprintf("%.3f %.3f %.3f", acceleration.x, acceleration.y, acceleration.z);
        that.debugWriter.accelerometer(info);
    }

    function deviceOrientationHandler(eventData) {
        var xyz = "[A, B, G]";
        info = xyz.replace("A", Math.round(eventData.alpha));
        info = info.replace("B", Math.round(eventData.beta));
        info = info.replace("G", Math.round(eventData.gamma));
        that.debugWriter.compas(info);
    }

    return Sensors;
});