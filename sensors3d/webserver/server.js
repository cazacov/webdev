var bufLength = 40;
var inBuf = new Buffer(bufLength);
var inBufPtr = 0;
var procBuffer = new Buffer(bufLength);
var inProcess = false;
var sensorsState = "abc";

console.log("Starting serial port");
var SerialPort = require("serialport").SerialPort;
var serialPort = new SerialPort("/dev/ttyATH0", {
    baudrate: 115200
});

serialPort.on("open", function () {
    console.log('open');
    serialPort.on('data', function(data) {
        //console.log(data.length);
        for (var i = 0; i < data.length; i++)
        {
            var d = data[i];
            if (d == 64)    // @ character
            {
                var byteCount = inBufPtr;
                inBufPtr = 0;
                if (!inProcess) {
                    inBuf.copy(procBuffer);
                    processInput(procBuffer, byteCount);
                }
            }
            else {
                if (inBufPtr < bufLength)
                {
                    inBuf[inBufPtr++] = d;
                }
            }
        }
    });
    serialPort.write("nnnnnnnnnn"); // Send start signal to the Arduino
});
console.log("Serial port started");

function processInput(buffer, byteCount)
{
    for (j = byteCount; j< buffer.length; j++)
    {
        buffer[j] = 0;
    }
    sensorsState = buffer.toString();
    console.log(sensorsState);
}


console.log("Starting web server...");
var express = require('express');

var server = express();
server.use(express.static(__dirname));

// respond with "Hello World!" on the homepage
server.get('/sensors', function (req, res) {
    res.send(sensorsState);
});

var port = 8888;
server.listen(port, function() {
    console.log('Server listening at %s', port);
});