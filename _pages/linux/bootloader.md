---
layout: archive
title: "Desenvolvimento de Sistemas Embarcados Linux"
permalink: /linux/bootloader
author_profile: false
  
---

{% include base_path %}


---
# Bootloader -- U-Boot

## Baixando o U-Boot

Assim como nas atividades anteriores, os fontes do **U-Boot** foram previamente baixados e encontram-se no diretório `∼/dsle19/dl/bootloader`. Crie um diretório chamado `bootloader` dentro da pasta `∼/dsle19` e, em seguida, extraia o **U-boot** no diretório criado:

<pre>
cd ~/dsle19/
mkdir bootloader && cd bootloader
unzip ~/dsle19/dl/bootloader/u-boot-master.zip
</pre>

Acesse o diretório do **U-Boot** e liste as configurações pré-definidas para as diversas plataformas suportadas pelo **U-Boot**. Devido à extensão da lista de configurações, é recomendado a utilização do comando `less`. Este comando permite a visualização do conteúdo de um arquivo ou output de algum comando, por meio de páginas do tamanho da tela:

<pre>
cd u-boot-master
ls configs/ | less
</pre>
<pre>
10m50_defconfig
3c120_defconfig
A10-OLinuXino-Lime_defconfig
A10s-OLinuXino-M_defconfig
A13-OLinuXino_defconfig
A13-OLinuXinoM_defconfig
A20-Olimex-SOM204-EVB_defconfig
A20-Olimex-SOM204-EVB-eMMC_defconfig
A20-Olimex-SOM-EVB_defconfig
A20-OLinuXino-Lime2_defconfig
A20-OLinuXino-Lime2-eMMC_defconfig
A20-OLinuXino-Lime_defconfig
A20-OLinuXino_MICRO_defconfig
A20-OLinuXino_MICRO-eMMC_defconfig
A33-OLinuXino_defconfig
a64-olinuxino_defconfig
adp-ae3xx_defconfig
adp-ag101p_defconfig
Ainol_AW1_defconfig
alt_defconfig
am335x_baltos_defconfig
am335x_boneblack_defconfig
am335x_boneblack_vboot_defconfig
:
</pre>

Use as teclas *espaço*, *b* e *q* para exibir a próxima página, a página anterior ou encerrar a visualização, respectivamente. Uma vez que o **U-Boot** suporta diversas arquiteturas de hardware diferentes, é necessário selecionar uma delas antes de compilar o programa. Selecione a configuração `rpi_3_32b_defconfig` e compile o **U-Boot**, indicando o prefixo do cross-compilador conforme configurado anteriormente:

<pre>
make rpi_3_32b_defconfig
make -j2 CROSS_COMPILE=arm-linux-
</pre>

Verifique o arquivo criado, `u-boot.bin`, através do comando:

<pre>
ls - l u-boot.bin
-rw-rw-r- - 1 gbs gbs 427560 Oct 03 06:39 u-boot.bin
</pre>

## Gravando o U-Boot

O processo de gravação do bootloader é dependente de hardware, específico para cada plataforma. Conforme visto em aula, a RPi 3 busca o bootloader e firmwares relacionados ao processo de boot na partição `boot` do cartão micro SD. Assim, dois procedimentos são necessários para gravar e ativar o **U-Boot** no processo de boot da RPi:

1. Copiar o binário `u-boot.bin` para a partição `boot` do cartão micro SD;
2. Configurar o arquivo `config.txt` para que o firmware da GPU, `start.elf`, execute o `U-Boot` no lugar do kernel Linux;

É possível copiar o arquivo `u-boot.bin` para o cartão micro SD de várias maneiras. Visto que já existe uma configuração de rede entre a máquina de desenvolvimento e a RPi, realizada em atividades anteriores, o arquivo será copiado via comando `scp`:

<pre>
scp u-boot.bin pi@10.1.1.100:/home/pi/
</pre>

Logue na RPi, via SSH, e copie o arquivo do diretório `home` para o diretório `boot` com privilégios de administrador:

<pre>
ssh pi@10.1.1.100
</pre>

<pre>
sudo cp u-boot.bin /boot/
ls /boot
</pre>

<pre>
bcm2708-rpi-0-w.dtb
bcm2710-rpi-cm3.dtb
bcm2708-rpi-b.dtb
bootcode.bin
bcm2708-rpi-b-plus.dtb cmdline.txt
bcm2708-rpi-cm.dtb
bcm2709-rpi-2-b.dtb
bcm2710-rpi-3-b.dtb
config . txt
COPYING.linux
fixup_cd.dat
bcm2710-rpi-3-b-plus.dtb fixup .dat
fixup_db.dat
overlays
fixup_x.dat
start_cd. elf
issue. txt
start_db. elf
kernel7.img
start . elf
kernel.img
start_x . elf
LICENCE.broadcom 
u-boot.bin
</pre>

Feito isso, adicione a seguinte linha no final do arquivo `config.txt`:

<pre>
sudo nano /boot/config. txt
[..]
dtparam=audio=on
enable_uart=1
kernel=u-boot.bin
</pre>

O parâmetro acima especifica qual imagem do kernel, o firmware `start.elf` deve carregar. Neste caso, a imagem é o próprio **U-Boot**. Após salvar as alterações no arquivo, renicie a RPi (`sudo reboot`). 

> Atenção, só reinicie a RPi se você possui uma conexão serial funcional entre ela e a máquina de desenvolvimento, pois a única interação com o menu do **U-Boot**, por enquanto, é via serial.

Por último, interrompa o processo de boot do **U-Boot** pressionando uma tecla para entrar no shell:

<pre>
U-Boot 2018.07-rc1 (Oct 3 2019 - 19:50:41 -0300)
DRAM: 948 MiB
RPI 3 Model B (0xa02082)
MMC: mmc@7e202000: 0, sdhci@7e300000: 1
Loading Environment from FAT... ∗∗∗ Warning - bad CRC, using default environment
Failed ( -5)
In :
serial
Out: vidconsole
Err: vidconsole
Net: No ethernet found.
starting USB...
USB0: scanning bus 0 for devices ... 3 USB Device(s) found
scanning usb for storage devices ... 0 Storage Device(s) found
Hit any key to stop autoboot: 0
U-Boot>
</pre>

## Configurando variáveis de ambiente no U-Boot

Após obter acesso ao shell do **U-Boot**, configure algumas variáveis de ambiente básicas para manter o sistema da RPi bootável, pois por padrão, o **U-Boot** não identifica a imagem do kernel automaticamente. Inicialmente, desative o processo de *autoboot*:

<pre>
U-Boot> setenv bootdelay -1
</pre>

Futuramente, o **U-Boot** será configurado para carregar o kernel pela rede, de uma pasta de sua máquina de desenvolvimento. Portanto, configure o endereço *IP* da RPi e máquina de desenvolvimento:

<pre>
U-Boot> setenv ipaddr 10.1.1.100
U-Boot> setenv serverip 10.1.1.1
</pre>

Por fim, salve as alterações realizados no disco, de tal forma que elas estejam disponíveis na próxima inicialização, e reinicie o RPi:

<pre>
U-Boot> saveenv
U-Boot> reset
</pre>

Após enviar o comando `saveenv`, o **U-Boot** cria um arquivo de configuração chamado `u-boot.env` que contém todas as variáveis de ambiente definidas. Após reiniciar novamente a RPi, o processo de *autoboot* não deve ser inicializado e o controle do shell exibido logo em seguida. Para “bootar” o **Raspbian** novamente, pelo **U-Boot**, algumas configurações adicionais são necessárias. O primeiro passo, é carregar um arquivo (imagem do kernel) do cartão micro SD para a RAM em um endereço específico. Utilize o seguinte comando:

<pre>
U-Boot> fatload mmc 0:1 ${kernel_addr_r} kernel7.img
</pre>

O comando acima carrega um arquivo binário de um sistema de arquivos FAT (*fatload*). Os parâmetros são:

- **mmc**: o dispositivo de armazenamento onde se encontra o binário (cartão SD);

- **0**: o número do dispositivo, pois muitas vezes o seu target pode possuir mais de um dispositivo de armazenamento;

- **1**: o número da partição no dispositivo (partições são enumeradas a partir de 1);

- **${kernel_addr_r}**: o endereço inicial na RAM onde deseja-se carregar o binário, neste caso a configuração do **U-Boot** já fornece uma variável de ambiente com o endereço inicial da RAM, para carregar o kernel (*${kernel_addr_r}*);

- **kernel7.img**: o binário que se deseja carregar. Lembrando que por padrão, a partição boot do **Raspbian** fornece duas imagens: `kernel.img` e `kernel7.img`. A primeira é para as versões de hw anteriores (RPi e RPi 2) e a última (`kernel7.img`) é a imagem para as placas da RPi 3 em diante;

Algumas plataformas possuem dispositivos de hardware que não podem ser identificados dinamicamente pelo kernel. Em tais casos, é necessário um mecanismo para informar o kernel sobre dispositivos presentes no sistema. Atualmente, o mecanismo utilizado para tal função é chamado de *Device Tree*, que é uma estrutura de dados que descreve a topologia e configuração de hardware no sistema. Analisaremos esse mecanismo em breve durante o curso.

A RPI 3 é um tipo de plataforma que utiliza esse recurso e bootloader é o responsável por passar o *Device Tree* para o kernel e, portanto, é necessário fazer o loading desse arquivo no **U-Boot**. O processo é o mesmo anterior, porém com algumas alterações nos parâmetros:

<pre>
U-Boot> fatload mmc 0:1 ${fdt_addr_r} bcm2710-rpi-3-b.dtb
</pre>

- **mmc**: o dispositivo de armazenamento onde se encontra o binário (cartão SD);
- **0**: o número do dispositivo, pois muitas vezes o seu target pode possuir mais de um dispositivo de armazenamento;
- **1**: o número da partição no dispositivo (partições são enumeradas a partir de 1);
- **${fdt_addr_r}**: o endereço inicial na RAM onde deseja-se carregar o binário, neste caso a configuração do **U-Boot** já fornece uma variável de ambiente com o endereço inicial da RAM, para carregar o *Flattened Device Tree* (*${fdt_addr_r}*);
- **bcm2710-rpi-3-b.dtb**: arquivo compilado do Device Tree (*dtb*) referente à RPi 3 B;

Estes são basicamente os únicos arquivos necessários para realizar o boot do Raspbian via **U-Boot**. Entretanto, além dos arquivos, ainda é necessário configurar alguns parâmetros do kernel. Configure a variável de ambiente `bootargs`, responsável por armazenar parâmetros para serem passados ao kernel:

<pre>
U-Boot> setenv bootargs 8250.nr_uarts=1 root=/dev/mmcblk0p2 rootwait console=ttyS0,115200
</pre>
onde:

- **8250.nr_uarts=1**: número de portas seriais para serem registradas (utilizadas);
- **root=/dev/mmcblk0p2**: path para a localização do **RootFS** (*Root FileSystem*);
- **rootwait**: espera (indefinidamente) a inicialização dispositivo onde o **RootFS** está localizado. *mmcblk0* refere-se ao micro SD e *p2* à partição número 2, visto que a primeira é a partição de `boot`;
- **console=ttyS0,115200**: redireciona um console para a porta serial `ttyS0` (*mini UART* da RPi 3), e seu respectivo baudrate;

Finalmente, com as configurações acima realizadas, “basta” dar o comando de boot:

<pre>
U-Boot> bootz ${kernel_addr_r} - ${fdt_addr_r}
</pre>

onde:

- **kernel_addr_r**: é o endereço na RAM onde está carregada a imagem do kernel;
- **-**: seria o endereço na RAM da imagem *initrd*, que é uma imagem do **RootFS**. É possível carrega-lo na RAM, assim como kernel e *Device Tree*. No entanto, no momento a RPi não possui nenhuma imagem desse tipo. Ela será gerada em atividades futuras. Este parâmetro é opcional;
- **fdt_addr_r** é o endereço na RAM onde está carregado o compilado do *Device Tree*;

Se os comandos acima foram executados corretamente, você deverá enxergar o loading do kernel pela serial.

## Criando um script de inicialização no U-Boot

O **U-Boot** possui uma funcionalidade que permite que o usuário crie scripts contendo sequência de comandos, como os executados acima. Na sua máquina de desenvolvimento, navegue até o diretório do U-Boot
e crie o seguinte arquivo:

<pre>
cd ~/dsle19/bootloader/u-boot-master
gedit rpi3scr.txt
</pre>

Digite (copie) todos os comandos novamente no arquivo aberto e em seguida salve-o:

<pre>
fatload mmc 0:1 ${kernel_addr_r} kernel7.img
fatload mmc 0:1 ${fdt_addr_r} bcm2710-rpi-3-b.dtb
setenv bootargs 8250.nr_uarts=1 root=/dev/mmcblk0p2 rootwait console=ttyS0,115200
bootz ${kernel_addr_r} - ${fdt_addr_r}
</pre>

Em seguida, dentro da pasta tools no diretório do U-Boot, existe uma ferramenta chamada mkimage capaz de criar imagens do **U-Boot**, **kernel**, **RootFS** e inclusive scripts para o **U-Boot**. Digite o seguinte comando:

<pre>
tools/mkimage -A arm -O linux -T script -d rpi3scr.txt boot.scr
</pre>

onde os argumentos representam: arquitetura do executável (*-A*), sistema operacional (*-O*), tipo da imagem (*-T*), arquivo de entrada com os comandos digitados no gedit (*-d*) e arquivo de saída (`boot.src`), que é uma imagem do script.

Após a execução do comando, copie o arquivo `boot.scr` para o diretório `boot` da RPi via `scp`. Se tudo foi realizado corretamente, reinicie a RPi e digite o comando `boot` no shell do **U-Boot**. É possível ativar o *autoboot* através da modificação da variável de ambiente *bootdelay*, que representa o delay em segundos antes de iniciar o boot pelo script `boot.scr`. Se desejar, altera-a, salve as variáveis de ambiente no cartão SD (`saveen`) e reinicie o **U-Boot**.


---
# Navegação

* [Introdução](/linux/intro)
* [**Parte 1**](/linux/01)
    * [Toolchain](/linux/toolchain)
    * [**Bootloader**](/linux/bootloader)
    * [Config. Conexão de Rede](/linux/rede)
    * [Config. Comunicação Serial](/linux/serial)
* [Parte 2](/linux/02)
* [Parte 3](/linux/03)