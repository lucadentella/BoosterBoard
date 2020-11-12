# BoosterBoard come DCC Booster

## Firmware

Colleghiamo un adattatore USB Seriale alla porta `SERIAL` come segue:

> E' importante collegare il pin `DTR` per il reset automatico del microcontrollore durante la programmazione  e **invertire** i pin `RX` e `TX`

![](https://github.com/lucadentella/BoosterBoard/raw/main/images/serial-programming.jpg)

Scarichiamo [l'ultima versione del firmware](https://github.com/lucadentella/BoosterBoard/tree/main/firmware) da Github e programmiamo la scheda usando l'IDE di Arduino (selezioniamo *Arduino Uno* come scheda).

## Jumpers

Inseriamo i jumpers nelle posizioni evidenziate:

![](https://github.com/lucadentella/BoosterBoard/raw/main/images/jumpers-booster.jpg)

## Collegamenti

Colleghiamo il LED, il pulsante e l'encoder come segue:

![](https://github.com/lucadentella/BoosterBoard/raw/main/images/conn-booster-01.jpg)

Colleghiamo il display alla porta corrispondente (`LCD`), **pin to pin** (1->1, 2->2...): 

![](https://github.com/lucadentella/BoosterBoard/raw/main/images/conn-booster-02.jpg)

Colleghiamo il ponte H alla porta `H-BRIDGE` (1->1, 2->2...) e il sensore temperatura come segue:

![](https://github.com/lucadentella/BoosterBoard/raw/main/images/conn-booster-03.jpg)

## Funzionamento

Alimentiamo BoosterBoard e il ponte H con **12V CC**.

Colleghiamo il segnale **DCC** alla morsettiera `DCC`.

BoosterBoard si avvia in modalità **STOP**. E' possibile ACCENDERE e SPEGNERE il booster premendo il pulsante.

Quando il booster è SPENTO, è possibile modificare i valori massimi di corrente e temperatura usando l'encoder.