/*
 * Written by RJRP - 29/10/2023
 * ST25 Library for idf framework
 * This program is distributed under the MIT License
 */

#include <memory.h>
#include "st25dv_ndef.h"
#include "st25dv.h"

esp_err_t st25dv_ndef_write_ccfile(uint64_t ccfile) {
    uint8_t ccbyte[8];
    memcpy(ccbyte, &ccfile, sizeof(ccfile));
    return st25dv_write(ST25DV_USER_ADDRESS, 0x00, ccbyte, sizeof(ccfile));
}

esp_err_t st25dv_ndef_write_app_launcher_record(uint8_t st25_address, char *app_package) {
    uint16_t app_package_size = strlen(app_package);
    uint8_t *record_data = malloc(app_package_size + 24);
    uint8_t *record = record_data;

    //Type5 Tag TLV-Format: T
    *record++ = ST25DV_TYPE5_NDEF_MESSAGE;

    //Total length is : Type Length + Payload Length + ID + Type + Payload + Terminator
    uint16_t length = 1 + (app_package_size > 0xFF ? 4 : 1) + 1 + NDEF_APP_LAUNCHER_TYPE_SIZE + app_package_size + 1;

    //Type5 Tag TLV-Format: L
    if (length > 0xFF) {
        *record++ = 0xFF;
        *record++ = length >> 8;
        *record++ = length & 0xFF;
    } else {
        *record++ = length;
    }

    //Type5 Tag TLV-Format: V
    uint8_t tnf = 0;
    tnf |= NDEF_ST25DV_MB;
    tnf |= NDEF_ST25DV_ME;
    tnf |= app_package_size > 0xFF ? 0 : NDEF_ST25DV_SR;
    tnf |= NDEF_ST25DV_IC;
    tnf |= NDEF_ST25DV_TNF_EXTERNAL;
    *record++ = tnf;

    //Type length
    *record++ = NDEF_APP_LAUNCHER_TYPE_SIZE;

    //Payload length
    if (app_package_size > 0xFF) {
        *record++ = app_package_size >> 24;
        *record++ = (app_package_size >> 16) & 0xFF;
        *record++ = (app_package_size >> 8) & 0xFF;
        *record++ = app_package_size & 0xFF;
    } else {
        *record++ = app_package_size;
    }

    *record++ = 0x00;

    //Add record type
    char record_type[] = NDEF_APP_LAUNCHER_TYPE;
    memcpy(record, record_type, strlen(record_type));
    record += strlen(record_type);

    //Add record payload
    memcpy(record, app_package, app_package_size);
    record += app_package_size;

    st25dv_write(st25_address, 0x08, record_data, record - record_data);

    //Add terminator
    st25dv_write_byte(st25_address,0x08 + (record - record_data),ST25DV_TYPE5_TERMINATOR_TLV);

    free(record_data);
    return ESP_OK;
}