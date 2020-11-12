# BoosterBoard as DCC Booster

## Firmware

Connect a USB to Serial adapter to the `SERIAL` port as follows:

> It's important to connect `DTR` pin to automatically reset the microcontroller during programing and to **swap** `RX` and `TX` pins

![](https://github.com/lucadentella/BoosterBoard/raw/main/images/serial-programming.jpg)

Download the [latest firmware](https://github.com/lucadentella/BoosterBoard/tree/main/firmware) from Github and program using Arduino IDE (select *Arduino Uno* as board).

## Jumpers

Insert the jumpers as follows:

![](https://github.com/lucadentella/BoosterBoard/raw/main/images/jumpers-booster.jpg)

## Connections

Connect LED, button and encoder as follows:

![](https://github.com/lucadentella/BoosterBoard/raw/main/images/conn-booster-01.jpg)

Connect the display to the corresponding port (`LCD`), **pin to pin** (1->1, 2->2...): 

![](https://github.com/lucadentella/BoosterBoard/raw/main/images/conn-booster-02.jpg)

Connect the H-Bridge board to `H-BRIDGE` port (1->1, 2->2...) and the temperature sensor as follows:

![](https://github.com/lucadentella/BoosterBoard/raw/main/images/conn-booster-03.jpg)

## Operation

Power both BoosterBoard and H-Bridge driver with **12V CC**.

Connect **DCC** signal to `DCC` terminal.

BoosterBoard starts in **STOP** mode. You can turn the booster ON and OFF pressing the push button.

When the booster is OFF, you can change the maximum current and temperature using the rotary encoder.