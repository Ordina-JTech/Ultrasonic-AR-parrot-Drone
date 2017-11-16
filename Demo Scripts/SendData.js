/*
/ Script for sending arduino data.
/ 
*/

var arDrone = require('ar-drone'); // Library location on drone.
var client = arDrone.createClient(); 
var Project;

// Connecting to the serial port to read the output of the arduino.
var serialport = require('serialport'); // Port liberary
var sp = new serialport("/dev/ttyO3", {
    parser: new serialport.parsers.Readline("\n"),
    baud: 9600, // Chosen port of the arduino.
    highWaterMark: 65536 // Makes sure it can handle the bit size of the Arduino input.
});

// Commands acting upon the output of the arduino.
sp.on('data', function (chunk) {
    Project = chunk.toString();
    console.log(Project);
});