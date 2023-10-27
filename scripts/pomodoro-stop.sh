#!/bin/bash

ps -ef | grep "pomodoro-start.sh" | grep "/bin/bash" | awk '{print $2}' | xargs kill -9
