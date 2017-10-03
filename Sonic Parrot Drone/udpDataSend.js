var PORT = 33333;
var HOST = '192.168.1.2';
var Project;
var dgram = require('dgram');
var udpclient = dgram.createSocket('udp4');
var message;
var serialport = require('node-serialport');
var sp = new serialport.SerialPort("/dev/ttyO3", {
    parser: serialport.parsers.readline("\n"),
    baud: 9600
});
sp.on('data', function (chunk) {
    Project = chunk.toString();
    console.log("%s", Project);
    if (Project == 'T') {
        message = new Buffer(Project);
    }
    var values = Project.split(" ");
    if (values.length == 2) {
        var x = parseFloat(values[0]);
        var y = parseFloat(values[1]);
        message = new Buffer('X:' + x + ' Y:' + y);
    }
    udpclient.send(message, 0, message.length, PORT, HOST, function(err, bytes) {
        if (err) throw err;
        console.log('UDP message sent to ' + HOST +':'+ PORT);
    });
});


