#![no_std]
#![no_main]

use bsp::board;
use cortex_m::asm;
use teensy4_bsp as bsp;
use teensy4_panic as _;

const BUZZER_HZ: u32 = 2700;

#[bsp::rt::entry]
fn main() -> ! {
    let mut resources = board::t41(board::instances());

    // teensy pin 6 = GPIO2_IO10
    let buzzer = resources.gpio2.output(resources.pins.p6).unwrap();

    // half of one 2700 Hz period
    let half_period_cylces = board::ARM_FREQUENCY / (BUZZER_HZ * 2);

    loop {
        // beep for approx 500 ms
        for _ in 0..(BUZZER_HZ / 2) {
            buzzer.set();
            asm::delay(half_period_cylces);

            buzzer.clear();
            asm::delay(half_period_cylces);
        }

        // make sure its off
        buzzer.clear();

        // silence for approx 500ms
        asm::delay(board::ARM_FREQUENCY / 2);
    }
}
