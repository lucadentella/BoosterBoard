# Istruzioni per il montaggio
Iniziamo saldando i componenti più bassi (diodo, quarzo, condensatori da 22pf). Consiglio fortemente l'utilizzo di **sockets** per i circuiti integrati:

![](https://github.com/lucadentella/BoosterBoard/raw/main/images/mount-01.jpg)

Continuiamo con i condensatori rimanenti e il transistor:

![](https://github.com/lucadentella/BoosterBoard/raw/main/images/mount-02.jpg)

E' ora tempo di saldare le resistenze (inclusa quella variabile), i pin e il pulsante:

![](https://github.com/lucadentella/BoosterBoard/raw/main/images/mount-03.jpg)

Completiamo la scheda con le morsettiere e il regolatore di tensione:

![](https://github.com/lucadentella/BoosterBoard/raw/main/images/mount-04.jpg)

Se avete scelto di usare i sockets, è ora possibile inserire i circuiti stampati. 
L'atmega328p deve essere programmato con il **bootloader Arduino**. E' possibile acquistare microcontrollori già programmati o programmare il bootloader usando un Arduino Uno che esegue il firmware *ArduinoISP*:

![](https://github.com/lucadentella/BoosterBoard/raw/main/images/bootloader-burn.png)

Ho trovato molto utile [questo shield](https://bit.ly/38shwaZ) per programmare il bootloader:

![](https://github.com/lucadentella/BoosterBoard/raw/main/images/bootloader-shield.jpg)