#!/usr/bin/env sh

######################################################################
# @author      : kistenklaus (karlsasssie@gmail.com)
# @file        : run
# @created     : Sonntag Jun 23, 2024 14:24:48 CEST
#
# @description : 
######################################################################

canzero gen power_board24 src/canzero
cmake -Bbuild
make -C build
alacritty -e ./build/power-board24&


