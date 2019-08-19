---
layout: single
title: "Projeto Integrador 1B -- Lab1"
permalink: /pi/lab1
author_profile: false
  
---

{% include base_path %}


---


Objetivos
======
* Compreender a aplicação básica do Transistor BJT como chave.
* Entender e realizar a montagem de circuitos elétricos com a utilização de relés.
* Utilizar Displays 7-segmentos.
* Compreender o processo de multiplexação e aplica-lo no acionamento de dois Displays 7-segmentos.


Lista de Materiais
======

* Placa de Desenvolvimento Arduino Uno
* 2x Transistor BJT [(BC-548)](http://www.mouser.com/ds/2/149/BC547-190204.pdf) ou similar
* 1x Rele - bobina 6 Vdc, contato NA 127 Vac
* 2x [Displays 7-segmentos](https://e-radionica.com/productdata/LD3361BS.pdf) Catodo Comum
* 9x Resistores de 820 ohms.
* 1x Lâmpada 127 Vac com borne
* 1x Chave
* 1x Diodo [1N4007](https://www.diodes.com/assets/Datasheets/ds28002.pdf)

Instruções Gerais
======

Antes de iniciar este roteiro, e durante a execução do mesmo siga estas recomendações:
* Tenha em mãos o roteiro impresso e os datasheets dos componentes que serão utilizados.
* Use a placa de desenvolvimento Arduino Uno, evite colocar as mãos diretamente nos componentes, sempre segure a placa pelas lateraisde modo a evitar contatos estáticos. 
* Sempre realize as ligações entre o Arduino e o Protoboard com extremo cuidado, atente-se principalmente as ligações de GND e VCC.
* Ao utilizar a montagem com o Rele e a Lâmpada, chame o responsável para verificar antes de ligar o sistema. **Eventual troca de pinos na montagem do Rele são perigosas!**

------------------

Princípio de funcionamento do Rele
======

Reles podem ser vistos como chaves elétricas que utilizam o princípio eletromagnético para abrir e/ou fechar contatos. São muito utilizados quando há a necessidade de acionar uma carga elétrica com corrente e tensão elevada a partir de um sinal digital em baixa tensão. Para exemplificar, seu uso é muito comum em automação residencial, para acionamentos de cargas elétricas ligadas à rede elétrica em tensão 127/220 Vac a partir de sinais de microcontroladores. A figura 1 mostra o digrama de um Rele tradicional com um contato NA (normalmente aberto) e um contato NF (normalmente fechado).

<center>
<br/>
<img src='/images/pi/lab1/rele.png'>
<p>Figura 1-Rele no Estado em Repouso (esquerda) e Estado Ativo do Rele com corrente elétrica sobre a bobina (direita)</p>
</center>

De forma resumida, o Rele possui uma bobina, responsável por “comandar” os contatos de “força”. Normalmente um Rele possui o pino comum, o pino NA (normalmente aberto) e o pino NF (normalmente fechado). Caso não haja corrente elétrica passando sobre a bobina, os contatos “Comum” e “NF” estão curto-circuitados, enquanto o contato NA está desconectado do comum. Se houver uma corrente elétrica adequada sobre a bobina, o contato Comum-NF se abre enquanto o contato Comum-NA se torna um curto-circuito. 

A grande vantagem é que a bobina pode ser acionada, por exemplo, por um sinal de microcontrolador (como será feito no experimento com o Arduino), enquanto que os contatos de força permitem o acionamento de cargas com correntes e tensões da rede elétrica (como com a lâmpadaque será acionada no experimento). O princípio de funcionamento aplicado no acionamento de uma lâmpada a partir de um sinal microcontrolado é apresentado no circuito elétrico da Montagem Experimental I.


O Transistor BJT NPN como chave
======

Outro problema muito comum em eletrônica é que mesmo que a carga e o comando possuam níveis de tensão similares (como, por exemplo, a saída do Arduino para acionar a bobina do Rele explicado anteriormenteonde ambos são 5 V), o dispositivo que deve enviar o sinal para acionar o outro não consegue fornecer corrente suficiente para tal.

No caso do Arduino (ou um microcontrolador qualquer), uma porta digital não possui capacidade de fornecer corrente suficiente para acionar a bobina do Rele e consequentemente o mesmo funcionar corretamente. Portanto, **NÃO** podemos realizar a ligação abaixo:

<center>
<br/>
<img src='/images/pi/lab1/ligacao_errada.png'>
</center>

Efetuar a ligação como na figura anterior pode causar danos aos dispositivos. Desta forma, precisamos adicionar no sistema um semicondutor capaz de fornecer acorrente para a bobina do Rele. A forma mais simples de realizar esta tarefa é a partir de um Transistor BJT como Chave.

O transistor é um dispositivos que se projetado para atuar como chave é capaz de impedir ou permitir a passagem da corrente entre dois de seus terminais (Coletor e Emissor) conforme o sinal da Base (Terceiro Terminal), conforme um diagrama genérico abaixo:

<center>
<br/>
<img src='/images/pi/lab1/transistor.png'>
<p>Figura 2-Transistor BJT NPN como chave</p>
</center>

A figura 3 mostra o detalhamento da figura anterior, caso o resistor da base esteja ligado ao terra, não existe corrente elétrica fluindo em <kbd>Ib</kbd>. Neste cenário podemos simplificar a analisando dizendo que os contatos CE do transistor estão abertos, o que impede a passagem da corrente na carga genérica <kbd>Z</kbd>. Agora, se colocarmos 5V no resistor de base surge uma corrente em <kbd>Ib</kbd>, o que idealmente transforma o contato CE do transistor em um curto circuito fazendo surgir uma corrente elétrica sobre a carga <kbd>Z</kbd>.


<center>
<br/>
<img src='/images/pi/lab1/detalhamento_transistor.png'>
<p>Figura 3-Detalhamento do Circuito da Figura 2 conforme o sinal da base.</p>
</center>

Retornando ao problema do acionamento da bobina do Rele sendo comandada por um sinal de um microcontrolador, podemos utilizar o transistor BJT NPN conforme o diagrama da figura 4. Caso o Pino 1 esteja em 0V, não haverá a corrente <kbd>I</kbd> e o Rele estará desativado. Caso o estado do Pino seja invertido (5 V), o transistor atua como uma chave fechada e a bobina do Rele será energizada.

<center>
<br/>
<img src='/images/pi/lab1/ligacao_bobina.png'>
<p>Figura 4-Acionamento da bobina de um Rele utilizando um sinal de microcontrolador com Transistor NPN</p>
</center>



Display 7-segmentos
======

Uma forma muito simples de mostrar informações numéricas para um usuário em sistemas eletrônicos é a partir do uso de display 7-segmentos. Este é composto por 7 LEDs que conforme a combinação de acionamentos mostram números de 0-9. A figura 5 mostra os dois tipos de display 7-segmentos possívels (Catodo ou Anodo comum).

<center>
<br/>
<img src='/images/pi/lab1/display.png'>
<p>Figura 5-Esquemático de Display 7-segmentos Câtodo comum e Anodo Comum</p>
</center>

Utilizando um display 7-segmentos Catodo comum, podemos ligar ao cada um de seus segmentos a uma porta específica do Arduino. Acionamento corretamente as portas será possível mostrar o número desejado no Display. Por exemplo, para mostrarmos o número ‘3’ devemos acionar os segmentos ‘a’, ‘b’, ‘c’, ‘d’, ‘g’. Isso correponde a colocar em nível lógico alto os Pinos 0, 1, 2, 3 e 6 do Arduino.

<center>
<br/>
<img src='/images/pi/lab1/ligacao_display.png'>
<p>Figura 6-Acionamento de um display Catodo comum utilizando o Arduino</p>
</center>

Montagem Experimental
=====
* [**Introdução**](/pi/lab1)
* [Warm Up](/pi/lab1/00)
* [Projeto 1](/pi/lab1/01)
* [Projeto 2](/pi/lab1/02)
* [Projeto 3](/pi/lab1/03)
* [Desafio](/pi/lab1/04)