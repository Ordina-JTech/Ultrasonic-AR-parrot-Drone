var arDrone = require('ar-drone');
var client = arDrone.createClient();


client.config('general:navdata_demo', 'FALSE');

client.takeoff();
	client.after(5000, function(){
		this.stop();
	})
	client.after(3000, function(){
		this.front(0.1);
	})
	client.after(5000, function(){
		this.stop();
	})
	client.after(5000,function(){
		this.right(0.1);
	})
	client.after(3000, function(){
		this.stop();
	})
	client.after(5000,function(){
		this.back(0.1);
	})
	client.after(3000, function(){
		this.stop();
	})
	client.after(5000, function(){
		this.land();
});

client.on('navdata', function(navdata) {
	try {
	    console.log('Hoogte:' + navdata.demo.altitude);
	    console.log('Phi:' + navdata.demo.phi);
	    console.log('Psi:' + navdata.demo.psi);
	    console.log('Theta:' + navdata.demo.theta);
	}
	catch(err) {
	    console.log(err.message);
	}
});