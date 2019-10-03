---
layout: archive
title: "Desenvolvimento de Sistemas Embarcados Linux"
permalink: /linux/serial
author_profile: false
  
---

{% include base_path %}


---
# Configurando a Comunicação Serial com a RPi 3

Por padrão, a Raspberry Pi possui duas built-in *UARTs*, uma comum *(PL011)* e outra *mini UART*. Essa última, é limitada e carece de alguns recursos básicos como break detection, bit de paridade, dentre outros. Alem disso, a *mini UART* possui uma FIFO menor quando comparada à *PL011* e sua baudrate é linkada ao clock da GPU, ou seja, a taxa de transmissão da *mini UART* varia de acordo com a oscilação do clock da GPU.

O módulo BT (bluetooth) da RPi 3 necessita de uma UART para funcionar e, por padrão, o BT da RPi 3 é conectado à UART *PL011*, tornando-a inutilizável para o usuário. No entanto, o firmware da GPU permite que o usuário escolha uma dentre as três opções:

- Desabilitar o módulo BT;
- Utilizar o módulo BT com a *mini UART*;
- Utilizar o módulo BT com a UART *PL011*;

A princípio, a utilização da *mini UART* para redirecionamento de console é suficiente, pois além da interação entre usuário e target via shell possuir um fluxo de dados baixo, existe a possibilidade de realizar a comunicação via rede (SSH). Portanto, será necessário apenas ativar o redirecionamento do console para a *mini UART*. Para tal, acesse a RPi via SSH e adicione as seguintes linhas no final do arquivo `config.txt`:

<pre>
ssh pi@10.1.1.100
</pre>

<pre>
sudo nano /boot/config.txt
[..]
dtparam=audio=on
enable_uart=1
</pre>

> Obs: para salvar as alterações feitas em um arquivo com o nano, utilize as teclas `CTRL+X, Y`, `Enter`.

Para maiores informações, consulte a [documentação da UART](https://www.raspberrypi.org/documentation/configuration/uart.md) no site da RPi. Após realizar a configuração acima, desligue a Raspberry Pi,

<pre>
sudo poweroff
</pre>

e faça a conexão entre o adaptador USB-Serial (TTL) e a placa. Certifique-se de escolher a opção/jumper 3.3v caso o adaptador permita. Por padrão, a RPi roteia os pinos `GPIO14` e `GPIO15` como *TX* e *RX* da serial principal (aquela que não está sendo utilizada pelo módulo BT), respectivamente. Esses GPIOS estão mapeados nos *pinos 08 e 10*, respectivamente, do conector geral de 40 pinos. Os *pinos 01 e 02* de tal conector são aqueles fisicamente próximos da borda oposta às entradas USB. O *pino 01* é o pino mais interno e o *pino 02* é o mais externo, próximo da borda lateral. As figuras a seguir exibem a descrição completa do conector de 40 pinos e indicação dos pinos fisicamente. Após analisar as figuras, faça as três conexões, *TX*, *RX* e *GND*, entre seu adaptador e a RPi3.

![Pinout RPi3](images/linux/rpi_conector.jpg)