/*
 * Written by RJRP - 28/10/2023
 * ST25 Library for idf framework
 * This program is distributed under the MIT License
 */

#include <stdio.h>
#include "st25dv.h"
#include "driver/i2c.h"


esp_err_t st25dv_write_byte(uint8_t st25_address, uint16_t address, uint8_t byte) {

    esp_err_t ret;
    i2c_cmd_handle_t cmd = i2c_cmd_link_create();
    i2c_master_start(cmd);

    //St25 Write sequence :
    i2c_master_write_byte(cmd, (st25_address << 1) | I2C_MASTER_WRITE, ACK_CHECK_EN);
    i2c_master_write_byte(cmd, address >> 8, ACK_CHECK_EN);
    i2c_master_write_byte(cmd, address & 0xFF, ACK_CHECK_EN);
    i2c_master_write_byte(cmd, byte, ACK_CHECK_EN);

    i2c_master_stop(cmd);
    ret = i2c_master_cmd_begin(I2C_NUM_1, cmd, 1000 / portTICK_PERIOD_MS);
    i2c_cmd_link_delete(cmd);

    return ret;
}

esp_err_t st25dv_read_byte(uint8_t st25_address, uint16_t address, uint8_t *byte) {

    esp_err_t ret;
    i2c_cmd_handle_t cmd = i2c_cmd_link_create();
    i2c_master_start(cmd);

    //St25 Read sequence :
    i2c_master_write_byte(cmd, (st25_address << 1) | I2C_MASTER_WRITE, ACK_CHECK_EN);
    i2c_master_write_byte(cmd, address << 8, ACK_CHECK_EN);
    i2c_master_write_byte(cmd, address & 0xFF, ACK_CHECK_EN);
    i2c_master_start(cmd);
    i2c_master_write_byte(cmd, (st25_address << 1) | I2C_MASTER_READ, ACK_CHECK_EN);
    i2c_master_read_byte(cmd, byte, ACK_CHECK_EN);

    i2c_master_stop(cmd);
    ret = i2c_master_cmd_begin(I2C_NUM_1, cmd, 1000 / portTICK_PERIOD_MS);
    i2c_cmd_link_delete(cmd);

    return ret;
}

esp_err_t st25dv_write_bit(uint8_t st25_address, uint16_t address, uint8_t bit_mask, bool bit) {

    uint8_t byte = 0;
    esp_err_t ret;
    ret = st25dv_read_byte(st25_address, address, &byte);

    if (ret != ESP_OK) {
        return ret;
    }

    if (bit) {
        byte |= bit_mask;
    } else {
        byte &= ~bit_mask;
    }

    ret = st25dv_write_byte(st25_address, address, byte);

    return ret;
}

esp_err_t st25dv_read_bit(uint8_t st25_address, uint16_t address, uint8_t bit_mask, bool *bit) {
    uint8_t byte = 0;
    esp_err_t ret;
    ret = st25dv_read_byte(st25_address, address, &byte);

    if (ret != ESP_OK) {
        return ret;
    }

    *bit = (byte & bit_mask);
    return ESP_OK;
}

esp_err_t st25dv_init_i2c(i2c_port_t port, i2c_config_t config) {
    i2c_param_config(port, &config);
    i2c_set_timeout(port, 0x0000001FU);

    return i2c_driver_install(port, config.mode, 0, 0, 0);
}

esp_err_t st25dv_write(uint8_t st25_address, uint16_t address, uint8_t *data, size_t size) {
    esp_err_t ret;
    i2c_cmd_handle_t cmd = i2c_cmd_link_create();
    i2c_master_start(cmd);

    //St25 Write sequence :
    i2c_master_write_byte(cmd, (st25_address << 1) | I2C_MASTER_WRITE, ACK_CHECK_EN);
    i2c_master_write_byte(cmd, address >> 8, ACK_CHECK_EN);
    i2c_master_write_byte(cmd, address & 0xFF, ACK_CHECK_EN);
    i2c_master_write(cmd, data, size, ACK_CHECK_EN);

    i2c_master_stop(cmd);
    ret = i2c_master_cmd_begin(I2C_NUM_1, cmd, 1000 / portTICK_PERIOD_MS);
    i2c_cmd_link_delete(cmd);

    return ret;
}

esp_err_t st25dv_read(uint8_t st25_address, uint16_t address, uint8_t *data, size_t size) {
    esp_err_t ret;
    i2c_cmd_handle_t cmd = i2c_cmd_link_create();
    i2c_master_start(cmd);

    //St25 Read sequence :
    i2c_master_write_byte(cmd, (st25_address << 1) | I2C_MASTER_WRITE, ACK_CHECK_EN);
    i2c_master_write_byte(cmd, address << 8, ACK_CHECK_EN);
    i2c_master_write_byte(cmd, address & 0xFF, ACK_CHECK_EN);
    i2c_master_start(cmd);
    i2c_master_write_byte(cmd, (st25_address << 1) | I2C_MASTER_READ, ACK_CHECK_EN);
    if (size > 1) {
        i2c_master_read(cmd, data, size - 1, 0);
    }
    i2c_master_read_byte(cmd, data + size - 1, 1);

    i2c_master_stop(cmd);
    ret = i2c_master_cmd_begin(I2C_NUM_1, cmd, 1000 / portTICK_PERIOD_MS);
    i2c_cmd_link_delete(cmd);

    return ret;
}

