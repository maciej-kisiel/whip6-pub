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
 * @author Szymon Acedanski <accek@mimuw.edu.pl>
 */

#include <NetStackCompileTimeConfig.h>

configuration PlatformFrameAllocatorPub {
    provides interface ObjectAllocator<platform_frame_t> as FrameAllocator;
}
implementation {
    components BoardStartupPub;
    components new PoolPub(platform_frame_t, WHIP6_IEEE154_MAX_CONCURRENT_FRAMES);
    BoardStartupPub.InitSequence[0] -> PoolPub;
    FrameAllocator = PoolPub;
}
