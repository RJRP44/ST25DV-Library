# ST25DV library for ESP32

This is a library for ST's [ST25DV-I2C series](https://www.st.com/en/nfc/st25dv-i2c-series-dynamic-nfc-tags.html). The ST25DV chip is an RFID/NFC dynamic tag. It can be accessed by any NFC smartphone or NFC/RFID HF reader, and also by an MCU (an esp32 for this library), using the I²C wired link.  


> **Warning**
> This Library is **not** compatible with Arduino framework

## 📌 Contents
* [Getting started](#Getting-started)
  * [Wiring for the ST25DV 🔌](#Wiring-the-ST25DV-)
  * [Library Installation](#library-installation-)
  * [Ndef](#ndef)
* [Examples](#examples-)

## Getting started
### Wiring the ST25DV 🔌

The wiring is made with the [reference board](https://www.st.com/en/evaluation-tools/ant7-t-25dv64kc.html). Check the [datasheet](https://www.st.com/resource/en/datasheet/st25dv64kc.pdf) to wire directly the chip.

| ST25DV Pins | ESP32S3 Pins                                 |           
|-------------|----------------------------------------------|
| GND         | GND                                          |
| VCC         | 3v3                                          |
| SCL         | GPIO2, 47 kΩ pullup resistor required to 3v3 |
| SDA         | GPIO1, 47 kΩ pullup resistor required to 3v3 |
| GPO (RF)    | Not used in the examples                     |
### Library Installation 📥

The library is available at https://components.espressif.com/components/rjrp44/st25dv.

So, you can use the [IDF Component Manager](https://docs.espressif.com/projects/esp-idf/en/latest/esp32/api-guides/tools/idf-component-manager.html) to easily import this library into your project.
To add this component to your project, run:

```log
idf.py add-dependency "rjrp44/st25dv^0.1.0" 
```

### Ndef
This library contains a basic implementation of ndef to read or write data. However, more specific data types like uri and text require their formats to be added.

For simple write you can use this function `st25dv_ndef_write_content` as shown :
```c
st25dv_config st25dv_config = {
        ST25DV_USER_ADDRESS,
        ST25DV_SYSTEM_ADDRESS
};

char record_type[] = "android.com:pkg";
char record_payload[] = "fr.ouchat.app";

std25dv_ndef_record record = {
            NDEF_ST25DV_TNF_EXTERNAL,
            record_type,
            record_payload
};

st25dv_ndef_write_content(st25dv_config, &address, mb, me, ndef_record);
```
Arguments of the function :
- `st25dv_config` is your st25dv config
- `address` is the pointer of the value for the memory address, after writing it is updated to the end of what was written
- `mb` stands for "message begin" and should be true is this record is the first one
- `me` stands for "message end" and should be true for the last record
- `ndef_record` contains 3 values:
  - `tnf` : Type Name Format, witch describes the content format. Theses are all the values :
    - `0x00` : Empty
    - `0x01` : Well known
    - `0x02` : Mime
    - `0x03` : URI
    - `0x04` : External
    - `0x05` : Unknown
    - `0x06` : Unchanged
    - `0x07` : Reserved
  - `record_type` : The name of your record type 
  - `record_payload` : The payload

To read data you can use this function `st25dv_ndef_read`

```c
std25dv_ndef_record *read = malloc(sizeof(std25dv_ndef_record));
memset(read, 0 , sizeof(std25dv_ndef_record));

uint8_t record_num = 2;
uint8_t record_count = 0;
st25dv_ndef_read(st25dv_config, record_num,read, &record_count);

//Delete record after use
st25dv_ndef_delete_records(read);
```
## Examples 📄
You can find in the `📁 /examples` folder an example project showcasing the main features of the library to help you understand how it works.

## 📝 License

Copyright © 2023 [RJRP44](https://www.github.com/RJRP44).

This project is [MIT](https://opensource.org/license/mit/) licensed.

## ✨ Show your support

Give a ⭐️ if this project helped you!

## 👤 Authors

- [@RJRP44](https://www.github.com/RJRP44)