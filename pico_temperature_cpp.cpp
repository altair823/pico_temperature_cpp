#include <stdio.h>
#include <string>
#include "pico/stdlib.h"
#include "hardware/adc.h"
#include "hardware/i2c.h"
#include "hardware/gpio.h"
#include "lcd.h"

#define LED_ON      gpio_put(LED_PIN, true)
#define LED_OFF     gpio_put(LED_PIN, false)
#define LED_BLINK   gpio_put(LED_PIN, false); \
                    sleep_ms(INTERVAL); \
                    gpio_put(LED_PIN, true)

int main()
{
    stdio_init_all();

    // This example will use I2C0 on the default SDA and SCL pins (4, 5 on a Pico)
    i2c_init(i2c_default, 100 * 1000);
    gpio_set_function(PICO_DEFAULT_I2C_SDA_PIN, GPIO_FUNC_I2C);
    gpio_set_function(PICO_DEFAULT_I2C_SCL_PIN, GPIO_FUNC_I2C);
    gpio_pull_up(PICO_DEFAULT_I2C_SDA_PIN);
    gpio_pull_up(PICO_DEFAULT_I2C_SCL_PIN);
    // Make the I2C pins available to picotool
    bi_decl(bi_2pins_with_func(PICO_DEFAULT_I2C_SDA_PIN, PICO_DEFAULT_I2C_SCL_PIN, GPIO_FUNC_I2C));

    lcd_init();

    const uint LED_PIN = 25;
    gpio_init(LED_PIN);
    gpio_set_dir(LED_PIN, GPIO_OUT);

    LED_ON;

    adc_init();
    adc_set_temp_sensor_enabled(true);
    adc_select_input(4);

    // Primary Core 0 Loop
    while(1){
        uint16_t raw = adc_read();
        const float conversion_factor = 3.3f / (1<<12);
        float result = raw * conversion_factor;
        float temp = 27 - (result -0.706)/0.001721;
        printf("Temp = %f C\n", temp);

        lcd_set_cursor(0, 0);
        char title[16] = "Pico temp!";
        lcd_string(title);

        lcd_set_cursor(1, 0);
        char temp_str[16];
        std::string t = "temp: " + std::to_string(temp);
        strcpy(temp_str, t.c_str());
        lcd_string(temp_str);
        sleep_ms(1000);
        //lcd_clear();
        
    }

    return 0;
}
