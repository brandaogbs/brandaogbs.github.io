---
layout: post
title:  Embedded Linux Development Course - Architecture (pt. 3) 
date:   2020-03-04 22:57:49 +0000
categories: jekyll update
usemathjax: true
tags: [course, linux, embedded]
description: >-
  Descrição dos principais componentes da arquitetura de um sistema Linux
  embarcado.
---

# Arquitetura

## Arquitetura Geral

A arquitetura geral de um sistema com Linux embarcado consiste nos seguintes elementos:

* **Hardware:** o seu produto ou aplicação.
* **Bootloader:** responsável pela inicialização básica do sistema, carregar e executar o kernel Linux.
* **Kernel Linux:** núcleo do sistema operacional, gerenciamento de memória, I/O, pilha de rede, drivers, fornece serviços para a aplicação do usuário.
* **Bibliotecas padrão C:** interface entre o kernel e as aplicações do usuário \(lembre-se o Linux é escrito em C\).
* **Bibliotecas Gerais e aplicações:** são as bibliotecas de terceiros ou in-house, necessárias para a sua aplicação.
* **Toolchain:** Conjunto de ferramentas necessários para gerar os binários para o target \(hardware\). ****

<figure>
<img src="/assets/posts/dsle20/arch-1.png" alt="">
</figure>

A arquitetura básica de um sistema com Linux embarcado é dotada de dois componentes principais, uma máquina de desenvolvimento _host_ e uma plataforma embarcada, o _target_.

O _host_ é, em geral, um computador pessoal que é utilizado para fazer o desenvolvimento do software/aplicação. Assim, é comum que esta máquina tenha todos os recusos para o desenvolvimento, sendo necessários principalmente a presença de uma toolchain para a programação. Isto é, a presença de um conjunto de ferramentas para fazer a compilação, debugging e todos os processos envolvidos para a geração da aplicação.

Após o desenvolvimento da aplicação no _host_, esta é copiada para dentro da plataforma embarcada, o _target_. Esta aplicação, em geral, utiliza-se de outras bibliotecas próprias ou de terceiros para realizar suas funções. Além disso, para realizar a interação com outras partes do sistema, como chamadas à hardware, é necessário uma API que faça a interface entre o Kernel Linux e a aplicação. Esta API é a biblioteca padrão C.

A biblioteca C fornece mecânismo de comunicação entre a aplicação e o Kernel Linux, principalmente através de chamadas de sistema \(system calls\). Portanto, quando a aplicação deseja acessar ou utilizar algum recurso externo, como acesso a algum hardware, por exemplo. É utilizada uma função da biblioteca padrão C, que em geral abstrai uma chamada de sistema, e então interage com o Kernel. O Kernel Linux, por sua vez, realiza a interação com o device driver necessário para a obtenção do recurso solicitado pela aplicação e então retorna sua resposta via biblioteca C até a aplicação solicitante.

Além dos items já citados, um outro programa é necessário para o funcionamento do _target_, o bootloader. Este é um pequeno programa que realiza a inicialização básica do hardware e é responsável por carregar o Kernel Linux dentro da memória RAM, passando todo o controle do processador para o mesmo.

# Hardware

## O Hardware \(target\)

O target ou hardware é onde de fato roda nossa aplicação embarda. Ele deve conter os itens apresentados na seção anterior \(exceto pela toolchain\). Mas em geral, trata-se da nossa plataforma de desenvolvimento onde vamos rodar nossa aplicação, ler sensores, enviar dados, fazer telemetria e etc.

<figure>
<img src="/assets/posts/dsle20/arch-2.png" alt="">
</figure>

### Processadores

Atualmente o kernel Linux suporta mais de 30 arquiteturas de processadores, como: x86, x86-64, ARM, MIPS, SuperH, Blackfin, Coldfire, PowerPC, SPARC e etc. 

O Linux foi originalmente projetado para trabalhar com processadores que possuiam unidade de gerenciamento de memória \(MMU\). Não sendo projetado para microcontroladores. Contudo, o projeto uClinux foi criado para dar suporte a CPUs sem MMU, tendo algumas limitações, mas ainda assim funcional para casos específicos.

### Memória RAM e Armazenamento

Um sistema bem básico pode funcionar com 8MB de RAM, mas um sistema mais realístico necessita de pelo menos 32MB de RAM. Vai depender muito do tipo e tamanho da aplicação. 

Sistemas muito enxutos podem até rodar com 2MB de armazenamento, as vezes até menos, mas para isso é preciso limitar e enxugar muito o kernel Linux e claro que depende também do tamanho da aplicação.

Ele apresenta suporte para a maioria dos armazenamentos, como: flash NAND e NOR, disco rígido, cartões SD/MMC e eMMC e etc.

### Comunicação

O Linux suporta muitos barramentos comuns em sistemas embarcados: I2C, SPI, CAN, USB, etc. E também os principais protocolos de rede: Ethernet, Wi-Fi, Bluetooth, IPv4, IPv6, TCP, UDP, etc. 

Se o barramento ou protocolo não possuir restrições de licença, é bem provável que esteja implementado no kernel. E isso vale para hardware em geral, se não tiver nenhuma restrição de licença, o driver estará implementado no kernel Linux, pronto para ser utilizado. É por isso que quando você instala uma distruibuição em um PC, é muito comum não precisar de driver nenhum.

### Critérios de seleção

* Certifique-se de que o hardware escolhido seja suportado pelo kernel Linux e por algum dos bootloaders open-source, caso contrário será necessário fazer o porte e este é um trabalho árduo.
* Suporte nas versões oficias dos projetos \(kernel e bootloader\): maior qualidade, novas versões disponíveis.
* A diferença entre um hardware suportado na árvore oficial do kernel e outro não suportado de forma oficial, PODE trazer grandes consequências no custo e tempo de desenvolvimento!

# Toolchain

Nesta etapa iremos abordar as características e conceitos sobre a Toolchain. De forma geral, esta faz parte da máquina de desenvolvimento \(notebook, desktop e etc\), que também chamamos de host. Mas há também a possibilidade da toolchain estar dentro do próprio target, é algo bem menos comum, mas é uma alternativa.

<figure>
<img src="/assets/posts/dsle20/arch-3.png" alt="">
</figure>

Basicamente, o toolchain é o conjunto de ferramentas necessárias para desenvolver seu produto, seja ele um software ou um sistema completo.

Quando instalamos um sistema e este acompanha um certo toolchain para gerar código \(como o Linux por exemplo\), ou instalamos um toolchain por conta própria, este toolchain irá gerar código para a mesma arquitetura da máquina em que ele foi instalado. Por exemplo, se instalamos uma toolchain no nosso processador x86, esta gera binários para nossa própria arquitetura. Assim, recebendo o nome de toolchain nativo, já que gera códigos para sua arquitetura nativa.

No entanto, normalmente em sistemas embarcados não é interessante utilizar um toolchain nativo, por diversos motivos. Por exemplo, seu target pode ter limitações de memória e espaço, a velocidade de compilação no target é muito mais lenta devido a limitação de processamento e etc.

Desta forma, é recomendado a utilização de um cross-compiling toolchain. Este por sua vez, realiza a compilação para outra arquitetura, ou seja, no cenário do nosso computador x86 conseguiriamos gerar código para uma outra plataforma, por exemplo ARM.

<figure>
<img src="/assets/posts/dsle20/arch-4.png" alt="">
</figure>

Basicamento o toolchain é composto por um compilador, assembler e linker. Como por exemplo, o compilador _gcc,_ o assembler e linker da _binutils, a_ biblioteca padrão C, como a _glibc, uclib_ ou alguma de suas variações, os headers do kernel e etc. 

Enfim, essa é uma idéia geral, no decorrer do treinamento iremos explorar cada um desses tópicos mais profundamente, não somente na teoria mas também na prática.

# Bootloader

O bootloader tem como função principal fazer o carregamento de uma aplicação, que normalmente é o kernel do sistema. No nosso caso, o bootloader deve realizar o carregamento do Kernel Linux. 

Este carregamento, é feito de uma memória não volátil. Em seguida, após o carregamento, a aplicação deve ser inicializada segundo os parâmetros do kernel.

**Funções básica do bootloader:**

* Iniciação básica do hardware;
* Carregar uma aplicação \(kernel Linux\) de uma memória não volátil;
* Executar a aplicação.

Bem como outros softwares e firmwares o bootloader apresenta outras funções complementares que foram adicionadas ao longo dos anos, para facilitar usos específicos e aplicações diferentes. Desta forma, o bootloader apresenta um conjunto de funcionalidades extras. Estas funcionalidades variam deste um terminal de comandos para navegação e diagnóstico dos discos e partições, passagem de parâmetros fixos ou temporários para o bootloader e até mesmo a mudança do caminho de busca do kernel, podendo ser uma imagem da rede, por exemplo.

**Funções extras do bootloader:**

* Passagem de parâmetros para o kernel;
* Explorador de arquivos;
* Boot via rede, flash, sd e etc;
* Diagnóstico de hardware.

Os principais bootloader para aplicações x86 são o LILO, Grub e o Syslinux, ao passo que para os sistemas embarcados, em especial para a arquitetura ARM, são o U-Boot, Barebox e o Redoot.

# Kernel Linux

O kernel é carregado e iniciado pelo bootloader, assim que este foi inicializado ele desempenha o papel de iniciar o processador, as memórias e os barramentos de comunicação. Ou seja, o bootloader é responsável por carregar o kernel e este, por sua vez, é responsável por carregar o sistema propriamente dito.

Após a inicialização destes periféricos, o kernel configura a memória virtual do sistema, no caso do kernel Linux esta memoria virual é a memória swap. Em resumo, esta memória virtual é uma área reservada no disco rigido que o sistema utiliza como uma extensão da memória RAM. Desta forma, existe um mapeamento da memória virtual para a RAM e da memória virtual para o disco rígido.

Em seguida, após a configuração e mapeamento da memória virtual, o kernel inicializa todos os drivers para os dispositivos de hardware presentes no sistema, é neste momento que o kernel carrega todos os módulos e drivers do sistema, inclusivel os módulos presentes na nossa aplicação.

Por conseguinte inicializa o escalonador de tarefas. Que é responsável por administrar a ordem de execução dos programas do sistema. Ele cria uma ordem de prioridades e tempos que cada processo tem direito em relação à CPU, e faz esse gerenciamento.

Então, inicializa as threads do kernel, que são processos que auxilliam o kernel no gerenciamento do sistema, algumas dessas threads podem ser vistas rodando no nosso sistema, através do monitoramento de processos do Linux.

Por fim, é montado o sistema de arquivos principal \(rootfs\), que é a partição onde o sistema está instalado e chama o processo `init`. Que é um script de programas que deseja-se inicilizar logo em seguida ao kernel.

**Inicialização básica:**

* Processador;
* Memórias;
* Barramentos de comunicação;
* Memória virtual \(caso o processador tenha MMU\);
* Device Drivers;
* Escalonador;
* Threads do kernel;
* RootFS;
* `init`.

Além da inicialização básica do sistema, o kernel possui outras característica. Ele é responsável por gerenciar todos os processos do sistema operacional, desde processos internos do Linux até processos relacionados à aplicação. Esta tarefa é desempenhada pelo escalonador de processos. Ele também controla o acesso à RAM do sistema e também quaisquer I/O \(entrada/saida\) do sistema. Em resumo, tudo passa ou deve passar pelo kernel.

 Não obstante, no Linux existe também o conceito de Kspace e Uspace. Por exemplo, a memória de swap - memória virtual - é divida entre ks e us. 

O KS é protegido das aplicações do usuário, ou seja, é uma região de memória que não pode ser acessada através da aplicação. Esta região armazena o próprio código do kernel e uma estrutura que descreve toda a memória física. Ao passo que o US é separado pra rodar as aplicações do usuário. Qualquer programa executado pelo usuário, é armazenado no US.

A interface entre o usuário e qualquer dispositivo/componente que seja gerenciado pelo kernel, é realizado através das System Calls, portanto devem ser engatilhadas por uma entidade interna do kernel. Por exemplo se a aplicação do usuário precisa acessar um hardware, ela faz uma system call, então o kernel acessa aquele hardware e envia a resposta para a aplicação do usuário. O KERNEL SPACE é totalmente protegido e isto faz total sentido!

Neste ponto, devemos entender como são representados os periféricos e quaisquer outras entidades no sisitema Linux. Em geral, todas essas entidade de harware, como GPIOS, LEDS, periféricos de comunicação serial e etc que possuem um driver, são representados através de um arquivo no sistema, desta forma, para realizar a interação com um desses componentes é necessário realizar uma interação com um desses arquivos, e isto pode ser realizado através de chamadas de sistema. Além disso, o kernel consegue prover também, um gerenciamento dinâmico dos módulos do sistema.

**Características:**

* Gerenciamento de processos;
* Gerenciamento da RAM e I/O;
* Kernel Space vs. User Space;
* System Calls;
* Arquivos de dispositivos;
* Gerenciamento dinâmico de módulos.

# RootFS

É a partição onde o sistema está instalado. Contém todas as bibliotecas que o kernel necessita para ser executado. 

<figure>
<img src="/assets/posts/dsle20/arch-5.png" alt="">
</figure>

Contém todos os arquivos necessários para inicialização do sistema, inclusive bibliotecas do usuário e aplicações \(programas instalados\).

Dentro do RootFS são encontrados diversos componentes básicos, dentre estes os principais são, todas as bibliotecas do sistema, isto é, as bibliotecas utilizados pelo sistema, pelos programas instalados e mesmo as bilbiotecas de terceiros.

Além das bibliotecas built-in, são presentes dentro do RootFS também, as bibliotecas utilizadas pela aplicação, sejam essas bibliotecas _in-house_ ou bibliotecas proprietárias.

São encontrados dentro do RootFS, além dos arquivos de configuração, os arquivos de inicialização do sistema.

**Componentes básicos:**

* Bibliotecas do sistema;
* Arquivos de inicialização;
* Bibliotecas de aplicação.

O RootFS é comumente montado pelo próprio Kernel Linux, quando este entra em operação, logo após o processo de booting. Portando, não é possível, tão pouco necessário, realizar a montagem deste sistema através do comando `mount`. 

Além disso, é possível, através de passagem de parâmetros do Kernel Linux, estipular onde o RootFS será inicializado. 

Dentre as possibilidades, destacam-se algumas opções interessantes, como a montagem do RootFS juntamente a imagem do Kernel Linux, o que em geral é uma opções que acelerá o processo de boot e de operação, já que o RootFS já estará presente na memórias RAM, contudo há um conjunto de limitações para esta opção. 

Outra possibilidade, é a montagem deste sistema através do protocolo NFS, podendo montar o RootFS na máquina _host_, ao contrário de ser montado no _target_.

# Aplicações Embarcadas

Alguns exemplos de aplicações para sistemas embarcados, que normalmente possuem recursos limitados \(memória, processador, etc\):

* **Dropbear:** é um cliente e servidor SSH que possui aproximadamente 110KB
* **Thttpd:** é um servidor web com aproximadamente 88KB;
* **DIrectFB:** é uma biblioteca gráfica, útil para alguns sistemas embarcados possuem display LCD, possibilita exibir gráficos, desenhos e imagens, com apenas 1.4MB;
* **SQLite:** um sistema de banco de dados com apenas 250KB! 

Essas aplicações apenas ressaltam a eficiência do kernel linux, como é possível rodar um sistema completo e robusto com pouco hardware.

### **Busybox**

Uma outra aplicação, comumente utilizada em sistemas Linux embarcados é a **Busybox.** 

Normalmente, um sistema Linux necessita de um conjunto mínimo de ferramantas para funcionar, como por exemplo o _`init`_, `shell`, alguns utilitários para manipulação de arquivos e configuração do sistema ****e ****etc. 

Estas ferramentas representam, basicamente, todos o ferramental que o Linux Desktop carrega nativamente, através de seus binários que normalmente são fornecidos por diferentes projetos. Desta forma, se para utilizar estas ferramentas em um ambiente embarcado seria necessário sua integração, além do fato de não serem projetadas inicialmente para sistemas embarcados, não fornecem uma grande liberdade em termos de configuração e incluindo diversas funcionalidades que geralmente não usadas em embarcados.

Uma solução para isso é o **Busybox,** que é considerado o canivete suiço dos sistemas LInux embarcados. Ele combina as ferramentas UNIX mais utilizadas, otimizadas por tamanho em um único binário, retirando tudo aquilo desncessário e apresenta estas ferramentas de forma altamente configurável. 

A seguir uma lista de ferramentas contidas no **Busybox.**

> addgroup, adduser, adjtimex, ar, arp, arping, ash, awk, basename, bbconfig, bbsh, brctl, bunzip2, busy- box, bzcat, bzip2, cal, cat, catv, chat, chattr, chcon, chgrp, chmod, chown, chpasswd, chpst, chroot, chrt, chvt, cksum, clear, cmp, comm, cp, cpio, crond, crontab, cryptpw, cttyhack, cut, date, dc, dd, deallocvt, del- group, deluser, depmod, devfsd, df, dhcprelay, diff, dirname, dmesg, dnsd, dos2unix, dpkg, dpkg\_deb, du, dumpkmap, dumpleases, e2fsck, echo, ed, egrep, eject, env, envdir, envuidgid, ether\_wake, expand, expr, fakeidentd, false, fbset, fbsplash, fdflush, fdformat, fdisk, fetchmail, fgrep, find, findfs, fold, free, freeram- disk, fsck, fsck\_minix, ftpget, ftpput, fuser, getenforce, getopt, getsebool, getty, grep, gunzip, gzip, halt, hd, hdparm, head, hexdump, hostid, hostname, httpd, hush, hwclock, id, ifconfig, ifdown, ifenslave, ifup, inetd, init, inotifyd, insmod, install, ip, ipaddr, ipcalc, ipcrm, ipcs, iplink, iproute, iprule, iptunnel, kbd\_mode, kill, killall, killall5, klogd, lash, last, length, less, linux32, linux64, linuxrc, ln, load\_policy, loadfont, loadkmap, logger, login, logname, logread, losetup, lpd, lpq, lpr, ls, lsattr, lsmod, lzmacat, makedevs, man, match- pathcon, md5sum, mdev, mesg, microcom, mkdir, mke2fs, mkfifo, mkfs\_minix, mknod, mkswap, mktemp, modprobe, more, mount, mountpoint, msh, mt, mv, nameif, nc, netstat, nice, nmeter, nohup, nslookup, od, openvt, parse, passwd, patch, pgrep, pidof, ping, ping6, pipe\_progress, pivot\_root, pkill, poweroff, printenv, printf, ps, pscan, pwd, raidautorun, rdate, rdev, readahead, readlink, readprofile, realpath, reboot, renice, reset, resize, restorecon, rm, rmdir, rmmod, route, rpm, rpm2cpio, rtcwake, run\_parts, runcon, runlevel, runsv, runsvdir, rx, script, sed, selinuxenabled, sendmail, seq, sestatus, setarch, setconsole, setenforce, setfiles, setfont, setkeycodes, setlogcons, setsebool, setsid, setuidgid, sh, sha1sum, showkey, slattach, sleep, softlimit, sort, split, start\_stop\_daemon, stat, strings, stty, su, sulogin, sum, sv, svlogd, swapoff, swapon, switch\_root, sync, sysctl, syslogd, tac, tail, tar, taskset, tcpsvd, tee, telnet, telnetd, test, tftp, tftpd, time, top, touch, tr, traceroute, true, tty, ttysize, tune2fs, udhcpc, udhcpd, udpsvd, umount, uname, uncom- press, unexpand, uniq, unix2dos, unlzma, unzip, uptime, usleep, uudecode, uuencode, vconfig, vi, vlock, watch, watchdog, wc, wget, which, who, whoami, xargs, yes, zcat, zcip

O **Busybox** fornece praticamente tudas as ferramentas abaixo em aproximadamente 1MB, e é possível deixa-lo menor, eliminando tudo aquilo que sua aplicação não necessita ou depende. Desta forma, desenvolver sistemas Linux embarcado é muito parecido com brincar de Lego.

# Trabalhando com Linux Embarcado

Quando se trabalha com Sistemas Linux embarcado, normalmente existem três frentes de trabalho e os desenvolvedores estão divididos entre elas:

* **Desenvolvimento de BSP** _**\(Board Support Package\):**_ Porte do kernel e bootloader para determinada arquitetura, desenvolvimento de device drivers para o target e dispositivos de hardware utilizados;
* **Integração do Sistema:** Integra todos os componentes, bootloader, kernel, bibliotecas e aplicações em um sistema Linux embarcado.
* **Desenvolvimento de Aplicações:** Desenvolvimento de aplicações para um sistema Linux embarcado já montado e devidamente configurado.

O foco deste treinamento é **Integração e Desenvolvimento de Aplicações!**

