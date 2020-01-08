---
layout: single
title: "Curso Linux"
permalink: /linux/
author_profile: false
  
---

{% include base_path %}


---


Desenvolvimento de Sistemas Linux Embarcados
======

## Introdução

Olá! Esta página destina-se a disponibilizar informações gerais e atualizações relacionadas ao curso Desenvolvimento de Sistemas Linux Embarcados, ministrado no mês de fevereiro de 2020, na Especialização em Sistemas Eletrônicos Embarcados (ESEE) da Universidade Estadual de Londrina (UEL). 

## Requisitos

### Hardware
Como o curso é composto por muitos exercícios práticos (hands-on), os seguintes componentes de hardware são recomendados e de responsabilidade do participante: 

- `Raspberry Pi 3 Model B` -> **Obrigatório**. A placa de desenvolvimento utilizada durante o curso será a Raspberry Pi 3 model B. Essa placa é bem popular e fácil de ser encontrada no Brasil. No Mercado Livre, por exemplo. 

- `Fonte de alimentação` -> **Obrigatório**. Uma fonte micro usb de 5V@2.5A é recomendada para alimentar a RPi3. É um item fácil de ser encontrado na internet. Existem muitos carregadores de celular compatíveis (5V@2.5A). 

- `Cartão MicroSD` -> **Obrigatório**. A Raspberry Pi 3 não possui nenhum armazenamento interno. Portanto é necessário também um cartão Micro SD (8Gb já é suficiente). 

-  `Adaptador USB-Serial (Ttl)` -> **Obrigatório**. Em alguns exercícios práticos, utilizaremos uma comunicação serial entre o computador de desenvolvimento e a Raspberry Pi. Esse tipo de adaptador é bem barato e fácil de encontrar. Link de exemplo.
  
- `Notebook` -> **Obrigatório**. Traga seu notebook para utilizá-lo como ferramenta de desenvolvimento. Por favor, prepare-o com os itens indicados na seção Software, pois durante as aulas não teremos tempo para ficar configurando computadores pessoais.
  
- `Cabo de rede` -> **Obrigatório**. Traga um cabinho de rede básico, pode ser daqueles "amarelinhos" que vem com modems / roteadores. Em alguns exercícios faremos comunicação com a RPi3 via rede e por cabo.
  
- `Adaptador USB-micro SD ou Adaptador SD-micro SD` -> **Opcional**. Quem possuir este tipo de adaptador, para manusear o cartão micro SD pelo notebook, por favor traga.
  
- `Fios/jumpers fêmeas` -> **Opcional**. Quem possuir uns jumpers/fios fêmeas, daqueles usados para fazer conexão entre pinos geralmente, por favor traga. Temos alguns disponíveis no laboratório, mas não sei se serão suficientes.

### Software

Instruções gerais.

Será necessário utilizar um host Linux como ambiente de desenvolvimento. Por ser extremamente popular, estável e fácil de usar, utilizaremos a distribuição Ubuntu 16.04.4 - LTS de 32 bits. Caso você seja um usuário Linux experiente e queira utilizar sua distro de costume, sem problemas.

Baixar e instalar a distribuição Ubuntu 16.04.4 - LTS 32 bits: Download (torrent), Download (http).

Quanto ao método de instalação, VM, Single Boot, Dual Boot (windows+linux), fica a critério do participante. Recomendo que reserve um espaço de aproximadamente 40GB (já com swap). Pois algumas ferramentas de desenvolvimento como toolchain, fontes do kernel e drivers, por exemplo, costuma ocupar bastante espaco.

Durante a instalação:

- Selecionar download de updates enquanto instala o Ubuntu;
    
- Selecionar third party softwares;
    
- Na tela de boas-vindas, criar um nome de usuário e senha.
    
- **Nota Máquina Virtual**: Caso esteja presenciando lags ou alguma lentidão na VM, verifique se o pacote de ferramentas de drivers foi instalado corretamente. Praticamente todos os aplicativos de VM possui um pacote desse tipo, para ser instalado após a criação da VM. Ex: Guest Additions para VirtualBox, VMware Tools para VMware ou Parallels Tools para o Parallels.

Caso não queira utilizar o Gedit, editor de texto padrão do Ubuntu, favor instalar o editor de texto de sua preferência. Ex: Sublime Text, Atom, VsCode, Emacs, Vim, etc... 

Instalar os seguintes pacotes: 

- autoconf
- automake
- bc
- bison
- build-essential
- curl
- cvs
- flex
- gawk
- git
- gperf
- help2man
- libexpat1-dev
- libncurses5-dev
- libtool-bin
- minicom
- patch
- pkg-config
- putty
- python-dev
- texinfo
- subversion
- gperf
- wget

Caso não esteja familiarizado, no Ubuntu um pacote pode ser instalado pelo shell da seguinte maneira: 

```
$ sudo apt-get install nome_do_pacote
```

Para facilitar a instalação dos pacotes sugeridos acima, execute o seguinte comando: 

```
$ sudo apt install autoconf bison flex texinfo automake help2man gawk libtool-bin libncurses5-dev libexpat1-dev python-dev patch curl cvs git bc build-essential subversion gperf unzip pkg-config wget minicom putty
```

Raspbian-strech lite:

- Se possível, baixe e instale a versão Raspbian-strech lite (sem desktop) no seu cartão micro SD. Apesar de gerarmos nosso próprio sistema Linux durante o treinamento, em alguns exercícios iniciais será interessante possuir algo "rodando" na RPi3 para realização de testes.

- Após instalar o raspbian, conecte um teclado USB, um monitor hdmi e ligue a Raspberry. Ela irá carregar o sistema e então as informações de login serão pedidas. Por padrão, o Raspbian possui o usuário "pi" e a senha "raspberry". Após logar no sistema, ative o servidor ssh. Rode o comando abaixo para acessar o menu de configurações da RaspberryPi e acesse a seguinte opção: 5 Interfacing Options -> P2 SSH -> YES

```
$ sudo raspi-config
```

Em seguida, atribua um IP estático para a Raspberry Pi. Para isso, edite o arquivo dhcpcd.conf, localizado no diretório /etc/: 

```
$ sudo nano /etc/dhcpcd.conf
```

Procure pela linha "# Example static IP configuration:" e altere-a da seguinte maneira: 

```
# Example static IP configuration:
#interface eth0
static ip_address=10.1.1.100/24
#static ip6_address=fd51:42f8:caae:d92e::ff/64
static routers=10.1.1.1
... 
```
Após editar o arquivo, salve-o pressionando Ctrl+X, então confirme as modificações pressionando Y e por último, não altere o nome do arquivo, apenas pressione Enter. 

Mais informações em breve ...
