var bufLength = 40;
var inBuf = new Buffer(bufLength);
var inBufPtr = 0;
var procBuffer = new Buffer(bufLength);
var inProcess = false;

console.log("Starting...");

var SerialPort = require("serialport").SerialPort;
var serialPort = new SerialPort("/dev/ttyATH0", {
    baudrate: 57600
});


serialPort.on("open", function () {
    console.log('open');
    serialPort.on('data', function(data) {
        console.log(data);
        for (var i = 0; i < data.length; i++)
        {
            var d = data[i];
            if (d == 64)    // @ character
            {
                inBufPtr = 0;
                if (!inProcess) {
                    inBuf.copy(procBuffer)
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
});
console.log("Started");

function processInput(buffer, byteCount)
{
    for (j = byteCount; j< buffer.length; j++)
    {
        buffer[j] = 0;
    }
    console.log(buffer.toString());
}