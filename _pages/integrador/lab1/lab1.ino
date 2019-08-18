/**
  ******************************************************************************
  * @file    lab1.ino
  * @brief   Experimento de acionamento de display 7seg,
  *          transistors como chave e acionamento de rele.
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
void debugLD();
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
    // #5. TODO: Inserir a funcao que pisca o LD13
    setDisplayCountdown();
}


// #4. TODO: Fazer cabecalho da funcao que pisca o LD13
/**
  * @brief 
  * @param  
  * @retval 
  */
void debugLD(int tempo_ms)
{
    
    // 3#. TODO: Implementar uma funcao que pisque o LD13
    //      conforme o tempo_ms.
    //      Utilize a funcao 'delay()'
}


/**
  * @brief  Realiza o acionamento do display 7seg conforme a entrada.
  * @param  digit: um inteiro de 0-9.
  * @retval None
  */
void setDisplayDigit(int digit)
{
    // 7#. TODO: Implemente a função setDisplayDigit
}

/**
  * @brief  Desliga individualmente todos os LEDs 
  *         do display 7seg
  * @param  None
  * @retval None
  */
void setDisplayOff()
{
    // 8#. TODO: Implemente a cao setDisplayOff()
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
