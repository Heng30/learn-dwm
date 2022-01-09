#!/bin/bash

echo 'BTC $0' > /tmp/bitcoin_price.dat

# 状态栏显示设置
/bin/bash ~/.dwm/dwmbar-functions/dwm_status_refresh.sh &

# 背景图片设置
/bin/bash ~/.dwm/change_wallpaper.sh &

# 后台定时任务
/bin/bash ~/.dwm/dwm-bg-task/dwm_bg_timer.sh &

# 键盘启动设置
/bin/bash ~/.dwm/keyboard-setup.sh &

# 开启触摸板点击功能
/bin/bash ~/.dwm/touchpad-setup.sh &

# 开启shadowsock
/bin/bash ~/.dwm/shadowsock-manager.sh &

# 设置屏幕色温
/bin/bash ~/.dwm/redshift-setup.sh &

/bin/bahs ~/.dwm/nvidia-gpu-setup.sh &

# start fcitx, 支持中文输入法的框架
fcitx5 &

# 启动翻译
simdict-baidu &

# 启动todo list
simtdl &

# 获取窗口名称, 用于设置imwhell
# xprop WM_CLASS | grep -o '"[^"]*"' | head -n 1

# 设置鼠标, 不阻塞前后按键
imwheel -b 45 &

# 加载透明背景控件
picom -b --backend glx --vsync --unredir-if-possible --glx-no-stencil

# Disables Energy Star features
xset -dpms

# Disables screen saver
xset s off

# 启动st
st

