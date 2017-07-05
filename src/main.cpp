/**
******************************************************************************
* @file    main.cpp
* @author  Kleber Lima da Silva (kleber@ioton.cc)
* @version V0.0.1
* @date    05-Julho-2017
* @brief   Programa de exemplo do Robô TON-BOT no modo seguidor de linha.
******************************************************************************
* @attention
*
* COPYRIGHT(c) 2017 IOTON Technology
*
* Licensed under the Apache License, Version 2.0 (the "License");
* you may not use this file except in compliance with the License.
* You may obtain a copy of the License at
*
*     http://www.apache.org/licenses/LICENSE-2.0
*
* Unless required by applicable law or agreed to in writing, software
* distributed under the License is distributed on an "AS IS" BASIS,
* WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
* See the License for the specific language governing permissions and
* limitations under the License.
******************************************************************************
*/

/* Includes ------------------------------------------------------------------*/
#include "main.h"

/** @addtogroup Seguidor de linha TON-BOT
 * @{
 */

/* Variáveis privadas --------------------------------------------------------*/


/* Funções Privadas ----------------------------------------------------------*/

/**
 * @brief  Programa Principal
 * @param  Nenhum
 * @retval Nenhum
 */
int main(void)
{
  const float KP = 0.008, PWM_MEDIO = 0.3;
  int32_t erro = 0, erro_anterior = 0;
  float MV = 0;

  /* Ligue o TON com o botão USER pressionado para indicar o estado da bateria */
  if (ton.USERisPressed())
  {
    /* Necessário pressionar o botão RESET voltar ao modo normal */
    ton.batteryStatus();
  }

  /* Inicialização do robô para seguir linha preta (pista branca) */
  ton.setLED(GREEN);
  initTonBot(PRETA);

  /* Inicio do programa ------------------------------------------------------*/
  /* Aguarda o botão USER ser pressionado para ligar o robô */
  while(!ton.USERisPressed())
  {
    ton.toggleLED(RED);
    wait_ms(100);
  }
  wait(1);
  ton.setLED(BLUE);
  beeps(3, 100, 50);


  /* LOOP principal ----------------------------------------------------------*/
  while (1)
  {
    /* Verifica a leitura dos sensores */
    erro = getSensoresLinha();
    if (erro == INFINITO)
    {
      erro = erro_anterior;
    }

    /* Controlador Proporcional */
    MV = KP * erro;

    /* Acionamento dos motores */
    setMotores(PWM_MEDIO + MV, PWM_MEDIO - MV);

    /* Base de tempo do controlador */
    wait_ms(10);

  } // fim do loop principal
} // fim da função principal


/**
 * @}
 */

/************************ (C) COPYRIGHT IOTON Technology **********************/
/***********************************END OF FILE********************************/
