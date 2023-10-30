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

static esp_err_t st25dv_ndef_write_content(uint8_t st25_address, uint16_t *address, bool mb, bool me, uint8_t ndef_type, char *type, char *payload) {
    uint8_t type_size = strlen(type);
    uint16_t payload_size = strlen(payload);

    uint8_t *record_data = malloc(NDEF_RECORD_SIZE(mb, type_size, payload_size));
    uint8_t *data = record_data;

    //Total length : Record header + Type length + Payload length + ID + Type + Payload
    uint16_t record_length = 1 + 1 + (payload_size > 0xFF ? 4 : 1) + 1 + type_size + payload_size;

    //If this ndef is the first one
    if (mb) {
        //Type5 Tag TLV-Format: T
        *data++ = ST25DV_TYPE5_NDEF_MESSAGE;

        //Type5 Tag TLV-Format: L
        if (record_length > 0xFE) {
            *data++ = 0xFF;
            *data++ = record_length >> 8;
            *data++ = record_length & 0xFF;
        } else {
            *data++ = record_length;
        }
    }

    //Type5 Tag TLV-Format: V
    uint8_t tnf = 0;
    tnf |= NDEF_ST25DV_MB;
    tnf |= NDEF_ST25DV_ME;
    tnf |= payload_size > 0xFF ? 0 : NDEF_ST25DV_SR;
    tnf |= NDEF_ST25DV_IC;
    tnf |= ndef_type;
    *data++ = tnf;

    //Type length
    *data++ = type_size;

    //Payload length
    if (payload_size > 0xFF) {
        *data++ = payload_size >> 24;
        *data++ = (payload_size >> 16) & 0xFF;
        *data++ = (payload_size >> 8) & 0xFF;
        *data++ = payload_size & 0xFF;
    } else {
        *data++ = payload_size;
    }

    //ID
    *data++ = 0x00;

    //Add record type
    memcpy(data, type, type_size);
    data += type_size;

    //Add record payload
    memcpy(data, payload, payload_size);
    data += payload_size;

    uint8_t record_address = CCFILE_LENGTH;

    if (*address > CCFILE_LENGTH) {
        record_address = *address;
    }

    //If this ndef record is not the first one, we need to update the TLV-Format L value
    if (!mb) {

        //Read the possible 3 byte l value
        uint8_t *l_value = malloc(0x03);
        st25dv_read(st25_address, CCFILE_LENGTH + 1, l_value, 0x03);
        uint16_t old_length = 0;
        uint16_t total_length = 0;

        if (*l_value == 0xFF) {
            //The l value is already 3 byte long
            old_length |= *(l_value + 1) << 8;
            old_length |= *(l_value + 2) & 0xFF;

            total_length = old_length + record_length;

            *(l_value + 1) = total_length >> 8;
            *(l_value + 2) = total_length & 0xFF;

            //Update the value
            st25dv_write(st25_address, CCFILE_LENGTH + 1, l_value, 0x03);
        } else {
            //The l value is 1 byte long
            old_length = *l_value;

            total_length = old_length + record_length;

            if (total_length > 0xFE) {
                //The l value is 1 byte but needs to be 3
                *l_value = 0xFF;
                *(l_value + 1) = total_length >> 8;
                *(l_value + 2) = total_length & 0xFF;

                //Copy and move the existing records
                uint8_t *st25dv_content = malloc(old_length);
                st25dv_read(st25_address, CCFILE_LENGTH + 2, st25dv_content, old_length);
                st25dv_write(st25_address, CCFILE_LENGTH + 1, l_value, 0x03);
                vTaskDelay(100 / portTICK_PERIOD_MS);
                st25dv_write(st25_address, CCFILE_LENGTH + 4, st25dv_content, old_length);
                record_address += 2;
                free(st25dv_content);
            } else {
                //The l value is already 1 byte
                *l_value = total_length;

                //Update the value
                st25dv_write_byte(st25_address, CCFILE_LENGTH + 1, *l_value);
            }
        }
        free(l_value);
    }
    vTaskDelay(100 / portTICK_PERIOD_MS);
    st25dv_write(st25_address, record_address, record_data, data - record_data);
    vTaskDelay(100 / portTICK_PERIOD_MS);
    //Add terminator
    if (me) {
        st25dv_write_byte(st25_address, record_address + (data - record_data), ST25DV_TYPE5_TERMINATOR_TLV);
    }

    *address = record_address + (data - record_data);

    free(record_data);
    return ESP_OK;
}

esp_err_t st25dv_ndef_write_app_launcher_record(uint8_t st25_address, uint16_t *address, bool mb, bool me, char *app_package) {
    char record_type[] = NDEF_APP_LAUNCHER_TYPE;
    st25dv_ndef_write_content(st25_address, address, mb, me, NDEF_ST25DV_TNF_EXTERNAL, record_type, app_package);
    return ESP_OK;
}

esp_err_t st25dv_ndef_write_json_record(uint8_t st25_address, uint16_t *address, bool mb, bool me, cJSON *json_data) {
    char *json = cJSON_PrintUnformatted(json_data);
    char record_type[] = NDEF_JSON_TYPE;
    st25dv_ndef_write_content(st25_address, address, mb, me, NDEF_ST25DV_TNF_MIME, record_type, json);
    free(json);
    return ESP_OK;
}