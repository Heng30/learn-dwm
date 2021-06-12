#!/bin/bash

# Get id of touchpad and the id of the field corresponding to tapping to click
id=`xinput list | grep "TouchPad" | cut -d'=' -f2 | cut -d'[' -f1`
tap_to_click_id=`xinput list-props $id | grep "Device Enabled (" \
                      | cut -d'(' -f2 | cut -d')' -f1`

move_speed=`xinput list-props $id | grep "Move Speed (" \
                      | cut -d'(' -f2 | cut -d')' -f1`

tap_action=`xinput list-props $id | grep "Tap Action (" \
                      | cut -d'(' -f2 | cut -d')' -f1`

# 启用触控板
xinput --set-prop $id $tap_to_click_id 1

# 设置速度
xinput set-prop $id $move_speed 4.0 2.5 2.0 1.0

# 设置双击触控板选中内容
xinput set-prop $id $tap_action 1 1 1 1 1 1 1
