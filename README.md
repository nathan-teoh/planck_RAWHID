# Planck RAWHID
My personal project for playing around with RAWHID on my Planck keyboard. Ideally I'd like to fully "clone" the VIA keyboard suite, but also make it opensource as well. IIRC, VIA also communicates through HID. Even if it doesn't, I'm sure I can do it with HID.

## Installation

1) add RAW_ENABLE = YES to your rules.mk
2) add "raw_hid.h" to your keymap.c 
3) implement raw_hid_receive(uint8_t *data, uint8_t length) in keymap.c (or take a look at my keymap.c and copy that code)
4) node-hid installed

## Usage
1) Open up HID.js
2) Modify keyboard.write() with the HSV values you desire

## NOTE
1) This is in very, very early stages of development. I am not familiar with js or node in anyway.
2) HSV values are hard coded, but I'm working on an adonisjs front end to communicate with the keyboard. This would be the "user interface".


## Contributing
Pull requests are welcome. For major changes, please open an issue first to discuss what you would like to change.

Please make sure to update tests as appropriate.

## License
[MIT](https://choosealicense.com/licenses/mit/)
