var arDrone = require('./ar-drone/index');
var client = arDrone.createClient();
var Project;

// Basic flight Commands
client.after(1000, function () {
    this.takeoff(); 
})
client.after(2000, function () {
    this.stop();
})
client.after(500, function() {
    this.front(0.03);
})
client.after(500, function() {
    this.stop();
})

// Connecting to the serial port to read the output of the arduino.
var serialport = require('node-serialport');
var sp = new serialport.SerialPort("/dev/ttyO3", {
    parser: serialport.parsers.readline("\n"),
    baud: 9600, // Chosen port of the arduino.
    highWaterMark: 65536 // Makes sure it can handle the bit size of the Arduino input.
});

// Commands acting upon the output of the arduino.
sp.on('data', function (chunk) {
    Project = chunk.toString();
    P = Project.split(" ")
    //console.log(Project);
    F = P[0];
    L = P[1];
    R = P[2];
    T = P[3];
    if (T <= 10) {
        client.stop();
        client.land();
        client.animateLeds('blinkRed', 5, 2);
        console.log("Drone Landed\n");
    }
    if (F > 100) {
        client.front(0);
    } 
    if (F < 100) {
        client.back(0.08); 
        console.log("Retreat");        
    }
    if (R < 50) {
        client.left(0.06);
        console.log("Evade Left");  
    }
    if (L < 50) {
        client.right(0.06);
        console.log("Evade Right");  
    }
    sp.flush();
});

