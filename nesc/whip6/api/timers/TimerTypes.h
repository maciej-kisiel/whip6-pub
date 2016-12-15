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


#ifndef __TIMER_TYPES_H__
#define __TIMER_TYPES_H__

typedef struct { uint8_t dummy; } TMilli;  // 1024 ticks per second
typedef struct { uint8_t dummy; } T32khz;  // 32768 ticks per second
typedef struct { uint8_t dummy; } TMicro;  // 1048576 ticks per second

// Ticks of the MCU clock.
typedef struct { uint8_t dummy; } TMcuClk;

// Radio clock for accurrate radio MAC timing. To get its interval, use
// the RadioClockFrequency interface.
typedef struct { uint8_t dummy; } TRadio;

#endif /* __TIMER_TYPES_H__ */
