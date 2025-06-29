#include <stdint.h>

#include "main.h"
#include "cmsis_vio.h"

static void delay(uint32_t ms);

void main_app(void)
{
    vioInit();
    while (1)
    {
        vioSetSignal(vioLED3, vioLEDon);
        delay(500);
        vioSetSignal(vioLED3, vioLEDoff);
        delay(500);
    }
}

static void delay(uint32_t ms)
{
    uint32_t delayTime;

    if (ms > UINT32_MAX/100000)
    {
        return;
    }

    delayTime = ms*100000;
    while (delayTime--)
    {
        __NOP();
    }
}