/***************************************************************************//**
  @file     main.c
  @brief    FW main
  @author   Nicolás Magliola
 ******************************************************************************/

#include "hardware.h"


void App_Init (void);
void App_Run (void);



int main (void)
{

    hw_Init();
    printf("%d",3);
    hw_DisableInterrupts();
    App_Init(); /* Program-specific setup */
    hw_EnableInterrupts();

    __FOREVER__
       App_Run(); /* Program-specific loop  */
}
