#!/bin/bash

vol=$(amixer get Master | tail -n1 | sed -r "s/.*\[(.*)%\].*/\1/")
mute="$(amixer get Master | sed -n '$p' | cut -d] -f3 | cut -d[ -f2)"

if [ "$mute" == "off" ]; then
    amixer sset Speaker toggle
    amixer sset Master toggle
else
    amixer sset Master toggle
fi
