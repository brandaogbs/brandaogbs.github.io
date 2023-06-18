---
layout: post
title:  Embedded Linux Development Course - Workstation (pt. 4) 
date:   2020-03-04 22:57:49 +0000
categories: jekyll update
usemathjax: true
tags: [course, linux, embedded, setup]
description: >-
    Setup do ambiente de trabalho para a execução do curso.
---

# Ambiente de Trabalho

Como mencionado no Capítulo de [Configuração Inicial](https://brandaogbs.gitbook.io/dsle20/configuracao-inicial), ao se desenvolver sistemas Linux embarcados, é fortemente recomendado o uso de uma plataforma de desenvolvimento \(_host_\) também com Linux. 

<figure>
<img src="/assets/posts/dsle20/ws-1.png" alt="">
</figure>

Isto, pois, a grande maioria das ferramentas que existem na comunidade open-source foram projetas para rodar em Linux. Quando existe algum porte ou versão para Windows/macOS, normalmente esse porte foi feito por algum determinado grupo de desenvolvedores e você fica sem suporte dos desenvolvedores oficiais, não recebe atualizações, correções de bugs e etc.

Além disso, lembre-se que o kernel que roda na sua aplicação  é também o que roda na sua máquina, então quando você passa por problemas durante o desenvolvimento, possivelmente a solução é válida para ambos os sistemas. **De forma geral,  usando Linux você aprende Linux.** 

Por estes motivos, durante esse treinamento vamos utilizar a distribuição Ubuntu 16.04 LTS. Porém, ao se desenvolver, fora do curso, deve-se escolher a distribuição que mais agrada e torna o trabalho mais produtivo. 

Uma vez usando Linux você já terá grande parte do suporte que precisa, contudo é recomendado utilizar uma distribução que seja estável o suficiente e não trabalho com as ultimas versões de pacotes disponíveis, por exemplo Debian, Slack, Redhat e etc. Visando um ambiente corporativo, o legal é fechar um sistema operacional LTS, que terá suprote por pelo menos cinco anos da comunidade e partir para o desenvolvimento dos sistemas.

# Sistema Multi-Usuários

Uma das primeiras características que notamos ao começar a trabalhar com sistemas Linux, é o fato deste ser um sistema operacional multi-usuários. Isto significa que existem diferenciações entre os usuários que operam a máquina. Distinguindo o contexto de acesso a determinadas regiões ou diretórios e também certas operações dentro do sistema.

Em especial, existe o usuário _root_ este é o usuário "administrador" do sistema, possuindo acesso privilegiado sobre o sistema. Esse acesso privilegiado, consede ao usuário _root_ o poder de executar operações que necessitem de permissão elevada, tais como: criar um sistema de arquivos, montar uma partição, adicionar e remover um software, configurar rede, operar arquivos em diretórios com privilégio e etc.

Por padrão, o Ubuntu não permite que usuário _root_ faça login no sistema, essa opção é bloqueada mas pode ser alterada, contudo não é uma atitude recomendada. No entanto, em suas configurações padrão, o Ubuntu usa uma política de que o primeiro usuário criado no sistema \(normalmente aquele logo depois da instalação\), recebe a permissão de executar as operações privilegiadas do _root_, através do comando `sudo`.

Para exemplificar a utilização do comando `sudo` vamos realizar a seguinte demonstração. Ao tentar montar uma partição, através do comando `mount`.

```shell
mount /dev/sda2 /mnt/disk_test
```

Recebemos a seguinte mensagem, negando a permissão do nosso usuário:

> mount: only root can do that

Ou seja, para realizar esta operação, é necessário utilizar um usuário com permissão de _root,_ portanto devemos utilizar o comando `sudo`, demonstrando que realmente queremos utilizar este comando com privilégios.

```shell
sudo mount /dev/sda2 /mnt/disk_test
```

> No Ubuntu 16.04,  a senha de _root_ é definida durante a instalação do sistemas. Por padrão, algumas distribuições utilizam como senha a palavra _root_ ou mesmo _toor._ Este tópico será abordado em outro momento do treinamento.

# \[LAB\] Conhecendo o Terminal



Nesta atividade iremos estudar alguns comandos e conceitos básicos da linha de comandos do Linux, necessários para um melhor aproveitamento e entendimento do treinamento.

### Linha de Comando Básico

Nesta atividade iremos estudar os comandos básicos da linha de comandos do Linux.

#### O _shell_

O shell é uma interface de linha de comandos entre o usuário e o sistema operacional. No Ubuntu, ele pode ser acessado pressionando a tecla `Super` e digitando “Terminal” ou pelas teclas de atalho `CTRL+ALT+T`. 

Sua aparência inicial é uma tela preta com um cursor piscando para a entrada de comandos. Dentro desta janela, você pode abrir outras abas e trabalhar nelas simultaneamente, acessando o menu “_File-&gt; Open Tab_” ou pelas teclas de atalho `CTRL+SHIFT+T`. 

> Estude e decore as teclas de atalho! Trabalhando com o _shell_, você será muito mais produtivo!

#### Diretórios e arquivos

Windows e Linux são sistemas operacionais com conceitos totalmente diferentes. Enquanto que no Windows temos diversas árvores de diretório, cada uma associada à um dispositivo \(**C:\**, **D:** e etc\), no Linux temos apenas uma árvore de diretórios “`/`”, chamada de diretório _root_ ou diretório principal. Perceba que inclusive a orientação da barra é diferente.

Outra diferença importante é que o Linux é “case sensitive”, ou seja, diferencia maiúsculas de minúsculas. Portanto, “`Texto.txt`” é diferente de “`texto.txt`”.

Alguns comandos básicos para manipulação de arquivos:

| Comando | Descrição |
| :--- | :--- |
| `cd` | Mudar de diretório |
| `mkdir` | Criar diretório |
| `rmdir` | Remover diretório vazio |
| `rm` | Remover arquivo |
| `rm -R` | Remove diretórios e subdiretórios recursivamente |
| `ls` | Listar arquivos e diretórios |
| `cp` | Copiar arquivo |
| `mv` | Mover/renomear arquivo |
| `cat` | Listar conteúdo do arquivo |

No Linux, enquanto que o diretório “`/`” representa o diretório principal \(raiz\), um ponto “`.`” representa o diretório atual, e dois pontos “`..`” representam o diretório anterior. Exemplos:

Listando o diretório principal:

```text
ls /
```

Listando o diretório atual:

```text
ls .
```

Listando o diretório anterior:

```text
ls ..
```

**Exercício 1**: Entre na pasta de arquivos temporários “`/tmp`”. Crie um diretório “`testedir`” e entre nele. Faça uma cópia do arquivo “`/etc/resolv.conf`” para este diretório. Liste o diretório e o conteúdo deste arquivo. Renomeie este arquivo para “`resolv.txt`”. Liste novamente o conteúdo do arquivo. Apague o arquivo, volte ao diretório “`/tmp`” e apague o diretório “`testedir`”.

> Você pode usar as teclas de seta para cima e para baixo para navegar entre os comandos já digitados. O comandos “history” também exibe os últimos comandos executados. A tecla `TAB` ajuda a preencher de forma inteligente enquanto você esta digitando um comando.

#### Variáveis de ambiente

Todo _shell_ do Linux possui um ambiente de execução com algumas variáveis configuradas. Você pode imprimir estas variáveis com o comando `printenv`.

Um variável importante é o `PATH`, que possui todos os caminhos por onde o _shell_ irá procurar um binário para execução. Aqui é o mesmo conceito usado em máquinas Windows para variáveis de ambiente.

Você pode usar o comando `echo` para imprimir uma variável ambiente:

```text
echo $PATH
```

```text
/home/gbs/bin:/home/gbs/.local/bin:/usr/local/sbin:/usr/local/bin:/usr/sbin:/usr/bin:/sbin:/bin:/usr/games:/usr/local/games:/snap/bin
```

Os valores são separados por dois pontos “`:`”. Neste exemplo, quando você tentar executar uma aplicação na linha de comandos, o _shell_ irá procurar esta aplicação nos diretórios `/usr/sbin`,  `/usr/bin`, `/bin` e  `/sbin`.

Se sua aplicação não estiver em um dos diretórios do `PATH`, você pode executá-la digitando o caminho completo:

```text
/home/user/bin/app
```

Ou então entrar no diretório da aplicação e executar usando “`./`” conforme abaixo:

```text
cd /home/user/bin/
./app
```

Para alterar ou criar uma nova variável de ambiente, você precisa usar o comando `export`:

```text
export VAR=value
```

E para remover você pode usar o comando `unset`, conforme abaixo:

```text
unset VAR
```

**Exercício 2**: Crie, imprima e remova uma variável de ambiente.

#### Editor de Texto

Existem dezenas de editores de texto disponíveis no Linux. Um dos mais usados é o _vi_, ou sua versão mais avançada, o _vim_.

Apesar de altamente produtivo, o _vi_ possui uma curva de aprendizado relativamente grande, o que pode assustar um pouco quem esta começando a aprender Linux. Uma outra solução menos agressiva é o _nano,_ que também possui diversas funcionalidade e permite a edição de arquivos dentro do terminal. Por fim, uma escolha gráfica pode ser o _gedit_.

#### Shell Script

Shell script tem o mesmo conceito de arquivos `.bat` no Windows. Possui uma linguagem de programação própria, e permite automatizar diversas tarefas que de outra forma seriam repetitivas.

Um shell script normalmente tem na primeira linha o nome do programa interpretador, seguido pelos comandos a serem executados. Exemplo:

```bash
#!/bin/bash

mkdir -p /tmp/testedir
cp /etc/resolv.conf /tmp/testedir/
```

Um shell script precisa de permissão para execução. Portanto, após criar um shell script, você precisa dar esta permissão com o comando abaixo:

```bash
chmod u+x script.sh
```

**Exercício 4**: Crie um shell script dentro do diretório `/tmp` para printar uma mensagem no terminal. Execute-o e depois remova-o.

#### Dispositivos

No Linux, boa parte dos dispositivos do sistema são representados através de arquivos, incluindo o hardware, cujo acesso é abstraído através de arquivos de dispositivo.

Ou seja, se uma aplicação quer enviar um byte pela porta serial, ela deve escrever este byte no arquivo correspondente à porta serial.

Os arquivos de dispositivo no Linux ficam no diretório “`/dev`”, que tem a seguinte correspondência com relação aos dispositivos no Windows:

| Tipo | Windows | Linux |
| :--- | :--- | :--- |
| Porta Serial | COM1 | /dev/ttyS0 |
| Porta Paralela | LPT1 | /dev/lp0 |
| HD | C: | /dev/sda1 |
| CDROM | D: | /dev/sr0 |

#### Ponto de montagem

Dispositivos de armazenamento, para serem utilizados, devem ser montados em um diretório do sistema operacional. Este diretório é chamado de ponto de montagem.

Por exemplo, ao inserir o pendrive em uma porta USB, será criado um arquivo de dispositivo \(Ex: `/dev/sdc1`\). Este dispositivo deve ser montado com o comando `mount` em um diretório do sistema para que se possa acessar os arquivos do pendrive:

```bash
sudo mount /dev/sdc1 /mnt/pendrive
```

No exemplo acima, o pendrive estará acessível através do diretório `/mnt/pendrive`. Perceba a necessidade do comao entrar no diretório da ao entrar no diretório dao entrar no diretório da ao entrar no diretório dando `sudo` antes do `mount`, já que o `mount` requer permissões de root para execução.

Após o uso, o pendrive deve ser desmontado com o comando:

```bash
sudo umount /dev/sdc1
```

> CUIDADO! Se você não desmontar, corre o risco de perder as alterações realizadas no pendrive!

O nome atribuído ao seu dispositivo é normalmente dinâmico. Existem algumas técnicas e ferramentas disponíveis que podem nos ajudar a descobrir o nome do arquivo associado ao dispositivo.

Uma delas é usando a ferramenta `fdisk`, conforme abaixo:

```bash
sudo fdisk -l
```

```bash
Disk /dev/sda: 447,1 GiB, 480103981056 bytes, 937703088 sectors
Units: sectors of 1 * 512 = 512 bytes
Sector size (logical/physical): 512 bytes / 512 bytes
I/O size (minimum/optimal): 512 bytes / 512 bytes
Disklabel type: gpt
Disk identifier: 0E18D5E1-5210-47B3-A1FB-73F4C8699FEF

Device         Start       End   Sectors   Size Type
/dev/sda1       2048   1050623   1048576   512M EFI System
/dev/sda2    1050624 935700479 934649856 445,7G Linux filesystem
/dev/sda3  935700480 937701375   2000896   977M Linux swap


Disk /dev/sdb: 7,5 GiB, 8086618112 bytes, 15794176 sectors
Units: sectors of 1 * 512 = 512 bytes
Sector size (logical/physical): 512 bytes / 512 bytes
I/O size (minimum/optimal): 512 bytes / 512 bytes
Disklabel type: dos
Disk identifier: 0xe0e0a313

Device     Boot Start      End  Sectors  Size Id Type
/dev/sdb1        2048 15794175 15792128  7,5G  c W95 FAT32 (LBA)
```

Você pode também listar o arquivo `/proc/partitions`:

```bash
cat /proc/partitions
```

```bash
major minor  #blocks  name

   8        0  468851544 sda
   8        1     524288 sda1
   8        2  467324928 sda2
   8        3    1000448 sda3
   8       16    7897088 sdb
   8       17    7896064 sdb1
```

Outra forma é usando olhando as mensagens do kernel com o comando dmesg. Para isso, conecte o dispositivo, execute o comando `dmesg` e olhe as últimas linhas da saída do comando.

Estas foram atividades básicas para conhecer o shell e o ambiente Linux. É extremamente aconselhável um estudo mais completo usando o Guia Foca Linux ou outro livro qualquer que explique bem o funcionamento de sistemas operacionais baseados em Linux.

* **Guia Foca Linux** – documento “_GuiaFocaLinux.pdf_” disponível em “docs/guides/”. 
* **Canivete suíço do Shell** – documento “_canivete-shell.pdf_” disponível em “docs/guides/”. 
* **Guia de referência do vi** – documento “_vi.pdf_” disponível em “docs/guides/”. 
* **Guia de referência do Shell** – documento “_shell.pdf_” disponível em “docs/guides/”.

# \[LAB\] Configurando o Ambiente de Trabalho

## Configuração Inicial

Devido ao limitado tempo de aula em função da quantidade de conteúdo a ser visto, seria inapropriado realizar o download das diversas ferramentas, códigos fontes, documentos, dentre outros, necessários para a realização das atividade práticas deste treinamento, Assim, todo o material julgado necessário para a realização das atividades foi previamente baixado e compilado em um único tarball.

O objetivo desta atividade é extrair o conteúdo desse tarball, analisá-lo e familiarizar-se com o ambiente de trabalho que será utilizado ao longo de todo o treinamento.

### Configurando o ambiente de trabalho

Faça download e extraia o arquivo `dsle20.tar.xz`:

```bash
cd
wget http://brandaogbs.github.io/linux/dsle20.tar.xz
tar xvf dsle20.tar.xz
```

O comando `cd` é utilizado para a navegação entre os diretórios do Linux, executando-o sem argumentos vamos para a pasta `home` do usuário que estamos logados. O comando `wget` é utilizado para fazer o download de um diretório web, neste caso o repositório com o tarball do curso. Por fim, o comando `tar` é utilizado para a manipulação de arquivos tarball enquanto o primeiro argumento `xvf` é referente a operação de extração-verbose-arquivo, ao passo que o segundo argumento diz respeito ao arquivo tarball.

Quando houver dúvida/curiosidade sobre os comandos utilizados é possível utilizar o comando `man` no terminal do Linux, este retorna o descritivo do comando desejado. Por exemplo: `man cd`, `man wget` e `man tar`. Esta função será utilizada com frequência durante o curso.

Ao finaliza o procedimento de extração, todo o centeúdo do tarball estará disponível na recém criada pasta `dsle20`, dentro do diretório `home` do usuário logado \(_~/dsle20_\). Este diretório possui a seguinte estrutura.

```text
+dsle20
|
+---+dl
|
+---+docs
|   |
|   +---+guides
|   |
|   +---+hardware
|   |
|   +---+training
|
+---+exs
```

O diretório `dl` contém todos os componentes que foram baixados. Durante a realização dos exercícios, os comandos comuns de download \(`wget`\) e clonagem de repositório \(`git clone`\) serão substituídos pelo processo de extrair esses componentes. Cada atividade conterá as informações necessárias para realização de tal procedimento.

O diretório `docs` contém uma documentação de apoio para consulta durante o treinamento. Neste diretório, estão contidos pdfs relacionados ao hardware da RaspberryPi, tabelas de comandos do shell, vi, guia introdutório do Ubuntu e kernel Linux, por exemplo.

O diretório `training` contém a Agenda, Slides e Atividades de Laboratório \(este documento\).

O diretório `exs` será dedicado a realização dos exercícios. A fim de manter uma estrutura organizada, cada exercício será realizado dentro de seu próprio diretório .


