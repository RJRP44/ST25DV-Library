/*
 * Written by RJRP - 29/10/2023
 * ST25 Library for idf framework
 * This program is distributed under the MIT License
 */

#include <esp_err.h>

#define ST25DV_TYPE5_NDEF_MESSAGE 0x03
#define ST25DV_TYPE5_TERMINATOR_TLV 0xFE

#define NDEF_APP_LAUNCHER_TYPE "android.com:pkg"
#define NDEF_APP_LAUNCHER_TYPE_SIZE 15

#define NDEF_ST25DV_MB (1<<7)
#define NDEF_ST25DV_ME (1<<6)
#define NDEF_ST25DV_CF (1<<5)
#define NDEF_ST25DV_SR (1<<4)
#define NDEF_ST25DV_IC (1<<3)

#define NDEF_ST25DV_TNF_EMPTY 0x00
#define NDEF_ST25DV_TNF_WELL_KNOWN 0x01
#define NDEF_ST25DV_TNF_MIME 0x02
#define NDEF_ST25DV_TNF_ABSOLUTE_URI 0x03
#define NDEF_ST25DV_TNF_EXTERNAL 0x04
#define NDEF_ST25DV_TNF_UNKNOWN 0x05
#define NDEF_ST25DV_TNF_UNCHANGED 0x06
#define NDEF_ST25DV_TNF_RESERVED 0x07

esp_err_t st25dv_ndef_write_ccfile(uint64_t ccfile);
esp_err_t st25dv_ndef_write_app_launcher_record(uint8_t st25_address, char *app_package);