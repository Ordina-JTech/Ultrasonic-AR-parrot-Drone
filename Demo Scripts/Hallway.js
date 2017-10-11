var arDrone = require('./ar-drone/index');
var client = arDrone.createClient();
var Project;

// Basic flight Commands
client.after(1000, function () {
    this.takeoff(); 
});
client.after(1000, function () {
    this.stop();
});

// Connecting to the serial port to read the output of the arduino.
var serialport = require('node-serialport')
var sp = new serialport.SerialPort("/dev/ttyO3", {
    parser: serialport.parsers.readline("\n"),
    baud: 9600, // Chosen port of the arduino.
    highWaterMark: 65536
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
    if (values.length == 4) {
        // Calling sensor values from the ardu
        var x = parseFloat(values[0]);
        var ymed = parseFloat(values[3]);

        if (x <= 50) {
            client.back(0.05);
        } 
        else if (x > 50) {
            client.front(0.05);
        }

        if (ymed > 20) {
            client.left(0.05);
        } 
        else if (ymed < 20 && ymed > -20) {
            client.left(0);
            client.right(0);
        } 
        else if (ymed < -20) {
            client.right(0.05);
        }
    }
    sp.flush();
});
