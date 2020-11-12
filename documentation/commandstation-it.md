# BoosterBoard come Centralina DCC

## Firmware

Colleghiamo un adattatore USB Seriale alla porta `SERIAL` come segue:

> E' importante collegare il pin `DTR` per il reset automatico del microcontrollore durante la programmazione  e **invertire** i pin `RX` e `TX`

![](https://github.com/lucadentella/BoosterBoard/raw/main/images/serial-programming.jpg)

BoosterBoard è compatibile con [DCC++ Base Station](https://github.com/DccPlusPlus/BaseStation). 

Scarichiamo l'ultima versione del firmware da Github e programmiamo la scheda usando l'IDE di Arduino (selezioniamo *Arduino Uno* come scheda).

## Jumpers

Inseriamo i jumpers nelle posizioni evidenziate:

![](https://github.com/lucadentella/BoosterBoard/raw/main/images/jumpers-cs.jpg)

Avendo solo un ponte H, dobbiamo scegliere quale segnale DCC++ inviare al suo ingresso.

Usiamo le posizioni in **blu** per il `TRACCIATO PRINCIPALE (MAIN` o le posizioni in **arancione** per il `BINARIO DI PROGRAMMAZIONE`.

## Collegamenti

DCC++ non supporta periferiche esterne come display o pulsanti. 

Dobbiamo solo collegare un adattatore USB Seriale per inviare comandi alla command station dal nostro computer. Colleghiamo l'adattatore come segue:

![](https://github.com/lucadentella/BoosterBoard/raw/main/images/serial-cs.jpg)

## Funzionamento

Alimentiamo BoosterBoard e il ponte H con **12V CC**.

Colleghiamo l'adattatore seriale al nostro computer.

Utilizziamo un programma che supporti DCC++ per inviare comandi alla centralina e controllare il plastico.

Alcuni programmi gratuiti che ho testato:

 - JMRI (https://www.jmri.org/)
 - Rocrail (https://wiki.rocrail.net/doku.php)
 