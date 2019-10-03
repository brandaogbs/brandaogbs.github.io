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

