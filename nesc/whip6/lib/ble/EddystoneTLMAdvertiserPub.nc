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


generic configuration EddystoneTLMAdvertiserPub(uint32_t intervalMs) {
    provides interface OnOffSwitch @exactlyonce();

    uses interface DimensionalRead<TDeciCelsius, int16_t> as Temperature
        @atmostonce();
    uses interface DimensionalRead<TMilliVolt, int16_t> as VDDDividedBy3
        @atmostonce();
}
implementation {
    components new EddystoneTLMAdvertiserPrv(intervalMs) as Prv;

    components new PlatformBLEAdvertiserPub();
    Prv.RawBLEAdvertiser -> PlatformBLEAdvertiserPub;
    Prv.AdvertisementsSent <-
        PlatformBLEAdvertiserPub.NumSuccessfulBLEAdvTXStat;

    components new PlatformTimerMilliPub() as Timer;
    Prv.Timer -> Timer;
    Prv.TimerOverflow -> Timer;

    components PlatformRandomPub as Random;
    Prv.Random -> Random;

    OnOffSwitch = Prv;
    Temperature = Prv.Temperature;
    VDDDividedBy3 = Prv.VDDDividedBy3;
}
