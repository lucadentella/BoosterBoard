# Assembly instructions
Start soldering the lowest components (diode, crystal, 22pf capacitors). I strongly suggest the use of **sockets** for ICs:

![](https://github.com/lucadentella/BoosterBoard/raw/main/images/mount-01.jpg)

Continue with the remaining capacitors and the the transistor:

![](https://github.com/lucadentella/BoosterBoard/raw/main/images/mount-02.jpg)

It's now time to solder the resistors (including the variable one), the pin headers and the switch:

![](https://github.com/lucadentella/BoosterBoard/raw/main/images/mount-03.jpg)

Complete the board with the terminal blocks and the voltage regulator:

![](https://github.com/lucadentella/BoosterBoard/raw/main/images/mount-04.jpg)

If you chose to use sockets, now you can insert the ICs. 
ATmega328p must be programmed with **Arduino bootloader**. You can buy pre-programmed microcontrollers or burn the bootloader using one Arduino Uno running the *ArduinoISP* firmware:

![](https://github.com/lucadentella/BoosterBoard/raw/main/images/bootloader-burn.png)

I found very useful [this shield](https://bit.ly/38shwaZ) to program the bootloader:
![](https://github.com/lucadentella/BoosterBoard/raw/main/images/bootloader-shield.jpg)