#!/bin/bash

function dwm_alsa () {
    vol=$(amixer get Master | tail -n1 | sed -r "s/.*\[(.*)%\].*/\1/")
    mute="$(amixer get Master | sed -n '$p' | cut -d] -f3 | cut -d[ -f2)"

    if [ "$vol" -eq 0 ] || [ "$mute" == "off" ]; then
        printf "🔇 "
    else
        printf  "🔊%3s%%" "$vol"
    fi
}
