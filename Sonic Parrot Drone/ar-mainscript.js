var arDrone = require('./ar-drone/index');
var client = arDrone.createClient();
var Project;
client.after(1000, function () {
    this.takeoff();
})
client.after(4000, function () {
    this.stop();
})
client.after(500, function () {
    this.front(0.03);
})
client.after(500, function () {
    this.stop();
})
var serialport = require('node-serialport')
var sp = new serialport.SerialPort("/dev/ttyO3", {
    parser: serialport.parsers.readline("\n"),
    baud: 9600
})
sp.on('data', function (chunk) {
    Project = chunk.toString();
    console.log("%s", Project);
    if (Project == 'T') {
        client.stop();
        client.land();
        client.animateLeds('blinkRed', 5, 2);
        console.log("Drone Landed\n");
    }
    var values = Project.split(" ");
    if (values.length == 2) {
        var x = parseFloat(values[0]);
        var y = parseFloat(values[1]);
        if (x >= 0) {
            client.back(0);
            client.front(0.02);
        } else {
            client.front(0);
            client.back(0.02);
        }

        if (y >= 0) {
            client.right(0);
            client.left(0.02);
        } else {
            client.left(0);
            client.right(0.02);
        }
    }
});

