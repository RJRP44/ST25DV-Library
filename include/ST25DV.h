#include <stdint.h>
#include <driver/i2c.h>
#include "esp_err.h"

//GPO registers
#define REG_GPO1 0x00

#define BIT_GPO1_GPO_EN (1 << 0)
#define BIT_GPO1_RF_USER_EN (1 << 1)
#define BIT_GPO1_RF_ACTIVITY_EN (1 << 2)
#define BIT_GPO1_RF_INTERRUPT_EN (1 << 3)
#define BIT_GPO1_FIELD_CHANGE_EN (1 << 4)
#define BIT_GPO1_RF_PUT_MSG_EN (1 << 5)
#define BIT_GPO1_RF_GET_MSG_EN (1 << 6)
#define BIT_GPO1_RF_WRITE_EN (1 << 7)

#define ST25_MAX_CLK_SPEED 1000000

#define ST25_USER_ADDRESS 0x53
#define ST25_SYSTEM_ADDRESS 0x57

#define ACK_CHECK_EN 0x1

esp_err_t st25_write_byte(uint8_t st25_address, uint16_t address, uint8_t byte);
esp_err_t st25_read_byte(uint8_t st25_address, uint16_t address, uint8_t *byte);

esp_err_t st25_write_bit(uint8_t st25_address, uint16_t address, uint8_t bit_mask, bool bit);
esp_err_t st25_read_bit(uint8_t st25_address, uint16_t address, uint8_t bit_mask, bool *bit);

esp_err_t st25_init_i2c(i2c_port_t port, i2c_config_t config);