/**
 * DAPLink Interface Firmware
 * Copyright (c) 2021 Arm Limited, All Rights Reserved
 * SPDX-License-Identifier: Apache-2.0
 *
 * Licensed under the Apache License, Version 2.0 (the "License"); you may
 * not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 * http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS, WITHOUT
 * WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#ifndef DAPLINK_ADDR_H
#define DAPLINK_ADDR_H

#if defined(NRF52840_PROMICRO)
/*
 NRF52840_PROMICRO uses Nordic MBR + adafruit uf2 bootloader for nice!nano + optional SoftDevice 
 so DAPLINK_ROM_BL_SIZE is defined to cover MBR or MBR + SoftDevice
*/

/* Device sizes */

#define DAPLINK_ROM_START               0x00000000
#define DAPLINK_ROM_SIZE                0x00040000 // 256 KiB

#define DAPLINK_ROM_CONFIG_USER_START   0x0003F000
#define DAPLINK_ROM_CONFIG_USER_SIZE    0x00001000

#define DAPLINK_ROM_BL_START            DAPLINK_ROM_START // 0x00000000
#ifndef DAPLINK_ROM_BL_SIZE
#define DAPLINK_ROM_BL_SIZE             0x00001000 // our bootloader is 4 KiB Nordic MBR
#endif

#define DAPLINK_ROM_IF_START            (DAPLINK_ROM_BL_START + DAPLINK_ROM_BL_SIZE) //0x00001000
#define DAPLINK_ROM_IF_SIZE             (DAPLINK_ROM_CONFIG_USER_START - DAPLINK_ROM_IF_START) // 0x0003e000


/* RAM sizes */

#define DAPLINK_RAM_START               (0x20000008) // 8 bytes is reserved for MBR and SoftDevice
#define DAPLINK_RAM_SIZE                (0x00010000-8) // 64 KiB

#define DAPLINK_RAM_APP_START           DAPLINK_RAM_START
#define DAPLINK_RAM_APP_SIZE            (DAPLINK_RAM_SIZE - DAPLINK_RAM_SHARED_SIZE)//0x0000FEF8

#else

/* Device sizes */

#define DAPLINK_ROM_START               0x00000000
#define DAPLINK_ROM_SIZE                0x00040000 // 256 KiB


#define DAPLINK_RAM_START               0x20000000
#define DAPLINK_RAM_SIZE                0x00010000 // 64 KiB

/* ROM sizes */

#define DAPLINK_ROM_BL_START            0x00000000
#define DAPLINK_ROM_BL_SIZE             0x00010000 // 64 KiB bootloader

#define DAPLINK_ROM_IF_START            0x00010000
#define DAPLINK_ROM_IF_SIZE             0x0002F000

#define DAPLINK_ROM_CONFIG_USER_START   0x0003F000
#define DAPLINK_ROM_CONFIG_USER_SIZE    0x00001000

/* RAM sizes */

#define DAPLINK_RAM_APP_START           0x20000000
#define DAPLINK_RAM_APP_SIZE            0x0000FF00

#endif

#define DAPLINK_RAM_SHARED_START        0x2000FF00
#define DAPLINK_RAM_SHARED_SIZE         0x00000100

/* Flash Programming Info */

#define DAPLINK_SECTOR_SIZE             0x00001000
#define DAPLINK_MIN_WRITE_SIZE          0x00000100

/* Current build */

#if defined(DAPLINK_BL)

#define DAPLINK_ROM_APP_START            DAPLINK_ROM_BL_START
#define DAPLINK_ROM_APP_SIZE             DAPLINK_ROM_BL_SIZE
#define DAPLINK_ROM_UPDATE_START         DAPLINK_ROM_IF_START
#define DAPLINK_ROM_UPDATE_SIZE          DAPLINK_ROM_IF_SIZE

#elif defined(DAPLINK_IF)

#define DAPLINK_ROM_APP_START            DAPLINK_ROM_IF_START
#define DAPLINK_ROM_APP_SIZE             DAPLINK_ROM_IF_SIZE
#define DAPLINK_ROM_UPDATE_START         DAPLINK_ROM_BL_START
#define DAPLINK_ROM_UPDATE_SIZE          DAPLINK_ROM_BL_SIZE

#else

#error "Build must be either bootloader or interface"

#endif

#endif
