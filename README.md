# DwinMusicPlayer

> Exemplo de um Music Player com Display Dwin e Esp32

![Slide1.jpeg](Slide1.jpeg)

## Display HMI

Existe uma  [diferença essencial entre um display HMI e um display touch screen](https://www.stoneitech.com/the-difference-between-hmi-and-touch-screen-display) .

Isso ocorre porque o Touch Screen é  **apenas a parte de hardware**  que pode ser usada em telas HMI. Os displays  **HMI** é um equipmento de interação humano-computador  que inclui  **hardware e software**. Esta seria sua principal diferença para uma tela LCD comum.

Existem diferentes marcas no mercado, sendo a Nextion, Proculus e Dwin uma das mais conhecidas. Aqui usamos o display Dwin de 7 polegagadas com toque capacitivo, modelo DMG80480C070_04WTC.

## MAX98357

Um link interessante para conhecer este amplificador é o site da  [Adafruit](https://learn.adafruit.com/adafruit-max98357-i2s-class-d-mono-amp/overview). A função do max98357 basicamente é receber um sinal digital de entrada pela interface I2S e converter para uma saída analógica amplificada de 3w. 





## Referências

Bluetooth A2DP API - https://github.com/pschatzmann/ESP32-A2DP

Biblioteca Original dWin LCD HMI Arduino - https://github.com/akkoyun/dWin
