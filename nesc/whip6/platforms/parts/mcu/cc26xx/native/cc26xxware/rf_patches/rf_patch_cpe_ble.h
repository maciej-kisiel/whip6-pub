/******************************************************************************
*  Filename:       rf_patch_cpe_ble.h
*  Revised:        2015-10-30 10:00:00 +0100 (fr, 30 Oct 2015)
*  Revision:       
*
*  Description:    RF Core patch file for CC26xx Bluetooth Low Energy
*
*  Copyright (c) 2015, Texas Instruments Incorporated
*  All rights reserved.
*
*  Redistribution and use in source and binary forms, with or without
*  modification, are permitted provided that the following conditions are met:
*
*  1) Redistributions of source code must retain the above copyright notice,
*     this list of conditions and the following disclaimer.
*
*  2) Redistributions in binary form must reproduce the above copyright notice,
*     this list of conditions and the following disclaimer in the documentation
*     and/or other materials provided with the distribution.
*
*  3) Neither the name of the ORGANIZATION nor the names of its contributors may
*     be used to endorse or promote products derived from this software without
*     specific prior written permission.
*
*  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
*  AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
*  IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
*  ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE
*  LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
*  CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
*  SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
*  INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
*  CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
*  ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
*  POSSIBILITY OF SUCH DAMAGE.
*
******************************************************************************/

#ifndef _RF_PATCH_CPE_BLE_H
#define _RF_PATCH_CPE_BLE_H

//*****************************************************************************
//
// If building with a C++ compiler, make all of the definitions in this header
// have a C binding.
//
//*****************************************************************************
#ifdef __cplusplus
extern "C"
{
#endif

#include <stdint.h>
#include <string.h>

#ifndef CPE_PATCH_TYPE
#define CPE_PATCH_TYPE static const uint32_t
#endif

#ifndef SYS_PATCH_TYPE
#define SYS_PATCH_TYPE static const uint32_t
#endif

#ifndef PATCH_FUN_SPEC
#define PATCH_FUN_SPEC static inline
#endif

#ifndef _APPLY_PATCH_TAB
#define _APPLY_PATCH_TAB
#endif


CPE_PATCH_TYPE patchImageBle[] = {
   0x21000471,
   0x4c17b5f0,
   0x18612140,
   0x280278c8,
   0x4809d005,
   0x60012100,
   0x47884908,
   0x6e25bdf0,
   0x60354e07,
   0x43280760,
   0x68276620,
   0x480e6024,
   0x60274780,
   0xbdf06035,
   0x4004112c,
   0x000065a5,
   0x40044028,
   0x4c07b510,
   0x29007da1,
   0x2101d105,
   0x024875a1,
   0x393e4904,
   0x68204788,
   0xd0002800,
   0xbd104780,
   0x21000254,
   0x0000398b,
   0x4e1ab5f8,
   0x6b314605,
   0x09cc4819,
   0x2d0001e4,
   0x4918d011,
   0x29027809,
   0x7b00d00f,
   0xb6724304,
   0x4f152001,
   0x47b80240,
   0x38204811,
   0x09c18800,
   0xd00407c9,
   0x7ac0e016,
   0x7b40e7f0,
   0x490fe7ee,
   0x61cc6334,
   0x07c00a40,
   0x2001d00c,
   0x6af10380,
   0xd0012d00,
   0xe0004301,
   0x46084381,
   0x490762f1,
   0x63483940,
   0x47b82000,
   0xbdf8b662,
   0x21000280,
   0x21000088,
   0x21000296,
   0x00003cdf,
   0x40044040,
};
#define _NWORD_PATCHIMAGE_BLE 59

#define _NWORD_PATCHSYS_BLE 0

#define _IRQ_PATCH_0 0x21000409
#define _IRQ_PATCH_1 0x21000449


#define _BLE_SYS_PATCH_FIXED_ADDR 0x20000000

PATCH_FUN_SPEC void enterBleCpePatch(void)
{
   uint32_t *pPatchVec = (uint32_t *) 0x21000404;

#if (_NWORD_PATCHIMAGE_BLE > 0)
   memcpy(pPatchVec, patchImageBle, sizeof(patchImageBle));
#endif
}

PATCH_FUN_SPEC void enterBleSysPatch(void)
{
}

PATCH_FUN_SPEC void configureBlePatch(void)
{
   uint8_t *pPatchTab = (uint8_t *) 0x2100033C;
   uint32_t *pIrqPatch = (uint32_t *) 0x210003AC;


   pPatchTab[103] = 0;

   pIrqPatch[1] = _IRQ_PATCH_0;
   pIrqPatch[9] = _IRQ_PATCH_1;
}

PATCH_FUN_SPEC void rf_patch_cpe_ble(void)
{
   enterBleSysPatch();
   enterBleCpePatch();
   configureBlePatch();
}

PATCH_FUN_SPEC void refreshBlePatch(void)
{
   enterBleCpePatch();
   configureBlePatch();
}

#undef _IRQ_PATCH_0
#undef _IRQ_PATCH_1

//*****************************************************************************
//
// Mark the end of the C bindings section for C++ compilers.
//
//*****************************************************************************
#ifdef __cplusplus
}
#endif

#endif //  _APPLY_BLE_PATCH_H

