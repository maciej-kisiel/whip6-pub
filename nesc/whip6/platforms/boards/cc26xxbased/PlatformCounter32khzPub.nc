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

configuration PlatformCounter32khzPub {
  provides interface AsyncCounter<T32khz, uint32_t>;
  provides interface AsyncCounter<T32khz, uint64_t> as AsyncCounter64;
}
implementation {
  components HalCC26xxRTCPub as HalTimer;
  AsyncCounter = HalTimer;
  AsyncCounter64 = HalTimer;
}
