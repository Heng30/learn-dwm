#!/bin/bash

vol=$(amixer get Master)
is_master=$(echo $vol | grep "Unable")

if [ "$is_master" == "" ]; then
    amixer -qM set Speaker 5%- umute
else
    amixer -qM set Master 5%- umute
fi
