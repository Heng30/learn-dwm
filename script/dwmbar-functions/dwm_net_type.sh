#!/bin/bash

function net_type_icon(){
    wlan_id=$(rfkill list all | grep -e 'Wireless LAN' | cut -d ':' -f1)

    if [ $? -eq 0 ]; then
        rfkill list $wlan_id | grep -e 'yes' > /dev/null
        if [ $? -eq 0 ]; then
            printf "🛫"
            exit
        fi
    fi

    value=$(iwctl station wlan0 show | grep 'State' | awk '{ print $2 }')
    if [ $value = "connected" ];then
        printf "📶 "
    else
        printf "❎"
    fi
}

function net_name() {
    printf "$(iwctl station wlan0 show | grep "network" | awk '{ print $3 }')"
}

function dwm_net_type(){
    printf "$(net_type_icon)$(net_name)"
}

