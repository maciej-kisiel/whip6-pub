/*
 * whip6: Warsaw High-performance IPv6.
 *
 * Copyright (c) 2012-2016 InviNets Sp z o.o.
 * All rights reserved.
 *
 * This file is distributed under the terms in the attached LICENSE     
 * files. If you do not find these files, copies can be found by writing
 * to technology@invinets.com.
 */

/**
 * @author Szymon Acedanski
 */

#include <inc/hw_memmap.h>
#include <AudioFormat.h>
#include "hal_configure_i2s.h"

generic configuration HalI2SPub(i2s_word_size_t wordSize,
        uint32_t preferredRate, i2s_clock_pol_t clockPol,
        audio_sample_format_t sampleFormat) {
    provides interface AudioInput;
    provides interface AudioFormat;

    uses interface OnOffSwitch;
}

implementation {
    components HplI2SInterruptPub;
    components new HalGenericI2SPrv(I2S0_BASE,
            wordSize == I2S_WORD_16BIT ? 2048 : 3072) as GenericI2S;
    GenericI2S.Interrupt -> HplI2SInterruptPub.I2SInterrupt;

    components HalI2SPinsPub as Pins;
    components new HalConfigureI2SPrv(I2S0_BASE, wordSize, preferredRate,
            clockPol, sampleFormat) as Configure;
    Configure.WCLKPin -> Pins.PWCLK;
    Configure.BCLKPin -> Pins.PBCLK;
    Configure.ADPin -> Pins.PAD;

    components HalDMAPub;
    Configure.DMAEngineOnOff -> HalDMAPub.ShareableOnOff;

    components CC26xxPowerDomainsPub as PowerDomains;
    Configure.PowerDomain -> PowerDomains.PeriphDomain;

    components new HalAskBeforeSleepPub();
    GenericI2S.AskBeforeSleep -> HalAskBeforeSleepPub;

    GenericI2S.HalI2SSampleSize -> Configure.HalI2SSampleSize;
    GenericI2S.OnOffSwitch -> Configure.OnOffSwitch;

    AudioInput = GenericI2S.AudioInput;
    AudioFormat = Configure.AudioFormat;
    OnOffSwitch = GenericI2S.OnOffSwitch;
}
