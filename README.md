# flirc_retransmit
This program will read [flirc](https://flirc.tv/products/flirc-usb-receiver?variant=42687976538340) 
keystrokes, as read as keyboard input, then transmit associated IR signals as configured.

First, use `Flirc` or `flirc_util` to configure the input IR signals to keys as usual.  Then use the 
debug mode to read the IR signals to retransmit, as used for `flirc_util sendir`.  Store them in 
`config.txt` with the key id follwed by the IR code.

My `config.txt`:
```
115 0,2417,534,633,526,1202,555,633,526,631,527,1222,535,632,527,630,529,628,530,627,532,625,534,609,550,1223,534,1226,531,605,554,624
115 0,2418,534,633,526,1203,555,623,535,632,527,1222,535,632,527,630,528,629,530,627,532,625,534,623,536,1224,533,1226,536,621,533,624
114 0,2395,556,1204,554,1195,561,607,553,624,535,1225,532,604,555,602,556,601,558,630,529,597,562,595,564,1195,562,1229,528,629,530,607
114 0,2396,556,1202,555,1204,554,624,534,614,545,1223,535,619,539,601,558,599,560,597,561,628,531,631,528,1195,563,1228,529,597,563,641
```

To build you'll need the flirc [sdk](https://github.com/flirc/sdk), libusb-1.0, and libhidapi-hidraw.  Tested on Raspberry Pi.
