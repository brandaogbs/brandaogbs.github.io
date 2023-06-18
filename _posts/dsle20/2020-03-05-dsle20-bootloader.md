---
layout: post
title:  Embedded Linux Development Course - Bootloader (pt. 6) 
date:   2020-03-07 22:57:49 +0000
categories: jekyll update
tags: [course, linux, embedded, bootloader, uboot]
usemathjax: true
---

# Bootloader

O bootloader é um pequeno pedaço de código que normalmente é a primeira coisa a ser executada ao ligar um computador, ou sistemas em geral. Sua principais atribuições e funções são:

* Inicializar o hardware base;
* Carregar o kernel;
* Passar o controle para a aplicação;

De uma forma mais precisa, o bootloader deve realizar a inicialização e configuração básica do hardware. Isto é, inicializar a  CPU, as GPIOs as memórias e etc. 

Em seguida, deve carregar um código de aplicação, em geral são arquivos binários em especial o kernel do sistema operacional. Este código é carrega, em geral, de uma memória não-volátil, por exemplo: um HDD, SDD, da rede, ou mesmo de um flash drive. Este é carregado para a RAM e executado.

Por fim, deve passar o controle da CPU para o programa carregado, seja ele uma aplicação ou um sistema operacional.

Assim, para entender melhor o funcionamento e a utilizade dos bootloaders, vamos apresentar os processos de boot das principais arquiteturas de processadores.

### Boot em arquitetura X86 baseado em BIOS

Processadores com arquitetura x86, normalmente possuem uma memória interna não-volatil. Esta em geral, é uma ROM com um firmware dedicado gravado nela. Este firmware é o que costumeiramente chamamos de BIOS do computador.

O diagrama a seguir, descreve as principais etapas do processo de boot de uma processador x86.

<figure>
<img src="/assets/posts/dsle20/boot-1.png" alt="">
</figure>


A BIOS, é responsável pela inicialização básica de hardware, e em seguida procurar, dentre as opções disponíveis de armazenamento não-volatil, normalmente disco rígidos, por um programa bem pequeno na MBR \(Master Boot Record\). 

A MBR é gravada nos primeiros 512 bytes do disco e contém informações de particionamento. Por ser uma memória extremamente pequena, realiza o carregamento do bootloader de primeiro estágio para dentro da memória RAM. Este é responsável apenas por encontrar quem é a partição ativa, através da tabela da MBR.

Então, é carregado o bootloader de segundo estágio. Este é mais completo, e consegue carregar alguns drivers para ler os tipos da partição e outras funções específicas. E então é capaz de ler a imagem do kernel e carrega-la na RAM e por fim executa-la.

Alguns exemplos de bootloaders de segundo estágio são por exemplo:

* \*\*\*\*[**GRUB** \(Grand Unified Bootloader\)](https://www.gnu.org/software/grub/): que é o padrão utilizado em algumas distribuições GNU/Linux como o próprio Ubuntu. É um dos bootloaders mais completas utilizado tanto em desktops como em servidores.
* \*\*\*\*[**Syslinux**](https://www.syslinux.org/): é um bootloader muito utilizado, principalmente em sistemas com boot de mídias removíveis e boots via rede. É por exemplo disponibilizado em distribuições como o Arch Linux.
* \*\*\*\*[**LILO** \(Linux Loader\)](https://lilo.alioth.debian.org/): era um dos bootloaders padrão, sendo adotado em distribuições como o Debian. Porém, com o crescimento do Syslinux e do GRUB/2 acabou ficando obsoleto.

# Bootloaders em Sistemas Embarcados

### Boot em arquiteturas ARM

O processo de boot basico de um processador ARM, está exemplificado no diagrama a seguir:

<figure>
<img src="/assets/posts/dsle20/boot-2.png" alt="">
</figure>


De forma geral, o processador possui um código de boot gravado em uma ROM interna, tal como o caso anterior. Ao ser energizado, o processador executa o código desta ROM que é responsável por encontrar o SPL \(_Secoundary Program Loader_\). 

Apesar de ter o nome de secundário, este é na verdade o bootloader de primeiro estágio e está presente em uma memória não-volátil. Em  geral, se encontra em uma partição primária da NAND Flash, MMC, ou SD Card e normalmente é a partição boot com FAT32.

Então, o boot code encontra o SPL e carrega-o em uma memória RAM interna também do processador, normalmente uma SRAM ou IRAM. Como o tamanho da SRAM é limitado, comumente, o SPL precisa inicializar o hardware em geral, mas principalmente a memória RAM e carregar o bootloader regular, isto é, carregar o bootloader de segundo estágio, do armazenamento não-volátil para a RAM. O principal fator para os bootloaders regulares não estarem na SRAM, precisando ser carregados na RAM, é que eles costumam oferecer outras funcionalidades, tornando-se maiores.

Então, o bootloader regular carrega o kernel para a memória RAM e este passa a ter controle sobre o processador. A partir deste momento, o bootloader não tem mais função e é desalocado da RAM, tal como no caso do x86.

### Boot em ARM Microchip AT91

Para exemplificar melhor o processo de boot dos processadores embarcados, vamos avaliar outra CPU ARM. No caso, o chip em questão é o AT91 da Microchip \(ex-Atmel\), o processo de boot esta ilustrado na figura a seguir.

<figure>
<img src="/assets/posts/dsle20/boot-3.png" alt="">
</figure>


É possível nota que o processo não é muito diferente dos já citados, ARM geral e x86. Primeiramente, o boot code da ROM interna é executado e busca pelo bootloader de primeiro estágio. Em seguida, este é carregado e executado na RAM interna de 4KB. Particularmente a Atmel gostava de chamar seus bootloaders de primeiro estágio de ATxxBootstrap, tal como os bootloaders de primeiro estágio das arquiteturas x86 baseadas em BIOS.

O bootstrap, assim como os demais,  é responsável por inicializar o hadware básico, mas principalmente a controladora de DRAM,  para poder carregar o bootloader na RAM ou DRAM e executa-lo.

Nos processadores da Atmel/Microchip o bootloader é o U-boot que é executado na RAM. O U-boot é um bootloader bem popular, com varias funcionalidades interessantes, que serão abordadas ao longo do treinamento. 

Então, por fim, o bootloader encontra o kernel e faz o carregamento dele na RAM, passando o controle da CPU para ele.

Este mesmo processo esta presente em outros chips como: processadores ARM da Texas Instruments \(por ex: ARM TI OMAP3\), processadores Freescale \(por ex: i.MX5/6\) e tantos outros. Cada um com suas peculiaridades, mas o processo é, em geral, na mesma estrutura dos apresentados nesta sessão.

### Bootloaders para Sistemas Linux Embarcado

Durante as seções anteriores, foram apresentados algums processos de boot, principalmente da arquitetura ARM, que é a adotada para este treinamento. Uma vez que estamos utilizando como plataforma embarcada a RPi3 que possui um processador ARM da Broadcom.

O bootloader de primeiro estágio é sempre relacionado a arquitetura do processador escolhido, desta forma, estamos mais interessados nos bootloaders de segundo estágio. Uma vez que estes, podem ser modificados e são uma escolha do desenvolvedor.

Existem alguns bootloaders disponiveis no mercado e nas comunidades, e diversos deles são multi-arquitetura. Contudo, os dois bootloaders regulares mais usados, em projetos embarcados, são o [U-Boot](http://denx.de/wiki/U-Boot/) e o [Barebox](https://www.barebox.org/).

O U-Boot é o bootloader mais utilizado, sendo encontrado em diversos projetos e sendo a escolha mais popular entre os desenvolvedores. Ele apresenta suporte a diversas arquiteturas incluindo ARM, Blackfin, RISC-V e x86. Esta presente no mercado a mais de 20 anos, sendo utilizado tanto como bootloader de primeiro estágio como de segundo. Além disso, tem comunidade ativa de desenvolvimento e por isso é o padrão em diversas fabricantes de SoC.

O Barebox, por sua vez, foi anunciado como o sucessor do U-Boot, no seu início ganhou uma certa atenção, desenvolvedores começaram a tocar o projeto e manter uma comunidade ativa. Contudo, com seu surgimento, o u-boot passou a ser melhorado,  provavelmente devido a concorrência e o anúncio de seu sucessor. Por isso, o barebox ficou meio que de lado e o U-Boot continua sendo o mais usado.

Assim, durante este treinamento vamos adotar o U-Boot como bootloader para o nosso sistema embarcado.


# U-Boot

Como mencionado anteriormente, o U-Boot é o bootloader mais utilizado, sendo adotado por diversos fabricantes de SoC. 

O projeto é open-source e fornecido pela DENX, empresa de software alemã, através do [repositório oficial](http://www.denx.de/wiki/U-Boot). Além disso, o mesmo possui uma comunidade muito ativa de desenvolvedores e também uma vasta [documentação](http://www.denx.de/wiki/U-Boot/Documentation). 

Tanto a comunicação, como o suporte, são feitos através de uma [lista de emails](https://lists.denx.de/pipermail/u-boot/), assim como outras ferramentas open-source. Desde 2008, mantém um intervalo fixo de releases, sendo nos períodos de dois ou três meses uma nova versão é lançada, normalmente identificados com a cada \(YYYY.MM\).

### Funcionalidades

As principais funcionalidades do U-Boot podem ser listadas de forma resumida, como:

* Listar informações de hardware;
* Manipulação da RAM \(leitura, escrita, comparação, testes\);
* Manipulação de memórias FLASH \(leitura, escrita\);
* Boot via flash;
* Boot via rede \(bootp, tftp, dhcp\)
* Boot via SD/MMC ou USB;
* Suporta vários sistemas de arquivo \(fat, ext2/3, ubifs, jffs2, etc\);
* Suporta scripts e variáveis de ambiente;
* Capaz de executar código bare-metal;
* Fornece linha de comando para o usuário;
* Carrega e executa o kernel \(parametrização\).

### Configuração e Instalação

Normalmente, o fabricante fornece os fontes do U-Boot para a sua placa, quando esta utiliza o U-Boot como bootloader. No entanto, quando o fabricante não fornece os códigos, assim como no caso da RPi3, os fontes genéricos podem ser baixados via[ repositório ftp](ftp://ftp.denx.de/pub/u-boot/) ou pelo[ repositório oficial do git](https://github.com/u-boot/u-boot).

Assim como o Crosstool-ng  e quase todas as ferramentas que vamos estudar no treinamento, o U-Boot também fornece alguns arquivos de configuração pré-definidos, sendo disponibilizados pra algumas placas. Esses arquivos podem ser visualizados no diretório `configs` presente dentro do diretório da ferramenta, isto é, o diretório gerado na extração do download.

É comum que esses arquivos de configurações sejam mantidos pelo próprio fabricante, sendo ele o responsável por atualizar a árvore principal do projeto \(u-boot\) no caso.

Caso a sua plataforma que estamos utilizando tenha as configurações já definidas no arquivo de configuração, é altamente recomendado utiliza-lo. Isto, principalmente, pois o U-Boot utiliza-se de drivers para interagir com o hardware da placa embarcada, assim, utilizando o arquivo de configuração já estabelecido, será um caminho mais simples, rápido e estável.

Para carregar uma configuração, basta executar o comando `make` seguido do nome do arquivo de configuração, no caso da plataforma do nosso treinamento:

```bash
make rpi_3_32b_defconfig
```

Além disso, é necessário especificar o toolchain de cross-compilação, uma vez que estamos na plataforma _host_ e o código deve rodar na plataforma _target._ Desta forma_,_ para que ele gere um binário para a arquitetura do _target_ é necessário relacionar o compilador específico.

Para compilar o U-Boot, é preciso fornecer o cross-compilador por meio da variável de ambiente `CROSS_COMPILE`:

```bash
export CROSS_COMPILE=arm-linux−
```

Ao final do processo, após carregar a arquitetura e configurar o cross-compiling toolchain,  é só dar um `make` novamente, como saída, será gerado o binario `u-boot.bin`.

### Gravação no _target_

O processo de gravação do binário gerado para o _target,_ é normalmente dependente do hardware utilizado.

Se o _target_ permitir carregar o bootloader de uma mídia removivel por exemplo, então esse binario pode ser gravado numa mídia  deste tipo, como por exemplo: SD Card, MMC, HDD e etc. 

Porém, para _targets_ baseados em memória Flash ou _targets_ que requerem que o bootloader esteja na Flash normalmente fornecem uma ou mais das seguintes opções:

* O bootloader de primeiro estágio pode fornecer algum mecânismo de escrita na Flash;
* O processador pode fornecer um tipo de monitor de boot \(uma espécie de shell básico\) que se comunica via Serial ou USB;
* É fornecido pinos para a gravação via JTAG, como feito em outro micros que possibilitam o update de bootloader;
* Se o U-Boot já for o bootloader de segundo estágio, é possível gravar uma nova versão.

> Se o U-Boot for utilizado para gravar uma norva imagem, é necessário um certo cuidado, pois caso envie um arquivo com erro ou corrompido e ele sobreescrever, não há o que fazer, a placa fica inutilizável, pois o processo de boot foi corrompido.

# U-Boot vs. RPi

### Processo de Boot na RPi 3

O processo de boot da RPi é um tanto diferente do que os outros SoCs. Quando o hardware é energizado, quem assume o controle não é o CPU e sim a GPU, diferentemente dos boots abordados anteriormente. A imagem a seguir, ilustra resumidamente o processo de boot da RPi 3.

<figure>
<img src="/assets/posts/dsle20/boot-4.png" alt="">
</figure>

Inicialmente, o boot ROM, que é um código gravado na ROM interna do chip é executado por um pequeno núcleo RISC interno da GPU. Ele verifica se o modo de boot GPIO está ativado, se sim procura pela partição de boot no dispositivo equivalente da GPIO, caso contrário, segue uma ordem de procura definida por SD1, SD2, NAND, SPI e USB.

Enfim, ele encontra a partição de boot, monta-a e procura pelo arquivo `bootcode.bin`, que seria um bootloader de segundo estágio. Ao encontra-lo, carrega-o na cache L2 \(128K\) interna da GPU e executa-o.

O `bootcode.bin`, por sua vez, inicializa a RAM, procura o arquivo `start.elf` na partição boot. Este na verdade é o firmware da GPU, então carrega-o na RAM, agora devidamente inicializada, e executa-o. O `start.elf`, é o bootloader completo, que termina de inicializar o hardware, incluindo a CPU. Então, configura o hardware de acordo com parâmetros presentes nos arquivos `config.txt` e `cmdline.txt`**.** 

O arquivo `config.txt` pode ser visto como a interface da BIOS, onde cada opção da BIOS seria uma opção no neste arquivo. Ao passo que o arquivo `cmdline.txt` apresenta os parâmetros do kernel Linux. Existem diversas documentações trantando cada uma das opções disponível nestes arquivos, e as possíveis configurações.

Por fim, o kernel Linux é executado pela CPU na memória RAM, assumindo assim o controle completo do processador e então o bootloader deixa de existir na memória volátil.

Infelizmente esses binarios são de propriedade da Broadcom e não da Raspberry Foundation e seus códigos fontes não são divulgados. Em diversas fontes é comentado que se assinar um NDA com a Broadcom ela libera o datasheet e os principais fontes para a empresa, o que não é nosso caso no treinamento e em projetos em geral.

### Gravando U-Boot na RPi

Sendo os binários fechados e os códigos fontes não divulgados, como fazer então para carregar o U-Boot na RPi? Bem, a resposta mais simples seria não fazer nada. Contudo, existe uma maneira de se conseguir isso, para tal vamos explorar o processo de boot e inserir o nosso bootloader dentro dele, conforme apresentado na figura a seguir.

<figure>
<img src="/assets/posts/dsle20/boot-5.png" alt="">
</figure>

Apesar de fornecer apenas os executáveis, a Broadcom fornece uma ampla variedade de configurações por esse arquivo `config.txt` e `cmdline.txt`. O que viabiliza a utilização do processador em diversas plataformas e também flexibiliza as configurações.

Uma das configurações que é possível fazer, inclusive, é especificar a imagem do kernel para ser carregada, que nada mais é  que um executável. E é justamente nesse ponto, onde vamos "hackear" o processo de boot da RPi e inserir nosso bootloader.

Uma vez que é permitido especificar a imagem do kernel a ser executada, podemos driblar este passo, inserindo o U-Boot ao invés da imagem. Colocando o U-Boot, como se fosse o kernel, deste modo ao invés do `start.elf` carregar o kernel ele carrega e roda o U-Boot.

Inserindo esse passo a mais, conseguimos burlar o processo de boot natural da RPi, inserindo o nosso bootloader na inicialização da placa. 

Mas porque utilizar o U-Boot ao invés do bootloader padrão? Bom, o U-Boot fornece várias funcionalidades extras, como já foi apresentado durante as seções anteriores, e grande parte delas são bem úteis durante o desenvolvimento de sistemas Linux embarcado. Além disso, a nossa plataforma de estudo tem essa limitação, outras placas que vão possuir o firmware aberto, será obrigatório a instalação do U-Boot ou outro bootloader, então este processo, é de suma importância para o treinamento.

# \[LAB\] Configurando a Comunicação Serial

## Configurando a Comunicação Serial com a RPi 3

Por padrão, a Raspberry Pi possui duas built-in _UARTs_, uma comum _\(PL011\)_ e outra _mini UART_. Essa última, é limitada e carece de alguns recursos básicos como break detection, bit de paridade, dentre outros. Alem disso, a _mini UART_ possui uma FIFO menor quando comparada à _PL011_ e sua baudrate é linkada ao clock da GPU, ou seja, a taxa de transmissão da _mini UART_ varia de acordo com a oscilação do clock da GPU.

O módulo BT \(bluetooth\) da RPi 3 necessita de uma UART para funcionar e, por padrão, o BT da RPi 3 é conectado à UART _PL011_, tornando-a inutilizável para o usuário. No entanto, o firmware da GPU permite que o usuário escolha uma dentre as três opções:

* Desabilitar o módulo BT;
* Utilizar o módulo BT com a _mini UART_;
* Utilizar o módulo BT com a UART _PL011_;

A princípio, a utilização da _mini UART_ para redirecionamento de console é suficiente, pois além da interação entre usuário e target via shell possuir um fluxo de dados baixo, existe a possibilidade de realizar a comunicação via rede \(SSH\). Portanto, será necessário apenas ativar o redirecionamento do console para a _mini UART_. Para tal, acesse a RPi via SSH e adicione as seguintes linhas no final do arquivo `config.txt`:

```bash
ssh pi@10.1.1.100
```

```bash
sudo nano /boot/config.txt
[..]
dtparam=audio=on
enable_uart=1
```

> Para salvar as alterações feitas em um arquivo com o nano, utilize as teclas `CTRL+X, Y`, `Enter`.

Para maiores informações, consulte a [documentação da UART](https://www.raspberrypi.org/documentation/configuration/uart.md) no site da RPi. Após realizar a configuração acima, desligue a Raspberry Pi,

```bash
sudo poweroff
```

e faça a conexão entre o adaptador USB-Serial \(TTL\) e a placa. Certifique-se de escolher a opção/jumper 3.3v caso o adaptador permita. Por padrão, a RPi roteia os pinos `GPIO14` e `GPIO15` como _TX_ e _RX_ da serial principal \(aquela que não está sendo utilizada pelo módulo BT\), respectivamente.

<figure>
<img src="/assets/posts/dsle20/boot-6.png" alt="">
</figure>

Esses GPIOS estão mapeados nos _pinos 08 e 10_, respectivamente, do conector geral de 40 pinos. Os _pinos 01 e 02_ de tal conector são aqueles fisicamente próximos da borda oposta às entradas USB. O _pino 01_ é o pino mais interno e o _pino 02_ é o mais externo, próximo da borda lateral. As figuras a seguir exibem a descrição completa do conector de 40 pinos e indicação dos pinos fisicamente. Após analisar as figuras, faça as três conexões, _TX_, _RX_ e _GND_, entre seu adaptador e a RPi3.

<figure>
<img src="/assets/posts/dsle20/boot-7.png" alt="">
</figure>


### Configurando Acesso ao USB no Ubuntu

Para acessar a Serial no Ubuntu com o usuário padrão \(você\), dois procedimentos são necessários: Primeiramente deve-se criar o grupo `dialout`, pois por padrão a serial pertencerá a este e grupo e, o grupo ainda não foi criado e nem você pertence a ele:

```text
sudo groupadd dialout
```

  
O comando acima cria o grupo `dialout` no sistema. Então, é preciso adicionar você como um usuário deste grupo, ou seja, para que você tenha acesso à qualquer arquivo/dispositivo pertencente ao grupo:

```text
sudo gpasswd -a nome_do_seu_usuario dialout
```

O comando acima adiciona o usuário _nome\_de\_usuario_ ao grupo `dialout`. Para maiores informações sobre grupos e usuários:  [https://wiki.archlinux.org/index.php/users\_and\_groups](https://wiki.archlinux.org/index.php/users_and_groups)

Normalmente, existe uma opção para chavear um dispositivo de hardware entre o _host_ \(seu computador\) e _guest_ \(máquina virtual\). Verifique na sua aplicação da VirtualBox as opções ficam no menu _Devices&gt;USB._ Encontre o dispositivo que você deseja colocar na máquina virtual e selecione.

### Testando a Comunicação Serial

Conecte o adaptador serial na máquina de desenvolvimento e rode o comando `dmesg` no terminal. A saída será algo parecido com:

```bash
dmseg
```

```text
[5331.599292] usb 1-3: new full-speed USB device number 9 using xhci_hcd
[5331.740103] usb 1-3: New USB device found, idVendor=1a86, idProduct=7523
[5331.740106] usb 1-3: New USB device strings: Mfr=0, Product=2, SerialNumber=0
[5331.740107] usb 1-3: Product: USB2.0-Serial
[5331.740607] ch341 1-3:1.0: ch341-uart converter detected
[5331.740888] usb 1-3: ch341-uart converter now attached to ttyUSB0
```

Procure pelo nome do arquivo criado pelo driver para manipular o dispositivo conectado. No caso acima, o nome do arquivo é `ttyUSB0`. Normalmente dispositivos seriais são mapeados como `ttyUSB0`, `ttyS0`, ou algo similar, e são criados dentro do diretório de dispositivos do Linux `/dev`. Não se preocupe com detalhes a respeito de drivers e arquivos de dispositivo neste momento, essas informações serão vistas mais adiantes no treinamento.

Após identificar seu dispositivo, abra o **putty** e o configure da seguinte maneira:

* _Connection type:_ Serial;
* _Serial line:_ Nome do seu dispositivo. No exemplo acima: `/dev/ttyUSB0`;
* _Speed:_ Este é o baudrate da conexão serial. Configure-o para: _115200_;

> Clique em _Default Settings_ e em seguida _Save_, de modo a salvar as configurações feitas e não precisar repeti-las sempre que iniciar o **putty**.

Clique em _Open_ para iniciar uma nova conexão e, se tudo foi configurado corretamente, ao ligar a RPi 3, um console deverá ser exibido na janela do **putty**. Caso tenha ocorrido algum erro, peça ajuda ao instrutor.

# \[LAB\] Bootloader  \(U-Boot\)

### Baixando o U-Boot

Assim como nas atividades anteriores, os fontes do **U-Boot** foram previamente baixados e encontram-se no diretório `∼/dsle20/dl/bootloader`. Crie um diretório chamado `bootloader` dentro da pasta `∼/dsle20` e, em seguida, extraia o **U-boot** no diretório criado:

```bash
cd ~/dsle20/
mkdir bootloader && cd bootloader
unzip ~/dsle20/dl/bootloader/u-boot-master.zip
```

Acesse o diretório do **U-Boot** e liste as configurações pré-definidas para as diversas plataformas suportadas pelo **U-Boot**. Devido à extensão da lista de configurações, é recomendado a utilização do comando `less`. Este comando permite a visualização do conteúdo de um arquivo ou output de algum comando, por meio de páginas do tamanho da tela:

```bash
cd u-boot-master
ls configs/ | less
```

```bash
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
```

Use as teclas _espaço_, _b_ e _q_ para exibir a próxima página, a página anterior ou encerrar a visualização, respectivamente. Uma vez que o **U-Boot** suporta diversas arquiteturas de hardware diferentes, é necessário selecionar uma delas antes de compilar o programa. Selecione a configuração `rpi_3_32b_defconfig` e compile o **U-Boot**, indicando o prefixo do cross-compilador conforme configurado anteriormente:

```bash
make rpi_3_32b_defconfig
make -j2 CROSS_COMPILE=arm-linux-
```

Verifique o arquivo criado, `u-boot.bin`, através do comando:

```bash
ls -l u-boot.bin
```

### Gravando o U-Boot

O processo de gravação do bootloader é dependente de hardware, específico para cada plataforma. Conforme visto em aula, a RPi 3 busca o bootloader e firmwares relacionados ao processo de boot na partição `boot` do cartão micro SD. Assim, dois procedimentos são necessários para gravar e ativar o **U-Boot** no processo de boot da RPi:

1. Copiar o binário `u-boot.bin` para a partição `boot` do cartão micro SD;
2. Configurar o arquivo `config.txt` para que o firmware da GPU, `start.elf`, execute o `U-Boot` no lugar do kernel Linux;

É possível copiar o arquivo `u-boot.bin` para o cartão micro SD de várias maneiras. Visto que já existe uma configuração de rede entre a máquina de desenvolvimento e a RPi, realizada em atividades anteriores, o arquivo será copiado via comando `scp`:

```bash
scp u-boot.bin pi@10.1.1.100:/home/pi/
```

Logue na RPi, via SSH, e copie o arquivo do diretório `home` para o diretório `boot` com privilégios de administrador:

```bash
ssh pi@10.1.1.100
```

```bash
sudo cp u-boot.bin /boot/
ls /boot
```

```text
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
```

Feito isso, adicione a seguinte linha no final do arquivo `config.txt`:

```bash
sudo nano /boot/config. txt
[..]
dtparam=audio=on
enable_uart=1
kernel=u-boot.bin
```

O parâmetro acima especifica qual imagem do kernel, o firmware `start.elf` deve carregar. Neste caso, a imagem é o próprio **U-Boot**. Após salvar as alterações no arquivo, renicie a RPi \(`sudo reboot`\).

> Atenção, só reinicie a RPi se você possui uma conexão serial funcional entre ela e a máquina de desenvolvimento, pois a única interação com o menu do **U-Boot**, por enquanto, é via serial.

Por último, interrompa o processo de boot do **U-Boot** pressionando uma tecla para entrar no shell:

```text
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
```

### Configurando variáveis de ambiente no U-Boot

Após obter acesso ao shell do **U-Boot**, configure algumas variáveis de ambiente básicas para manter o sistema da RPi bootável, pois por padrão, o **U-Boot** não identifica a imagem do kernel automaticamente. Inicialmente, desative o processo de _autoboot_:

```bash

setenv bootdelay -1
```

Futuramente, o **U-Boot** será configurado para carregar o kernel pela rede, de uma pasta de sua máquina de desenvolvimento. Portanto, configure o endereço _IP_ da RPi e máquina de desenvolvimento:

```bash

setenv ipaddr 10.1.1.100
setenv serverip 10.1.1.1
```

Por fim, salve as alterações realizados no disco, de tal forma que elas estejam disponíveis na próxima inicialização, e reinicie o RPi:

```bash

saveenv
reset
```

Após enviar o comando `saveenv`, o **U-Boot** cria um arquivo de configuração chamado `u-boot.env` que contém todas as variáveis de ambiente definidas. Após reiniciar novamente a RPi, o processo de _autoboot_ não deve ser inicializado e o controle do shell exibido logo em seguida. Para “bootar” o **Raspbian** novamente, pelo **U-Boot**, algumas configurações adicionais são necessárias. O primeiro passo, é carregar um arquivo \(imagem do kernel\) do cartão micro SD para a RAM em um endereço específico. Utilize o seguinte comando:

```bash
f
atload mmc 0:1 ${kernel_addr_r} kernel7.img
```

O comando acima carrega um arquivo binário de um sistema de arquivos FAT \(_fatload_\). Os parâmetros são:

* **mmc**: o dispositivo de armazenamento onde se encontra o binário \(cartão SD\);
* **0**: o número do dispositivo, pois muitas vezes o seu target pode possuir mais de um dispositivo de armazenamento;
* **1**: o número da partição no dispositivo \(partições são enumeradas a partir de 1\);
* **${kernel\_addr\_r}**: o endereço inicial na RAM onde deseja-se carregar o binário, neste caso a configuração do **U-Boot** já fornece uma variável de ambiente com o endereço inicial da RAM, para carregar o kernel \(_${kernel\_addr\_r}_\);
* **kernel7.img**: o binário que se deseja carregar. Lembrando que por padrão, a partição boot do **Raspbian** fornece duas imagens: `kernel.img` e `kernel7.img`. A primeira é para as versões de hw anteriores \(RPi e RPi 2\) e a última \(`kernel7.img`\) é a imagem para as placas da RPi 3 em diante;

Algumas plataformas possuem dispositivos de hardware que não podem ser identificados dinamicamente pelo kernel. Em tais casos, é necessário um mecanismo para informar o kernel sobre dispositivos presentes no sistema. Atualmente, o mecanismo utilizado para tal função é chamado de _Device Tree_, que é uma estrutura de dados que descreve a topologia e configuração de hardware no sistema. Analisaremos esse mecanismo em breve durante o curso.

A RPI 3 é um tipo de plataforma que utiliza esse recurso e bootloader é o responsável por passar o _Device Tree_ para o kernel e, portanto, é necessário fazer o loading desse arquivo no **U-Boot**. O processo é o mesmo anterior, porém com algumas alterações nos parâmetros:

> Caso esteja utilizando a RPi 3B+ substitua o device tree utilizado pelo device tree `bcm2710-rpi-3-b-plus.dtb`, ao longo do treinamento.

```bash
fatload mmc 0:1 ${fdt_addr_r} bcm2710-rpi-3-b.dtb
```

* **mmc**: o dispositivo de armazenamento onde se encontra o binário \(cartão SD\);
* **0**: o número do dispositivo, pois muitas vezes o seu target pode possuir mais de um dispositivo de armazenamento;
* **1**: o número da partição no dispositivo \(partições são enumeradas a partir de 1\);
* **${fdt\_addr\_r}**: o endereço inicial na RAM onde deseja-se carregar o binário, neste caso a configuração do **U-Boot** já fornece uma variável de ambiente com o endereço inicial da RAM, para carregar o _Flattened Device Tree_ \(_${fdt\_addr\_r}_\);
* **bcm2710-rpi-3-b.dtb**: arquivo compilado do Device Tree \(_dtb_\) referente à RPi 3 B;

Estes são basicamente os únicos arquivos necessários para realizar o boot do Raspbian via **U-Boot**. Entretanto, além dos arquivos, ainda é necessário configurar alguns parâmetros do kernel. Configure a variável de ambiente `bootargs`, responsável por armazenar parâmetros para serem passados ao kernel:

```bash
setenv bootargs 8250.nr_uarts=1 root=/dev/mmcblk0p2 rootwait console=ttyS0,115200
```

* **8250.nr\_uarts=1**: número de portas seriais para serem registradas \(utilizadas\);
* **root=/dev/mmcblk0p2**: path para a localização do **RootFS** \(_Root FileSystem_\);
* **rootwait**: espera \(indefinidamente\) a inicialização dispositivo onde o **RootFS** está localizado. _mmcblk0_ refere-se ao micro SD e _p2_ à partição número 2, visto que a primeira é a partição de `boot`;
* **console=ttyS0,115200**: redireciona um console para a porta serial `ttyS0` \(_mini UART_ da RPi 3\), e seu respectivo baudrate;

Finalmente, com as configurações acima realizadas, “basta” dar o comando de boot:

```bash
bootz ${kernel_addr_r} - ${fdt_addr_r}
```

onde:

* **kernel\_addr\_r**: é o endereço na RAM onde está carregada a imagem do kernel;
* **-**: seria o endereço na RAM da imagem _initrd_, que é uma imagem do **RootFS**. É possível carrega-lo na RAM, assim como kernel e _Device Tree_. No entanto, no momento a RPi não possui nenhuma imagem desse tipo. Ela será gerada em atividades futuras. Este parâmetro é opcional;
* **fdt\_addr\_r** é o endereço na RAM onde está carregado o compilado do _Device Tree_;

Se os comandos acima foram executados corretamente, você deverá enxergar o loading do kernel pela serial.

### Criando um script de inicialização no U-Boot

O **U-Boot** possui uma funcionalidade que permite que o usuário crie scripts contendo sequência de comandos, como os executados acima. Na sua máquina de desenvolvimento, navegue até o diretório do U-Boot e crie o seguinte arquivo:

```bash
cd ~/dsle20/bootloader/u-boot-master
gedit rpi3scr.txt
```

Digite \(copie\) todos os comandos novamente no arquivo aberto e em seguida salve-o:

```bash
fatload mmc 0:1 ${kernel_addr_r} kernel7.img
fatload mmc 0:1 ${fdt_addr_r} bcm2710-rpi-3-b.dtb
setenv bootargs 8250.nr_uarts=1 root=/dev/mmcblk0p2 rootwait console=ttyS0,115200
bootz ${kernel_addr_r} - ${fdt_addr_r}
```

Em seguida, dentro da pasta tools no diretório do U-Boot, existe uma ferramenta chamada mkimage capaz de criar imagens do **U-Boot**, **kernel**, **RootFS** e inclusive scripts para o **U-Boot**. Digite o seguinte comando:

```bash
tools/mkimage -A arm -O linux -T script -d rpi3scr.txt boot.scr
```

onde os argumentos representam: arquitetura do executável \(_-A_\), sistema operacional \(_-O_\), tipo da imagem \(_-T_\), arquivo de entrada com os comandos digitados no gedit \(_-d_\) e arquivo de saída \(`boot.src`\), que é uma imagem do script.

Após a execução do comando, copie o arquivo `boot.scr` para o diretório `boot` da RPi via `scp`. Se tudo foi realizado corretamente, reinicie a RPi e digite o comando `boot` no shell do **U-Boot**. 

É possível ativar o _autoboot_ através da modificação da variável de ambiente _bootdelay_, que representa o delay em segundos antes de iniciar o boot pelo script `boot.scr`. Se desejar, altera-a, salve as variáveis de ambiente no cartão SD \(`saveen`\) e reinicie o **U-Boot**.

