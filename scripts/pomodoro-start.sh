#!/bin/bash

m=15
time=$((m * 60))
dir=~/private-data/pomodoro
ymd=$(date +%Y-%m-%d)
start_time=$(date +%Y-%m-%d-%H:%M)
filename=$dir/$ymd.log
info=$(printf "%s %d start" $start_time $m)

sleep $time

echo $info >> $filename

pomodoro
# st sleep 10000
