/* SPDX-License-Identifier: GPL-2.0+ */
/*
 * Library to support AAEON SRG3352 family
 *
 * Copyright (C) LYD/AAEON Technology Inc.
 */

#ifndef __BOARD_DETECT_H
#define __BOARD_DETECT_H

#define SRG52_EEPROM_HDR_MAGIC      0x544F4941	 /* 'AIOT'  */
#define SRG52_EEPROM_HDR_REV01      0x3130       /* '01'    */
#define SRG52_EEPROM_HDR_REV        (SRG52_EEPROM_HDR_REV01)

#define SRG52_EEPROM_HDR_ETH_ALEN   (6)
#define SRG52_EEPROM_HDR_BRD_LEN    (32)
#define SRG52_EEPROM_HDR_REV_LEN    (2)
#define SRG52_EEPROM_HDR_SN_LEN     (16)
#define SRG52_EEPROM_HDR_MNF_LEN    (32)
#define SRG52_EEPROM_HDR_HWREV_LEN  (2)
#define SRG52_EEPROM_HDR_HWCFG_LEN  (4)
#define SRG52_EEPROM_HDR_SWVER_LEN  (2)
#define SRG52_EEPROM_HDR_SWCFG_LEN  (4)
#define SRG52_EEPROM_HDR_RVSCS_LEN  (32)
#define SRG52_EEPROM_HDR_BTCNT_LEN  (4)
#define SRG52_EEPROM_HDR_CRC16_LEN  (2)

struct  srg52_eeprom_t {
    u32 magic;				/* header magic numver */
    u16 rev;				/* header revision, 01 */
    u8  bname[32];			/* board name */
    u8 	serial[16];			/* board serial number */
    u8 	manufacturer[32];	/* manufacture name */
    u8 	macEth0[6];			/* eth0 address */
    u8 	macEth1[6];			/* eth1 address */
    u8 	macBt[6];
    u8 	macWlan[6];
    u16 hwRev;				/* hardware revision */
    u32 hwCfg;				/* hardware configuration */
    u16 swVer;				/* software verision */
    u32 swCfg;				/* software configuration */
    u8 	reservedCus[32];	/* reserve for customer */
    u32 bootCount;          /* Boot counter */
    u16 crc16;
} __attribute__((__packed__));

#define SRG52_EEPROM_SIZE	sizeof(struct srg52_eeprom_t)
#define SRG52_EEPROM_DATA   ((struct srg52_eeprom_t *)\
                               TI_SRAM_SCRATCH_BOARD_EEPROM_START)
/**
 * set_project_info_env() - Setup default project info environment vars
 *
 */
void set_project_info_env(void);
/**
 * set_board_info_env() - Setup commonly used board information environment vars
 * @name:	Name of the board
 *
 * If name is NULL, default_name is used.
 */
void set_board_info_env(char *name);

/**
 * board_ti_set_ethaddr- Sets the ethaddr environment from EEPROM
 * @index: The first eth<index>addr environment variable to set
 *
 * EEPROM should be already read before calling this function.
 * The EEPROM contains 2 MAC addresses which define the MAC address
 * range (i.e. first and last MAC address).
 * This function sets the ethaddr environment variable for all
 * the available MAC addresses starting from eth<index>addr.
 */
void board_ti_set_ethaddr(int index);

/**
 * board_srg52_was_eeprom_read() - Check to see if the eeprom contents have been read
 *
 * This function is useful to determine if the eeprom has already been read and
 * its contents have already been loaded into memory. It utiltzes the magic
 * number that the header value is set to upon successful eeprom read.
 */
bool board_srg52_was_eeprom_read(void);

#endif	/* __BOARD_DETECT_H */
