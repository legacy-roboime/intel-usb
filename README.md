intel-usb
=========

    cargo run

After you have claimed the device, run this (where $ represents the terminal entry point):

$ sudo lsusb -v -d 16c0:05df

Where 16c0:05df are your vendor and product ids separated by a colon. (If you don't know these, type lsusb and figure out which device is yours by unplugging and re-running lsusb)

If you get confused use the lsusb man page:

http://linux.die.net/man/8/lsusb

Then once your description comes up, find the line labeled bEndpointAddress and the hex code following will be the endpoint for that specific Report.
