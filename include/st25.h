/*
 * Written by RJRP - 28/10/2023
 * ST25 Library for idf framework
 * This program is distributed under the MIT License
 */

#include <stdint.h>
#include <driver/i2c.h>
#include "esp_err.h"

#define ST25_MAX_CLK_SPEED 1000000

#define ST25_USER_ADDRESS 0x53
#define ST25_SYSTEM_ADDRESS 0x57

#define ACK_CHECK_EN 0x1

esp_err_t st25_write_byte(uint8_t st25_address, uint16_t address, uint8_t byte);
esp_err_t st25_read_byte(uint8_t st25_address, uint16_t address, uint8_t *byte);

esp_err_t st25_write_bit(uint8_t st25_address, uint16_t address, uint8_t bit_mask, bool bit);
esp_err_t st25_read_bit(uint8_t st25_address, uint16_t address, uint8_t bit_mask, bool *bit);

esp_err_t st25_init_i2c(i2c_port_t port, i2c_config_t config);