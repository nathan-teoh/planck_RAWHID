var HID = require('node-hid');	//required
var keyboard = null;	//keyboard object. null at start.


connectKeyboard();
writeKeyboard();
readKeyboard();


function readKeyboard(){
	keyboard.on('data', function(data) {
		console.log(data);
		keyboard.close();
	});
}

function writeKeyboard(){
	keyboard.write([0,2,50,255,255]);	//0, "hid chooser", "values".....
}

function connectKeyboard(){
	var vid = 0xFEED;	//VID for planck
	var pid = 0x6060;	//PID for planck
	var usagePage = 0xFF60;	//usagePage for planck. dumped from HID.devices()
	var usage = 0x61;	//usage for planck. dumped from HID.devices();
	var devices = HID.devices();	//get all HID devices instead of connecting directly with PID and VID as some devices will have multiple HID "channels(?)"
	var deviceInfo = devices.find( function(d) {	
    var isPlanck = d.vendorId===vid && d.productId===pid;	//make sure eveyrthing matches
    	return isPlanck && d.usagePage===usagePage && d.usage===usage;	//including usage. without matching usage, i could not read or write.
	});
	if( deviceInfo ) {
  		var device = new HID.HID( deviceInfo.path );	//create new device with matched information
  		keyboard = device;	//assign global "keyboard" variable to newly created keyboard object.
	}
}

