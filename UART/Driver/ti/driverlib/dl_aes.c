/*
 * Copyright (c) 2020, Texas Instruments Incorporated
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 *
 * *  Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 *
 * *  Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 *
 * *  Neither the name of Texas Instruments Incorporated nor the names of
 *    its contributors may be used to endorse or promote products derived
 *    from this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO,
 * THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
 * PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR
 * CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
 * EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
 * PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS;
 * OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
 * WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR
 * OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE,
 * EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#include <ti/driverlib/dl_aes.h>

#ifdef __MSPM0_HAS_AES__

static void LoadData(volatile uint32_t *pReg, uint32_t *pData, uint8_t len);
static uint8_t GetNumOfWords(uint32_t keyLength);

void DL_AES_setKey(
    AES_Regs *aes, const uint8_t *key, DL_AES_KEY_LENGTH keyLength)
{
    uint8_t len;
    uintptr_t addr;
    uint32_t *pData;

    addr  = (uintptr_t) key;
    pData = (uint32_t *) addr;

    len = GetNumOfWords((uint32_t) keyLength);
    LoadData(&aes->AESAKEY, pData, len);
}

void DL_AES_loadDataIn(AES_Regs *aes, const uint8_t *data)
{
    uintptr_t addr;
    uint32_t *pData;

    addr  = (uintptr_t) data;
    pData = (uint32_t *) addr;

    LoadData(&aes->AESADIN, pData, 4);
}

void DL_AES_getDataOut(AES_Regs *aes, uint8_t *data)
{
    uint8_t i;
    uintptr_t addr;
    uint32_t *pData;

    addr  = (uintptr_t) data;
    pData = (uint32_t *) addr;

    for (i = 0; i < (uint8_t) 4; i++) {
        *pData++ = aes->AESADOUT;
    }
}

void DL_AES_loadXORDataIn(AES_Regs *aes, const uint8_t *data)
{
    uintptr_t addr;
    uint32_t *pData;

    addr  = (uintptr_t) data;
    pData = (uint32_t *) addr;

    LoadData(&aes->AESAXDIN, pData, 4);
}

void DL_AES_loadXORDataInWithoutTrigger(AES_Regs *aes, const uint8_t *data)
{
    uintptr_t addr;
    uint32_t *pData;

    addr  = (uintptr_t) data;
    pData = (uint32_t *) addr;

    LoadData(&aes->AESAXIN, pData, 4);
}

void DL_AES_xorData(uint8_t *data, uint8_t *xorData, uint8_t *xorOutputData)
{
    uint8_t i;

    uint8_t *tempData          = data;
    uint8_t *tempXorData       = xorData;
    uint8_t *tempXorOutputData = xorOutputData;

    for (i = 0; i < (uint8_t) 16; i++) {
        *tempXorOutputData++ = *tempData++ ^ *tempXorData++;
    }
}

static void LoadData(volatile uint32_t *pReg, uint32_t *pData, uint8_t len)
{
    uint8_t i;
    uint32_t *pTemp;

    pTemp = pData;

    for (i = 0; i < len; i++) {
        *pReg = *pTemp++;
    }
}

static uint8_t GetNumOfWords(uint32_t keyLength)
{
    const uint8_t KeyLengths[] = {4, 6, 8};

    return (KeyLengths[keyLength >> AES_AESACTL0_KLX_OFS]);
}

bool DL_AES_saveConfiguration(AES_Regs *aes, DL_AES_backupConfig *ptr)
{
    bool stateSaved = !ptr->backupRdy;
    if (stateSaved) {
        ptr->controlWord0   = aes->AESACTL0;
        ptr->controlWord1   = aes->AESACTL1;
        ptr->interruptMask0 = aes->INT_EVENT0.IMASK;
        ptr->interruptMask1 = aes->INT_EVENT1.IMASK;
        ptr->interruptMask2 = aes->INT_EVENT2.IMASK;
        ptr->interruptMask3 = aes->INT_EVENT3.IMASK;
        ptr->backupRdy      = true;
    }
    return stateSaved;
}

bool DL_AES_restoreConfiguration(AES_Regs *aes, DL_AES_backupConfig *ptr)
{
    bool stateRestored = ptr->backupRdy;
    if (stateRestored) {
        aes->AESACTL0         = ptr->controlWord0;
        aes->AESACTL1         = ptr->controlWord1;
        aes->INT_EVENT0.IMASK = ptr->interruptMask0;
        aes->INT_EVENT1.IMASK = ptr->interruptMask1;
        aes->INT_EVENT2.IMASK = ptr->interruptMask2;
        aes->INT_EVENT3.IMASK = ptr->interruptMask3;
        ptr->backupRdy        = false;
    }
    return stateRestored;
}

#endif /* __MSPM0_HAS_AES__ */
