#!/bin/bash

LOC=$(readlink -f "$0")
DIR=$(dirname "$LOC")

. "$DIR/dwm_bluetooth.sh"
. "$DIR/dwm_battery.sh"
. "$DIR/dwm_backlight.sh"
. "$DIR/dwm_alsa.sh"
. "$DIR/dwm_net_statistics.sh"
. "$DIR/dwm_date.sh"
. "$DIR/dwm_net_type.sh"
. "$DIR/dwm_sysinfo.sh"
. "$DIR/dwm_weather.sh"
. "$DIR/dwm_uptime.sh"
. "$DIR/dwm_redshift.sh"
. "$DIR/dwm_pomodoro_running.sh"
. "$DIR/dwm_ping_blog.sh"
. "$DIR/dwm_bitcoin_price.sh"

xsetroot -name "|$(dwm_net_type) $(dwm_net_statistics)|$(dwm_sysinfo)|$(dwm_backlight) $(dwm_redshift)|$(dwm_alsa)|$(dwm_bluetooth)|$(dwm_battery)|$(dwm_bitcoin_price)|$(dwm_weather)|$(dwm_uptime) $(dwm_pomodoro_running) $(dwm_ping_blog)|$(dwm_date) "

exit
