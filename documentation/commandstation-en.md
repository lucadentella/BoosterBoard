# BoosterBoard as DCC Command Station

## Firmware

Connect a USB to Serial adapter to the `SERIAL` port as follows:

> It's important to connect `DTR` pin to automatically reset the microcontroller during programing and to **swap** `RX` and `TX` pins

![](https://github.com/lucadentella/BoosterBoard/raw/main/images/serial-programming.jpg)

BoosterBoard is compatible with [DCC++ Base Station](https://github.com/DccPlusPlus/BaseStation). 

Download the latest version of this firmware from Github and program using Arduino IDE (select *Arduino Uno* as board).

## Jumpers

Insert the jumpers as follows:

![](https://github.com/lucadentella/BoosterBoard/raw/main/images/jumpers-cs.jpg)

Having only one H-Bridge, you have to choose which DCC++ signal will be its input.

Use the **blue** position for the `MAIN TRACK` signal or the **orange** position for the `PROGRAMMING TRACK` one.

## Connections

DCC++ doesn't support external peripherals like displays or buttons. 

You only need to connect a USB to Serial adapter to send commands to the command station from your computer. Connect the adapter as follows:

![](https://github.com/lucadentella/BoosterBoard/raw/main/images/serial-cs.jpg)

## Operation

Power BoosterBoard connecting **12V and GND**.

Power the H bridge (`B+ B-` terminals) and connect the output (`M+ M-` terminals) to the layout:

![](https://github.com/lucadentella/BoosterBoard/raw/main/images/conn-hbridge.jpg)

Connect the Serial adapter to your computer.

Use a software which supports DCC++ to send commands to the command station and control your layout.

Some free programs I tested:

 - JMRI (https://www.jmri.org/)
 - Rocrail (https://wiki.rocrail.net/doku.php)
 