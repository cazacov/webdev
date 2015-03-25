/**
 * Created by Victor on 25.03.2015.
 */
if (window.DeviceMotionEvent) {
    // Listen for the event and handle DeviceOrientationEvent object
    window.addEventListener('devicemotion', deviceMotionHandler, false);
}
else
{
    document.getElementById("lblAcceleration").innerHTML = "Not supported";
}


if (window.DeviceOrientationEvent) {
    // Listen for the event and handle DeviceOrientationEvent object
    window.addEventListener('deviceorientation', deviceOrientationHandler, false);
}
else
{
    document.getElementById("lblOrientation").innerHTML = "Not supported";
}


function deviceMotionHandler(eventData) {
    var xyz = "[X, Y, Z]";

    // Grab the acceleration including gravity from the results
    acceleration = eventData.accelerationIncludingGravity;
    info = xyz.replace("X", acceleration.x);
    info = info.replace("Y", acceleration.y);
    info = info.replace("Z", acceleration.z);
    document.getElementById("lblAcceleration").innerHTML = info;
}

function deviceOrientationHandler(eventData)
{
    // gamma is the left-to-right tilt in degrees, where right is positive
    var tiltLR = eventData.gamma;

    // beta is the front-to-back tilt in degrees, where front is positive
    var tiltFB = eventData.beta;

    // alpha is the compass direction the device is facing in degrees
    var dir = eventData.alpha

    var xyz = "[LR, FB, DIR]";
    info = xyz.replace("LR", Math.round(tiltLR));
    info = info.replace("FB", Math.round(tiltFB));
    info = info.replace("DIR", Math.round(dir));
    document.getElementById("lblOrientation").innerHTML = info;
}