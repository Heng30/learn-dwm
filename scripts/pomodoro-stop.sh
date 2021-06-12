#!/bin/bash

ps -ef | grep "pomodoro-start.sh" | grep "/bin/bash" | awk '{print $2}' | xargs kill -9


if [ $? -eq 0 ];then
    m=25
    time=$((m * 60))
    dir=~/private-data/pomodoro
    ymd=$(date +%Y-%m-%d)
    start_time=$(date +%Y-%m-%d-%H:%M)
    filename=$dir/$ymd.log
    info=$(printf "%s %d cancel" $start_time $m)
    echo $info >> $filename
fi

