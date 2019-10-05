---
layout: archive
title: "Desenvolvimento de Sistemas Embarcados Linux"
permalink: /linux/toolchain
author_profile: false
  
---

{% include base_path %}


---

# Cross-Compiling Toolchain

Os objetivos desta atividade são:

* Aprender a utilizar um toolchain pronto, isto é, fornecido pelo fabricante do SoC ou repositório padrão por exemplo;
* Compilar seu próprio toolchain utilizando a ferramenta `crosstool-ng`

## Utilizando um toolchain pré-compilado

A Raspberry Pi Foundation fornece gratuitamente em seu [repositório oficial](https://github.com/raspberrypi), diversos componentes open-source para a Raspberry Pi. Dentre eles, estão inclusos os fontes do kernel Linux, drivers, bibliotecas e firmwares específicos, além de seu próprio toolchain, o qual será utilizadonesta atividade.

### Instalação e Configuração

Inicialmente, abra um novo shell e crie a seguinte estrutura de diretórios dentro do diretório `dsle19`:

<pre>
cd ~/dsle19
mkdir toolchains
cd toolchains 
</pre>

Em seguida, o correto seria clonar a pasta `tools` do repositório oficial da Raspberry Pi, no intuíto de obter a última versão disponível do toolchain:

<pre>
git clone https://github.com/raspberrypi/tools.git
</pre>

No entanto, a fim de garantir uma maior eficiência na execução das atividades deste treinamento, todos os arquivos necessários foram previamente baixados e encontram-se no diretório `dsle19/dl`. Portanto, substituiremos o processo de clonar o repositório `tools` pela extração do seguinte arquivo:

<pre>
unzip ~/dsle19/dl/toolchains/tool.zip
</pre>

O comando acima extrai o arquivo *tools.zip* no diretório atual (`dsle19/toolchains`). Ao final do processo, verifique se o diretório `tools` foi criado, por meio do comando `ls`.

Como o toolchain fornecida pela RPi FOundation é pré-compilado, para instalá-lo basta adicionar o caminho das ferramentas (binários) do toolchain à variável de ambiente $PATH:

<pre>
export PATH=$PATH:~/dsle19/toolchains/tools/arm-bcm2708/gcc-linaro-arm-linux-gnueabihf-raspbian/bin
</pre>

Note que tal alteração é momentânea, isto é, ao fechar o shell atual ela será perdida. Um dos meios defazer essa alteração permanente (opcional) é por meio da inserção do mesmo comando no final do arquivo `∼.bashrc`, que é um script shell que é executado sempre que um novo shell é iniciado.

Simples assim, toolchain instalado! Uma maneira de verificar se o *export* do PATH funcionou é digitar `arm` no shell e pressionar a tecla TAB duas vezes. Ao fazer isso, o shell tentará auto-completar o comando `arm` de acordo com as opções de executáveis disponíveis na variável PATH. O resultado deverá ser uma lista semelhante à:

<pre>
arm2hpdl
arm-linux-gnueabihf-gfortran
arm-linux-gnueabihf-addr2line
arm-linux-gnueabihf-gprof
arm-linux-gnueabihf-ar
arm-linux-gnueabihf-ld
arm-linux-gnueabihf-as
arm-linux-gnueabihf-ld.bfd
arm-linux-gnueabihf-c++
arm-linux-gnueabihf-ldd
arm-linux-gnueabihf-c++ filt
arm-linux-gnueabihf-ld.gold
...
</pre>

### Testando o toolchain

É possível testar o toolchain através da compilação de um programa bem simples, como o `helloworld.c`, em C. Inicialmente, crie a pasta `ex01` dentro do diretório de exercícios `exs` e, em seguida, crie/edite o arquivo `helloworld.c` com seu editor favorito:

<pre>
cd ~/dsle2019/exs
mkdir ex01 && cd ex01
code helloworld.c
</pre>

E então,

<pre>
#include &lt stdio.h &gt

int main()
{
    printf("Hello cross-compiled world!\n");
    return 0;
}
</pre>

Em seguida, compile o arquivo `helloworld.c` nativamente, isto é, utilizando o *gcc*:

<pre>
gcc helloworld.c -o hellox86
</pre>

Utilizando o comando `file`, verifique as informações do binário gerado:

<pre>
file hellox86
</pre>

A saída do comando deve ser algo similar à:

<pre>
hellox86: ELF 32-bit LSB executable, Intel 80386, version 1 (SYSV), dynamically linked, interpreter /lib /ld - linux .so.2, for GNU/Linux 2.6.32, BuildID[sha1]=4d1dbc14e02c87dbf1578335b77febef80b524a4, not stripped
</pre>

Note que a segunda informação, *Intel 80386* indica que o programa foi compilado para a mesma arquitetura de sua máquina, x86. Em seguida, execute-o:

<pre>
chmod +x hellox86
./hellox86
Hello cross-compiled world!
</pre>

Agora repita o processo e utilize o recém-instalado toolchain para cross-compilar o mesmo programa para a RPi. Para isso, trocamos o compilador antivo *gcc* por *arm-linux-gnueabihf-gcc*:

<pre>
arm-linux-gnueabihf-gcc helloworld.c -o helloARM
</pre>

Novamente, verifique o programa gerado através do comando `file` e veja que desta vez a arquitetura indicada será *ARM*:

<pre>
helloARM: ELF 32-bit LSB executable, ARM, EABI5 version 1 (SYSV), dynamically linked, interpreter /lib/ld- linux -armhf.so.3, for GNU/Linux 2.6.26, BuildID[sha1]=68bc6061bdbb1b80e5190760e91b687a1caebf97, not stripped
</pre>

Não será possível executar este segundo programa na sua máquina pois o programa e a máquina possuem arquiteturas diferentes. Faça o teste. No entanto, é possível copiá-lo para a RPi e executá-lo nela. 

Para tal, utilizaremos o protocolo *SSH* para a comunicação entre a nossa plataforma host (PC) e a nossa placa (target). 

> Primeiramente, devemos estabelecer uma conexão de rede entre a RPi e nosso computador. O capítulo [Configurando a Rede da RPi](/linux/rede), apresenta algumas formas de se estabelecer esta comunicação.

Copie-o para a RPi através do comando `scp` (secure copy). Primeiramente, confira a funcionamento do comando através de seu manual `man scp` e então:

<pre>
scp helloARM pi@10.1.1.100:/home/pi/helloARM
</pre>

Acesse-a via *SSH* e tente executar o programa, lembre-se a senha padrão do usuário `pi` da RPi é **raspberry**.

<pre>
ssh pi@10.1.1.100
</pre>

<pre>
cd
./helloARM
</pre>

Neste ponto, conseguimos realizar a nossa primeira compilação (cross-compile) e também a nossa primeira execução na plataforma embarcada (RPi). Este procedimento foi realizado com base em uma toolchain pronta, fornecida por terceiros. Contudo, em um contexto profissional e em aplicações reais, faz-se necessário a utilização de toolchains próprias e criadas e adequadas ao nosso sistema. Desta forma, no próximo capítulo será discutido o procedimento de criação de toolchains suas principais ferramenteas e componentes.


## Compilando seu próprio toolchain

A [*Crosstool-ng*](https://crosstool-ng.github.io/) é provavelmente a principal ferramenta open-source para customização de toolchains. Suporta diversas arquiteturas diferentes, é capaz de gerar código bare-metal e possui uma interface baseada no *menuconfig*.

Nesta atividade, a ferramenta *Crosstool-ng* será utilizada para criar um toolchain customizado para a RPi. Este toolchain será utilizado para todas as atividades posteriores como compilação do bootloader, kernel, bibliotecas e aplicações.

### Instalação e Configuração

Abra um novo shell e navegue até a pasta `∼/dsle19/toolchains`. Em seguida, descompacte o arquivo `∼/dsle19/dl/toolchains/crosstool-ng-1.23.0.tar.xz` no diretório atual e navegue até o novo diretório:

<pre>
cd ~/dsle19/toolchains/
tar xvf ~/dsle19/dl/toolchains/crosstool-ng-1.23.0.tar.xz
cd crosstool-ng-1.23.0/
</pre>

Após a descompactação, configure o *crosstool-ng* para ser instalado localmente, isto é, no mesmo diretório em que se encontra o script de configuração. Então, execute os comandos `make` e `make install` para realizar a instalação:

<pre>
./configre --enable-local
make
make install
</pre>

Se tudo correu bem e nenhuma mensagem de erro foi exibida, o *crosstool-ng* pode ser executado a partir do diretório atual. O seguinte comando exibe as informações de ajuda da ferramenta:

<pre>
./ct-ng help
</pre>

O *Crosstool-ng* permite criar um ou mais toolchains para arquiteturas diferentes e, por isso, fornece um conjunto de configurações pré-definidas para arquiteturas mais comuns. É possível listá-las por meio do seguinte comando:

<pre>
./ct-ng list -samples
</pre>

Note que, dentre as configurações, existe uma pré-definida para a RPi 3: `armv8-rpi3-linux-gnueabihf`. Neste treinamento, essa configuração será usada como base para a criação do toolchain. Para tal,
carregue-a por meio do comando abaixo:

<pre>
./ct-ng armv8-rpi3-linux-gnueabihf
</pre>

Uma vez feito o *loading* da configuração, abra o menu de configurações do *crosstool-nt* e faça alguns ajustes:

<pre>
./ct-ng menuconfig
</pre>

> Nesta etapa você deverá realiza a configuração através do *menuconfig* portanto, muita atenção pois é um procedimento que requer cuidado, pois a configuração errada de algum módulo ou componente pode não ser evidente agora e causar problemas durante a fase de desenvolvimento.

### Configuração da CrossTool

1. Opção **Path and misc options**:
    -   **Number of parallel jobs**: (2) - Obs: Essa opção define a quantidade de threads de execução, que por sua vez diminui o tempo de compilação do toolchain.
    -   **Maximum log level to see**: (DEBUG) - Obs: Essa opção exibe informações a respeito do procedimento de build em tempo real. Assim, caso ocorra algum erro durante a compilação do toolchain, esse erro será exibido no shell.
    -   **CT_PREFIX**: Obs: Este é o diretório de instalação do toolchain. 
        Altere-o **de**: ${CT_PREFIX:-${HOME}/x-tools}... 
        **para**: ${CT_PREFIX:-${HOME}/dsle19/toolchains/x-tools}...

2. Opção **Toolchain options**:
    -   **Tuple's alias**: (arm-linux) - Obs: Desta maneira, o *crosstool-ng* irá gerar o compilador como `arm-linux-gcc`, por exemplo. Caso contrário ele gera um nome extenso como: `armv8-rpi3-linux- gnueabihf-gcc`.

3. Opção **Debug facilities**:
    -   **gdb**: (ativo) - Obs: Ative o `gdb`, pois será o debugger utilizado no restante do treinamento. Além disso, assegure-se de que as seguintes opções foram selecionadas:
        - Cross-gdb;
        - build a static cross gdb;
        - gdbserver

Salve suas alterações, saia do *menuconfig* e inicie o processo de compilação do toolchain:

<pre>
./ct-ng build
</pre>

Ao final do processo, conforme configurado em *CT_PREFIX*, os binários do toolchain gerado estarão disponíveis no diretório: `∼/dsle19/toolchains/x-tools/armv8-rpi3-linux-gnueabihf/bin/`. Dê um comando `ls` no diretório e verifique as ferramentas geradas.

### Configuração do PATH

Como este toolchain será utilizado nas próximas atividades do treinamento, é necessário adicionar seus executáveis à variável de ambiente `$PATH`. Abra o arquivo `∼/.bashrc` com seu editor favorito:

<pre>
gedit ~/.bashrc
</pre>

Em seguida, adicione a seguinte linha no final do arquivo:

<pre>
export PATH=$PATH:x-tools/armv8-rpi3-linux-gnueabihf/bin/
</pre>

Salve e feche o arquivo. Então basta carregar a configuração e, em seguida, realizar um pequeno teste para verificar se os binários foram adicionados corretamente à variável `$PATH`:

<pre>
source ~/.bashrc
arm-linux-gcc --version
</pre>

A saída deve ser algo semelhante à:

<pre>
arm-linux-gcc (crosstool-NG crosstool-ng-1.23.0) 6.3.0
Copyright (C) 2016 Free Software Foundation, Inc.
This is free software; see the source for copying conditions. There is NO warranty; not even for MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
</pre>

### Testando o toolchain

Recompile o programa da atividade 01, `helloworld.c`, em C com o novo toolchain gerado. Inicialmente, crie a pasta `ex02` dentro do diretório de exercícios `exs` e, em seguida, copie o arquivo `helloworld.c` da pasta `ex01` para a pasta `ex02`:

<pre>
cd ~/dsle19/exs
mkdir ex02
cp ex01/helloworld.c ex02
</pre>

Navegue até a pasta `ex02` e compile o programa `helloworld.c` utilizando o *gcc* do toolchain recém-criado:

<pre>
cd ex02
arm-linux-gcc helloworld.c -o helloARMctng
</pre>

Novamente, verifique o programa gerado através do comando `file` e veja que, as informações exibidas como arquitetura e versão do kernel, estarão de acordo com as opções selecionadas no *crosstool-ng*:

<pre>
file helloARMctng
</pre>

<pre>
helloARMctng: ELF 32-bit LSB executable, ARM, EABI5 version 1 (SYSV), dynamically linked, interpreter /lib/ld-
linux -armhf.so.3, for GNU/Linux 4.10.8, not stripped
</pre>

Se desejar, repita o teste de rodar o executável na RPi 3. Primeiramente copie através do `scp` para a plataforma embarcada.
<pre>
scp helloARMctng pi@10.1.1.100:/home/pi/helloARMctng
</pre>

Então, acesse-a e execute o código recém enviado:

<pre>
ssh pi@10.1.1.100
cd
./helloARMctng
</pre>


---
# Navegação

* [Introdução](/linux/intro)
* [**Parte 1**](/linux/01)
    * [**Toolchain**](/linux/toolchain)
    * [Bootloader](/linux/bootloader)
    * [Config. Conexão de Rede](/linux/rede)
    * [Config. Comunicação Serial](/linux/serial)
* [Parte 2](/linux/02)
* [Parte 3](/linux/03)