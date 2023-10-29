/*
 * Written by RJRP - 28/10/2023
 * ST25 Library for idf framework
 * This program is distributed under the MIT License
 */

#include <driver/i2c.h>
#include <st25dv.h>
#include <st25dv_registers.h>
#include <st25dv_ndef.h>
#include <string.h>

void app_main(void) {
    //Define the i2c bus configuration
    i2c_config_t i2c_config = {
            .mode = I2C_MODE_MASTER,
            .sda_io_num = 1,
            .scl_io_num = 2,
            .sda_pullup_en = GPIO_PULLUP_ENABLE,
            .scl_pullup_en = GPIO_PULLUP_ENABLE,
            .master.clk_speed = ST25DV_MAX_CLK_SPEED,
    };

    //Apply, init the configuration to the bus
    st25dv_init_i2c(I2C_NUM_1, i2c_config);

    //Read a byte from the st25dv
    uint8_t value = 0;
    st25dv_read_byte(ST25DV_USER_ADDRESS, 0x00, &value);

    printf("Reading 0x00 value : 0x%02X\n", value);

    //Read text from the st25dv
    uint8_t read_text[10];
    read_text[9] = '\0';
    st25dv_read(ST25DV_USER_ADDRESS, 0x00, read_text, 9);

    printf("Reading 0x00 text : %s\n", read_text);

    //Read a bit from the gpo register
    bool bit_value = 0;
    st25dv_read_bit(ST25DV_SYSTEM_ADDRESS, REG_GPO1, BIT_GPO1_GPO_EN, &bit_value);

    printf("Reading REG_GPO1 EN bit : 0x%02X\n", bit_value);

    //Clear the first 512 bytes
    uint8_t *blank = malloc(256);
    memset(blank, 0x00, 256);
    st25dv_write(ST25DV_USER_ADDRESS, 0x00, blank, 256);
    free(blank);

    printf("Clearing from 0x00 to 0x200\n");

    //Wait before writing again
    vTaskDelay(100 / portTICK_PERIOD_MS);

    //Write Capacity Container File
    st25dv_ndef_write_ccfile(0x00040000010040E2);
    printf("Writing CC File\n");

    //Wait before writing again
    vTaskDelay(100 / portTICK_PERIOD_MS);

    //Ndef record
    char app_package[] = "fr.ouchat.app";
    st25dv_ndef_write_app_launcher_record(ST25DV_USER_ADDRESS, app_package);
}
