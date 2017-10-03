/**
 * Created by robert on 28-9-17.
 */
var arDrone = require('./ar-drone/index');
var client = arDrone.createClient();
var Project;
client.takeoff();
client.after(5000, function () {
    this.stop();
}).after(500, function () {
    this.back(0.05);
}).after(2000, function () {
    this.stop();
}).after(500, function () {
    this.land();
})