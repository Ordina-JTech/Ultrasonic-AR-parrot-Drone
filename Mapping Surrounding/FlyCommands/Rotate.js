/*
/ Script which causes the drone to hover and rotate while printing
/ measuring the distances of the environment it is in.
*/

var arDrone = require('./ar-drone/index');
var client = arDrone.createClient();
var Project;

// Basic flight Commands
client.takeoff();    
// This makes sure the drone hovers over the same spot.
// The drone camera detects the paper shape on the floor.
client.config('detect:detect_type', 12);
client.config('control:flying_mode', 2);  

// For hand held turning.
client.after(20000, function(){
    this.land();
});

/*
// Automated turning. Still deviates to much.
client.after(5000,function(){
    this.stop();
});
client.after(2000, function(){
    this.config('control:flying_mode', 0);  
    this.clockwise(0.5);
});
client.after(1000, function(){
    this.stop();
    this.land();
});
*/

// Logs navdata of the drone.
client.config('general:navdata_demo', 'FALSE');
client.on('navdata', function(navdata) {
    try {
        psi = navdata.demo.rotation.psi;
    }
    catch(err) {
        console.log(err.message);
    }
});

// Connecting to the serial port to read the output of the arduino.
var serialport = require('node-serialport');
var sp = new serialport.SerialPort("/dev/ttyO3", {
    parser: serialport.parsers.readline("\n"),
    baud: 9600 // Chosen port of the arduino.
})

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
});


