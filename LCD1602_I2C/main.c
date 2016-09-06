
#include "stm32f0xx_hal.h"
#include "lcd1602.h"

DISP_HandleTypeDef DISP_HandleStruct;


void DISP_Configure(DISP_HandleTypeDef *DISP_HandleStruct)
{
    DISP_HandleStruct.D4.Port = GPIOA;
    DISP_HandleStruct.D4.Pin = GPIO_PIN_5;
    DISP_HandleStruct.D5.Port = GPIOA;
    DISP_HandleStruct.D5.Pin = GPIO_PIN_6;
    DISP_HandleStruct.D6.Port = GPIOA;
    DISP_HandleStruct.D6.Pin = GPIO_PIN_7;
    DISP_HandleStruct.D7.Port = GPIOB;
    DISP_HandleStruct.D7.Pin = GPIO_PIN_1;
    DISP_HandleStruct.RS.Port = GPIOA;
    DISP_HandleStruct.RS.Pin = GPIO_PIN_9;
    DISP_HandleStruct.E.Port = GPIOA;
    DISP_HandleStruct.E.Pin = GPIO_PIN_10;
    DISP_HandleStruct.Lines = 2;
}


void GPIO_Configure()
{
    GPIO_InitTypeDef  GPIO_InitStruct;

    // enable GPIOA
    __GPIOA_CLK_ENABLE();

    GPIO_InitStruct.Mode  = GPIO_MODE_OUTPUT_PP;
    GPIO_InitStruct.Pull  = GPIO_PULLUP;
    GPIO_InitStruct.Speed = GPIO_SPEED_HIGH;
    GPIO_InitStruct.Pin = GPIO_PIN_4;
    HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);
    /* -3- Cobfigure PA3 in Input Mode with Pull-up */
    GPIO_InitStruct.Mode  = GPIO_MODE_INPUT;
    GPIO_InitStruct.Pull  = GPIO_PULLUP;
    GPIO_InitStruct.Pin = GPIO_PIN_3;
    HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);
}

int main(void)
{
    int i = 0;

    // BSP init
    HAL_Init();

    // set system priority
    HAL_NVIC_SetPriority(SysTick_IRQn, 0, 0);

    HAL_Delay(500);

    // Button init
    GPIO_Configure();

    // hd44780 init
    DISP_Configure(&DISP_HandleStruct);
    DISP_Init(&DISP_HandleStruct);

    DISP_PutString(&DISP_HandleStruct, "Hello World!");
    DISP_SetCursor(&DISP_HandleStruct, 0, 2);
    DISP_PutString(&DISP_HandleStruct, "Hello World!");

    HAL_Delay(1000);

    // clear screen
    DISP_CMD(&DISP_HandleStruct, DISP_CLR);
    HAL_Delay(1);

    while (1) {
        DISP_Setcursor(&DISP_HandleStruct, 0, 1);
        DISP_PutInt(&DISP_HandleStruct, i);
        i++;
        HAL_Delay(10);

        if (HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_3) == GPIO_PIN_RESET) {
            HAL_GPIO_WritePin(GPIOA, GPIO_PIN_4, GPIO_PIN_SET);
        } else {
            HAL_GPIO_WritePin(GPIOA, GPIO_PIN_4, GPIO_PIN_RESET);
        }
    }
}


