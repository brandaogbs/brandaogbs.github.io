/**
  ******************************************************************************
  * @file    lab1.ino
  * @brief   Experimento de acionamento de rele, transistor como
  *          chave e display 7 segmentos.
  * @authors 
  ******************************************************************************
  */

/* Includes ------------------------------------------------------------------*/
 #include <Arduino.h>

/* Defines -------------------------------------------------------------------*/

// #1.  TODO: Defina constante de tempo para ser utilizada no delay em msm 
#define DELAY_MS 1

#define PIN_BUTTON  3

// #1.  TODO: Defina a constante do pino do LED13

#define PIN_A 5
#define PIN_B 6
#define PIN_C 7
#define PIN_D 8
#define PIN_E 9
#define PIN_F 10
#define PIN_G 11

/* Private variables ---------------------------------------------------------*/

/* Private function prototypes -----------------------------------------------*/
// Debug
void debugLD();

// Botao
int isButtonPressed();

// Display
void setDisplayOn();
void setDisplayOff();
void setDisplayDigit(int digit);

/* Private user code ---------------------------------------------------------*/

/**
  * @brief  Inicializacao dos perifericos e das 
  *         entradas e saidas utilizadas.
  * @param  None
  * @retval None
  */
void setup() 
{  
  // 2#. TODO: Inicializar o LD13    

  pinMode(PIN_A, OUTPUT);
  pinMode(PIN_B, OUTPUT);
  pinMode(PIN_C, OUTPUT);
  pinMode(PIN_D, OUTPUT);
  pinMode(PIN_E, OUTPUT);
  pinMode(PIN_F, OUTPUT);
  pinMode(PIN_G, OUTPUT);

}

/**
  * @brief Loop embarcado.
  * @param  None
  * @retval None
  */
void loop() 
{
    debugLD(DELAY_MS);
    setDisplayCount();
}


// #3. TODO: Fazer cabecalho da funcao que pisca o LD13
/**
  * @brief  O que essa função faz?
  * @param  Quais os parametros de entrada?
  * @retval Qual o retorno?
  */
void debugLD(int delay_ms)
{
    // 4#. TODO: Implementar uma funcao que pisque o LD13
    //      conforme o tempo_ms.
    //      Utilize a funcao 'delay()'
}


/**
  * @brief  Verifica se o botao esta 
  *         pressionado
  * @param  None
  * @retval int: estado do botao 
  *              1- pressionado 
  *              0- caso contrario
  */
int isButtonPressed()
{
    return 0;
}


/**
  * @brief  Realiza o acionamento do display 7seg conforme a entrada.
  * @param  digit: um inteiro de 0-9.
  * @retval None
  */
void setDisplayDigit(int digit)
{
    if(digit!=1 && digit != 4)
    digitalWrite(PIN_A,HIGH);

    if(digit != 5 && digit != 6)
    digitalWrite(PIN_B,HIGH);

    if(digit !=2)
    digitalWrite(PIN_C,HIGH);

    if(digit != 1 && digit !=4 && digit !=7)
    digitalWrite(PIN_D,HIGH);

    if(digit == 2 || digit ==6 || digit == 8 || digit==0)
    digitalWrite(PIN_E,HIGH);

    if(digit != 1 && digit !=2 && digit!=3 && digit !=7)
    digitalWrite(PIN_F,HIGH);

    if (digit!=0 && digit!=1 && digit !=7)
    digitalWrite(PIN_G,HIGH);
}

/**
  * @brief  Desliga individualmente todos os LEDs 
  *         do display 7seg
  * @param  None
  * @retval None
  */
void setDisplayOff()
{
}

/**
  * @brief  Realiza o acionamento do display
  *         de forma a exibir uma contagem
  *         crescente de 0-9
  * @param  None
  * @retval None
  */
void setDisplayCount()
{
    int i;
    for(i=0; i>=9; i++)
    {
        setDisplayDigit(i);
        delay(DELAY_MS);
        setDisplayOff();
    }
}
