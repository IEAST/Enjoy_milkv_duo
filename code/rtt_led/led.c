#include "led.h"

int led_init(void)
{
    rt_pin_mode(LED_PIN, PIN_MODE_OUTPUT);

    return 0;
}

int led_on(void)
{
    rt_pin_write(LED_PIN, PIN_HIGH);

    return 0;
}

int led_off(void)
{
    rt_pin_write(LED_PIN, PIN_LOW);

    return 0;
}
