#!/bin/bash

function dwm_battery(){
    percent=$(acpi -b | grep "Battery 0" | awk -F ',' '{print $2}');
    icon="🔌";
    if $(acpi -b | grep "Battery 0" | grep --quiet Discharging); then
        icon="🔋";
    fi

    printf "%s%4s" $icon $percent;
}

