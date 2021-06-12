#!/bin/bash

function dwm_pomodoro_running() {
    pid=$(ps -ef | grep "pomodoro-start.sh" | grep "/bin/bash" | awk '{print $2}')

    if [ "$pid" == "" ]; then
        echo "X"
    else
        echo "Y"
    fi
}

