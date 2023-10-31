/*
 * Written by RJRP - 28/10/2023
 * ST25 Library for idf framework
 * This program is distributed under the MIT License
 */

#include <stdint.h>
#include <driver/i2c.h>
#include "esp_err.h"

#define ST25DV_MAX_CLK_SPEED 1000000

#define ST25DV_USER_ADDRESS 0x53
#define ST25DV_SYSTEM_ADDRESS 0x57

#define ST25DV_CHECK(check) if(!(check)) {          \
        return ESP_FAIL;                            \
        }

#define ACK_CHECK_EN 0x1

typedef struct {
    uint8_t user_address;
    uint8_t system_address;
} st25dv_config;

esp_err_t st25dv_write_byte(uint8_t st25_address, uint16_t address, uint8_t byte);
esp_err_t st25dv_read_byte(uint8_t st25_address, uint16_t address, uint8_t *byte);

esp_err_t st25dv_write_bit(uint8_t st25_address, uint16_t address, uint8_t bit_mask, bool bit);
esp_err_t st25dv_read_bit(uint8_t st25_address, uint16_t address, uint8_t bit_mask, bool *bit);

esp_err_t st25dv_init_i2c(i2c_port_t port, i2c_config_t config);

esp_err_t st25dv_write(uint8_t st25_address, uint16_t address, uint8_t *data, size_t size);
esp_err_t st25dv_read(uint8_t st25_address, uint16_t address, uint8_t *data, size_t size);

esp_err_t st25dv_open_session(uint8_t st25_address, uint64_t password);
esp_err_t st25dv_is_session_opened(uint8_t st25_address, bool *bit);