/**
 * @file    flash_blob.c
 * @brief   Flash algorithm for the ke15z
 *
 * DAPLink Interface Firmware
 * Copyright (c) 2009-2019, ARM Limited, All Rights Reserved
 * SPDX-License-Identifier: Apache-2.0
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#include "flash_blob.h"

static const uint32_t mke02z64_flash_prog_blob[] = {
    0xE00ABE00, 0x062D780D, 0x24084068, 0xD3000040, 0x1E644058, 0x1C49D1FA, 0x2A001E52, 0x4770D1F2,
    0x49564857, 0x49578041, 0x21008041, 0x808143c9, 0x718121ff, 0x210171c1, 0x21207041, 0x49527001,
    0x70082010, 0x4951206f, 0x60c80280, 0x47702000, 0x47702000, 0x484cb530, 0x71812130, 0x70822200,
    0x72812109, 0x230172c2, 0x72827083, 0x248072c2, 0x79817184, 0xd5fc0609, 0x06c97981, 0x2008d501,
    0x7981bd30, 0x42292533, 0x7082d119, 0x72812106, 0x708372c2, 0x72812104, 0x72c1210c, 0x70812102,
    0x728121ff, 0x220372c1, 0x72817082, 0x72c121fe, 0x79817184, 0xd5fc0609, 0x40287980, 0x2001d0e0,
    0x4931bd30, 0x718a2230, 0x708a2200, 0x728a220a, 0x0e520242, 0x220172ca, 0x0a02708a, 0x72c8728a,
    0x71882080, 0x06007988, 0x7988d5fc, 0xd50106c0, 0x47702008, 0x21337988, 0xd0fa4008, 0x47702001,
    0x2400b570, 0x4b201dc9, 0xe03208cd, 0x71992130, 0x70992100, 0x72992106, 0x72d90c01, 0x70992101,
    0x72990a01, 0x210272d8, 0x78517099, 0x78117299, 0x210372d9, 0x78d17099, 0x78917299, 0x210472d9,
    0x79517099, 0x79117299, 0x210572d9, 0x79d17099, 0x79917299, 0x218072d9, 0x79997199, 0xd5fc0609,
    0x26337999, 0xd0014231, 0xbd702001, 0x30083208, 0x42a51c64, 0x2000d8ca, 0x0000bd70, 0x000020c5,
    0x40052000, 0x000028d9, 0x40020000, 0xf0003000, 0x00000000
};

/**
* List of start and size for each size of flash sector - even indexes are start, odd are size
* The size will apply to all sectors between the listed address and the next address
* in the list.
* The last pair in the list will have sectors starting at that address and ending
* at address flash_start + flash_size.
*/
static const sector_info_t sectors_info[] = {
    { 0x00000000, 0x00000200 }
};

static const program_target_t flash = {
    0x20000021, // Init
    0x20000051, // UnInit
    0x20000055, // EraseChip
    0x200000c3, // EraseSector
    0x20000101, // ProgramPage
    0x00000000, // Verify

    // BKPT : start of blob + 1
    // RSB  : blob start + header + rw data offset
    // RSP  : stack pointer
    {
        0x20000001,
        0x20000190,
        0x20000400
    },

    0x20000000 + 0x00000A00,  // mem buffer location
    0x20000000,               // location to write prog_blob in target RAM
    sizeof(mke02z64_flash_prog_blob),   // prog_blob size
    mke02z64_flash_prog_blob,           // address of prog_blob
    0x00000100       // ram_to_flash_bytes_to_be_written
};
