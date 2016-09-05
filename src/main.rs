extern crate libusb;
extern crate gilrs;

use std::time::Duration;
use std::thread::sleep;
use gilrs::{Gilrs, Button, Axis};


fn open_device(context: &mut libusb::Context, vid: u16, pid: u16) -> Option<(libusb::Device, libusb::DeviceDescriptor, libusb::DeviceHandle)> {
    let devices = match context.devices() {
        Ok(d) => d,
        Err(_) => return None
    };

    for mut device in devices.iter() {
        let device_desc = match device.device_descriptor() {
            Ok(d) => d,
            Err(_) => continue
        };

        if device_desc.vendor_id() == vid && device_desc.product_id() == pid {
            match device.open() {
                Ok(handle) => return Some((device, device_desc, handle)),
                Err(_) => continue
            }
        }
    }

    None
}

fn main() {
    let mut context = libusb::Context::new().unwrap();

    let (device, device_desc, mut handle) = open_device(&mut context, 0x0483, 0x5740).unwrap();

    if handle.kernel_driver_active(0).unwrap_or(false) {
        handle.detach_kernel_driver(0).unwrap();
    }
    handle.claim_interface(0).unwrap();

    let mut gilrs = Gilrs::new();

    // Event loop
    loop {
        for (_id, _event) in gilrs.poll_events() {
            //println!("New event from {}: {:?}", id, event);
        }

        let mut kick = false;
        let mut chip_kick = false;
        let mut dribble = false;
        let mut data_out = [0u8; 6];
        let mut data_in = [0u8; 600];

        sleep(Duration::from_millis(3));

        let gamepad = gilrs.gamepad(0);

        if gamepad.is_btn_pressed(Button::South) {
            kick = true;
        }

        if gamepad.is_btn_pressed(Button::East) {
            chip_kick = true;
        }

        if gamepad.is_btn_pressed(Button::West) {
            dribble = true;
        }

        let v_norm = gamepad.axis_val(Axis::LeftStickX);
        let v_tan  = gamepad.axis_val(Axis::LeftStickY);
        let v_ang  = -gamepad.axis_val(Axis::RightStickX);

        //println!("v0: {}, v1: {}, v2: {}", v_norm, v_tan, v_ang);

        data_out[0] = 0x61; // lowercase a in ascii
        data_out[1] = if v_norm < 0.0 { -v_norm * 100.0 + 100.0 } else { v_norm * 100.0 } as u8;
        data_out[2] = if v_tan  < 0.0 { -v_tan  * 100.0 + 100.0 } else { v_tan  * 100.0 } as u8;
        data_out[3] = if v_ang  < 0.0 { -v_ang  * 100.0 + 100.0 } else { v_ang  *  40.0 } as u8;
        if kick {
            data_out[4] = 0b_0000_0001;
        } else if chip_kick {
            data_out[4] = 0b_0000_0010;
        } else {
            data_out[4] = 0;
        }
        if dribble {
            data_out[5] = 0xfe;
        }

        println!("{:?}", &data_out);

        handle.write_bulk(0x01, &data_out, Duration::from_millis(100)).unwrap();
        handle.read_bulk(0x81, &mut data_in, Duration::from_millis(100)).unwrap();
    }
}
