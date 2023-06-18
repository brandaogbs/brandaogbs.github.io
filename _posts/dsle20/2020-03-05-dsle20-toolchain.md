---
layout: post
title:  Embedded Linux Development Course - Toolchain (pt. 5) 
date:   2020-03-06 22:57:49 +0000
categories: jekyll update
tags: [course, linux, embedded, toolchain]
usemathjax: true
description: >-
    
---
# Toolchain

O toolchain nada mais é que uma cadeia de ferramentas, ou seja, é o conjunto de ferramentas que utilizamos para a compilação.

Esse processo de compilação, tomando como base a linguagem C, segue o seguinte protocolo:

* Pré-processamento;
* Compilação;
* _Assembly;_
* _Linking._

Em um primeiro momento são realizadas as atividades de pré-processamento, ou seja,  o pré-processador analisa todas as macros e definições criadas por um usuário e codifica elas, em código de linguagem C, técnicamente falando não precisamos de um pré-processador, no entanto ele promove uma certa facilidade pro programador. Por exemplo, seu uso mais comum é a diretiva inclusão de cabeçalhos:

```c
#include <stdio.h>
```

Em C/C++ todos os símbolos, isto é, funções, variáveis e etc, devem ser declarados antes de serem definitivamente utilizados pelo programa.  Eles não precisam necessariamente serem definidos, mas a declaração deve ocorrer antes, pois o compilador precisa saber que eles existem em algum lugar, separar as declarações das definições, além de boa práticas é um uso clássico de cabeçalhos.

Nesse processo, o pré-porcessador então copia todas essas definições para o local onde vc deseja utilizá-las, além disso o pré-processador inclui algumas facilidades de compilação condicional. Um uso bem comum que encontramos em diversos headers, são os header guards, que previnem múltiplas definições quando um arquivo é incluso varias vezes. Outra função, é a possibilidade de inserir arquivos de acordo com o sistema operacional ou arquitetura de hardware por exemplo.

```c

#ifndef LIB_H
#define LIB_H

[...]

#endif //LIB_H
```

O compilador por sua vez, literalmente traduz o código de linguagem C para o Assembly de uma determinada arquitetura, realizando várias otimizações, algumas por são definidas por padrão e outras de acordo com as flags utilizadas que podem ser estabelecidas. 

O código Assembly gerado pelo compilador é então passado ao assembler, que traduz de de lingaugem Assembly para código de máquina, isto é, código binário. O arquivo resultante deste processo é  comumente chamado arquivo objeto. O assembler é quem dá um endereço de memória por exemplo para cada variável e instrução. Por fim, os arquivos objetos tanto do seu código quanto aqueles de bibliotecas, são linkados ou agregados pelo linker que finalmente produz seu código executável com tudo que ele precisa para rodar.

Quando utilizamos uma IDE, ou mesmo chamamos o `GCC` diretamente via _shell,_ não notamos que esses processos são realizados por ferramentas distintas. Isto, pois utilizamos uma toolchain que abstrai essa chamada para nós. Mas na realidade, cada um desses processos é executado de forma separada por uma ferramenta específica.

Assim, uma toolchain é composta por:

* Pré-processador;
* Compilador;
* _Assembler_;
* _Linker_.

<figure>
<img src="/assets/posts/dsle20/tool-1.png" alt="">
</figure>

# Nativo vs. Cross-Compiling

As ferramentas de desenvolvimento que normalmente acompanham um desktop GNU/Linux são chamadas de toolchain nativo. Ou seja, são aquelas que fazem a compilação para a arquitetura da máquina _host_.

Este toolchain roda na sua máquina e compila um código para ser executado em sua máquina ou em uma máquina que possua a mesma arquitetura que a sua, normalmente uma arquitetura _x86_ nos desktops convencionais.

De forma semelhante, os processadores embarcados como ARM, MIPS, SuperH, Blackfin, Coldfire, PowerPC, SPARC e etc. Possuem também seu compilador nativo. Desta forma, é possível realizar a codificação diretamente no processador e então compilar utilizando a toolchain nativa deste processador.

Nota-se que este processo é feito internamente na plataforma _target,_ ou seja, esse processo é executado dentro da placa de desenvolvimento. Assim, é fácil perceber os problemas deste tipo de abordagem, uma vez que o _hardware_ que utilizamos em sistemas embarcados possuem recursos limitados do ponto de vista de execução. De forma geral, possuem baixa memória, baixo armazenamento, baixo processamento e etc.

Desta forma, encontramos alguns problemas ao executar a compilação nativa dentro da plataforma embarcada, tanto do ponto de vista do tempo de execução desta compilação, que pode ser um gargalo da operação, tornando-a demorada e gerando tempo ocioso para o desenvolvedor. Além disso, é normal que os sistemas embarcados apresentem um armazenamento restritivo, tornando inviável o armazenamento da toolchain, ferramentas de desenvolvimento, código fonte, arquivos de compilação, auxiliares e etc, dentro da plataforma embarcada. 

<figure>
<img src="/assets/posts/dsle20/tool-2.png" alt="">
</figure>


Não obstante, há um problema de logística que envolve o desenvolvimento nativo em sistemas embarcados, e este tem relação com as ferramentas de desenvolvimento. Normalmente quando realizamos o desenvolvimento de _software_ estamos utilizando programas que auxiliem na codificação, como IDEs, editores de texto, ferramentas de linkagem e indexação e até mesmo interfaces gráficas para a criação dos sistemas. Todo esse suporte esta disponível nos desktops, e a passagem de todos esses arquivos para o sistema embarcado é muitas vezes indesejável ou mesmo inviável.

Desta forma, normalmente é utilizado - e recomendado - o desenvolvimento do sistema nos desktops normais e a passagem do programa já compilado para a plataforma embarcada. Evitando assim, os problemas relacionados ao tempo de compilação, espaço de armazenamento, ferramentas de desenvolvimento e facilitando também a programação, já que é comum realizarmos diversos testes durante a codificação.

Para tal, é necessário uma toolchain que realize a compilação de um código desenvolvido na arquitetura da plataforma _host_ \(desktop\) para a arquitetura da plataforma _target_ \(sistema embarcado\). Este toolchain é chamado de _cross-compiling toolchain._ 

# Componentes Básicos

Os processos envolvidos em uma toolchain já foram discutidos, contudo, nesta etapa será apresentado os principais componentes presentes em uma toolchain.

Os componentes básicos de um toolchain, portanto, são: 

* Binutils; 
* Headers do kernel; 
* Biblioteca padrão C; 
* O compilador _gcc;_
* e opcionalmente um debugger como o _gdb._

A seguir, será explicado de forma mais completa o papel de cada um desses componentes.

<figure>
<img src="/assets/posts/dsle20/tool-3.png" alt="">
</figure>

## Binutils

O [Binutils \(_GNU Binary Utilities\)_](https://www.gnu.org/software/binutils/) é um conjunto de ferramentas da GNU para operações de arquivos binários. Este foi projetado para realizar a manipulação de arquivos binários em geral para uma dada arquitetura de processador.

O Binutils possui um conjunto de ferramentas internas que desempenham papeis específicos no processo de manipulação de binários. Dentre as ferramentas disponibilizadas pelo Binutils, temos:

* **`as`**: este é o _assembler_ do Binutils, ele realiza literalmente a tradução do código binários \(aquele gerado pelo processo de compilação\) para um arquivo em linguagem de máquina. Ou seja, converte _assembly_ para binário. Os arquivos gerados nesta etapa de montagem, são os arquivos com extensão _\*.o_ , também chamados de arquivos objetos.
* **`ld`**: este é o _linker_ do Binutils, ele realiza a combinação de diversos arquivos objetos ou arquivos de bibliotecas, gerados durante o processo de compilação e montagem, em um único arquivo executável \(ou em outro arquivo de biblioteca ou mesmo em outro arquivo de objetos\).  De forma resumida, ele relaciona os objetos e bibliotecas à um único arquivo.
* **`ar`, `randlib`**: este é o _archiver_ do Binutils, mas assim como outros também é um utilitário padrão do Unix. Ele é utilizado em geral para juntar grupos de arquivos em um único. Contudo, seu principal uso é na criação de bibliotecas estáticas \(_\*.a_\).
* **`objdump`**, **`readelf`**, **`size`**, **`nm`**, **`strings`**: estas são os principais utilitários do Binutils para a realização do processo de inspeção de binários. Por exemplo, o `objdump` é utilizado para realizar o dissasemble dos executáveis. Enquanto o `readelf` é utilizado para extrair as informações de um executável e comando `size` apresenta o tamanho do executável, separado por seções. O comando `nm` mostra informações dos símbolos sendo utilizados no executável, ao passo que o `strings` aparesenta todos os caracteres imprimíveis do programa.
* **`strip`**: este é o utilitário do Binutils responsável por separar as partes do não utilizadas de um binário. Por exemplo, remove as partes relacionadas e utilizados no processo de debugging.

Além desses utilitários, diversos outros são disponibilizados pelo Binutils, a lista completa pode ser acessada através do [site oficial do binutils](https://www.gnu.org/software/binutils/).

Para realizar o download do Binutils, basta realizar o clone do repositório oficial:

```text
git clone git://sourceware.org/git/binutils-gdb.git
```

## GCC

Além da Binutils, outra ferramenta presenta no toolchain é o compilador GCC \([GNU Compiler Collection](https://gcc.gnu.org/)\). Este é sem dúvidas um dos compiladores mais famosos do mundo, sendo vastamente utilizado. Em geral, estamos acostumados a fazer a compilação de códigos em Linguagem C com ele, contudo, este compilador apresentar solução para diversas outras linguagens, tais como: C, C++, JAVA, ADA, Fortran e  etc.

Não obstante, o GCC apresenta além do suporte à compilação de diversas linguagens de programação, apresenta também o suporte a diversas arquiteturas de processadores, desde processador embarcados como ARM e afins até PowerPC e x86.

É distribuído pela [Free Software Foundation](https://pt.wikipedia.org/wiki/Free_Software_Foundation) \(FSF\) sob os termos da [GNU GPL](https://pt.wikipedia.org/wiki/GNU_GPL), disponível para sistemas operacionais Unix e Linux e certos sistemas derivados como o macOS. 

Ele é software extremamente acessível em relação a usuabilidade, por exemplo: para gerar os binários de um código simple em linguagem C. Isto é, fazer o processo de compilação do _\*.c_, simplemeste chamamos o GCC e passamos as informações de operação, como o arquivo que queremos compilar e o nome do arquivo de saída.

```text
gcc arquivo.c -o saida
```

Através da simple evocação deste comando, o GCC executa todos os processos da compilação, já listados anteriormente, como pré-processamento, compilação, montagem e linkagem.

## Biblioteca Padrão C

Conforme comentado anteriormente, o kernel possui o conceito de espaço de usuário e espaço do kernel \(US e KS\) e, portanto suas aplicações não tem acesso direto à hardware. Isto significa, por exemplo, que é preciso passar pelo kernel para realizar a comunicação com algum dispositivo ou driver.

Desta forma, é faz-se necessário uma interface que possibilite a interação entre essas duas camadas, apliação e hardware. Quem fornece essa interface, é a biblioteca C, possibilitando a comunicação entre aplicações no US e o kernel.

Essa interface é na realidade uma API \(_Application Programming Interface_\) de desenvolvimento de aplicações. Em linhas gerais, cada função utilizada, quando estamos programando em C por exemplo, engatilha uma chamada de sistema que em geral cria uma thread para essa função, esta thread por sua vez, realiza a comunicação com o kernel e executa a função comandada.

Por exemplo, quando utilizamos funções comuns em C, como funções de `read`, `write` ou mesmo o `printf`, é disparada uma thread no sistema que realiza uma systemcall para o kernel Linux que em um determinado momento irá executar a função determinada. 

Estas características da API tornam o desenvolvimento de software totalmente modular e desacoplado. Uma vez que esta fornece uma abstração suficiente para que não seja necessário o desenvolvedor se preocupe com qual tarefa esta sendo escalonada no pelo kernel, ou mesmo quais são os endereços dos registradores ou a tabela de ender a serem utilizados e etc. Basta apenas evocar as funções da biblioteca padrão C, que ela realiza o trabalho 'sujo', se comunicando com o kernel de forma abstrata para o programador.

Assim, quando se deseja executar alguma função, basta chamar a função, indicando o que se deseja fazer e esta se comunica com o kernel, automaticamente, e retorna os valores para a _libc_ e então a _libc_ retorna ao usuário. 

Esse processo pode ser visualizado na figura no topo da página, onde é ilustrado a realização da leitura de um dado do disco rígido através da _libc._ Primeiramente é chamada a função, esta faz a requisição de leitura ao kernel que se comunica através de um driver com o periféricos desejado e então retorna a resposta para a _libc_ que apresenta o resultado para a aplicação. 

Como pretende-se desenvolver em um ambiente Linux embarcado, e o próprio Linux é dependente da biblioteca C, pois ela eh a API para o programador interfacear com o kernel, é natural que o toolchain também dependa de uma biblioteca C, uma vez vai gerar os executáveis para um determinador target rodando Linux.

Em suma, o mais interessante deste processo inteiro é o fato do desenvolvimento se tornar totalmente modular, seguindo o pipeline Desenvolvimento -&gt; Cross-compiling -&gt; Test no host e target.

Existem diversas bibliotecas C para uso, tanto em sistemas desktop como em sistemas embarcados, cada uma com suas próprias características e especificidades, por exemplo:c

A [_**glibc**_](https://www.gnu.org/software/libc/) **** __que é a bilbioteca C padrão do projeto GNU, ela está disponível em todas as distribuições GNU/Linux, só não está naquelas em que foi considerada grande ou com desempenho não satisfatorio, mas muito provalvemente a biblioteca que roda nesse sistema é derivada dela. Ela foi projetada para ter alta performance e alta portabilidade, sendo também extremamente eficiente em termos de manutenção e suporte, sendo atualizada sempre que uma nova versão do kernel é lançada. No entanto, por se tratar de uma biblioteca completa, pode ser restritiva para hardwares muito limitados, principalemente em relação a RAM e armazenamento em disco, o que pode ser contornado através de remoção de partes não utilizadas e edições.

* Projetada com foco em performance e portabilidade;
* Presente em todas as distribuições GNU/Linux;
* Suporte ativo da comunidade;
* Dependendo do hardware utilizado, ela pode não ser uma boa escolha devido ao consumo de RAM e espaço de disco. _****_

Ao passo que a [_**uClibc**_](https://uclibc-ng.org/), que é a uma biblioteca C projetada para sistemas embarcados pequenos. Foi desenvolvida para alta portabilidade, sendo altamente configurável e tendo seu principal foco na economia de recursos e não em performance. Por ter alta configurábilidade, diversos recursos podem ser ativados ou desativados, através de uma interface do tipo _menuconfig_ \(este tipo de configuração será abordado em outro momento do treinamento\). E tem seu principal emprego em dispositivos que visam baixo consumo, em uma arquitetura ARM pode ter até 600K, e várias funcionalidades da _glibc._

* Continuação do antigo projeto uClibc;
* Biblioteca C leve e projetada para sistemas embarcados;
* Altamente configurável;
* Comunidade de suporte ativa;
* É mais focada em economia de recursos do que performance;
* Em um arquitetura ARM pode ter 600K, e várias funcionalidades da _glibc_;

Outros exemplos de bibliotecas C para sistemas são:

* _**musl**;_
* _**eglibc**_; 
* _**dietlibc**_.

## Headers do Kernel Linux

Conforme mencionado na seção anterior, a biblioteca C fornece uma camada de abstração que serve de interface para o programador utilizar os recursos do KS através da sua aplicação US. Seja essa interação uma chamada de sistema, uma definição de constantes \(que nada mais são que flags\) ou mesmo estruturas de dados propriamente ditas. E esta interface é feita através de _wrappers_ de systems calls, de tal forma que o programador não precise "escovar bits" e tenha certa abstração ao interagir com o kernel. E portanto, a biblioteca C precisa dos headers do kernel para ser compilada.

Seus headers estão localizados principalmente nos diretórios `linux` e `asm`, mas existem outros no diretório`include` dos arquivos fontes do kernel, durante o treinamento, deveremos realizar a adição de alguns headers desses diretórios.

Para exemplificar melhor a utilização desses headers, vamos visualizar algumas estruturas fornecidas por eles e também sua localização e afins. Por exemplo, dentro desses headers é possível se obter algumas definições de system calls. Estas definições, nada mais são que os números das chamadas de sistema, um exemplo é os header `<asm/unistd.h>`.

```c
# define __NR_exit 1
# define __NR_fork 2
# define __NR_read 3
[...]
```

No Linux cada system call é representada por um número inteiro de oito bits \(0~255\). Além disso, muitas vezes são chamadas de kernel calls, pois é exatamente o que acontece na prática, isto é, são chamadas ao kernel.

Um outro exemplo de headers do kernel são as definições de constantes, que nada mais são do que flags que abstraem conceitos para facilitar a programação. Normalmente ao solicitar acesso para qualquer dispositivo, arquivo, periférico e etc.  É preciso especificar o modo que vc deseja operar tal arquivo, por exemplo, abrir em modo de leitura, modo de edição e etc. Essas definições de constantes \(flags\) podem ser observadas no header `<asm-generic/fcntl.h>`, por exemplo:

```c
# define O_RDONLY 00000000  // Permiss. para leitura.
# define O_WRONLY 00000001  // Permiss. para escrita.
# define O_RDWR   00000002  // Permiss. para leitura e escrita.
[...]
```

Existem também tipos de estruturas de dados definidas nos headers, muitas vezes essas estruturas são passadas como parâmetros em uma system call ou mesmo retornadas de uma syscall. A estrutura `stat` por exemplo, que compreende muito mais do que as duas variáveis que a compõe, contém o dado `st_mode`, que é o serial onde você armazena uma daquelas flags anteriores, ou seja, como o arquivo ou dispositivo foi aberto, além da `st_dev` que representa um identficador único do dispositivo onde o arquivo reside, ou que o arquivo representa, vide o header `<asm/stat.h>`.

```c
struct stat{
    unsigned long st_dev;  // ID do dispositivo que mantém o arquivo.
    unsigned long st_mode; // Modo de abertura do arquivo (flag).
}
[...]
```

# Utilizando Toolchains Pré-compilados

Em relação a utilização de um toolchain, existem basicamente duas formas: ou a utilização de uma toolchain já pré-compilada ou a criação de uma toolchain específica para a sua aplicação.

Na primeira opção, o uso de uma toolchain pronta, consiste no uso de uma toolchain pré-compilada normalmente fornecida pelo proprio fabricante do chip, ou empresas especializadas em toolchains para determinadas arquiteturas ou ainda algum fornecido por algum grupo de desenvolvimento da comunidade. 

Ao passo que a criação de uma toolchain de acordo com suas necessidades, é com certeza algo mais simples e específico. Para tal, existem diversas ferramentas que auxiliam no processo de montagem da toolchain e normalmente elas são usadas para o desenvolvimento de sistemas Linux embarcado.

### Toolchain pré-compilado

O uso de toolchains prontos é bem comum, desde que haja um fornecedor, e é uma das metodologias mais adotadas. Pois utilizar um toolchain pronto é fácil e rápido de configurar, e não é necessário muito conhecimento sobre o sistemas e etc. 

No entanto, este tipo de toolchain limita seu sistema, uma vez que sua aplicação fica amarrada com o as ferramentas fornecidas pelo toolchain, tirando o seu direito de escolha e restringindo suas escolhas de ferramentas. 

Por exemplo, se o fabricante fornece ferramentas como, o compilador e biblioteca C, você não tem muita opção a não ser utilizar o que ele te fornece, é até possível realizar algumas alterações, mas não há muito o que fazer. Ao invés da ferramente se adaptar as suas necessidades, sua aplicação que se adapta à ferramenta. 

Em muitos casos,  não há problema nenhum esse acoplamento, mas é sempre necessário certificar-se de que a toolchain pré-compilada atende seus requisitos, principalmente em termos de arquitetura do processador, endianness e etc.

Dentre as opções disponíveis, é possível usar algum toolchain fornecido pela propria fabricante, como a Freescale que costumam fornecer para as placas deles.

Ou ainda, é possível usar a toolchain de alguma empresa especializada como a Mentor Graphics, eles fornecem alguns toolchains para arquiteturas especificas, contudo boa parte é sobre licensa paga. 

Por fim, você pode utilizar um toolchain fornecido por comunidades de desenvolvedores, como [Linaro](https://www.linaro.org/), [Yocto](https://www.yoctoproject.org/). Outras referências podem ser encontradas em: [https://elinux.org/Toolchains](https://elinux.org/Toolchains).

### Instalando um Toolchain Pré-compilado

O processo de instalação de um toolchain pré-compilado é muito simples. Lembrando que a primeira tarefa é encontrar o toolchain para a sua plataforma de desenvolvimento, seja esse toolchain fornecido pelo fabricante, por uma comunidade ou empresa de terceiros.

Assim, a primeira etapa será a aquisição do toolchain, em geral, este tipo de código é baixado de um repositório `git` ou algo similar. Você deve realizar o download do diretório completo do toolchain em sua máquina _host_.

Após realizar o download do toolchain, é necessário incluir os executáveis no PATH da sua máquina. Para tal, utilizamos o comando `export`  no terminal. Este adiciona o diretório/local passado por parâmetro ao PATH. Assim, basta invocar o comando passando o diretório dos arquivos binários \(_\*.bin_\) como parâmetro, executando assim um _insert_ no arquivo PATH.

```bash
export PATH=/caminho/toolchain/bin:$PATH
```

Fazendo isso, o arquivo binário \(executável\) pode ser invocado diretamente no terminal, sem a necessidade de digitar o caminho inteiro até o mesmo.

Uma vez atualizada a variável de ambiente, você tem acesso direto a todas as ferramentas da toolchain que escolheu. Portanto, basta  apenas compilar seu programa C para a arquitetura desejada através de seu toolchain, e pronto. 

Por exemplo, com o seguinte comando `PREFIX-gcc`, onde o _PREFIX_  é substituido por sua arquitetura target. Normalmente este, está relacionado com a arquitetura que você deseja compilar o programa com o target, é basicamente isso que difere você compilar nativamente e cross-compilar o código.

```bash
PREFIX−gcc hellow.c −o hellow
```

# \[LAB\] Toolchain Pré-compilados

## Cross-Compiling Toolchain

Os objetivos desta atividade são:

* Aprender a utilizar um toolchain pronto, isto é, fornecido pelo fabricante do SoC ou repositório padrão por exemplo;
* Compilar seu próprio toolchain utilizando a ferramenta `crosstool-ng.`

### Utilizando um toolchain pré-compilado

A Raspberry Pi Foundation fornece gratuitamente em seu [repositório oficial](https://github.com/raspberrypi), diversos componentes open-source para a Raspberry Pi. Dentre eles, estão inclusos os fontes do kernel Linux, drivers, bibliotecas e firmwares específicos, além de seu próprio toolchain, o qual será utilizadonesta atividade.

#### Instalação e Configuração

Inicialmente, abra um novo shell e crie a seguinte estrutura de diretórios dentro do diretório `dsle19`:

```bash
cd ~/dsle20
mkdir toolchains
cd toolchains
```

Em seguida, o correto seria clonar a pasta `tools` do repositório oficial da Raspberry Pi, no intuíto de obter a última versão disponível do toolchain:

```bash
git clone https://github.com/raspberrypi/tools.git
```

No entanto, a fim de garantir uma maior eficiência na execução das atividades deste treinamento, todos os arquivos necessários foram previamente baixados e encontram-se no diretório `dsle19/dl`. Portanto, substituiremos o processo de clonar o repositório `tools` pela extração do seguinte arquivo:

```bash
unzip ~/dsle20/dl/toolchains/tool.zip
```

O comando acima extrai o arquivo _tools.zip_ no diretório atual \(`dsle19/toolchains`\). Ao final do processo, verifique se o diretório `tools` foi criado, por meio do comando `ls`.

Como o toolchain fornecida pela RPi Foundation é pré-compilado, para instalá-lo basta adicionar o caminho das ferramentas \(binários\) do toolchain à variável de ambiente `$PATH`:

```bash
export PATH=$PATH:~/dsle20/toolchains/tools/arm-bcm2708/gcc-linaro-arm-linux-gnueabihf-raspbian/bin
```

Note que tal alteração é momentânea, isto é, ao fechar o shell atual ela será perdida. Um dos meios defazer essa alteração permanente \(opcional\) é por meio da inserção do mesmo comando no final do arquivo `∼.bashrc`, que é um script shell que é executado sempre que um novo shell é iniciado.

Simples assim, toolchain instalado! Uma maneira de verificar se o _export_ do PATH funcionou é digitar `arm` no shell e pressionar a tecla TAB duas vezes. Ao fazer isso, o shell tentará auto-completar o comando `arm` de acordo com as opções de executáveis disponíveis na variável PATH. O resultado deverá ser uma lista semelhante à:

```bash
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
[...]
```

#### Testando o toolchain

É possível testar o toolchain através da compilação de um programa bem simples, como o `helloworld.c`, em C. Inicialmente, crie a pasta `ex01` dentro do diretório de exercícios `exs` e, em seguida, crie/edite o arquivo `helloworld.c` com seu editor favorito:

```bash
cd ~/dsle2020/exs
mkdir ex01 && cd ex01
gedit helloworld.c
```

E então,

```c
#include <stdio.h>

int main()
{
    printf("Hello cross-compiled world!\n");
    return 0;
}
```

Em seguida, compile o arquivo `helloworld.c` nativamente, isto é, utilizando o _gcc_:

```bash
gcc helloworld.c -o hellox86
```

Utilizando o comando `file`, verifique as informações do binário gerado:

```bash
file hellox86
```

A saída do comando deve ser algo similar à:

```bash
hellox86: ELF 32-bit LSB executable, Intel 80386, version 1 (SYSV), dynamically linked, interpreter /lib, for GNU/Linux 2.6.32, BuildID[sha1]=ae1b783e3b504073e808de7dc21fc4e3f2c0f2cf, not stripped
```

Note que a segunda informação, _Intel 80386_ indica que o programa foi compilado para a mesma arquitetura de sua máquina, x86. Em seguida, execute-o:

```bash
chmod +x hellox86
./hellox86
Hello cross-compiled world!
```

Agora repita o processo e utilize o recém-instalado toolchain para cross-compilar o mesmo programa para a RPi. Para isso, trocamos o compilador antivo _gcc_ por _arm-linux-gnueabihf-gcc_:

```bash
arm-linux-gnueabihf-gcc helloworld.c -o helloARM
```

Novamente, verifique o programa gerado através do comando `file` e veja que desta vez a arquitetura indicada será _ARM_:

```bash
helloARM: ELF 32-bit LSB executable, ARM, EABI5 version 1 (SYSV), dynamically linked, interpreter /lib/ld- linux -armhf.so.3, for GNU/Linux 2.6.26, BuildID[sha1]=68bc6061bdbb1b80e5190760e91b687a1caebf97, not stripped
```

Não será possível executar este segundo programa na sua máquina pois o programa e a máquina possuem arquiteturas diferentes. Faça o teste. No entanto, é possível copiá-lo para a RPi e executá-lo nela.

Para tal, utilizaremos o protocolo _SSH_ para a comunicação entre a nossa plataforma _host_ \(PC\) e a nossa placa \(_target_\).

> Primeiramente, devemos estabelecer uma conexão de rede entre a RPi e nosso computador. O capítulo [Configurando a Rede da RPi](/linux/rede), apresenta algumas formas de se estabelecer esta comunicação.

Copie-o para a RPi através do comando `scp` \(secure copy\). Primeiramente, confira a funcionamento do comando através de seu manual `man scp` e então:

```bash
scp helloARM pi@10.1.1.100:/home/pi/helloARM
```

Acesse-a via _SSH_ e tente executar o programa, lembre-se a senha padrão do usuário `pi` da RPi é **raspberry**.

```bash
ssh pi@10.1.1.100
cd
./helloARM
```

Neste ponto, conseguimos realizar a nossa primeira compilação \(cross-compile\) e também a nossa primeira execução na plataforma embarcada \(RPi\).

Este procedimento foi realizado com base em uma toolchain pronta, fornecida por terceiros. Contudo, em um contexto profissional e em aplicações reais, faz-se necessário a utilização de toolchains próprias e criadas e adequadas ao nosso sistema. Desta forma, no próximo capítulo será discutido o procedimento de criação de toolchains suas principais ferramenteas e componentes.

# Compilando seu próprio Toolchains

Sem dúvidas dentre as soluções esta é a mais flexível e adaptável para o desenvolvimento embarcado. Você tem a possibilidade de adaptar as ferramentas de acordo com suas necessidades, fazendo combinação de diversas ferramentas, adicionar tudo que precisa para o desenvolvimento e compilar sua própria toolchain.

Gerar uma toolchain do zero é uma tarefas extremamente árdua e dolorosa, pode demorar dias ou mesmo semanas para a construção de uma toolchain do zero, principalmente pela demanda de conhecimentos específicos e pesquisa.

São muitos detalhes, componentes para compilar de forma manual, configurar de maneira ideal e principalmente entender como cada uma dessas partes funcional e como se conectam.

O processo de criação de uma toolchain manualmente é extremamente delicado e demorado, exigindo muito conhecimento sobre os compiladores e ferramentas que serão adotados. Estudos profundos sobre as configurações de cada uma das ferramentas, documentações extensas e densas, mecânimos como de ponto flutuante e etc. De fato, é uma tarefa para uma classe específica de desenvolvedores.

Contudo, há uma abordagem menos abrupta para a criação do próprio toolchain, as **ferramentas de automatização para criação de toolchain.**

### **Ferramentas de automatização**

Estas são ferramentas que auxiliam na criação das nossas toolchains sem a necessidade de pesquisar, configurar, compilar e linkar manualmente cada ferramenta. Esse processo é encapsulado através de uma abstração automatizada que cria, através de menuconfigs, makefiles e outros arquivos de configuração, uma toolchain com as nossas configurações para uso específico da nossa demanda.

Assim, não há a necessidade de se preocupar com cada um dos detalhes de compatibilidade, versão de ferramenta e etc. As automatizações, fornecem a verificação de dependência dos componentes, caso seja necessário a aplicação de algum patch específico em determinada versão esse processo é feito automaticamente pela ferramenta, bastando apenas selecionar qual a versão desejada.

Essas ferramentas automatizadas permitem a criação de toolchain totalmente flexíveis, ao contrário das pré-compiladas. Em geral, é fornecida uma interface que possibilita a seleção de componentes e ferramentas em diversas versões, permitindo que você monte a toolchain da forma mais otimizada para a sua demanda. Então, você monta a toolchain do seu jeito e no final a ferramenta se encarrega do processo de configuração \(de acordo com suas escolhas\), compilação, linkagem, compatibilidade e dependências.

Outro ponto positivo deste tipo de ferramenta, é que elas oferecem correções para bugs conhecidos de incompatibilidade. Por exemplo, um problemas específico do componente X  na arquitetura Y. Isto, pois elas geralmente possuem comunidades bem ativa, então sempre que algum bug é reportado, os desenvolvedores já se encarregam de resolve-lo.

Basicamente, essas ferramentas são baseadas em shell scripts ou makefiles, elas fazem a busca automática do componentes que foram selecionados, algumas vezes até realizam o download, extraem e configuram o makefile daquele determinado componente e os compila.

### Ferramentas populares

Como de costume, existem várias ferramentas disponíveis parar geração de toolchains e essas são umas das mais populares, todas elas possuem uma comunidade bem ativa de desenvolvedores e suporte constante.

A principal diferença entre elas, esta nos pacotes e arquiteturas suportadas para a criação da toolchain.

* [Crosstool-ng](https://crosstool-ng.github.io/): Suporta diversas bibliotecas, como: `glicb`, `uClib` e `musl`. E diversas arquiteturas de processador ecomponentes, e tem uma interface no estilo menuconfig.
* [PTXdist](https://www.ptxdist.org/): É uma ferramenta nova, que tem ganhado muito espaço, mas ainda não esta totalmente completa, por exemplo não tem suporte a bibliotecas `musl`.
* [Yocto](https://www.yoctoproject.org/) \(_system build_\): o Yocto na verdade adotou a [Open Embedded](http://www.openembedded.org/) que tinha uma ferramenta exclusiva de geração de toolchain, e então acobou progredindo e virou um _system build_ completo.
* [Buildroot](https://buildroot.org) \(_system build_\): É uma das ferramentas mais utilizadas e tem uma comunidade muito ativa, devido a popularização do uso, o projeto foi incrementado e passou a ser um _system build_ completo.

> _System build_ é uma outra classe ferramentas que possibilitam gerar não somente o toolchain, mas também o RootFS, kernel, bootloader e etc.

Neste treinamento daremos uma atenção maior a duas ferramentas, a _Crosstool-ng_ e ao _Buildroot._

# Crosstool-ng

Neste treinamento, iremos utilizar a [Crosstool-ng](https://crosstool-ng.github.io/) para montar a nossa própria toolchain em um primeiro momento.

Ela é provavelmente a principal ferramenta open-source para geração de toolchains, foi projetada exclusivamente para geração de toolchains, diferente da [Buildroot](https://www.buildroot.org/) e [Yocto](https://www.yoctoproject.org/), por exemplo, que geram tudo desde toolchain, imagem do kernel, RootFS e etc. 

Além disso, como esperado o Crosstool-ng suporta diversas plataformas como ARM, PowerPC, x86 e outros bem como, tem a capacidade de gerar ferramentas para plataformas _bare-metal._ Por fim, o Crosstool-ng possue a interface de configuração similar a interface utilizada para configurar o kernel Linux.

### Instalando o Crosstool-ng

Como esperado a primeira etapa de instalação da ferramenta, constitui-se em baixar-la de algum repositório. Em seguida, devemos instalar a ferramenta localmente para utiliza-la. Então, depois de baixar e extrair a ferramenta realizamos sua instalação:

```bash
./configure --enable-local
make
make install
```

A instalação em um diretório local é sempre recomendada, pois é normal utilizar mais de uma arquitetura no mesmo desktop. Ou seja, você pode programar diversas arquiteturas sem que uma ferramenta interfira na outra. Para tal, basta utilizar a flag `--enable-local`, indicando que deseja instalar somente neste diretório.

Então, basta fazer a compilação automatizada através do comando `make` e então utilizar o `make install` para ajustar os binários nos diretórios correto e organizar tudo para que a ferramenta funcione.

A partir deste momento, a ferramenta já pode ser utilizada, por exemplo, é possível listar os _samples_ que ele fornece pelo comando `./ct-ng list-samples`. Estes _samples_ podem, ser uma espécie de esqueleto com as configurações básicas para uma determinada plataforma ou arquitetura.

Escolhido um exemplo da lista, basta carrega-lo através do comando `./ct-ng <sample-name>`. Depois de carregado, você vai lança a aplicação propriamente dita e personalizar.

```bash
./ct-ng list-samples
./ct-ng <sample-name>
./ct-ng menuconfig
./ct-ng build
```

### Detalhamento de alguma opções de configuração

Ao passo que estamos realizando a configuração do Crosstool-ng, podemos realizar-la de diversas formas, porém algumas opções podem ser uteis e não necessáriamente alto explicativas. Desta forma, vamos avaliar algumas opções do _menuconfig._ Algumas destas opções serão explicadas de forma mais profunda na seção seguinte durante o experimento.

Alguns comentários a respeito do Crosstool-ng: 

* Na opção **Target options**:
  * _Suffix to the architecture_: literalmente um sufixo a para indicar uma variante da arquitetura. Por exemplo: ARM -&gt; conjuntos de instruções, v7, v6 e v8. No caso do treinamento estamos interessados na RPi3, onde o sufixo é v8. É possível criar toolchains para mais de uma arquitetura, ou variação.
  * _Attemp to combine:_ É uma feature do Crosstool-ng para combinar as bibliotecas em um único diretório, é interessante por exemplo utilizando arch64. Uma vez que os toolchains usam lib, lib64 e quando se tem mais de uma arquitetura começa a ficar bagunçado o diretorio.
  * Nossa arquitetura possui MMU então vamos utiliza-la.
  * _Endianess_: _Little endian,_ isto é, bytes menos significativos primeiro.
  * Todo o sistema, toolchain, kernel e bootloader serão 32 bits. Apesar da RPi 3 suportar instruções 64 bits, pois o processador é 64 bits. Ela ainda é instável, tendo diversas ferramentas incompatíveis.
  * _Target Optimisations_: são configurações relacionadas ao GCC, é basicamente um wrapper do crosstool

  # \[LAB\] Compilando seu próprio Toolchain

## Compilando seu próprio toolchain

A [_Crosstool-ng_](https://crosstool-ng.github.io/) é provavelmente a principal ferramenta open-source para customização de toolchains. Suporta diversas arquiteturas diferentes, é capaz de gerar código bare-metal e possui uma interface baseada no _menuconfig_.

Nesta atividade, a ferramenta _Crosstool-ng_ será utilizada para criar um toolchain customizado para a RPi. Este toolchain será utilizado para todas as atividades posteriores como compilação do bootloader, kernel, bibliotecas e aplicações.

#### Instalação e Configuração

Abra um novo shell e navegue até a pasta `∼/dsle20/toolchains`. Em seguida, descompacte o arquivo `∼/dsle20/dl/toolchains/crosstool-ng-1.23.0.tar.xz` no diretório atual e navegue até o novo diretório:

```bash
cd ~/dsle20/toolchains/
tar xvf ~/dsle20/dl/toolchains/crosstool-ng-1.23.0.tar.xz
cd crosstool-ng-1.23.0/
```

Após a descompactação, configure o _crosstool-ng_ para ser instalado localmente, isto é, no mesmo diretório em que se encontra o script de configuração. Então, execute os comandos `make` e `make install` para realizar a instalação:

```bash

./configure --enable-local
make
make install
```

Se tudo correu bem e nenhuma mensagem de erro foi exibida, o _crosstool-ng_ pode ser executado a partir do diretório atual. O seguinte comando exibe as informações de ajuda da ferramenta:

```bash
./ct-ng help
```

O _Crosstool-ng_ permite criar um ou mais toolchains para arquiteturas diferentes e, por isso, fornece um conjunto de configurações pré-definidas para arquiteturas mais comuns. É possível listá-las por meio do seguinte comando:

```bash
./ct-ng list-samples
```

Note que, dentre as configurações, existe uma pré-definida para a RPi 3: `armv8-rpi3-linux-gnueabihf`. Neste treinamento, essa configuração será usada como base para a criação do toolchain. Para tal,carregue-a por meio do comando abaixo:

```bash
./ct-ng armv8-rpi3-linux-gnueabihf
```

Uma vez feito o _loading_ da configuração, abra o menu de configurações do _crosstool-nt_ e faça alguns ajustes:

```bash
./ct-ng menuconfig
```

> Nesta etapa você deverá realiza a configuração através do _menuconfig_ portanto, muita atenção pois é um procedimento que requer cuidado, pois a configuração errada de algum módulo ou componente pode não ser evidente agora e causar problemas durante a fase de desenvolvimento.

#### Configuração da CrossTool

1. Opção **Path and misc options**:
   * **Number of parallel jobs**: \(2\) - Obs: Essa opção define a quantidade de threads de execução, que por sua vez diminui o tempo de compilação do toolchain.
   * **Maximum log level to see**: \(DEBUG\) - Obs: Essa opção exibe informações a respeito do procedimento de build em tempo real. Assim, caso ocorra algum erro durante a compilação do toolchain, esse erro será exibido no shell.
   * **CT\_PREFIX**: Obs: Este é o diretório de instalação do toolchain. 

     Altere-o **de**: ${CT\_PREFIX:-${HOME}/x-tools}... 

     **para**: ${CT\_PREFIX:-${HOME}/dsle20/toolchains/x-tools}...
2. Opção **Toolchain options**:
   * **Tuple's alias**: \(arm-linux\) - Obs: Desta maneira, o _crosstool-ng_ irá gerar o compilador como `arm-linux-gcc`, por exemplo. Caso contrário ele gera um nome extenso como: `armv8-rpi3-linux- gnueabihf-gcc`.
3. Opção **Debug facilities**:
   * **gdb**: \(ativo\) - Obs: Ative o `gdb`, pois será o debugger utilizado no restante do treinamento. Além disso, assegure-se de que as seguintes opções foram selecionadas:
     * Cross-gdb;
     * build a static cross gdb;
     * gdbserver

Salve suas alterações, saia do _menuconfig_ e inicie o processo de compilação do toolchain:

```bash
./ct-ng build
```

Ao final do processo, conforme configurado em _CT\_PREFIX_, os binários do toolchain gerado estarão disponíveis no diretório: `∼/dsle20/toolchains/x-tools/armv8-rpi3-linux-gnueabihf/bin/`. Dê um comando `ls` no diretório e verifique as ferramentas geradas.

#### Configuração do PATH

Como este toolchain será utilizado nas próximas atividades do treinamento, é necessário adicionar seus executáveis à variável de ambiente `$PATH`. Abra o arquivo `∼/.bashrc` com seu editor favorito:

```bash
gedit ~/.bashrc
```

Em seguida, adicione a seguinte linha no final do arquivo:

```bash
export PATH=$PATH:~/dsle20/toolchains/x-tools/armv8-rpi3-linux-gnueabihf/bin/
```

Salve e feche o arquivo. Então basta carregar a configuração e, em seguida, realizar um pequeno teste para verificar se os binários foram adicionados corretamente à variável `$PATH`:

```bash
source ~/.bashrc
arm-linux-gcc --version
```

A saída deve ser algo semelhante à:

```bash
arm-linux-gcc (crosstool-NG crosstool-ng-1.23.0) 6.3.0
Copyright (C) 2016 Free Software Foundation, Inc.
This is free software; see the source for copying conditions. There is NO warranty; not even for MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
```

#### Testando o toolchain

Recompile o programa da atividade 01, `helloworld.c`, em C com o novo toolchain gerado. Inicialmente, crie a pasta `ex02` dentro do diretório de exercícios `exs` e, em seguida, copie o arquivo `helloworld.c` da pasta `ex01` para a pasta `ex02`:

```bash
cd ~/dsle20/exs
mkdir ex02
cp ex01/helloworld.c ex02
```

Navegue até a pasta `ex02` e compile o programa `helloworld.c` utilizando o _gcc_ do toolchain recém-criado:

```bash
cd ex02
arm-linux-gcc helloworld.c -o helloARMctng
```

Novamente, verifique o programa gerado através do comando `file` e veja que, as informações exibidas como arquitetura e versão do kernel, estarão de acordo com as opções selecionadas no _crosstool-ng_:

```bash
file helloARMctng
```

```bash
helloARMctng: ELF 32-bit LSB executable, ARM, EABI5 version 1 (SYSV), dynamically linked, interpreter /lib/ld-
linux -armhf.so.3, for GNU/Linux 4.10.8, not stripped
```

Se desejar, repita o teste de rodar o executável na RPi 3. Primeiramente copie através do `scp` para a plataforma embarcada.

```bash
scp helloARMctng pi@10.1.1.100:/home/pi/helloARMctng
```

Então, acesse-a e execute o código recém enviado:

```bash
ssh pi@10.1.1.100
cd
./helloARMctng
```

