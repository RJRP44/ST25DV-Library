#include <driver/i2c.h>
#include <ST25DV.h>

void app_main(void)
{
    //Define the i2c bus configuration
    i2c_config_t i2c_config = {
            .mode = I2C_MODE_MASTER,
            .sda_io_num = 1,
            .scl_io_num = 2,
            .sda_pullup_en = GPIO_PULLUP_ENABLE,
            .scl_pullup_en = GPIO_PULLUP_ENABLE,
            .master.clk_speed = ST25_MAX_CLK_SPEED,
    };

    //Apply, init the configuration to the bus
    st25_init_i2c(I2C_NUM_1, i2c_config);

    //Read a byte from the st25
    uint8_t value = 0;
    st25_read_byte(ST25_USER_ADDRESS, 0x00, &value);

    printf("Reading 0x00 value : 0x%02X\n", value);
}
