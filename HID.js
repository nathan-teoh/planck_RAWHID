var HID = require('node-hid');
var vid = 0x6F6C;
var pid = 0x706C;
var usagePage = 0xFF60;
var usage = 0x61;
var keyboard = null;


const KEYBOARD_NAME = 'Planck'
const KEYBOARD_USAGE_ID = 0x61
const KEYBOARD_USAGE_PAGE = 0xff60
const KEYBOARD_UPDATE_TIME = 1000



connectKeyboard();

	for(i = 0; i < 10; i++){
		keyboard.write([0,i]);

	}

keyboard.on('data', function(data) {
	console.log(data);
});

function connectKeyboard(){
	var devices = HID.devices();
	var deviceInfo = devices.find( function(d) {
    var isTeensy = d.vendorId===vid && d.productId===pid;
    	return isTeensy && d.usagePage===usagePage && d.usage===usage;
	});
	if( deviceInfo ) {
  		var device = new HID.HID( deviceInfo.path );
  		keyboard = device;
	}
}



// connectKeyboard();
// keyboard.resume();
// console.log(keyboard.write(1));
// keyboard.on('data', function(data) {
// 	console.log(data);
// });
// function connectKeyboard(){
// 	keyboard = new HID.HID(vid,pid);
// }
