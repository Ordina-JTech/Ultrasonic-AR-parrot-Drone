/*
/ Small script for a test flight whereby the drone hovers
/ and rotates.
*/

var arDrone = require('ar-drone');
var client = arDrone.createClient();
var Project;

client.takeoff();    
client.config('detect:detect_type', 12);
client.config('control:flying_mode', 2);  

client.after(10000, function(){
    this.stop();
})
client.after(2000, function(){
    this.config('control:flying_mode', 0);  
    this.clockwise(1.0)
})
client.after(1000, function(){
    this.stop();
    this.land();
});