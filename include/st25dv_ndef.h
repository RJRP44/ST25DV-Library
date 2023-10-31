/*
 * Written by RJRP - 29/10/2023
 * ST25 Library for idf framework
 * This program is distributed under the MIT License
 */

#include <esp_err.h>
#include <stdbool.h>
#include <cJson.h>
#include "st25dv.h"

#define ST25DV_TYPE5_NDEF_MESSAGE 0x03
#define ST25DV_TYPE5_TERMINATOR_TLV 0xFE

#define NDEF_APP_LAUNCHER_TYPE "android.com:pkg"
#define NDEF_JSON_TYPE "application/json"

#define NDEF_RECORD_SIZE(mb, type_size, payload_size) (((mb) ? 5 : 1) + 1 + ((payload_size) > 0xFF ? 4 : 1) + 1 + type_size + payload_size)
#define CCFILE_LENGTH 0x08

#define NDEF_ST25DV_MB (1<<7)
#define NDEF_ST25DV_ME (1<<6)
#define NDEF_ST25DV_CF (1<<5)
#define NDEF_ST25DV_SR (1<<4)
#define NDEF_ST25DV_IL (1<<3)
#define NDEF_ST25DV_PT 0x07

#define NDEF_RECORD_HEADER_BIT(header, bit) ((header) & (bit)) == bit

#define NDEF_ST25DV_TNF_EMPTY 0x00
#define NDEF_ST25DV_TNF_WELL_KNOWN 0x01
#define NDEF_ST25DV_TNF_MIME 0x02
#define NDEF_ST25DV_TNF_ABSOLUTE_URI 0x03
#define NDEF_ST25DV_TNF_EXTERNAL 0x04
#define NDEF_ST25DV_TNF_UNKNOWN 0x05
#define NDEF_ST25DV_TNF_UNCHANGED 0x06
#define NDEF_ST25DV_TNF_RESERVED 0x07

typedef struct {
    uint8_t tnf;
    char *type;
    char *payload;
} std25dv_ndef_record;

esp_err_t st25dv_ndef_write_ccfile(uint64_t ccfile);

esp_err_t st25dv_ndef_write_content(st25dv_config st25dv, uint16_t *address, bool mb, bool me, std25dv_ndef_record record);
esp_err_t st25dv_ndef_write_app_launcher_record(st25dv_config st25dv, uint16_t *address, bool mb, bool me, char *app_package);
esp_err_t st25dv_ndef_write_json_record(st25dv_config st25dv, uint16_t *address, bool mb, bool me, cJSON *json_data);

esp_err_t st25dv_ndef_read(st25dv_config st25dv, uint8_t record_num, std25dv_ndef_record *output_records, uint8_t *record_count);
esp_err_t st25dv_ndef_delete_records(std25dv_ndef_record *record);