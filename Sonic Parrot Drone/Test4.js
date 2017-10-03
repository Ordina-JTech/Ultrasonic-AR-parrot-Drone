var arDrone = require('ar-drone');
var droneClient = arDrone.createClient();

droneClient.config('general:navdata_demo', '');

droneClient.on('navdata', function(navdata) {
	try {
	    console.log('test:' + navdata.demo.altitude);
	}
	catch(err) {
	    console.log(err.message);
	}
});