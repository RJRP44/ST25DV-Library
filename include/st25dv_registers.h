/*
 * Written by RJRP - 29/10/2023
 * ST25 Library for idf framework
 * This program is distributed under the MIT License
 */

#ifndef ST25DV_LIBRARY_REGISTERS
#define ST25DV_LIBRARY_REGISTERS

/**************************
 *  REGISTERS DEFINITION  *
 **************************/

#define REG_GPO1 0x0
#define REG_GPO2 0x0001
#define REG_EH_MODE 0x0002
#define REG_RF_MNGMT 0x0003
#define REG_RFA1SS 0x0004
#define REG_ENDA1 0x0005
#define REG_RFA2SS 0x0006
#define REG_ENDA2 0x0007
#define REG_RFA3SS 0x0008
#define REG_ENDA3 0x0009
#define REG_RFA4SS 0x000a
#define REG_I2CSS 0x000b
#define REG_LOCK_CCFILE 0x000c
#define REG_FTM 0x000d
#define REG_I2C_CFG 0x000e
#define REG_LOCK_CFG 0x000f
#define REG_LOCK_DSFID 0x0010
#define REG_LOCK_AFI 0x0011
#define REG_DSFID 0x0012
#define REG_AFI 0x0013
#define REG_MEM_SIZE_BASE 0x0014
#define REG_BLOCK_SIZE 0x0016
#define REG_IC_REF 0x0017
#define REG_UID_BASE 0x0018
#define REG_IC_REV 0x0020
#define REG_I2C_PASSWD_BASE 0x0900

#define LEN_MEM_SIZE 0x02
#define LEN_UID_SIZE 0x08
#define LEN_I2C_PASSWD_SIZE 0x08

#define REG_GPO_CTRL_DYN 0x2000
#define REG_EH_CTRL_DYN 0x2002
#define REG_RF_MNGT_DYN 0x2003
#define REG_I2C_SSO_DYN 0x2004
#define REG_IT_STS_DYN 0x2005
#define REG_MB_CTRL_DYN 0x2006
#define REG_MB_LEN_DYN 0x2007

#define MAILBOX_BASE 0x2008

#define LEN_MAILBOX 0xff

#define EEPROM_SIZE 0x2000


/*******************************
 *  REGISTER'S BIT DEFINITION  *
 *******************************/

#define BIT_FTM_MB_MODE (1 << 0)

#define BIT_MB_CTRL_DYN_MB_EN (1 << 0)
#define BIT_MB_CTRL_DYN_HOST_PUT_MSG (1 << 1)
#define BIT_MB_CTRL_DYN_RF_PUT_MSG (1 << 2)
#define BIT_MB_CTRL_DYN_HOST_MISS_MSG (1 << 4)
#define BIT_MB_CTRL_DYN_RF_MISS_MSG (1 << 5)
#define BIT_MB_CTRL_DYN_HOST_CURRENT_MSG (1 << 6)
#define BIT_MB_CTRL_DYN_RF_CURRENT_MSG (1 << 7)

#define BIT_RF_MNGT_RF_DISABLE (1 << 0)
#define BIT_RF_MNGT_RF_SLEEP (1 << 1)

#define BIT_RF_MNGT_DYN_RF_DISABLE (1 << 0)
#define BIT_RF_MNGT_DYN_RF_SLEEP (1 << 1)
#define BIT_RF_MNGT_DYN_RF_OFF (1 << 2)

#define BIT_GPO1_GPO_EN (1 << 0)
#define BIT_GPO1_RF_USER_EN (1 << 1)
#define BIT_GPO1_RF_ACTIVITY_EN (1 << 2)
#define BIT_GPO1_RF_INTERRUPT_EN (1 << 3)
#define BIT_GPO1_FIELD_CHANGE_EN (1 << 4)
#define BIT_GPO1_RF_PUT_MSG_EN (1 << 5)
#define BIT_GPO1_RF_GET_MSG_EN (1 << 6)
#define BIT_GPO1_RF_WRITE_EN (1 << 7)

#define BIT_GPO2_I2C_WRITE_EN (1 << 0)
#define BIT_GPO2_I2C_RF_OFF_EN (1 << 1)

#define BIT_GPO_CTRL_DYN_GPO_EN (1 << 0)

#define BIT_IT_STS_DYN_RF_USER (1 << 0)
#define BIT_IT_STS_DYN_RF_ACTIVITY (1 << 1)
#define BIT_IT_STS_DYN_RF_INTERRUPT (1 << 2)
#define BIT_IT_STS_DYN_FIELD_FALLING (1 << 3)
#define BIT_IT_STS_DYN_FIELD_RISING (1 << 4)
#define BIT_IT_STS_DYN_RF_PUT_MSG (1 << 5)
#define BIT_IT_STS_DYN_RF_GET_MSG (1 << 6)
#define BIT_IT_STS_DYN_RF_WRITE (1 << 7)

#define BIT_EH_MODE_EH_MODE (1 << 0)

#define BIT_EH_CTRL_DYN_EH_EN (1 << 0)
#define BIT_EH_CTRL_DYN_EH_ON (1 << 1)
#define BIT_EH_CTRL_DYN_FIELD_ON (1 << 2)
#define BIT_EH_CTRL_DYN_VCC_ON (1 << 3)

#define BIT_LOCK_CCFILE_LCKBCK0 (1 << 0)
#define BIT_LOCK_CCFILE_LCKBCK1 (1 << 1)

#define BIT_LOCK_CFG_LCK_CFG (1 << 0)

#define BIT_I2C_SSO_DYN_I2C_SSO (1 << 0)

#define BIT_LOCK_DSFID_LOCK_DSFID (1 << 0)

#define BIT_LOCK_AFI_LOCK_AFI (1 << 0)

#define BIT_I2CSS_MEM1_WRITE (1 << 0)
#define BIT_I2CSS_MEM1_READ (1 << 1)
#define BIT_I2CSS_MEM2_WRITE (1 << 2)
#define BIT_I2CSS_MEM2_READ (1 << 3)
#define BIT_I2CSS_MEM3_WRITE (1 << 4)
#define BIT_I2CSS_MEM3_READ (1 << 5)
#define BIT_I2CSS_MEM4_WRITE (1 << 6)
#define BIT_I2CSS_MEM4_READ (1 << 7)

#endif //ST25DV_LIBRARY_REGISTERS