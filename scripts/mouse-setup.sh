#!/bin/bash

# Get id of touchpad and the id of the field corresponding to tapping to click
id=`xinput list | grep "Rapoo" | cut -d'=' -f2 | cut -d'[' -f1`

left_handed_enable=`xinput list-props $id | grep "Left Handed Enabled (" \
                      | cut -d'(' -f2 | cut -d')' -f1`

# 启用鼠标左手
xinput --set-prop $id $left_handed_enable 1
