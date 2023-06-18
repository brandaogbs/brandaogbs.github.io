---
layout: post
title:  Embedded Linux Development Course - Initial Setup (pt. 1) 
date:   2020-03-02 22:57:49 +0000
categories: jekyll update
usemathjax: true
tags: [linux, embedded, course, setup, rpi]
description: >-
  Material de apoio desenvolvido por Guilherme Brandão da Silva
  (brandaogbs.github.io) para o treinamento do curso Desenvolvimento de Sistemas
  Linux Embarcado.
---

# Desenvolvimento de Sistemas Embarcados Linux

* Este documento é baseado nos materiais de treinamentos disponibilizados pela Embedded Labworks e Bootlin \(Free Electrons\) em: 
  * [https://e-labworks.com/treinamentos/linux/slides](https://e-labworks.com/treinamentos/linux/slides) e
  * [https://bootlin.com/doc/training/embedded-linux/](https://bootlin.com/doc/training/embedded-linux/)
* Este documento é disponibilizado sob a Licença Creative Commons BY-SA 3.0. 
  * [http://creativecommons.org/licenses/by-sa/3.0/legalcode](http://creativecommons.org/licenses/by-sa/3.0/legalcode) 
* Os fontes serão liberados, ao final do curso, sob mesma licença, no link: 
  * [http://brandaogbs.github.io/dsle/slides](http://codebuilding.com.br/uel2018/slides)
* Além das bibliografia gostaria de deixar um agradecimento pessoal ao **`jmscaramal`** pela ajuda e por ceder o material base para esse texto.

## Conteúdo Abordado

* Configuração de um ambiente de desenvolvimento
* Introdução ao kernel Linux
* Arquitetura básica de um Sistema com Linux Embarcado
* Toolchain
* Bootloader
* Kernel Linux
* Módulos do Kernel
* Sistemas de Arquivo
* Ferramentas de Automação para geração de Sistemas Linux
* Ferramenta de Desenvolvimento, Debug e Profilling de Aplicações Linux
* Desenvolvimento de Aplicações \(acesso a hardware\)
* Desenvolvimento de Aplicações \(multi-thread\)

## Pré-Requisitos

* Computador com acesso a Internet
* Placa Raspberry Pi 3 Model B
* Cartão MicroSD \(&gt;8 GB\)
* Fonte de Alimentação 5V@2A
* Adaptador USB-Serial \(TTL\)
* Cabo de Rede \(RJ45\)
* Opcional: Mouse, Teclado e Monitor HDMI e jumpers/cabos.

> Para acompanhar os procedimentos apresentados durante o treinamento, é necessários portar os requisítos obrigatórios presentes nesta seção e seguir as instruções da seção [Configuração da VM](https://brandaogbs.gitbook.io/dsle20/configuracao-inicial/configuracao-da-maquina-virtual) .

# Configuração Inicial
## Configuração do Ambiente de Desenvolvimento
O objetivo desta seção é criar e configurar um ambiente de desenvolvimento para sistemas Linux embarcados que consiga desempenhar todos os papeis necessários para o treinamento. 

Na primeira seção [Configuração da Máquina Virtual](https://brandaogbs.gitbook.io/dsle20/configuracao-inicial/configuracao-da-maquina-virtual) é realizada a instalação e configuração da máquina virtual que será utilizada no treinamento. Ao passo que na seção [Configuração da Plataforma Embarcada](https://brandaogbs.gitbook.io/dsle20/configuracao-inicial/configuracao-da-plataforma-embarcada) é instalado um sistema operacional temporário na placa de desenvolvimento e são realizadas as primeiras configurações do sistema. 

> É fortemente recomendado que você utilize um ambiente Linux para desenvolver sistemas Linux embarcado.

Primeiro, todas as ferramentas que existem por aí da comunidade open-source foram projetas para rodar em Linux. Quando existe algum porte ou versão para Windows/macOS, normalmente esse porte foi feito por algum determinado grupo de desenvolvedores e você fica sem suporte dos desenvolvedores oficiais, não recebe atualizações, correções de bugs e etc.

Além disso, lembre-se que o kernel que roda na sua aplicação  é também o que roda na sua máquina, então quando você passa por problemas durante o desenvolvimento, possivelmente a solução é válida para ambos os sistemas. De forma geral,  usando Linux você aprende Linux.

Desta forma, durante o treinamento será utilizado uma máquina virtual com a distribuição Ubuntu 16.04 como ambiente de desenvolvimento. Assim, formamos um ambiente seguro e completo para o desenvolvimento da aplicação, bem como normalizamos os possíveis problemas que podem ocorrer durante o treinamento, já que todos estaremos com o mesmo sistema, mesmos pacotes e etc.

# Configuração da Máquina Virtual
### Download da Imagem Ubuntu 16.04
Primeiramente vamos realizar o [download](http://releases.ubuntu.com/16.04/) da imagem do Ubuntu 16.04  LTS. Note que há duas versões diferentes da distribuição: a Desktop e a Server. Deve-se realizar o download da versão desktop, não obstante escolhemos a arquitetura do processador da nossa máquina, **32bits**.

Alguns fatos a serem notados: a terminologia LTS se refere a distribuições _Long Term Support._ Ou seja, são distribuições que apresentam suporte extendido \(cinco anos\). Além disso, essa distribuição é a 16.04, o primeiro número se refere ao ano de lançamento e no caso específico do Ubuntu, existem versões .04 e .10, que denotam a época do ano que foram lançadas. O Ubuntu realiza lançamentos em Abril e Outubro \(04 e 10\).

Apesar desta versão ser relativiamente antiga \(2016/1\) ainda esta dentro do suporte. Esta é também, uma das distribuições mais utilizadas, ainda nos tempos de hoje, possuindo assim diversas threads para solução de problemas na comunidade e suporte a diversas ferramentas.

### Download do Virtualbox
Para facilitar a configuração do ambiente de desenvolvimento, não iremos realizar a instalação imediata do Ubuntu nas nossas máquinas através de formatação ou dual-boot. Uma solução menos drástica é a instalação de uma Máquina Virtual. Está é uma forma de realizar a instalação de um sistema operacional de forma virtual no computador. 

Com esse objetivo, vamos utilizar a VirtualBox para realizar a virtualização do Ubuntu. Ele permite a instalação e utilização de um sistema operacional dentro de outro, assim como seus respectivos softwares, como dois ou mais computadores independentes, mas compartilhando fisicamente o mesmo hardware. O VirtualBox pode ser instalado em vários sistemas operacionais hospedeiros, incluindo: Linux, macOS, Windows, Solaris e OpenSolaris.

Primeiramente devemos realizar o [download](https://www.virtualbox.org/wiki/Downloads) da VirtualBox, nesta etapa deve-se escolher qual é o sistema host da nossa máquina, qual sistema esta atualmente rodando no seu computador. Por exemplo, caso seja o Windows 64bits, clicar no link indicado para download da versão do VirtualBox para Windows.

> Aloque **2048MB** de memória RAM, **128MB** de memória de vídeo, **40GB** de armazenamento para a máquina virtual e **2 núcleos** do processador, essas configurações são obtidas através do painel de configuração do VirtualBox, acessado em _Setting&gt;System_ e _Setting&gt;Video._

### Configuração da VM e Instalação da Distribuição
Clique no arquivo baixado \(instalador do VirtualBox\) para executá-lo e iniciar a instalação**.** Uma vez que a instalação tenha sido iniciada clique em Next. Em seguida, você estará pronto para instalar o VirtualBox pressionando Install e por fim, quando a instalação for concluida é só finalizar o instalador através do Finish.

> Pode ser que as posições ou títulos das opções/menus estejam um pouco diferentes dos comentados durante a instalação, isto varia com as versões e sistemas.

> Instale preferencialmente na **Língua Inglesa**, pois foi a versão utilizada para a criação do treinamento.
Quando o VirtualBox for iniciado, clique em _New_ no canto superior esquerdo ****e em seguida em _Next_. Nesta etapa, vamos inserir as informações do sistema que desejamos instalar \(Ubuntu 16.04\). Em seguida, será necessário configurar a quantidade de memória RAM pra operação da máquina virtual e também o armazenamento.

Finalizando a configuração da máquina virtual, será necessário a instalação do Ubuntu 16.04. Para tal, basta selecionar o diretório onde a imagem foi baixada \(conforme apresentado na seção anterior\) e realizar a instalação. A instalação é simples, não requer nenhum comentário adicional, apenas seguir os passos indicados durante a instalação.

### Configuração Inicial da Máquina
Nesta etapa, será realizada a configuração básica da VM para atender as necessidades do treinamento. Primeiramente devemos realizar o download de alguns módulos e ferramentas para o desenvolvimento da aplicação embarcada. Para tal, é necessário configurar a VM para acessar a internet.

> Para continuar com a configuração certifique-se que seu computador tem conexão com a Internet. Além disso, habilite as opções: "_Download updates while installing Ubuntu_" e "_Install third-party software for graphics and..._ " durante a instalação.

#### Estabelecendo  Comunicação com a Internet
Abra o Virtualbox com o Ubuntu 16.04 e abra o navegador Firefox. Há duas formas de fazer isso, ou acesse o menu lateral direito e clique no atalho do navegador. Ou abra o _Dash_ com o botão `Super` em seguida digite Firefox e pressione `Enter`.

> Pressionando a tecla `Super` do teclado, irá aparecer uma tabela de atalhos do Ubuntu 16.04.

Tente acessar algum site, o navegador deve informar que você não possui conexão com a Internet. Caso contrário, pode avançar para próxima seção.

Outra forma de verificar se há conexão com a Internet é através do ping de um domínio que esteja online na internet. Para tal, abra o terminal do Linux `Ctrl+Alt+T` \(ou digite _Terminal_ na busca da _Dash_\),  digite a seguinte linha de comando:

```shell
ping brandaogbs.github.io
```

Caso a resposta seja a confirmação do enviou e recebimento dos pacotes, algo como:

```shell
PING brandaogbs.github.io (185.199.109.153) 56(84) bytes of data.
64 bytes from 185.199.109.153: icmp_seq=1 ttl=61 time=11.8 ms
64 bytes from 185.199.109.153: icmp_seq=2 ttl=61 time=12.0 ms
64 bytes from 185.199.109.153: icmp_seq=3 ttl=61 time=12.2 ms
64 bytes from 185.199.109.153: icmp_seq=4 ttl=61 time=16.3 ms
64 bytes from 185.199.109.153: icmp_seq=5 ttl=61 time=13.3 ms
```

Significa que tudo ocorreu conforme o esperado e a máquina virtual esta conectada à Internet.

Caso contrário, para estabelecer a comunicação com a Internet na nossa VM, é necessário configurar o adaptador e a rede tanto no Virtualbox quanto no Ubuntu 16.04.

Então, na aba superior do Virtualbox abra o menu _Settings_ e entre na seção _Network_ no menu lateral direito. Abrindo a seção _Network_ deve aparecer algumas abas de possíveis adaptadores de rede. Clique no _Adapter1_ e em _Attached To_ selecione a opção _NAT_.

Agora no Ubuntu, acesse a _Dash_ e pesquise por _Network_ abra este aplicativo. Na seção Ethernet desligue o adaptador de rede e ligue-o novamente. Após isto, tente novamente a conexão com um site no Firefox.

#### Update e Download de Pacotes Essenciais

Para realizar o update do repositório de downloads do Ubuntu:

```shell
sudo apt-get update
```

Então, baixe os seguintes pacotes

|  |  |  |  |  |  |
| :--- | :--- | :--- | :--- | :--- | :--- |
| autoconf | build-essential | gawk | texinfo | libexpat1-dev | path |
| automake | curl | git | subversion | libncurses5-dev | pkg-config |
| bc | cvs | gperf | wget | libtool-bin | putty |
| bison | flex | help2man | python-dev | minicom |  |

Caso não esteja familiarizado, no Ubuntu um pacote pode ser instalado pelo shell da seguinte maneira:

```shell
sudo apt-get install nome_do_pacote
```

Para facilitar a instalação dos pacotes sugeridos acima, execute o seguinte comando:

```shell
sudo apt install autoconf bison flex texinfo automake help2man gawk libtool-bin libncurses5-dev libexpat1-dev python-dev patch curl cvs git bc build-essential subversion gperf unzip pkg-config wget minicom putty
```

### Configuração de Rede Local

Para obter uma conexão entre a máquina host e a plataforma embarcada, devemos estabelecer uma conexão via SSH entre ambos, a forma mais trivial de se fazer isto é via uma rede física. Portanto, é necessário configurar um IP estático no computador e também na RPi. 

Como estamos utilizando uma máquina virtual sob um outro sistema operacional uma das formas de se fazer essa configuração é, configurar um IP estático no SO padrão Windows, macOS ou Linux e configurar a máquina virtual como conexão _NAT_ e atribuir IP dinâmico pra ela. 

Vou exemplificar como configurar um IP estático no computado com Windows 10 e Ubuntu 16.04, contudo o processo é bem similar a outro sistema operacional, faça de acordo com o seu.

> Essa configuração utilizando IP fixo no _host_ e **NAT** no _guest_ da VM não é obrigatório, fique a vontade para montar a sua conexão da forma que achar melhor. Na VM por exemplo, há a opção de criar o dispositivo como **bridge**, faça como achar melhor. O único requisito é que a VM tenha conexão via Ethernet com a RPi.

#### IP Estático \(Windows10\)

Acesse as configurações do adaptador de rede: _Control Panel &gt; Network and Internet &gt; Network Connection &gt; Networking_. Em seguida, crie um novo adaptador de rede ou modifique a rede _Ethernet_ existente. Botão direito na conexão _Ethernet &gt; Properties &gt; Protocolo IPV4 \(TCP/IPv4\)_. Por fim, habilite a opção de IP Fixo e atribua os seguintes parâmetros:

| Address | Netmask | Gateway |
| :--- | :--- | :--- |
| 10.1.1.101 | 255.255.255.0 | 10.1.1.1 |

Ao fazer isto, sua conexão tera apenas o IP fixo configurado, então será necessário desfazer estas modificações para retornar a sua configuração padrão. Utilize esta configuração somente quando for se comunicar com a Raspberry Pi.

#### IP Estático \(Ubuntu 16.04\)

No _Network Connections_ é possível ver duas divisões uma referente as conexões de Ethernet e outra para as WiFi. Para criar uma nova rede clique em _Add_ e em seguida escolha o tipo de conexão desejada

Para configurar a rede no Ubuntu, devemos acessar o painel de configuração de rede. Acessando a _Dash_ \(botão `Super`\) basta pesquisar pelo termo _Network_ e __abrir a o aplicativo _Network Connections._ Ou podemos utilizar o icone de conexão no canto superior direito. 

Portanto em Network Connections, clicamos em _Add e_ escolhemos na caixa de seleção a opção _Ethernet_. Escolhar um nome para a conexão, por exemplo RPi e em seguida clique na opção _IPV4 Settings_.

Nesta aba é feito a configuração dos IPs e do DHCP, portanto como desejamos obter uma rede local com a placa de desenvolvimento, vamos escolher o _Method Manual_ e então configuramos nossa rede.

| Address | Netmask | Gateway |
| :--- | :--- | :--- |
| 10.1.1.101 | 255.255.255.0 | 10.1.1.1 |

Por fim basta salvar a rede, na próxima seção iremos configurar a nossa plataforma embarcada e aonal dessa configuração, devemos obter um canal de comunicação via SSH entre nossa máquina e a RPi.

### Instalações Adicionais

Caso esteja presenciando lags ou alguma lentidão na VM, verifique se o pacote de ferramentas de drivers foi instalado corretamente. Praticamente todos os aplicativos de VM possui um pacote desse tipo, para ser instalado após a criação da VM. Ex: **Guest Additions para VirtualBox**, VMware Tools para VMware ou Parallels Tools para o Parallels.

Para instalar esta extensão no VirtualBox, basta baixar o [Extention Pack](https://www.virtualbox.org/wiki/Downloads) no site oficial do projeto. É necessário baixar a versão correta do Extention Pack de acordo com a versão do VirtualBox instalado.

Em seguida, basta instalar o arquivo baixado e então abrir o VirtualBox e incialize o Ubuntu. No menu superior do VirtualBox clique em _Devices&gt;Insert Guest Addicition CD Image._

Opcionalmente, outro aplicativo que pode ser útil é o `caffeine-indicator` que é utilizado para evitar que o sistema, no caso o Ubuntu, durma ou entre em hibernação. Para fazer download basta executar o comando, lembre-se que este aplicativo é opcional:

```shell
sudo apt-get install caffeine
```

E então busque pelo aplicativo `caffeine-indicator` na _Dash_ do Ubuntu, irá inicializar um ícone de um copo de café no menu superior do Ubuntu, basta clica e ativar o aplicativo.


# Configuração da Plataforma Embarcada

## Configuração do Ambiente Embarcado

Nesta etapa vamos realizar a configuração inicial do nosso sistema embarcado. Para tal, vamos instalar um sistema operacional da comunidade do Raspberry Pi. Este é um sistema completo, e será utilizado nas primeiras atividades do treinamento. Contudo, ao longo do treinamento realizaremos a montagem e configuração de um sistema operacional para aplicações reais.

### Download do Raspian Stretch Lite

Faça o download do [Raspian-Buster Lite](https://www.raspberrypi.org/downloads/raspbian/) \(versão sem desktop\) e instale-o em um cartão microSD. Para realizar a gravação dele no cartão SD, recomenda-se a utilização do software [Etcher](https://www.balena.io/etcher/).

O Etcher é uma ferramenta gráfica multiplataforma para gravação de imagens \(sistema operacional no nosso caso\) em outras unidades. 

Primeiramente, faça o download do Raspbian-Stretch Lite e do Etcher, então instale o Etcher em seu computador e conecte o cartão microSD no mesmo. Abra o Etcher e selecione o arquivo da imagem do Raspbian \(.img ou .zip\) em seu computador. Em seguida, selecione a unidade do cartão microSD onde deve ser gravado o Raspian e aperte em _Flash!_ para iniciar a gravação da imagem no cartão.

Se estiver utilizando o Ubuntu ou outro sistema Linux, talvez seja necessário instalar o `zenity`. Mais informações sobre a gravação do microSD para diversas plataformas podem ser vistas em:

* [Windows](https://www.raspberrypi.org/documentation/installation/installing-images/windows.md)
* [Linux](https://www.raspberrypi.org/documentation/installation/installing-images/linux.md)
* [MacOS](https://www.raspberrypi.org/documentation/installation/installing-images/mac.md)
* [ChromeOS](https://www.raspberrypi.org/documentation/installation/installing-images/chromeos.md)

### Configuração de Rede e SSH

> Esta seção é destinada a configuração para o setup que possui um **Monitor HDMI** e um **Teclado USB**. Caso não possua esse items utilize a seção [Configuração de Rede e SSH \(headless\)](https://brandaogbs.gitbook.io/dsle20/configuracao-inicial/configuracao-da-plataforma-embarcada#configuracao-de-rede-e-ssh-headless).

Após instalar o _Raspian-Stretch Lite,_ conecte um teclado USB e um monitor HDMI na RPi, e então ligue-a. Ela irá carregar o sistema e então as informações de login serão pedidas. Por padrão, o Raspbian possui o usuário  `pi` e a senha `raspberry`.

 Após logar no sistema, ative o servidor _ssh_. Para tal, acesse o menu de configurações da RPi, este é realizado através do comando:

```shell
sudo raspi-config
```

Rode o comando acima para acessar o menu de configurações e acesse a seguinte opção:  _5 Interfacing Options_ -&gt; _P2 SSH_ -&gt; _YES._

Em seguida, atribua um IP estático para a RPi. Para isso, edite o arquivo `dhcpcd.conf`, localizado no diretório `/etc/`:

```shell
sudo nano /etc/dhcpcd.conf
```

Este comando invoca o editor de texto _nano_ para a edição do arquivo. Então, procure pela linha "_Example static IP configuration_" e faça a seguinte edição:

```shell
# Example static IP configuration:
#interface eth0
static ip_address=10.1.1.100/24
#static ip6_address=fd51:42f8:caae:d92e::ff/64
static routers=10.1.1.1

[..] 
```

Após editar o arquivo, salve-o pressionando `Ctrl+X`, então confirme as modificações pressionando `Y` e por último, não altere o nome do arquivo, apenas pressione `Enter`.

Esta edição possibilita a retenção de um IP estático para a RPi \(10.1.1.100\) e coloca como gateway o IP \(10.1.1.1\). Assim, será possível estabelecer uma comunicação entre a RPi e o nosso computador _host_ via _ssh._

### Configuração de Rede e SSH \(headless\)

Esta seção é destinada a configuração sem os periféricos de Monitor e Teclado USB. O processo é praticamente o mesmo da seção anterior, porém iremos fazer essas configurações diretamente no cartão SD evitando o uso dos periféricos externos.

Primeiramente grave a imagem do Raspbian Strech Lite normalmente no cartão SD, utilizando o Etcher. Após a gravação, serão criadas duas partições, a `boot` e a `rootfs`. 

Para habilitar a comunicação via SSH, abra a partição de `boot` no seu computador e crie um arquivo chamado `ssh`, utilize letras minúsculas e não adicione nenhuma extensão ao arquivo. Este arquivo sinaliza que durante o processo de boot da RPi é desejável que a comunicação SSH seja disponibilizada, equivalente ao processo da seção anterior utilizando o menu de configurações da RPi.

Em seguida, é necessário realizar a configuração da rede com IP fixo na RPi. Para tal, abra a partição `rootfs` e então econtre o arquivo `dhcpcd.conf` dentro do diretório `etc`. Talvez você precise de permissão para editar este arquivo, então entre com previlégios de administrador no caso do Windows ou no Linux, utilize o comando sudo, para ganhar previlégio.

Então, procure pela linha "_Example static IP configuration_" e faça a seguinte edição:

```shell
# Example static IP configuration:
#interface eth0
static ip_address=10.1.1.100/24
#static ip6_address=fd51:42f8:caae:d92e::ff/64
static routers=10.1.1.1

[..] 
```

Pronto, basta salvar o arquivo e remover o dispositivo.

### Testando a Comunicação via __SSH

Para verificar se a configuração foi feita corretamente, tanto da máquina virtual quanto da RPi, basta conectar o conector RJ45 do cabo ethernet na RPi e no seu computador. Selecione a rede Ethernet no seu computador, de forma a se conectar com o cabo recém inserido.

Em seguida, ligue a placa a fonte de alimentação e abra o _Terminal_ no Ubuntu. Com o terminal aberto, iremos tentar realizar uma conexão entre o Ubuntu e a RPi através do programa `ssh`. Basta digitar o seguinte comando:

```shell
ssh pi@10.1.1.100
```

Isto é, desejamos nos conectar via SSH a um usuário chamado **pi** no endereço 10.1.1.100. Então, basta digitar a senha do usuário, que no caso do Raspbian é por padrão a senha **raspberry.** Então deveremos ter acesso a nossa RPi.

Caso ao tentar se conectar apareça um erro tal como:

```bash
gbs@core:~$ ssh pi@10.1.1.100
@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
@    WARNING: REMOTE HOST IDENTIFICATION HAS CHANGED!     @
@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
IT IS POSSIBLE THAT SOMEONE IS DOING SOMETHING NASTY!
Someone could be eavesdropping on you right now (man-in-the-middle attack)!
It is also possible that a host key has just been changed.
The fingerprint for the ECDSA key sent by the remote host is
SHA256:MfETDZ6CV+lZY7cjQhK57JT4nF+pcYTtjISd+iLN+nw.
Please contact your system administrator.
Add correct host key in /home/gbs/.ssh/known_hosts to get rid of this message.
Offending ECDSA key in /home/gbs/.ssh/known_hosts:1
  remove with:
  ssh-keygen -f "/home/gbs/.ssh/known_hosts" -R 10.1.1.100
ECDSA host key for 10.1.1.100 has changed and you have requested strict checking.
Host key verification failed.

```

Significa que já há um histórico de comunicação estabelecido neste target e então basta limpar o arquivo através do comando:

```bash
  ssh-keygen -f "/home/gbs/.ssh/known_hosts" -R 10.1.1.100
```

> Note que **gbs** é o meu nome de usuário, você deve adequar o comando ao seu nome de usuário. Ao longo de todo o treinamento utilizarei ele como exemplo nos comando, mas fique atento para realizar a modificação para atender ao seu sistema, o mesmo para os arquivos e diretórios.

Então basta digitar _yes_ e teremos acesso a nossa RPi.

```bash
gbs@core:~$ ssh pi@10.1.1.100
pi@10.1.1.100's password: 
Linux raspberrypi 4.19.75-v7+ #1270 SMP Tue Sep 24 18:45:11 BST 2019 armv7l

The programs included with the Debian GNU/Linux system are free software;
the exact distribution terms for each program are described in the
individual files in /usr/share/doc/*/copyright.

Debian GNU/Linux comes with ABSOLUTELY NO WARRANTY, to the extent
permitted by applicable law.
Last login: Thu Sep 26 01:25:03 2019 from 10.1.1.101

SSH is enabled and the default password for the 'pi' user has not been changed.
This is a security risk - please login as the 'pi' user and type 'passwd' to set a new password.

pi@raspberrypi:~ $ 
```

