#
# whip6: Warsaw High-performance IPv6.
#
# Copyright (c) 2012-2016 InviNets Sp z o.o.
# All rights reserved.
#
# This file is distributed under the terms in the attached LICENSE     
# files. If you do not find these files, copies can be found by writing
# to technology@invinets.com.
#
app name: CoreIeee154StackDemoApp
boards:
  - bboard
  - climboard
  - corebox
  - fedo
  - hyboard
  - mr3020
  - cc2650dk
define:
  - WHIP6_IEEE154_OLD_STACK
build dir: $(SPEC_DIR)/build/$(BOARD)
