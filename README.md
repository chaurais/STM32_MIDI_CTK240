# STM32_MIDI_CTK240
![20220116_173726](https://user-images.githubusercontent.com/73307680/204644537-88990a84-971b-4ebc-b484-aeb5a5fcf182.jpg)
Based on https://github.com/abelykh0/stm32f103-midi
I used part of the code developed by "abelykh0" and implemented a scan routine for the keyboard of my Casio CTK240.
The circuit developed for the CTK240 has a multiplexer for the keyboard, which automatically switches the keyboard to the main board of the CTK240, when powered by the power supply or to the MIDI board, when powered by the USB port.
That way I can use the CTK240 in the original way, as a musical keyboard or use it as a MIDI controller.
As a MIDI controller, the keyboard sends Note ON and Note OFF commands and through six commands I can split the keyboard and select the octave and velocity of each part, independently. O teclado do Casio CTK240 não possui controle de velocidade.
Firmware compiled with STM32CubeIDE.
