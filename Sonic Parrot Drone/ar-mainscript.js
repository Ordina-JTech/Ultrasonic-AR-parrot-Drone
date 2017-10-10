var arDrone = require('./ar-drone/index');
var client = arDrone.createClient();
var Project;

// Basic flight Commands
client.after(1000, function () {
    this.takeoff();
})
client.after(3000, function () {
    this.stop();
});

// Connecting to the serial port to read the output of the arduino.
var serialport = require('node-serialport')
var sp = new serialport.SerialPort("/dev/ttyO3", {
    parser: serialport.parsers.readline("\n"),
    baud: 9600 // Chosen port of the arduino.
});

// Commands acting upon the output of the arduino.
sp.on('data', function (chunk) {
    Project = chunk.toString();
    console.log("%s", Project);
    if (Project == 'T') { // Emergency stop command.
        client.stop();
        client.land();
        client.animateLeds('blinkRed', 5, 2);
        console.log("Drone Landed\n");
    }
    var values = Project.split(" ");
    if (values.length == 2) {
        var x = parseFloat(values[0]);
        var y = parseFloat(values[1]);
        if (x >= 100) {
            client.front(0.1);
        } else if (x > 50 &&  x < 100) {
            client.front(0);
        } else if (x < 50) {
            client.back(0.1);
        }
        if (y > 20) {
            client.left(0.1);
        } else if (y < 20 && y > -20) {
            client.left(0);
            client.right(0);
        } else if (y < -20) {
            client.right(0.1);
        }
    }
});


