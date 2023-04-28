#!/bin/bash

vol=$(amixer get Master | tail -n1 | sed -r "s/.*\[(.*)%\].*/\1/")
mute="$(amixer get Master | sed -n '$p' | cut -d] -f3 | cut -d[ -f2)"

if [ "$mute" == "off" ]; then
    amixer sset Speaker on
    amixer sset Headphone on
    amixer sset Master on
else
    amixer sset Speaker off
    amixer sset Headphone off
    amixer sset Master off
fi
