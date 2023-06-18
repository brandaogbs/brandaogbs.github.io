---
layout: post
title:  Embedded Linux Development Course - Development (pt. 9) 
date:   2020-03-15 22:57:49 +0000
tags: [linux, embedded, c, c++, course, setup]
categories: jekyll update
usemathjax: true
---

# Desenvolvimento de Aplicações

Quando trata-se de desenvolvimento de aplicações para Linux embarcado existe uma regra de outro, como já mencionado:

> Um Sistema Linux Embarcado é apenas um Sistema Linux normal, com uma limitada seleção de componentes!

Isto significa basicamente que desenvolver par aum Sistema Linux Embarcado, é a mesma coisa que desenvolver para um desktop Linux, ou seja, uma aplicação normal em Linux.

Todo o conhecimento de programação é reutilizável. Desta forma, é fácil reaproveitar sem nenhuma adaptação adicional os conceitos e práticas sobre Sistemas Operacionais, Threads, Estruturas de Dado e etc.

Além disso, outra característica que garante o desempenho enquanto se desenvolve para Linux embarcado é o fato da maioria das bibliotecas existentes para desktop, que é uma quantidade colossal, podem ser cross-compiladas para um sistema embarcado. Considerando, é claro, exclusividades de arquitetura, diferença de performance, armazenamento, memória e etc.

Este fato, da regra de ouro, é crucial para uma empresa ou para desenvolvedores. Visto que é possível começar o desenvolvimento da aplicação no seu desktop x86, antes mesmo de definir qual sera o hardware. Ou seja, muitas vezes é possível levantar todas as características que deveram ser implementadas, realizar o desenvolvimento \(logicamente em alguns pontos são necessários Mocks\) e então especificar o hardware para rodar a aplicação.

Isso poupa muito tempo, pois não é necessário ficar desenvolvendo código direto na plataforma, que geralmente demora mais por diversos fatores, além de garantir certo conforto para o desenvolvedor. Por exemplo, não há a necessidade de ficar realizando comunicações de hardware ou lendo diversos manuais antes de começar o desenvolvimento, a camada entre software e hardware é bem mais definida, diferentemente de desenvolvimento baremetal.

# Linguagens de Programação

### Linguagem de Programação

Existem diversas formas de se desenvolver aplicações para Linux embarcado. A mais comum e usual é o desenvolvimento de aplicações em C/C++, visto que é a forma natural de se comunicar com a API do Linux.

Lembre-se o Linux, tanto seu kernel quanto módulos, são desenvolvidos em linguagem C, a biblioteca padrão do sistema é a bilbioteca C e já esta presente no sistema.

C++ é simples de se utilizar também, nestes sistemas. Algumas bibliotecas desenvolvidas em C++, dependem da biblioteca c++ e portanto, podem estar presente no seu sistema. Um exemplo comumente utilizado é o QT, principalmente para aplicações que requerem interfaces gráficas para o usuário, como IHMs. 

Esse tipo de abordagem é prática e eficiente, as bibliotecas são similares e a possibilidade de se utilizar outros paradígmas de programação como Orientação a Objetos é sem dúvida um recurso extremamente poderoso para o desenvolvimento embarcado, tornando o código elegante e de fácil manutenção através de _design patterns_.

Outro caminho que pode ser utilizado é a adoção de linguagens interpretadas ou de script. Como o sistema Linux embarcado costuma ter mais capacidade que sistemas microcontrolados, esta é sem dúvidas uma opção viável para a implementação de sistemas.

As principais características deste tipo de desenvolvimento, utilizando linguagens interpretadas, é a velocidade de desenvolvimento e as possíveis camadas de abstrações fornecidas. É especialmente útil quando se trata de aplicações web. 

Não obstante, este tipo de desenvolvimento apresenta diversas facilidades para o desenvolvedor, como estruturas de dados complexas, abstrações e mesmo paradígmas diferentes de programação.

Contudo, normalmente requerem algum interpretador para que seja possível sua execução, possui um consumo de memória mais alto e levemente mais lentas quando comparado a aplicações C/C++.

Escolhas para comuns para este tipo de desenvolvimento são: Python, JavaScript, Shell Script, Lua, Perl, Ada, Java e etc.

### Bibliotecas C vs. Bibliotecas de Alto Nível

Em geral, a biblioteca padrão C já oferece um conjuto relativamente amplo de funcionalidades:

* I/O em arquivos e dispositivos de hardware, rede, threads e sincronização, IPC.
* Manual bem amplo e bem documentado \(man ou website\);
* No entanto, como é bastante antiga e possui um grande histórico de alterações, as vezes encontrar informação de uma funcionalidade nova pode ser trabalhoso.

Além disso, as vezes pode ser interessante utilizar frameworks de alto nível, como QT ou QTK. Isto pode ser bem útil, pois:

* Eles possuem uma separação bem clara entre o core da linguagem de programação \(C++\) e a parte gráfica;
* Tradeoff: desempenho vs. facilidade de desenvolvimento.

# Setups de Desenvolvimento

Quando se trata de desenvolvimento, a plataforma na qual se programa o código é tópico extensivo de discussões, mas existem basicamente duas abordagens. Aqueles que preferem ter controle sobre todos os aspéctos da edição, plugins e compilação e então preferem utilizar um editor de texto e adicionar plugins para obter um setup produtivo. E há aqueles que prefiram a utilizações de IDEs para o desenvolvimento, sistemas que garantem certa praticidade e conforto.

Para programas mais simples, um setup sugerido é:

* Vim/Emacs + terminal;
* VSCode/Sublime + terminal;
* Makefiles;
* CMake;

Para programas mais complexos:

* Vim/Emacs + terminal;
* VSCode/Sublime + terminal;
* CMake;
* IDE;

### Integrated Development Environments \(IDE\)

Aqui existem diversas escolhas plausíveis, desde editores de texto simples que aceitam recursos externos através de plugins, como no caso do Vim, Emacs e VSCode. Até IDE mais complexas como Eclipse, VisualStudio e CLion.

Uma opção é o KDevelop:

* Ada, C, C++, Java, Perl, PHP, Python, ...;
* Suporte a projetos gráficos \(GTK, Gnome\);
* Suporte a drivers do kernel e etc;
* Debugger, File Manager, Class Explorer.

Outra opção, mais utilizada é o Eclipse, ou qualquer um de seus derivados:

* Altamente configurável;
* Grande variedade de plugins disponíveis, de graça;
* Normalmente utilizado como base para a criação de IDEs de terceiros: CodeComposer, CodeWarrior, QNX Moments, CoIDE.
* Eclipse é na verade uma plataforma composta por vários projeto;
* A maioria dos fabricantes de embarcado utilizam a plataforma.

Outra opções são:

* Codelite;
* Visual Studio;
* CLion;

Além disso, como citado anteriormente, existe aqueles que preferem realizar o desenvolvimento em editores de texto simples e utilizar-se de plugins para o trabalho bruto. Algumas opções aqui são:

* Vim;
* Emacs;
* VSCode.

# Debbuging e Análise

### Debbuging

Sem dúvidas, a ferramenta mais utilizada para o debugging de aplicações é o [GDB - _The GNU Project Debugger_](https://www.gnu.org/software/gdb/)_._ 

Ele é o debugger padrão do GNU/Linux, disponível para a maioria das arquiteturas embarcadas. Apresenta suporte para diversas linguagens como C, C++, Pascal, Objective-C, Fortran, Ada e etc.

Possui uma interface por console \(terminal\), mas também possui algumas aplicações de front-ened para facilitar a visualização, por exemplo o VisualGDB.

Além disso, possui uma integração limpa e bem eficiente como IDEs como o Eclipse.

Os comandos básicos do GDB para debbugins são:

* **break sum** - Coloca um breakpoint na entrada da função sum\(\); 
* **break helloworld.c:45** - Coloca um breakpoint na linha 45 do ar- quivo helloworld.c;
* **print variável ou print node-&gt;data\_st.temperatura** - Imprime variável ou alguma referência mais complexa;
* **continue** - Continua a execução;
* **next** - Continua para a próxima linha \(step over na função\);
* **step** - Continua para a proxima linha \(step in na função\);
* **backtrace** - Imprime a stack do programa.

Além disso, existe o caso onde é necessário o Debugging Remoto. Isto é geralmente necessário em duas situações: na primeira, normalmente o fonte da aplicação se encontram na máquina de desenvolvimento e o binário no target. Ou, o target é limitado e não possui o gdb compilado de forma nativa \(~2.4mb\).

Para estes cenários uma solução é utilizar:

* **gdb client** \(arm-linux-gdb\) é utilizado na máquina de desenvolvimento;
* **gdbserver** é utilizado no target \(~100Kb\).

# \[LAB\] Configurando o Eclipse IDE

Para o treinamento vamos utilizar o [Eclipse IDE](https://www.eclipse.org/) para o desenvolvimento de algumas aplicações. Esta escolha foi feita com base na praticidade da utilização da ferramenta, visto que a maiorida dos desenvolvedores embarcados já tiveram algum tipo de contato com a ferramenta. 

Além disso, uma abordagem utilizando editores de texto fazendo as compilações por Makefiles/CMake pode ser um pouco abrupta para aqueles que não tem familiaridade, visto que a curva de aprendizado é mais complexa.

Desta forma, vamos realizar o download, configuração e integração desta ferramente para o desenvolvimento de aplicações em Sistemas Linux Embarcados.

### Instalando e iniciando o Eclipse

Instale o Eclipse CDT \(C/C++ Development Tooling\) através dos repositórios oficiais do Ubuntu:

```text
sudo apt install eclipse-cdt*
```

> O '`*`' no terminal Linux significa algo como _don't care_, desta forma ele seleciona todos os pacotes que contenham o começo "eclipse-cdt".

Ao terminar o processo de instalação, abra o Eclipse \(via terminal ou pelo launcher\) e configure um Workspace de sua preferência. Ex: /home/gbs/dsle20/workspace. Em seguida, clique no ícone superior direito _**Workbench**_.

### Configurando a conexão entre Eclipse e _Target_

A conexão entre o Eclipse e a RPi será realizada via SSH, por meio do plugin RSE \(_Remote System Explorer_\). Se o comando anterior, de instalação do Eclipse, foi executado corretamente, este plugin já estará instalado.

Antes de prosseguir nas configurações do Eclipse, faça a liberação de login sem senha de seu usuário/máquina no servidor SSH da RPi. Para isso, primeiro gere uma chave RSA para seu host \(Ubuntu\):

```text
ssh-keygen
```

A ferramenta irá perguntar sobre local para salvar a chave criada e senha, deixe ambos como padrão, apenas tecle `ENTER`.

```text
Generating public/private rsa key pair.
Enter file in which to save the key (/home/gbs/.ssh/id_rsa): 
Enter passphrase (empty for no passphrase): 
Enter same passphrase again: 
Your identification has been saved in /home/gbs/.ssh/id_rsa.
Your public key has been saved in /home/gbs/.ssh/id_rsa.pub.
The key fingerprint is:
SHA256:1E1uso97KS4cQYY6bo5nU5+W7H+zFnmDFhuqJaGAfeI gbs@dsle20
The key's randomart image is:
+---[RSA 2048]----+
|       .    .    |
|      . o. +     |
|   o . o. o +    |
|  . * ..o  +o    |
|   o = .So.. *   |
|    E o o oo* o  |
|   + . + B...+ . |
|  . =   X ..*    |
|   o . o.++=.o   |
+----[SHA256]-----+

```

Em seguida, copie sua chave recém criada para a RPi, utilizando o usuário que você deseja vincular a key:

```text
ssh-copy-id gbs@10.1.1.100
```

```text
/usr/bin/ssh-copy-id: INFO: attempting to log in with the new key(s), to filter out any that are already installed
/usr/bin/ssh-copy-id: INFO: 1 key(s) remain to be installed -- if you are prompted now it is to install the new keys
gbs@10.1.1.100's password: 

Number of key(s) added: 1

Now try logging into the machine, with:   "ssh 'gbs@10.1.1.100'"
and check to make sure that only the key(s) you wanted were added.
```

Por fim, adicione sua key recém-criada ao agente de autenticação SSH:

```text
ssh-add
```

```text
Identity added: /home/gbs/.ssh/id_rsa (/home/gbs/.ssh/id_rsa)
```

Este passo final vinculará a key com o usuário utilizado no passo anterior. Assim, sempre que o comando `ssh gbs@10.1.1.100` for chamado, o agente fornece tal key e remove a necessidade de digitar uma senha. Faça o teste:

```text
ssh gbs@10.1.1.100
```

Pronto. Agora retorne ao Eclipse. Abra a perspectiva do RSE em: "_Window &gt; Open Perspective &gt; Other..._". Selecione _Remote System Explorer_ e clique em OK. 

Na janela mais a esquerda, chamada _Remote Systems_, clique com o botão direto no espaço em branco e selecione: "_New &gt; Connection.._.".

Na janela _New Connection_ selecione o tipo Linux e clique em Next. Preencha com as seguintes informações:

* **Host name**: 10.1.1.100 - O endereço de IP da RPi;
* **Connection name**: RPi3 - O nome para esta conexão \(pode colocar o nome que achar melhor\);
* **Description**: Alguma descrição sobre essa conexão \(opcional\).

Clique em _Next_. Na janela superior esquerda, _Configuration_, marque a opção **ssh.files** e _Next_. 

Novamente, na janela superior esquerda, _Configuration_, marque a opção **processes.shell.linux** e _Next_. 

Em seguida, na mesma janela, marque ssh.shells, _Next_ e por último marque **ssh.terminals** e _Finish_.

A partir deste momento, será possível explorar os arquivos da RPi através do Eclipse. 

Expanda o menu _Sftp Files_ e perceba que todas as pastas do RootFS estão listadas ali. É possível copiar arquivos, editar, apagar, tudo de forma integrada com o Eclipse. Provavelmente será pedida a senha do seu usuário da RPi, apenas digite-a e o acesso aos arquivos será liberado. Caso digite errado, clique no com o botão direito no projeto e limpe as senhas.

Logo abaixo de _Sftp Files_, no menu _Shell Processes_, você possui acesso à todos os processos \(incluindo threads\) em execução no target. É possível finalizar um processo pelo Eclipse e escolher o tipo de sinal que deseja enviar \(botão direito no processo -&gt; kill -&gt; signal type\).

No canto superior direito do Eclipse, existe um ícone de atalho para a opção "_Open Perspective_", ele estará do lado do atalho para _Remote System Explorer perspective_. Clique nele e selecione a perspectiva _C/C++_.

Adicione também a _View do Remote Systems_ na perspectiva C/C++. Dessa forma você pode explorar os arquivos do target na mesma perspectiva de programação. 

Selecione o menu "_Window &gt; Show View &gt; Other..._". Em seguida, selecione "_Remote Systems &gt; Remote Systems_". A _View Remote System Details_ também é interessante. Ela exibe informações de permissão de arquivos e diretórios.

Na aba recém-adicionada _Remote Systems_, Clique no último ícone da lista com o botão direito, _Ssh Terminals_, e escolha a opção _Launch Terminal_. Note que um novo terminal SSH será aberto numa nova aba. A partir de agora é possível também acessar o terminal da RPi3 via SSH, pelo Eclipse.

### Cross-Compilando sua Primeira Aplicação

Na perspectiva C/C++, clique no menu "_File &gt; New &gt; C Project_". Em _Project type_, selecione _Hello World ANSI C Project_. 

Em _Toolchains_, selecione _Cross GCC_. Dê um nome para seu projeto em _Project name_: "_MyFirstApp_". Clique em _Next_ e, se desejar, adicione informações de autor \(suas iniciais, por exemplo\).

_Next_ novamente, _Next_ e, em _Cross compiler prefix_: **arm-linux-** e no campo _Cross compiler path_: selecione o caminho do toolchain gerado na primeira aula: **/home/gbs/dsle20/toolchains/x-tools/armv8-rpi3-linux-gnueabihf/bin**. Finalmente, clique em _Finish_.

Para compilar o projeto, acesse o menu _"Project &gt; Build All_ " ou `CTRL+B`. Se tudo foi configurado corretamente, algo como a seguinte mensagem será exibida na aba Console: "_15:46:14 Build Finished \(took 183ms\)_"

Para testar o binário, copie-o da pasta `Binaries`, logo abaixo da pasta do seu projeto para sua pasta `home`, na RPi, através da janela _Remote Systems_. Para fazer isso, basta clicar e segurar a pasta Binaries e arrasta-la para o Home em Remote Systems.

Note que ao tentar executar o arquivo pelo terminal SSH, será exibida uma mensagem de erro, dizendo que não é possível executar o binário:

```text
./MyFirstApp
```

```text
-sh: ./MyFirstApp: Permission denied
```

Para corrigir este problema, basta dar permissões de execução para o arquivo. Ainda no terminal SSH digite:

```text
chmod +x MyFirstApp
```

Pronto, basta rodar a aplicação:

```text
./MyFirstApp
```

```text
!!!Hello World!!!
```

### Configurando o GDB no Eclipse

Acesse o menu "_Run &gt; Debug Configurations_":

* Clique duas vezes em _C/C++ Remote Application_;
* Na aba "_Main_", no campo "_Connection_", selecione o nome \("_RPi3_"\) da conexão que você criou anteriormente no _Remote System Explorer_;
* Em "_Remote Absolute File Path for C/C++ Application_", digite o caminho do executável na RaspberryPi . Por exemplo: "**/home/gbs/MyFirstApp**";
* Na aba "_Debugger_", digite "**arm-linux-gdb**";
* Clique em "_Apply_"e depois em "_Debug_";
* Ao abrir a janela perguntando se você deseja abrir a perspectiva de "_Debug_", apenas clique em _Yes_;

### Configurando o Eclipse para Copiar seu Executável no _Target_ Automaticamente

Clique com o botão direito no seu projeto, na janela da esquerda chamada _Project Explorer_, e acesse propriedades. 

Na janela exibida, navegue em "_C/C++ Build &gt; Settings_". Clique na aba "_Build Steps_" e digite o seguinte comando no campo "_Command_"do bloco "_Post-build steps_": **scp MyFirstApp gbs@10.1.1.100:/home/gbs**

O comando acima faz com que o Eclipse copie seu binário para o _Target_, na pasta "`/home/gbs`", a cada novo _build_. Apague o arquivo via terminal SSH: 

```text
rm /home/gbs/MyFirstApp
```

e em seguida, compile o projeto novamente e verifique que o novo binário estará disponível na pasta e pronto para execução: 

```text
ls
./MyFirstApp
```

### Configurando e Linkando Bibliotecas Externas no Eclipse

Três configurações devem ser realizadas no intuito de linkar uma biblioteca a um projeto do Eclipse:

* **Definir o diretório de headers da biblioteca**: A adição deste diretório no projeto possibilita que o indexer do Eclipse reconheça as funções, definições de constantes, declarações em geral da biblioteca. Uma vez reconhecida a biblioteca, é possível utilizar o recurso autocompletar durante a programação. Para adicionar um diretório de headers a um projeto do eclipse: Clique com o botão direito no projeto desejado e selecione P_roperperties &gt; C/C++ Build &gt; Settings_. Em seguida, no Menu da direita, selecione as opções: _Cross GCC Compiler &gt; Includes_ e, finalmente, adicione o path onde se encontra os headers da biblioteca a ser incluída.
* **Definir o nome da biblioteca para linkagem durante a compilação**: Além de definir o diretório de headers, é necessário especificar ao compilador quais são as bibliotecas que devem ser linkadas com o executável do seu projeto. Para isso: Clique com o botão direito no projeto desejado e selecione _Properperties &gt; C/C++ Build &gt; Settings_. Em seguida, no Menu da direita, selecione as opções: _Cross GCC Linker &gt; Libraries_ e, finalmente, adicione o nome das bibliotecas que deseja linkar com seu projeto. Note que, em C, apesar de os executáveis de bibliotecas normalmente serem nomeados como `libNOMEDABIBLIOTECA.so`, deve- se adicionar apenas o `NOMEDABIBLITOECA`, sem o _lib_ e o _.so_. Ex: se o nome do executável da biblioteca é `libpigpio.so`, adiciona-se somente `pigpio`.
* **Definir o diretório onde se encontra o executável da biblioteca**: Além de definir quais bibliotecas deseja-se linkar com o executável, é necessário indicar no projeto, o diretório onde tal executável se encontra, caso a biblioteca seja externa ou não esteja incluída na _GLibC_. Navegue até o mesmo ponto descrito no passo anterior: Clique com o botão direito no projeto desejado e selecione _Properperties &gt; C/C++ Build &gt; Settings_. Em seguida, no Menu da direita, selecione as opções: _Cross GCC Linker &gt; Libraries_. Note que existe uma barra de rolagem lateral e, ao rolá-la para baixo, uma nova opção será exibida: _Library Search Path_:. Este é o local onde deve ser indicado o diretório contendo o executável da biblioteca a ser adicionada.

### Configurando o Path de Bibliotecas Externas no GDB

Normalmente, para debugar uma aplicação remotamente que foi compilada com alguma biblioteca externa \(não incluída na _GLIBC_\), é necessário definir o _path_ de tal biblioteca em um arquivo de configuração do GDB, chamado `.gdbinit`. Esse arquivo, na verdade, é utilizado para passar parâmetros ao _gdb_, que normalmente seriam passados via linha de comando. 

Crie um arquivo chamado `.gdbinit` e adicione a seguinte linha no arquivo:

```text
set solib-search-path /PATH/DA//BIBLITOECA
```

Salve o arquivo e adicione-o nas configurações de _Debug_ do seu projeto. Acesse o menu "_Run &gt; Debug Configurations_":

* Selecione a configuração já realizada no passo descrito na seção de _Configuração do GDB no Eclipse._
* Na aba "_Debugger_", no campo "_GDB command file_", clique no botão browse e selecione o path do arquivo `.gdbinit`;

_Obs: a\) É possível selecionar um path qualquer para o arquivo ou; b\) deixar essa opção inalterada e criar o arquivo na raiz do seu workspace atual_;

# \[LAB\] Led Blink e File Descriptors

A partir deste laboratório iremos dar início a etapa de aplicação em sistemas embarcados.  Assim, nesta prática iniciaremos através da manipulação de hardware e os conceitos básicos de file descriptors.

Nesta primeira prática iremos entender o funcionamento dos file descriptors e utilizá-los para realizar o acionamento dos LEDs built-in da RPi3.

### LEDs Internos da RPi 3

A Raspberry Pi 3 Model B/B+ possui dois LEDs internos que são utilizadaos para funções internas da placa. Um deles é um LED na cor verde e é utilizado para explicitar as atividades do cartão SD do dispositivo. Ao passo, que o segundo, LED vermelho, indica a alimentação do circuito de potência da placa. Ambos podem ser visto na imagem abaixo.

<figure>
<img src="/assets/posts/dsle20/dev-1.png" alt="">
</figure>

| LED | Cor | Localização | Função |
| :--- | :--- | :--- | :--- |
| OK/ACT | Verde | `/sys/class/leds/led0/brightness` | Atividade do Cartão SD |
| PWR | Vermelho | `/sys/class/leds/led1/brightness` | Alimentação |

###  Acionamento via dos Arquivos de Dispositivo

Como explicado durante o treinamento, os dispositivos, em geral, são representados por arquivos no Linux. Não diferente, os dois LEDs built-in da RPi3 são representados através deste tipo de arquivo.

O acesso a esses dispositivos são feitos através do arquivo de dispositivo que representa cada um deles. Por exemplo, caso deseje ler o valor do LED0 \(verde\) basta executar o comando `cat` no diretório especificado.

```bash
cat /sys/class/leds/led0/brightness 
```

O mesmo pode ser feito para o vermelho:

```bash
cat /sys/class/leds/led1/brightness 
```

Note que o valor retornado pelo `cat`, caso o Led em questão esteja ligado, é _255_ \(ou outro valor diferente de 0\), ao passo que o valor do Led desligado é igual a _0._ Ou seja, é possível notar o comportamento binário dos Led, de tal forma que: _0_ é desligado e qualquer outro valor é ligado.

Com base nisso, é possível especular que para acionar um dos Leds, basta escrever _1_ ou _0_ nos respectivos arquivos. Assim, para acionar o Led verde, basta escrever _1_ no arquivo `/sys/class/leds/led0/brightness`. 

```bash
echo 1 | sudo tee /sys/class/leds/led0/brightness
```

Ao passo que para apagar o Led, deve-se escrever _0._

```bash
echo 0 | sudo tee /sys/class/leds/led0/brightness
```

O mesmo para o Led vermelho, bastando apenas substituir o arquivo `/sys/class/leds/led0/brightness` por `/sys/class/leds/led1/brightness`.

Até este momento, foi possível interagir de formar manual com os dispositivos. Contudo, em um sistema embarcado real este tipo de operação não é usual, sendo necessário a manipulação desses dispositivos via programação. Para esse tipo de manipulação em sistema Linux utilizamos os _File Descriptors_.

### File Descriptors

Um _file descriptor_, ou também chamado de _file handler_, é um número que unicamente identifica um arquivo aberto no sistema operacional. Ele descreve um recurso de dados, e como esse recurso pode ser acessado.

Quando um programa pede para abrir um arquivo \(ou outros recurso, como um _socket_ ou um _pipe_\) o kernel Linux garante o acesso ao recurso, cria uma entrada na tabela global de arquivos e fornece a localização desta entrada ao software.

O descriptor é identificado por um número inteiro não-negativo único, tal como, 0, 13 ou 37. Existe pelo menos um file descriptor para cada arquivo aberto no sistema. 

Para mais informações sobre File Descriptors é recomendado a leitura das discussões propóstas em: [https://stackoverflow.com/questions/5256599/what-are-file-descriptors-explained-in-simple-terms](https://stackoverflow.com/questions/5256599/what-are-file-descriptors-explained-in-simple-terms)

Mas, em linha gerais:

* File descriptors são número inteiros não-negativos únicos que são associados a arquivos abertos no sistema;
* São alocados de forma sequencial;
* Utilizamos eles para manipular arquivos via biblioteca padrão C;
* Para um processo em particular seus file descriptors podem ser vistos em: `/proc/$pid/fd`.

Em linguagem C, usualmente representamos um file descriptor como um `int`:

```c
int led0_fd;
int led1_fd;
```

Para realizar a associação dos nossos file descriptors com os arquivos de dispositivos utilizamos a função padrão `open`:

> Para mais informações sobre as funções utilizadas, basta ler a documentação disponível no `man` digitando o comando `man func`. Por exemplo, `man open`, `man tee`, `man echo` e etc.

```c
#define LED0 "/sys/class/leds/led0/brightness"
#define LED1 "/sys/class/leds/led1/brightness"

led0_fd = open(LED0, O_RDWR);
led1_fd = open(LED1, O_RDWR);
```

Repare que como o interesse é realizar tanto leituras quanto escritas utilizamos a flag de "_read and write_", além disso para facilitar foram criados duas definições `LED0` e `LED1`, para armazenar os caminhos para os dispositivos.

Para verificar se os file descriptors foram devidamente associados, podemos observar e validar o retorno da função `open`. Isto é, como o file descriptor é sempre um número positivo, basta verificar se o retorno da função é de fato um valor positivo, caso não seja, significa que o file descriptor deste arquivo não foi relacionado através da função `open`.

```c
if (led0_fd < 0)
{
	printf(" Error: Failed to open %s \n\n", LED0);
}

if (led1_fd < 0)
{
	printf(" Error: Failed to open %s \n\n", LED1);
}
```

Para escrever valores nesses arquivos utilizamos a função pradrão `write`, passando os  file descriptors e os valores.

```c
#define LED_ON 	"1"
#define LED_OFF	"0"

write(led0_fd, LED_ON, sizeof(LED_ON));
write(led1_fd, LED_OFF, sizeof(LED_OFF));
```

Assim, acionamos o Led verde e desligamos o Led vermelho, escrevendo "_1_" e "_0_" em seus respectivos arquivos.

Por fim, é sempre necessário fechar esses file descriptors, indicando que não há mais necessidade de suas referências, fazemos isto através da função `close`.

```c
close(led0_fd);
close(led1_fd);
```

### Código de Led Blink com File Descriptors

```c
 /*============================================================================
 Name        : ex01.c
 Author      : gbs
 Version     :
 Copyright   : Your copyright notice
 Description : A simple C program for demonstrating the file descriptors.
 ============================================================================
 */

//==============================================================================
//                              USED INTERFACES
//==============================================================================

#include <fcntl.h>				/* Required by open / write system calls.     */
#include <pthread.h>			/* POSIX threads Library. Required by PIGPIO. */
#include <stdint.h>				/* Standard Int Library.(uint32_t, uint8_t...)*/
#include <stdio.h>				/* Standard Input/Ouput Library. (printf...)  */
#include <stdlib.h>				/* General (standard) Library. (EXIT_SUCCESS. */
#include <termios.h>			/* Terminal Input/Output interfaces.          */
#include <unistd.h>				/* Complement (flags, constants, definitions..)
									for the POSIX API. */

//==============================================================================
//                        MACROS AND DATATYPE DEFINITIONS
//==============================================================================

/* HW and Interfaces */

#define LED0	"/sys/class/leds/led0/brightness" // Green Led
#define LED1	"/sys/class/leds/led1/brightness" // Red Led

#define LED_ON 	"1"
#define LED_OFF	"0"

//==============================================================================
//                     STATIC (PRIVATE) FUNCTION PROTOTYPES
//==============================================================================

/**
 * @brief A function to verify if any key was pressed on terminal.
 *
 * @return TRUE     If a key was pressed.
 * @return FALSE    Otherwise.
 */
static int kbhit(void);

//==============================================================================
//                          STATIC GLOBAL VARIABLES
//==============================================================================


//==============================================================================
//                      IMPLEMENTATION OF PUBLIC FUNCTIONS
//==============================================================================

int main(void)
{

	int led0_fd; 			/* A file descriptor to manipulate the LED0. */
	int led1_fd; 			/* A file descriptor to manipulate the LED1. */

	led0_fd = open(LED0, O_RDWR); /* Opens LED0 for reading and writing*/
	led1_fd = open(LED1, O_RDWR); /* Opens LED1 for reading and writing*/

	if (led0_fd < 0)
	{
		printf(" Error: Failed to open %s \n\n", LED0);
	}

	if (led1_fd < 0)
	{
		printf(" Error: Failed to open %s \n\n", LED1);
	}

	while(!kbhit()) /* While a key from the keyboard isn't pressed... */
	{
		write(led0_fd, LED_ON, sizeof(LED_ON));
		write(led1_fd, LED_OFF, sizeof(LED_OFF));

		printf("LED0 -> ON, LED1 -> OFF\n");
		sleep(1);

		write(led0_fd, LED_OFF, sizeof(LED_OFF));
		write(led1_fd, LED_ON, sizeof(LED_ON));

		printf("LED0 -> OFF, LED1 -> ON\n");
		sleep(1);
	}

	close(led0_fd);
	close(led1_fd);

	return EXIT_SUCCESS;
}

//==============================================================================
//                IMPLEMENTATION OF STATIC (PRIVATE) FUNCTIONS
//==============================================================================

static int kbhit(void)
{
    struct termios oldt, newt;

    int ch;
    int oldf;

    /** Gets the attributes from the standard input file descriptor. */
    tcgetattr(STDIN_FILENO, &oldt);

    /** Enables raw input. (unprocessed). */
    newt = oldt;
    newt.c_lflag &= ~(ICANON | ECHO);

    /** Sets the new attributes. */
    tcsetattr(STDIN_FILENO, TCSANOW, &newt);

    /** Gets the file access mode and status flags. */
    oldf = fcntl(STDIN_FILENO, F_GETFL, 0);

    /** Sets the same above read values + the O_NONBLOCK flag. */
    fcntl(STDIN_FILENO, F_SETFL, oldf | O_NONBLOCK);

    /** Checks if there is a char on the standard terminal. (nonblock). */
    ch = getchar();

    /** Make changes now, without waiting for data to complete. */
    tcsetattr(STDIN_FILENO, TCSANOW, &oldt);

    /** Removes the O_NONBLOCK flag. */
    fcntl(STDIN_FILENO, F_SETFL, oldf);

    /** If any key was hitted, return true. And puts back the pressed key onto
     *  the terminal. */
    if(ch != EOF)
    {
        ungetc(ch, stdin);
        return 1;
    }

    return 0;
}
```

# \[LAB\] Bibliotecas e Hardware Handling

Neste projeto vamos aprofundar um pouco mais na manipulação dos hardwares e periféricos dos sistemas embarcados utilizando Linux. Vamos desenvolver uma aplicação básica que realize algumas tarefas que são comumente utilizadas em aplicações embarcadas, como: manipulação de GPIO, geração de PWM, trigggers e callbacks.

Para desenvolver aplicações em sistemas Linux embarcados, geralmente utilizamos bibliotécas _in-house_ ou de terceiros para desempenhar determinados papeis na aplicação, por exemplo, comunicação com hardware, protocolos, criptografias e etc. 

Esta é uma escolha usualmente simples, pois muitas vezes não é desejável re-implementar este tipo de função, ou está fora do escopo do projeto ou simplesmente pois existe uma gama tão grande de bibliotecas que desempenham este papel com maestria e já foram massivamente testadas e possuem um bom suporte que não convém desenvolvelas novamente. 

Para a manipulação de hardware não é diferente, existem diversas bibliotecas e APIs na comunidade para este fim. Cada uma com sua especificidade, sua aplicação, sua interface e sua linguagem de implementação, tais como: [WiringPi](http://wiringpi.com/), [PIGPIO](http://abyz.me.uk/rpi/pigpio/) e [RPi.GPIO](https://pypi.org/project/RPi.GPIO/).

Por alguns motivos em particular, vamos utilizar a biblioteca `PIGPIO` para as implementações desta atividade. Elá possui um interface em linguagem C, é suportada para todas as versões das Raspberrys e possui uma boa gama de funções, tais como: manipulação básica de GPIOs, timers, comunicação serial e etc.

### Cross-compilando e Instalando o PIGPIO no _host_

```text
cd ~/dsle20/dl
mkdir libs
cd libs
```

> A compilação deve ser feita utilizando cross-compiling, uma vez que o código é feito para rodar no embarcado. Portando, altere a variável `CROSS_COMPILE` dentro do `Makefile` para receber o prefixo da ferramenta de cross compilação.

```text

wget abyz.me.uk/rpi/pigpio/pigpio.zip
unzip pigpio.zip
cd PIGPIO
make
sudo make install
```

Após a compilação observe os arquivos gerados dentro do diretório `PIGPIO`. Estamos especialmente interessados nas bibliotecas compartilhadas \(`.so`\) e nos cabeçalhos.

### Instalando o PIGPIO no _target_ \(Buildroot\)

Para instalar a `PIGPIO` podemos utilizar o Buildroot, uma vez que o Busybox tem esta biblioteca em seu repositório.

Abra o menu de configuração dos pacotes do Buildroot:

```c
cd ~/dsle20/rootfs/buildroot-2019.02.8
make menuconfig 
```

Na seção _Target packages_ entre na subseção _Hardware Handling,_ onde se encontram diversos pacotes para a manipulação e periféricos e então selecione o pacote `pigpio`. Save a configuração e recompile o nosso RootFS. Não se preocupe, o processo de compilação ignora os arquivos já compilado, desta forma o processo se torna simples e rápido. 

Então, grave a nova imagem do RootFS no cartão SD e realize a configuração novamente. Para que tenhamos acesso agora, a essa nova biblioteca no nosso sistema embarcado.

Por padrão, as bibliotecas são instaladas dentro de `/usr/lib` no nosso _target_. Não diferente, se listarmos os arquivos disponíveis dentro deste diretório encontraremos os referidos arquivos.

```c
ls -ll /usr/lib | grep *pig*

-rwxr-xr-x    1 root     root        193672 Feb  2  2020 libpigpio.so
-rwxr-xr-x    1 root     root         45108 Feb  2  2020 libpigpiod_if.so
-rwxr-xr-x    1 root     root         45108 Feb  2  2020 libpigpiod_if2.so
```

### Utilizando a `PIGPIO`:

Primeiro passo que devemos fazer é importar esta nossa biblioteca através da primitiva de pré-processamento:

```c
#include "pigpio.h"
```

Então, ao compilar o código percebemos que não é possível realizar a compilação pois o linker não encontrou a referida biblica, pois a mesma não se encontra no diretório de execução. Portanto, faz-se necessário informar tanto o caminho do diretório que deve ser incluído no PATH do compilador como o nome da biblioteca, assim:

Clique com o botão direito sobre o projeto e em _Properies &gt; C/C++ Build &gt; Settings_. 

Então, na aba central, escolhemos a subseção _Cross GCC Compiler &gt; Includes_. 

Em "_includes paths \(-l\)_" adicionamos o caminho até a biblioteca compilada: `/home/gbs/dsle20/libs/PIGPIO`.

Na subseção _Cross GCC Linker &gt; Libraries_ em _"Libraries \(-l\)_" adicionamos o nome da biblioteca: `pigpio` \(sem o prefixo _lib_ e sem a extensão _.so_\). 

Por fim, em "_Library search path \(-L\)_" adicionamos novamente o caminho para a biblioteca compilada: `/home/gbs/dsle20/libs/PIGPIO`

Finalmente após a compilação iremos copiar os binários gerados para dentro da RPi e então executar o nosso código de teste.

```c
cd exs/
sudo ./ex02

./ex02: error while loading shared libraries: libpigpio.so.1: cannot open shared object file: No such file or directory
```

Este erro é ocasionado pois o executável não conseguiu encontrar o arquivo "`libpigpio.so.1`". De fato, podemos listar as bibliotecas instaladas e procurar pela _libpigpio_ no target:

```c
ls -ll /usr/lib/ | grep libpigpio.so
-rwxr-xr-x    1 root     root        193672 Feb  2  2020 libpigpio.so
```

Ao passo que no host:

```c
gbs@core:~$ ls -ll ~/dsle20/libs/PIGPIO/ | grep libpigpio.so

lrwxrwxrwx 1 gbs  gbs      14 Jan 10 14:26 libpigpio.so -> libpigpio.so.1
-rwxrwxr-x 1 gbs  gbs  260000 Jan 10 14:26 libpigpio.so.1
```

Nota-se que há um link simbólico _libpigpio.so -&gt; libpigpio.so.1_, ou seja, no processo de compilação a biblioteca a `libpigpio.so` é substituída por `libpigpio.so.1`. Normalmente, este número no final da biblioteca indica o versionamento atual da biblioteca, é muito comum realizar este tipo de link. Porém, na versão instalada na plataforma target, não há o arquivo `*.so.1` desta forma, precisamos criar este link no target para conseguir realizar a execução corretamente.

```c
sudo ln -s /usr/lib/libpigpio.so /usr/lib/libpigpio.so.1
```

```c
$ ls -ll /usr/lib/ | grep pig
-rwxr-xr-x    1 root     root        193672 Feb  2  2020 libpigpio.so
lrwxrwxrwx    1 root     root            21 Jan  1 00:32 libpigpio.so.1 -> /usr/lib/libpigpio.so
```

Agora basta compilar o código e tudo deve funcionar como o esperado.

> Toda as funções utilizadas nesta \(e nas seguintes\) prática podem ser consultadas através da documentação da biblioteca `PIGPIO` ou mesmo através do comando `man`.

### Geração de Sinal PWM utilizando a Biblioteca `PIGPIO`

Com a biblioteca devidamente instalada em ambas as plataformas podemos dar início a prática deste laboratório. 

O primeiro objetivo é gerar um sinal PWM em um dos pinos de uso geral da RPi3, de acordo com a especificação mostrada no diagrama de forma de onda abaixo, isto é, PWM de 50Hz e 50% de duty-cycle.

![Sinal PWM 50Hz@1000/500](../.gitbook/assets/image%20%2817%29.png)

Primeiramente, devemos inicializar a biblioteca PIGPIO, esta inicialização é feita através da função `gpioInitialise`.

```c
	if (gpioInitialise() < 0)
	{
		fprintf(stderr, "pigpio initialization failed\n");
		return 1;
	}
```

Depois de inicializada devemos configurar o modo de operação do pino que produzirá o sinal PWM. Nesta prática iremos utilizar o GPIO 23 \(observe o pinout da RPi para verificar a localização física do mesmo\). Para configurar o GPIO 23 como um pino de saída, basta utilizar a função `gpioSetMode`.

```c
if (gpioSetMode(23, PI_OUTPUT) != 0)
{
    printf("Error: Failed to set GPIO %d \n\n", 23);
}
```

Em seguida, utilizamos a função `gpioSetPWMfrequency` para definir a frequência de geração do pulso.

```c
int freq_ret;
freq_ret = gpioSetPWMfrequency(23, 50);

printf("Freq: %d \n\n", freq_ret);
```

Em seguida devemos definir o através da função `gpioSetPWMrange` a resolução do pulso gerado, bem como o duty-cycle do PWM através da função `gpioPWM`. O duty-cycle é definido pela razão entre o range e o parâmetro passado a função `gpioPWM`.

```c
gpioSetPWMrange(23, 1000);
```

```c
gpioPWM(23, 500);
```

Após a execução do código é necessário encerar as configurações dos pinos, similarmente como realizado no processo de inicialização.

```c
gpioTerminate();
```

### ISR e Callbacks utilizando a Biblioteca `PIGPIO`

Na segunda parte da atividade iremos realizar a configuração de uma ISR \(interrupção\) em um dos pinos. Esta interrupção será vinculada a uma função `signal_handler_io` que tem como objetivo executar uma determinada tarefa, como por exemplo a manipulação de um outro pino ou mesmo a execução de uma outra função qualquer.

Primeiramente vamos realizar a configuração de mais duas GPIOs. A GPIO 20 será configurada como uma porta de entrada e estará vinculada à ISR. Além disso, iremos inializar o GPIO 16 como saída para que a mesma seja manipulada pela callback da interrupção. 

```c
if (gpioSetMode(20, PI_INPUT) != 0)
{
    printf("Error: Failed to set GPIO %d \n\n", 20);
}

if (gpioSetMode(16, PI_OUTPUT) != 0)
{
    printf("Error: Failed to set GPIO %d \n\n", 16);
}
```

Para atrelar um GPIO a uma ISR devemos utilizar a função `gpioSetISRFunc` da biblioteca PIGPIO. Como parâmetros podemos passar a GPIO utilizada, a borda à ser detectada, um timeout e também a função \(callback\) a ser chamada quando o evento acontecer.

```c
gpioSetISRFunc(20, FALLING_EDGE, 300, signal_handler_IO);
```

Assim, devemos criar a função signal\_handler\_IO para ser utilizada como callback.

```c
void signal_handler_IO(int gpio, int level, uint32_t tick) 
{
    int gpio_val = gpioRead(16);
    gpio_val = !gpio_val;
    gpioWrite(16, gpio_val);
    printf("Interrupt Occurred! Level-> %d\t tick-> %d\n",level, tick-tick_spent);
    tick_spent = tick;
}
```

Populamos a função com alguma tarefa qualquer, neste caso, foi proposto calcular o tempo entre duas interrupções e também alterar o estado do GPIO 16, ligando-o e desligando conforme ocorrem as interrupções.

Ao executar o código podemos observar o seguinte diagrama:

<figure>
<img src="/assets/posts/dsle20/dev-2.png" alt="">
</figure>


A primeira forma de onda é o sinal PWM gerado pelo GPIO 23 ao passo que a segunda é a forma de onda gerada pelo GPIO 16.

Realizando um contato elétrico entre os GPIO 23 e GPIO 20, ou seja, conectando o PWM ao pino ISR é possível obter o diagrama a seguir.

<figure>
<img src="/assets/posts/dsle20/dev-3.png" alt="">
</figure>


Desta forma, foi possível visualizar a operação da ISR dos dois modos: timeout e detecção de borda. Estes tópicos serão abordados no projeto final.

```c
/*
 ============================================================================
 Name        : ex02.c
 Author      : gbs
 Version     :
 Copyright   : Your copyright notice
 Description : A simple C program for demonstrating the PIGPIO interface.
 ============================================================================
 */

//==============================================================================
//                              USED INTERFACES
//==============================================================================

#include <fcntl.h>				/* Required by open / write system calls.     */
#include <pthread.h>			/* POSIX threads Library. Required by PIGPIO. */
#include <stdint.h>				/* Standard Int Library.(uint32_t, uint8_t...)*/
#include <stdio.h>				/* Standard Input/Ouput Library. (printf...)  */
#include <stdlib.h>				/* General (standard) Library. (EXIT_SUCCESS. */
#include <termios.h>			/* Terminal Input/Output interfaces.          */
#include <unistd.h>				/* Complement (flags, constants, definitions..)
									for the POSIX API. */

#include "pigpio.h"				/* PIGPIO Library Header */

//==============================================================================
//                        MACROS AND DATATYPE DEFINITIONS
//==============================================================================

/* HW and Interfaces */


//==============================================================================
//                     STATIC (PRIVATE) FUNCTION PROTOTYPES
//==============================================================================

/**
 * @brief A function to verify if any key was pressed on terminal.
 *
 * @return TRUE     If a key was pressed.
 * @return FALSE    Otherwise.
 */
static int kbhit(void);

/**
 * @brief The callback function attached to the GPIO pin interrupt. The bellow
 * 		  parameters are provided by the RPiGPIO Library.
 *
 * @param[in] gpio     0-53     The GPIO which has changed state.
 * @param[in] level    0-2      0 = change to low (a falling edge)
 *		                        1 = change to high (a rising edge)
 *           		            2 = no level change (interrupt timeout)
 * @param[in] tick     32 bit   The number of microseconds since boot
 *
 */
static void signal_handler_IO(
		int gpio,
		int level,
		uint32_t tick);

//==============================================================================
//                          STATIC GLOBAL VARIABLES
//==============================================================================

uint32_t tick_spent;		/* A variable used to store the number of occurred
								ticks between each GPIO interrupt. */


//==============================================================================
//                      IMPLEMENTATION OF PUBLIC FUNCTIONS
//==============================================================================

int main(void)
{
	tick_spent = 0;


	if (gpioInitialise() < 0) /* Such function must be called before using the
									 PIGPIO library.*/
	{
		fprintf(stderr, "pigpio initialization failed\n");
		return 1;
	}

    if (gpioSetMode(23, PI_OUTPUT) != 0)
    {
    	printf("Error: Failed to set GPIO %d \n\n", 23);
    }

    if (gpioSetMode(16, PI_OUTPUT) != 0)
    {
		printf("Error: Failed to set GPIO %d \n\n", 16);
	}

    if (gpioSetMode(20, PI_INPUT) != 0)
	{
		printf("Error: Failed to set GPIO %d \n\n", 20);
	}

    /**
     * Registers the signal_handler function to be called
     * (a callback) whenever an interrupt occurs on
     * the specified GPIO (20). The EITHER_EDGE parameter
     * specifies an interrupt for both: Rising or Falling
     * edges. The parameter 100 indicates a 100ms timeout.
     */
    gpioSetISRFunc(20, EITHER_EDGE, 300, signal_handler_IO);
    /* PS: If you want to see a result different from the timeout,
     * i.e., a detected RISING or FALLING edge, you should connect
     * the GPIO pins (BCM) 20(input)-23(pwm). Which physically are:
     * the pins 38 and 16, respectively. */


    int freq_ret;

	/* Sets a 50Hz PWM Frequency for the GPIO  23 pin.
	 * It returns the numerically closest frequency if OK.
	 * The frequency depends on other factors, please for
	 * further details check:
	 * http://abyz.me.uk/rpi/pigpio/cif.html#gpioSetPWMfrequency*/
	freq_ret = gpioSetPWMfrequency(23, 50);

	printf("Freq: %d \n\n", freq_ret);

	/* Selects the duty-cycle range to be used for the GPIO.
	 * Subsequent calls to gpioPWM will use a duty-cycle
	 * between 0 (off) and range (fully on).]
	 * the range value can be: 25-40000 */
	gpioSetPWMrange(23, 1000);

	/* According to the above specified range (1000), sets a duty-cicle
	 * of 50%. */
	gpioPWM(23, 500);

	while(!kbhit()) /* While a key from the keyboard isn't pressed... */
	{

		printf("Running..\n");
		sleep(1);
	}

	/* Similar to the gpioInitialise function, this one must be called at the end of your program.*/
	gpioTerminate();


	return EXIT_SUCCESS;
}

//==============================================================================
//                IMPLEMENTATION OF STATIC (PRIVATE) FUNCTIONS
//==============================================================================

void signal_handler_IO(int gpio, int level, uint32_t tick)
{
	/* Reads the current state of the GPIO pin 16. */
	int gpio_val = gpioRead(16);

	/* Inverts such state. */
	gpio_val = !gpio_val;

	/* Updates the gpio pin's state. */
	gpioWrite(16, gpio_val);

	/* Computes and shows the number of spent ticks between the last and the current interrupt. */
	printf("Interrupt Occurred! Level-> %d\t tick-> %d\n",level, tick-tick_spent);
	tick_spent = tick;
}

static int kbhit(void)
{
    struct termios oldt, newt;

    int ch;
    int oldf;

    /** Gets the attributes from the standard input file descriptor. */
    tcgetattr(STDIN_FILENO, &oldt);

    /** Enables raw input. (unprocessed). */
    newt = oldt;
    newt.c_lflag &= ~(ICANON | ECHO);

    /** Sets the new attributes. */
    tcsetattr(STDIN_FILENO, TCSANOW, &newt);

    /** Gets the file access mode and status flags. */
    oldf = fcntl(STDIN_FILENO, F_GETFL, 0);

    /** Sets the same above read values + the O_NONBLOCK flag. */
    fcntl(STDIN_FILENO, F_SETFL, oldf | O_NONBLOCK);

    /** Checks if there is a char on the standard terminal. (nonblock). */
    ch = getchar();

    /** Make changes now, without waiting for data to complete. */
    tcsetattr(STDIN_FILENO, TCSANOW, &oldt);

    /** Removes the O_NONBLOCK flag. */
    fcntl(STDIN_FILENO, F_SETFL, oldf);

    /** If any key was hitted, return true. And puts back the pressed key onto
     *  the terminal. */
    if(ch != EOF)
    {
        ungetc(ch, stdin);
        return 1;
    }

    return 0;
}

```

# \[LAB\] Comunicação Serial

Nesta atividade iremos realizar a implementação de uma aplicação simples que envia dados via serial. Para a implementação iremos adotar duas abordagem: a primeira será a utilização explicita de file descriptors e a segunda será utilizando as abstrações fornecidas pela biblioteca `PIGPIO`.

### Comunicação Serial utilizando File Descriptors

```c
#define SERIAL 	"/dev/ttyS0"
#define SERIAL_BAUD 115200

int serial_fd;
```

```c
uint8_t serial_st;
serial_st = serial_initialize(SERIAL, &serial_fd, SERIAL_BAUD);
```

```c
uint8_t serial_initialize(const char *p_path, int32_t *p_fd, const uint32_t speed);
```

A primeira etapa que devemos realizar é justamente tentar abrir o dispositivo \(porta serial\), tal como fizemos com os os `LED0` e `LED1`, no projeto anterior. Então utilizamos o caminho e o file descriptor passados por parâmetro.

```c
*p_fd = open(p_path, O_RDWR);

if (p_fd < 0)
{
	printf("Error: Failed to open serial %s \n\n", p_path);
	ret = 0;
}
```

Caso contrário, ou seja, o file descriptor tenha sido devidamente relacionado com um dispositivo, precisamos verificar se ele é de fato uma porta serial e caso seja, devemos configura-la de acordo com o que desejamos.

Para fazer a configuração, utilizaremos uma estrutura de dados, `config`, para adquirir e atribuir os parâmetros do dispositivos.

```c
struct termios config;
```

Como mencionado, a primeira verificação que devemos fazer é justamente avaliar se o dispositivo relacionado ao file descriptor é um interface serial. Para tal, carregamos todos os atributos do dispositivo para nossa estrutura de dados.

```c
if (tcgetattr(*p_fd, &config) < 0)
{
		printf("Error: Could not get the %s attributes!\n\n", p_path);
}
```

Então, realizamos as validações, primeiramente se o dispositivo em questão é ou não uma interface serial:

```c
if (!isatty(*p_fd))
{
    printf("Error: %s isnt pointing to a TTY device!!\n\n", p_path);
}
```

Em seguida, tentamos atribuir o baud rate especificado

```c
if (cfsetspeed(&config, (speed_t)speed) < 0)
{
    printf("Error: Couldn't set the %s baudrate!!\n\n", p_path);
}
```

Então, especificamos os outros parâmetros:

```c
config.c_cflag     &=  ~PARENB;
config.c_cflag     &=  ~CSTOPB;
config.c_cflag     &=  ~CSIZE;
config.c_cflag     |=  CS8;
config.c_cflag     &=  ~CRTSCTS;
config.c_cc[VMIN]   =  1;
config.c_cc[VTIME]  =  5;
config.c_cflag     |=  CREAD | CLOCAL;

cfmakeraw(&config);
```

E enfim, atribuimos os atributos ao dispositivo.

```c
if (tcsetattr(*p_fd, TCSAFLUSH, &config) < 0)
{
    printf("Error: Couldn't set the %s attributes!!\n\n", p_path);
}
```

```c
uint8_t serial_initialize(const char *p_path, int32_t *p_fd, const uint32_t speed)
{
	uint8_t ret;

  /** Tries to open the serial device (p_path).
    *  O_RDWR:     Request read and write permissions. */
	*p_fd = open(p_path, O_RDWR);

	if (p_fd < 0)
	{
		printf("Error: Failed to open serial %s \n\n", p_path);
		ret = 0;
	}
	else
	{
		printf("Serial (%s) opened!!\n\n", p_path);

		/** The structure to set and get the device parameters. */
		struct termios config;

		/** Get the current configuration of the serial interface. */
		if (tcgetattr(*p_fd, &config) < 0)
		{
			printf("Error: Could not get the %s attributes!\n\n", p_path);
		}
		else
		{
			printf("Serial (%s) attributes read.. \n\n", p_path);

			/** Check if the fd is pointing to a TTY device or not. */
			if (!isatty(*p_fd))
			{
				printf("Error: %s isnt pointing to a TTY device!!\n\n", p_path);
			}
			else
			{
				printf("%s is a tty device. Continuing...\n\n", p_path);

				/** Setting the baudrate. */
				if (cfsetspeed(&config, (speed_t)speed) < 0)
				{
					printf("Error: Couldn't set the %s baudrate!!\n\n", p_path);
				}
				else
				{
					/** No parity. */
					config.c_cflag     &=  ~PARENB;
					/** One stop bit. */
					config.c_cflag     &=  ~CSTOPB;
					/** Zeroes the char size mask. */
					config.c_cflag     &=  ~CSIZE;
					/** Sets data size = 8 bits. */
					config.c_cflag     |=  CS8;
					/** Disables HW flow control. */
					config.c_cflag     &=  ~CRTSCTS;
					/** Minimum number of characters for read. */
					config.c_cc[VMIN]   =  1;
					/** Timeout in deciseconds for read. (0.5s) */
					config.c_cc[VTIME]  =  5;
					/** Enables READ and ignores control lines. */
					config.c_cflag     |=  CREAD | CLOCAL;

					/** Set the terminal to "raw mode". */
					cfmakeraw(&config);

			    /** Flushes the serial dev and sets the new attributes. */
    			if (tcsetattr(*p_fd, TCSAFLUSH, &config) < 0)
    			{
    				printf("Error: Couldn't set the %s attributes!!\n\n", p_path);
    			}
    			else
    			{
    				ret = 1;
    			}
				}
			}
		}
	}
	return ret;
}
```

```c
uint8_t serial_st; 
serial_st = serial_initialize(SERIAL, &serial_fd, SERIAL_BAUD);

if (serial_st == 0)
{
    printf("Error: Failed to open serial %s \n\n", SERIAL);
}
```

```text
write(serial_fd, "Running.. Serial is easy\r\n", sizeof("Running.. Serial is easy\r\n"));
```

```
close(serial_fd);
```

```c
/*
 ============================================================================
 Name        : ex03.c
 Author      : gbs
 Version     :
 Copyright   : Your copyright notice
 Description : A simple C program for demonstrating the serial communication.
 ============================================================================
 */

//==============================================================================
//                              USED INTERFACES
//==============================================================================

#define _GNU_SOURCE             /* See feature_test_macros(7) */

#include <fcntl.h>				/* Required by open / write system calls.     */
#include <pthread.h>			/* POSIX threads Library. Required by PIGPIO. */
#include <stdint.h>				/* Standard Int Library.(uint32_t, uint8_t...)*/
#include <stdio.h>				/* Standard Input/Ouput Library. (printf...)  */
#include <stdlib.h>				/* General (standard) Library. (EXIT_SUCCESS. */
#include <termios.h>			/* Terminal Input/Output interfaces.          */
#include <unistd.h>				/* Complement (flags, constants, definitions..)
									for the POSIX API. */

#include "pigpio.h"				/* PIGPIO Library header. */

//==============================================================================
//                        MACROS AND DATATYPE DEFINITIONS
//==============================================================================

/* HW and Interfaces */

#define SERIAL 	"/dev/ttyS0"
#define SERIAL_BAUD 115200

//==============================================================================
//                     STATIC (PRIVATE) FUNCTION PROTOTYPES
//==============================================================================

/**
 * @brief A function to verify if any key was pressed on terminal.
 *
 * @return TRUE     If a key was pressed.
 * @return FALSE    Otherwise.
 */
static int kbhit(void);

/**
 * @brief Initializes the p_path serial device. Opens the serial device and
 * 		  sets minimal attributes to get it working.
 *
 * @param[in] p_path    The serial device path.
 * @param[out] p_fd     A file descriptor to link to the serial device above.
 * @param[in] speed     The serial BAUDRATE.
 *
 * @return  1   If the serial device was initialized.
 * @return  0   If an error has occurred.
 */
uint8_t serial_initialize(
  const char *p_path,
  int32_t *p_fd,
  const uint32_t speed);


//==============================================================================
//                          STATIC GLOBAL VARIABLES
//==============================================================================

//==============================================================================
//                      IMPLEMENTATION OF PUBLIC FUNCTIONS
//==============================================================================

int main(void)
{
  int serial_fd;			/* A file descriptor to manipulate the SERIAL.*/
  uint8_t serial_st;		/* A status for the serial_initialize func.   */

  /* Opens SERIAL for reading and writing at SERIAL_BAUD baudrate.*/
  serial_st = serial_initialize(SERIAL, &serial_fd, SERIAL_BAUD);

  if (serial_st == 0)
  {
    printf("Error: Failed to open serial %s \r\n", SERIAL);
  }

  while(!kbhit())	/* While a key from the keyboard isn't pressed... */
  {
    write(serial_fd, "Running.. Serial is easy\r\n", sizeof("Running.. Serial is easy\r\n"));
  }

  close(serial_fd);

  return EXIT_SUCCESS;
}


//==============================================================================
//                IMPLEMENTATION OF STATIC (PRIVATE) FUNCTIONS
//==============================================================================

static int kbhit(void)
{
  struct termios oldt, newt;

  int ch;
  int oldf;

  /** Gets the attributes from the standard input file descriptor. */
  tcgetattr(STDIN_FILENO, &oldt);

  /** Enables raw input. (unprocessed). */
  newt = oldt;
  newt.c_lflag &= ~(ICANON | ECHO);

  /** Sets the new attributes. */
  tcsetattr(STDIN_FILENO, TCSANOW, &newt);

  /** Gets the file access mode and status flags. */
  oldf = fcntl(STDIN_FILENO, F_GETFL, 0);

  /** Sets the same above read values + the O_NONBLOCK flag. */
  fcntl(STDIN_FILENO, F_SETFL, oldf | O_NONBLOCK);

  /** Checks if there is a char on the standard terminal. (nonblock). */
  ch = getchar();

  /** Make changes now, without waiting for data to complete. */
  tcsetattr(STDIN_FILENO, TCSANOW, &oldt);

  /** Removes the O_NONBLOCK flag. */
  fcntl(STDIN_FILENO, F_SETFL, oldf);

  /** If any key was hitted, return true. And puts back the pressed key onto
   *  the terminal. */
  if(ch != EOF)
  {
    ungetc(ch, stdin);
    return 1;
  }

  return 0;
}

uint8_t serial_initialize(
  const char *p_path,
  int32_t *p_fd,
  const uint32_t speed)
{

  uint8_t ret;

  /** Tries to open the serial device (p_path).
   *  O_RDWR:     Request read and write permissions. */
  *p_fd = open(p_path, O_RDWR);

  if (p_fd < 0)
  {
    printf("Error: Failed to open serial %s \n\n", p_path);
    ret = 0;
  }
  else
  {
    printf("Serial (%s) opened!!\n\n", p_path);

    /** The structure to set and get the device parameters. */
    struct termios config;

    /** Get the current configuration of the serial interface. */
    if (tcgetattr(*p_fd, &config) < 0)
    {
      printf("Error: Could not get the %s attributes!\n\n", p_path);
    }
    else
    {
      printf("Serial (%s) attributes read.. \n\n", p_path);

      /** Check if the fd is pointing to a TTY device or not. */
      if (!isatty(*p_fd))
      {
        printf("Error: %s isnt pointing to a TTY device!!\n\n", p_path);
      }
      else
      {
        printf("%s is a tty device. Continuing...\n\n", p_path);

        /** Setting the baudrate. */
        if (cfsetspeed(&config, (speed_t)speed) < 0)
        {
          printf("Error: Couldn't set the %s baudrate!!\n\n", p_path);
        }
        else
        {
          /** No parity. */
          config.c_cflag     &=  ~PARENB;
          /** One stop bit. */
          config.c_cflag     &=  ~CSTOPB;
          /** Zeroes the char size mask. */
          config.c_cflag     &=  ~CSIZE;
          /** Sets data size = 8 bits. */
          config.c_cflag     |=  CS8;
          /** Disables HW flow control. */
          config.c_cflag     &=  ~CRTSCTS;
          /** Minimum number of characters for read. */
          config.c_cc[VMIN]   =  1;
          /** Timeout in deciseconds for read. (0.5s) */
          config.c_cc[VTIME]  =  5;
          /** Enables READ and ignores control lines. */
          config.c_cflag     |=  CREAD | CLOCAL;

          /** Set the terminal to "raw mode". */
          cfmakeraw(&config);

          /** Flushes the serial dev and sets the new attributes. */
          if (tcsetattr(*p_fd, TCSAFLUSH, &config) < 0)
          {
            printf("Error: Couldn't set the %s attributes!!\n\n",
              p_path);
          }
          else
          {
            ret = 1;
          }
        }
      }
    }
  }
  return ret;
}
```

### Comunicação Serial utilizando a Bilbioteca `PIGPIO`

Similarmente com a prática anterior é possível abstrair o uso do file descriptors através de encapsulamentos que já realizam essa tarefa mecânica para nós. Desta forma, vamos realizar o mesmo exercício utilizando as implementações fornecidas pela biblioteca PIGPIO.

Primeiramente devemos definir o nosso file descriptor para a manipulação do dispositivo serial.

```c
  int serial_fd;      /* A file descriptor to manipulate the SERIAL.*/
```

Então inicializamos as funções da bilbioteca PIGPIO:

```c
  if (gpioInitialise() < 0)
  {
    printf("PIGPIO init error\n");
  }
```

Em seguida, devemos atrelar o nosso file descriptor com o arquivo de dispositivo que queremos utilizar por meio da função `serOpen`:

```c
  /* Opens SERIAL for reading and writing at SERIAL_BAUD baudrate.*/
  serial_fd = serOpen(SERIAL, SERIAL_BAUD, 0);

  if (serial_fd < 0)
  {
    printf("Failed to open SERIAL\r\n");
  }
```

Por fim, basta utilizar a função `serWrite` passando o nosso file descriptor e a mensagem a ser enviada:

```c
    if (serWrite(serial_fd, (char *)"Running.. Serial is easy\r\n",
                 sizeof("Running.. Serial is easy\r\n")) != 0)
    {
      printf("Error: Failed to send message.\r\n");
    }
```

Se tudo ocorrer bem a mensagem será enviada através da porta serial `ttyS0`.

```c
/*
 ============================================================================
 Name        : ex03b.c
 Author      : gbs
 Version     :
 Copyright   : Your copyright notice
 Description : A simple C program for demonstrating the serial communication.
 ============================================================================
 */
//==============================================================================
//                              USED INTERFACES
//==============================================================================

#define _GNU_SOURCE             /* See feature_test_macros(7) */

#include <fcntl.h>        /* Required by open / write system calls.     */
#include <pthread.h>      /* POSIX threads Library. Required by PIGPIO. */
#include <stdint.h>       /* Standard Int Library.(uint32_t, uint8_t...)*/
#include <stdio.h>        /* Standard Input/Ouput Library. (printf...)  */
#include <stdlib.h>       /* General (standard) Library. (EXIT_SUCCESS. */
#include <termios.h>      /* Terminal Input/Output interfaces.          */
#include <unistd.h>       /* Complement (flags, constants, definitions..)
                  for the POSIX API. */

#include "pigpio.h"       /* PIGPIO Library header. */
//==============================================================================
//                        MACROS AND DATATYPE DEFINITIONS
//==============================================================================

/* HW and Interfaces */

#define SERIAL      "/dev/ttyS0"
#define SERIAL_BAUD 115200

//==============================================================================
//                     STATIC (PRIVATE) FUNCTION PROTOTYPES
//==============================================================================

/**
 * @brief A function to verify if any key was pressed on terminal.
 *
 * @return TRUE     If a key was pressed.
 * @return FALSE    Otherwise.
 */
static int kbhit(void);

//==============================================================================
//                          STATIC GLOBAL VARIABLES
//==============================================================================

//==============================================================================
//                      IMPLEMENTATION OF PUBLIC FUNCTIONS
//==============================================================================

int main(void)
{

  int serial_fd;      /* A file descriptor to manipulate the SERIAL.*/

  if (gpioInitialise() < 0)
  {
    printf("PIGPIO init error\n");
  }

  /* Opens SERIAL for reading and writing at SERIAL_BAUD baudrate.*/
  serial_fd = serOpen(SERIAL, SERIAL_BAUD, 0);

  if (serial_fd < 0)
  {
    printf("Failed to open SERIAL\r\n");
  }


  while(!kbhit())
  {
    sleep(1);

    if (serWrite(serial_fd, (char *)"Running.. Serial is easy\r\n",
                 sizeof("Running.. Serial is easy\r\n")) != 0)
    {
      printf("Error: Failed to send message.\r\n");
    }
  }

  /* Similar to the gpioInitialise function, this one must be called at the end of
   * your program.*/
  gpioTerminate();

	return EXIT_SUCCESS;
}

//==============================================================================s
//                IMPLEMENTATION OF STATIC (PRIVATE) FUNCTIONS
//==============================================================================

static int kbhit(void)
{
  struct termios oldt, newt;

  int ch;
  int oldf;

  /** Gets the attributes from the standard input file descriptor. */
  tcgetattr(STDIN_FILENO, &oldt);

  /** Enables raw input. (unprocessed). */
  newt = oldt;
  newt.c_lflag &= ~(ICANON | ECHO);

  /** Sets the new attributes. */
  tcsetattr(STDIN_FILENO, TCSANOW, &newt);

  /** Gets the file access mode and status flags. */
  oldf = fcntl(STDIN_FILENO, F_GETFL, 0);

  /** Sets the same above read values + the O_NONBLOCK flag. */
  fcntl(STDIN_FILENO, F_SETFL, oldf | O_NONBLOCK);

  /** Checks if there is a char on the standard terminal. (nonblock). */
  ch = getchar();

  /** Make changes now, without waiting for data to complete. */
  tcsetattr(STDIN_FILENO, TCSANOW, &oldt);

  /** Removes the O_NONBLOCK flag. */
  fcntl(STDIN_FILENO, F_SETFL, oldf);

  /** If any key was hitted, return true. And puts back the pressed key onto
   *  the terminal. */
  if(ch != EOF)
  {
    ungetc(ch, stdin);
    return 1;
  }

  return 0;
}
```

# \[LAB\] Processos Multi-thread e PTHREAD

Uma das ferramentas mais importantes no desenvolvimento de uma aplicação em um sistema Linux embarcados é a utilização de multi-threading. Isto é, realizar os recursos disponíveis pelo kernel Linux \(escalonador, gerenciamento de recuso, ICP e etc\) para realizar o processamento de diversas tarefas simultaneamente.

Nesta atividade, vamos entender os conceitos básicos da criação de uma aplicação multi-threading.

### Utilizando a Biblioteca `PTHREAD`

Nesta primeira implementação vamos realizar a criação de `N_THREADs` threads genéricas e observar seu funcionamento. 

Para declarar uma thread devemos utilizar o tipo `pthread_t` já implementadona biblioteca `PTHREAD`. Esta variável armazenará um ID único que representa a thread criada, isto permite sua manipulação atuando como um handler para a thread, mecanismo similar aos file descriptors já utilizados.

```c
#define N_THREADS 20

pthread_t my_threads[N_THREADS];
```

Para criar, de fato, uma thread no sistema devemos utilizar a função `pthread_create`. Esta função espera como parâmetros o endereço do nosso handler `pthread_t`, um ponteiro para a estrutura de atributos \(caso deseje alterar os atributos padrões\) da thread, a função a ser atrelada a esta thread \(callback\) e por último um quarto parâmetro que representa um parâmetro a ser passado para a função.

O processo de criação da thread resulta em um número inteiro que representa se houve ou não problemas durante a criação da thread.

Para a prática iremos criar dois tipos de thread, estas serão definidas por um índice de criação. Caso o índice em questão seja par, a thread criada será vinculada à dunção `thread_function_1`. Caso o índice seja impar, esta thread será vinculada a uma função `thread_function_2` que recebe como parâmetro o índice, `i`,  atual.

```c
int32_t th_ret;
int32_t i;
	
for(i=0; i < N_THREADS; i++)
{
	if(i%2 == 0)
	{
		th_ret = pthread_create(&my_threads[i], NULL, thread_function_1, NULL);
	}
	else
	{
		th_ret = pthread_create(&my_threads[i], NULL, thread_function_2, i);
	}
}
```

Para encerrar uma thread basta executar a função `pthread_exit` e passar o handler da thread desejada, caso o argumento seja `NULL`, a thread encerrada será a própria que evocou a função.

```c
printf(">> main(): Created %u threads.\n\n", i);

pthread_exit(NULL);
```

Por fim, devemos definir o escopos das funções vinculadas as thread. Na função `thread_function_1` iremos apenas executar um simples `printf` e deletar a thread.

```c
void *thread_function_1(void *p_thread_arg)
{
	printf("Hello Embedded World! I'm a Thr	ead running function 1!\n\n");
	
	pthread_exit(NULL);
}
```

Já para a `thread_function_2` vamos realizar a conversão do nosso parâmetro, passado para a thread. E então, colocar a thread para dormir através do comando `sleep`. Por fim, iremos executar um `printf` com uma mensagem utilizando o argumento convertido e deletar a thread.

```c
void *thread_function_2(void *p_thread_arg)
{
	int32_t p_thread_id = (int32_t) p_thread_arg;

	sleep(2); 
	
	printf("Hello Embedded World! I'm the Thread %d and I'm running function 2!\n\n",p_thread_id);

	pthread_exit(NULL);
}
```

Ao executar o programa devemos observar o efeito da criação das threads, a ordem com que os eventos acontecem e também o impacto da função `sleep`.

```c
/*
 ============================================================================
 Name        : ex04.c
 Author      : gbs
 Version     :
 Copyright   : Your copyright notice
 Description : A simple C program which demonstrates the Pthread library.
 ============================================================================
 */

//==============================================================================
//                              USED INTERFACES
//==============================================================================

#include <pthread.h>   /* The POSIX Threads Library. */
#include <stdint.h>	   /* Standard Int Library.(uint32_t, uint8_t...)*/
#include <stdio.h>	   /* Standard Input/Ouput Library. (printf...)  */
#include <stdlib.h>	   /* General (standard) Library. (EXIT_SUCCESS. */
#include <string.h>    /* String manipulation. (strerror). */
#include <unistd.h>	   /* Complement (flags, constants, definitions..)
									for the POSIX API. */

//==============================================================================
//                        MACROS AND DATATYPE DEFINITIONS
//==============================================================================

/* The number of threads to create. */
#define N_THREADS 20

//==============================================================================
//                     STATIC (PRIVATE) FUNCTION PROTOTYPES
//==============================================================================

/**
 * @brief An example of function to be ran by a thread. Without arguments.
 */
void *thread_function_1(void *p_thread_arg);

/**
 * @brief An example of function to be ran by a thread. With arguments. See the
 * function definition.
 *
 * @param[in] p_thread_arg 		According to the POSIX Library, You should always
 * 							pass a single argument (void *) to the function that
 * 							your new thread will run. If you need more than one
 * 							argument, you must put those in a data structure.
 */
void *thread_function_2(void *p_thread_arg);

//==============================================================================
//                          STATIC GLOBAL VARIABLES
//==============================================================================

//==============================================================================
//                      IMPLEMENTATION OF PUBLIC FUNCTIONS
//==============================================================================

int main(void)
{

	/* The pthread_t data type acts as a handle for a new created thread. It stores
	 * a unique id which allows for manipulating such thread. */
	pthread_t my_threads[N_THREADS];

	int32_t th_ret;
	int32_t i;

	for(i=0; i < N_THREADS; i++)
	{

		/* Just a trick to differ odd and even values of the i variable. */
		if(i%2 == 0)
		{
			/* Attaches the thread_function1 to a new thread when "i" is even.
			 *
			 * The pthread_create function takes 4 parameters:
			 *
			 * <pthread_t *thread_id> - my_threads[i]
			 * This parameter stores a unique thread ID. It is returned from the
			 * pthread_create function call. From the pthread_create man page:
			 * "... this identifier is used to refer to the thread in subsequent
			 * calls to other pthreads (Library) functions".
			 *
			 * <const pthread_attr_t *attributes> - NULL
			 * This structure is used to change
			 * the attributes of the thread creation process. When NULL is passed,
			 * the new thread is created with the default attributes.
			 *
			 * <void *(*thread_function)(void *)> - thread_function_1
			 * The third argument must have a signature of a function that takes a
			 * SINGLE void pointer as argument and returns a void pointer. This is because
			 * there is no way for a start function know what kind of data the developer
			 * wishes to pass into and return. This is the function the created thread
			 * will run.
			 *
			 * <void *arguments> - NULL
			 * the fourth and last parameter is a void pointer and it represents the
			 * arguments of the function passed in as third parameter. It must be "casted"
			 * before and inside the function, when necessary. It is allowed only a single
			 * parameter in the ptrhead_create function, so, if you wish to design a function
			 * with more than one parameter, you should group them into a data structure,for
			 * example. When NULL is used, no arguments are passed to the function.
			 *
			 * */
			th_ret = pthread_create(&my_threads[i], NULL, thread_function_1, NULL);

			if(th_ret) /* Checks and exhibits if an error occurred when creating a new thread. */
			{
				printf("ERROR: Failed to call pthread_create(). Returned error is %d\n", th_ret);
				printf("Code %d= %s\n",th_ret,strerror(th_ret));

				return EXIT_FAILURE;
			}
		}
		else
		{
			/* Attaches the thread_function2 to a new thread when "i" is odd. It is very similar to
			 * the previous process. However, note that in this case, the variable "i" is passed as
			 * an argument to the thread_function_2. */
			th_ret = pthread_create(&my_threads[i], NULL, thread_function_2, (void *)i);

			if (th_ret) /* Checks and exhibits if an error occurred when creating a new thread. */
			{
				printf("ERROR: Failed to call pthread_create(). Returned error is %d\n", th_ret);
				printf("Code %d= %s\n",th_ret,strerror(th_ret));

				return EXIT_FAILURE;
			}
		}
	}

	printf(">> main(): Created %u threads.\n\n", i);

	/* In addition to closing the main program, when the pthread_exit is called by
	 * the Main function, it allows other threads to continue execution, after its
	 * closure. */
	pthread_exit(NULL);
}

//==============================================================================
//                IMPLEMENTATION OF STATIC (PRIVATE) FUNCTIONS
//==============================================================================

void *thread_function_1(void *p_thread_arg)
{
	/* Takes no arguments.*/
	printf("Hello Embedded World! I'm a Thread running function 1!\n\n");

	/* Terminates the calling thread. */
	pthread_exit(NULL);
}

void *thread_function_2(void *p_thread_arg)
{
	/* Casts the void* p_thread_arg argument to int32_t, which is the type of
	 * the argument passed in the previously called pthread_create function. */
	int32_t p_thread_id = (int32_t) p_thread_arg;

	sleep(2); /* Just a 2s sleep, in order to demonstrate that the Linux scheduler
	 	 	 	 does not have a fixed order for scheduling threads and processes.*/

	printf("Hello Embedded World! I'm the Thread %d and I'm running function 2!\n\n",p_thread_id);

	/* Terminates the calling thread. */
	pthread_exit(NULL);
}
```
# \[PROJ\] Sistema de Aquisição de Dados e Telemetria

### Proposta

Para finalizar a etapa de aplicação e também o treinamento, é proposto o projeto de um sistema embarcado para a aquisição de dados e telemetria. 

A proposta inicial para a execução deste projeto, é que o mesmo seja desenvolvido em Linguagem C em uma plataforma embarcada projetada para a aplicação. 

Além disso, é proposta uma arquitetura base para o desenvolvimento do projeto, ela consiste em três threads, sendo duas para aquisição de dados e uma para telemetria. Esta arquitetura é melhor detalhada ao longo deste roteiro.

Os dados serão obtidos de dois sistemas de uma central inercial contendo seis conjuntos de sensores e serão adquiridos pelo nossa plataforma embarcada, ao passo que a mesma deve realizar a tarefa de telemetria via comunicação serial.

Por fim, será desenvolvida uma aplicação gráfica em Qt com o propósito de realizar o monitoramento da telemetria em tempo real. Esta aplicação será desenvolvida para um sistema desktop mas pode ser portada posteriormente para o próprio sistema embarcado.

### Preparação dos Dados

Para a etapa de aquisição de dados, vamos utilizar os dados adquiridos através de dois sistemas. O primeiro é uma central inercial **MDAN**, que fornece os dados de um conjunto de três placas \(X, Y, Z\). Cada placa conta com um acelerômetro e um sensor de temperatura ligado ao seu conversor V/F. Além destes dados de cada placa, são fornecidos também a tensão instantânea de quatro alimentações.

Uma amostra dos dados enviados pelo sistema **MDAN** é apresentados na tabela a seguir:

#### Log de dados do MDAN:

| Cycle | X\_Accel | X\_Temp | X\_VF\_Temp | Y\_Accel | Y\_Temp | Y\_VF\_Temp | Z\_Accel | Z\_Temp | Z\_VF\_Temp | Volt\_R5V | Volt\_5V | Volt\_15V | Volt\_m15V | Time\_ms |
| :--- | :--- | :--- | :--- | :--- | :--- | :--- | :--- | :--- | :--- | :--- | :--- | :--- | :--- | :--- |
| 0 | 0.000804 | 26.145761 | 71.561798 | 0.000618 | 25.852840 | 58.380398 | -0.097774 | 25.608742 | 53.498398 | 4.769714 | 5.008932 | 15.315810 | -15.573580 | 9.998470 |
| 1 | 0.000799 | 26.145761 | 74.979202 | 0.000084 | 25.852840 | 57.892200 | -0.097762 | 25.608742 | 53.986599 | 4.769714 | 5.008932 | 15.315810 | -15.573580 | 9.998470 |
| ... | ... | ... | ... | ... | ... | ... | ... | ... | ... | ... | ... | ... | ... | ... |

Além do sistema **MDAN**, existe também um sistema **GYRO** composto por um conjunto de três girômetros. Este sistema fornece, assim como o **MDAN**, diversos dados entre eles a velocidade angular em cada um dos girômetros, o estado do sensor, sua temperatura e etc.

Uma amostra dos dados enviados pelo sistema **GYRO** é apresentada na tabela a seguir:

#### Log de dados do GYRO:

| Cycle | X\_Gyro\_Status | X\_Gyro\_AngVel | X\_Gyro\_Temp | X\_Gyro\_Count | X\_Gyro\_Ser | Y\_Gyro\_Status | Y\_Gyro\_AngVel | Y\_Gyro\_Temp | Y\_Gyro\_Count | Y\_Gyro\_Ser | Z\_Gyro\_Status | Z\_Gyro\_AngVel | Z\_Gyro\_Temp | Z\_Gyro\_Count | Z\_Gyro\_Ser |
| :--- | :--- | :--- | :--- | :--- | :--- | :--- | :--- | :--- | :--- | :--- | :--- | :--- | :--- | :--- | :--- |
| 0 | 98 | -0.000076 | 36.000000 | 1 | 4 | 99 | 0.000055 | 36.500000 | 1 | 4 | 98 | -0.000008 | 36.000000 | 1 | 4 |
| 1 | 98 | -0.000308 | 36.000000 | 2 | 4 | 99 | -0.000031 | 36.500000 | 2 | 4 | 98 | 0.000034 | 36.000000 | 2 | 4 |
| ... | ... | ... | ... | ... | ... | ... | ... | ... | ... | ... | ... | ... | ... | ... | ... |

Para facilitar a prática durante o treinamento, optou-se por trabalhar com um arquivo de _log_ de dados destas duas unidades. Isto é, adquiriu-se dados de ambos os sistemas e esses dados serão utilizados para o treinamento. 

Este processo é vastamente utilizado para aplicações que não estão em processo de produção, assim como projetos mockados e etc. Como a tarefa de realizar a leitura de um arquivos binário e um arquivo de dispositivo é o mesmo, como visto durante os laboratórios, não haverá nenhum prejuizo didático na abordagem.

Então, ambos os _logs_ foram convertidos da forma apresentada para uma stream de bytes, ou seja, tranformados em arquivos binários. Desta forma, podemos emular com eficiência o processo de comunicação entre nosso sistema embarcado \(RPi\) e as placas **MDAN** e **GYRO**, representados pelos arquivos `mdanbin` e `gyrosbin`.

Para armazenar os dados de ambos os sensores foi fornecido, no código base, um conjunto de estruturas de dados:

A estrutura de dados `mdan_t` é composta por:

* Um contador que armazena o número de leituros \(ciclos\);
* Três acelerômetros, um para cada eixo \(X, Y e Z\);
* Três temperaturas, uma de cada acelerômetro \(X, Y e Z\);
* Três temperaturas, uma de cada V/F \(X, Y e Z\);
* Quatro tensões internas: DC/DC \(5V, 15V, -15V\) e Regulador 5V;
* Uma medida do tempo decorrido da última interrupção.

Ao passo que a estrutura de dados `gyros_t` é composta por:

* Um contador que armazena o número de leituros \(ciclos\);
* Três girômetros, um para cada eixo \(X, Y e Z\);
* Três temperaturas, uma de cada girômetro \(X, Y e Z\);
* Uma medida do tempo decorrido da última interrupção.

Além destas, foi criada também uma estrutura de dados `sensors_t` que representa o pacote de telemetria enviado pela RPi, isto é, um pacote devidademente estruturado contendo os dados de ambos os sensores, um cabeçalho e um CRC.

### Código Base

Para facilitar o desenvolvimento do projeto, foi fornecido um conjunto de arquivos na forma de um código base. O código foi estruturado da seguinte forma:

```text
+Sensors
|
+---+inc
|   |
|   +---+defines.h
|   |
|   +---+structs.h
|   |
|   +---+gyro_task.h
|   |
|   +---+mdan_task.h
|   |
|   +---+telemetry_task.h
|
+---+src
|   |
|   +---+Sensors.c
|   |
|   +---+gyro_task.c
|   |
|   +---+mdan_task.c
|   |
|   +---+telemetry_task.c
|
+---+logs
|   |


```

### Diagrama de Entidades e Arquitetura

<figure>
<img src="/assets/posts/dsle20/dev-4.png" alt="">
</figure>

Para um melhor visualização recomenda-se o downloada do arquivo `sensors_class.pdf` fornecido no link abaixo.

<figure>
<img src="/assets/posts/dsle20/dev-5.png" alt="">
</figure>


Para um melhor visualização recomenda-se o downloads do arquivo `sensors_threads.pdf` fornecido no link abaixo.


