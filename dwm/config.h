#include <X11/XF86keysym.h>
/* See LICENSE file for copyright and license details. */

/* appearance */
static const unsigned int borderpx  = 3;        /* border pixel of windows */
static const unsigned int snap      = 5;       /* snap pixel */
static const unsigned int gappih    = 5;       /* horiz inner gap between windows */
static const unsigned int gappiv    = 5;       /* vert inner gap between windows */
static const unsigned int gappoh    = 5;       /* horiz outer gap between windows and screen edge */
static const unsigned int gappov    = 5;       /* vert outer gap between windows and screen edge */
static const int smartgaps          = 0;        /* 1 means no outer gap when there is only one window */
static const int showbar            = 1;        /* 0 means no bar */
static const int topbar             = 1;        /* 0 means bottom bar */
static const Bool viewontag         = True;     /* Switch view on tag switch */
static const char *fonts[]          = { "Noto Sans Mono:size=16", "Symbola:size=16" };
static const char dmenufont[]       = "Noto Sans Mono:size=16";
static const char col_gray1[]       = "#222222";
static const char col_gray2[]       = "#444444";
static const char col_gray3[]       = "#bbbbbb";
static const char col_gray4[]       = "#eeeeee";
static const char col_cyan[]        = "#005577";
static const char col_pink[]        = "#ff3399";
static const unsigned int baralpha  = 0xd0;
static const unsigned int borderalpha = OPAQUE;
static const char *colors[][3]      = {
	/*               fg         bg         border   */
	[SchemeNorm] = { col_gray3, col_gray1, col_gray2 },
	[SchemeSel]  = { col_gray4, col_cyan,  col_pink  },
	[SchemeHid]  = { col_cyan,  col_gray1, col_pink  },
};

static const unsigned int alphas[][3]      = {
	/*               fg      bg        border     */
	[SchemeNorm] = { OPAQUE, baralpha, borderalpha },
	[SchemeSel]  = { OPAQUE, baralpha, borderalpha },
};

/* tagging */
static const char *tags[] = { ">_", "", "", "", "", "", "", "", "" };

static const Rule rules[] = {
	/* xprop(1):
	 *	WM_CLASS(STRING) = instance, class
	 *	WM_NAME(STRING) = title
	 */
	/* class                  instance                title       tags mask     isfloating   monitor */
	{ "Gimp",                 "gimp",                 NULL,       0,            1,           -1 },
    // { "Google-chrome",        "google-chrome",        NULL,       1 << 8,       0,           -1 },
    // { "Firefox",        "firefox",        NULL,       1 << 8,       0,           -1 },
    // { "Zathura",             "zathura",               NULL,       1 << 7,       0,           -1 },
	// { "Vlc",                  "vlc",                  NULL,       1 << 6,       0,           -1 },
	// { "St",                   "st",                   NULL,       1 << 1,       0,           -1 },
};

/* layout(s) */
static const float mfact     = 0.55; /* factor of master area size [0.05..0.95] */
static const int nmaster     = 1;    /* number of clients in master area */
static const int resizehints = 1;    /* 1 means respect size hints in tiled resizals */

static const Layout layouts[] = {
	/* symbol     arrange function */
	{ "[=]",      tile },    /* first entry is default */
	{ "~~",      NULL },    /* no layout function means floating behavior */
	{ "<>",   monocle },
};

/* key definitions */
#define MODKEY Mod4Mask // win 键
#define TAGKEYS(KEY,TAG) \
	{ MODKEY,                       KEY,      view,           {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask,           KEY,      toggleview,     {.ui = 1 << TAG} }, \
	{ MODKEY|ShiftMask,             KEY,      tag,            {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask|ShiftMask, KEY,      toggletag,      {.ui = 1 << TAG} },

/* helper for spawning shell commands in the pre dwm-5.0 fashion */
#define SHCMD(cmd) { .v = (const char*[]){ "/bin/sh", "-c", cmd, NULL } }

/* commands */
static char dmenumon[2] = "0"; /* component of dmenucmd, manipulated in spawn() */
static const char *dmenucmd[] = { "dmenu_run", "-m", dmenumon, "-fn", dmenufont, "-nb", col_gray1, "-nf", col_gray3, "-sb", col_cyan, "-sf", col_gray4, NULL };
static const char *termcmd[]  = { "st", NULL };
static const char scratchpadname[] = "scratchpad";
static const char *scratchpadcmd[] = { "st", "-t", scratchpadname, "-g", "120x34", NULL };

static const char *volupscript[] = {"/home/blue/.dwm/vol-up.sh", NULL};
static const char *voldownscript[] = {"/home/blue/.dwm/vol-down.sh", NULL};
static const char *voltogglescript[] = {"/home/blue/.dwm/vol-toggle.sh", NULL};
static const char *backlight_up[] = {"/home/blue/.dwm/backlight-up.sh", NULL};
static const char *backlight_down[] = {"/home/blue/.dwm/backlight-down.sh", NULL};
static const char *network_manager[] = {"/home/blue/.dwm/network-manager.sh", NULL};
static const char *suspend[] = { "/home/blue/.dwm/suspend.sh", NULL };
static const char *screenshotcmd[] = { "flameshot", "gui", NULL };
static const char *lockscreen[] = {"slock", NULL };

static Key keys[] = {
	/* modifier                     key        function        argument */

    // 音量和屏幕亮度控制
	{ 0,          XF86XK_AudioRaiseVolume,     spawn,          {.v = volupscript } },
	{ 0,          XF86XK_AudioLowerVolume,     spawn,          {.v = voldownscript } },
	{ 0,                 XF86XK_AudioMute,     spawn,          {.v = voltogglescript } },
	{ 0,           XF86XK_MonBrightnessUp,     spawn,          {.v = backlight_up } },
	{ 0,           XF86XK_MonBrightnessDown,   spawn,          {.v = backlight_down } },

	{ MODKEY|ControlMask,           XK_n,      spawn,          {.v = network_manager } }, // 网络控制
	{ MODKEY|ControlMask,           XK_s,      spawn,          {.v = suspend } }, // 待机
	{ MODKEY|ControlMask,           XK_l,      spawn,           {.v = lockscreen } }, // 锁屏
	{ MODKEY|ControlMask,           XK_q,      quit,           {0} }, // 退出dwm

	{ MODKEY,                       XK_space,      spawn,          {.v = dmenucmd } },
	{ MODKEY,                       XK_Return,      spawn,          {.v = termcmd } },
	{ MODKEY,                       XK_p,     togglescratch,  {.v = scratchpadcmd } }, // 弹出一个临时窗口
	{ MODKEY,                       XK_s,      spawn,          {.v = screenshotcmd } }, // 屏幕截图
	{ MODKEY,                       XK_b,      togglebar,      {0} }, // 是否隐藏状态栏
	{ MODKEY,                       XK_j,      focusstackvis,  {.i = +1 } }, // 不同窗口切换
	{ MODKEY,                       XK_k,      focusstackvis,  {.i = -1 } }, // 不同窗口切换
	{ MODKEY,                       XK_h,      setmfact,       {.f = +0.05} }, // 调整窗口大小
	{ MODKEY,                       XK_l,      setmfact,       {.f = -0.05} }, // 调整窗口大小
	{ MODKEY,                       XK_i,      incnmaster,     {.i = +1 } }, // 窗口重排
	{ MODKEY,                       XK_d,      incnmaster,     {.i = -1 } }, // 窗口重排
	{ MODKEY,                       XK_0,      view,           {.ui = ~0 } }, // 水平平铺窗口
	{ MODKEY,                       XK_Tab,    view,           {0} },  // 切换最近两个tag
	{ MODKEY,                       XK_c,      killclient,     {0} }, // 关闭一个窗口

    // 设置窗口模式
	{ MODKEY,                       XK_t,      setlayout,      {.v = &layouts[0]} },
	{ MODKEY,                       XK_f,      setlayout,      {.v = &layouts[1]} },
	{ MODKEY,                       XK_m,      setlayout,      {.v = &layouts[2]} },
	{ MODKEY,                       XK_g,      togglegaps,     {0} }, // 显示/隐藏gap

	{ MODKEY|ShiftMask,             XK_g,      defaultgaps,    {0} }, // 恢复默认gap
	{ MODKEY|ShiftMask,             XK_j,      focusstackhid,  {.i = +1 } }, // 不同tag切换
	{ MODKEY|ShiftMask,             XK_k,      focusstackhid,  {.i = -1 } }, // 不同tag切换
	{ MODKEY|ShiftMask,             XK_h,      hide,           {0} }, // 隐藏窗口
	{ MODKEY|ShiftMask,             XK_s,      show,           {0} }, // 显示隐藏的窗口
	{ MODKEY|ShiftMask,             XK_0,      tag,            {.ui = ~0 } }, // 平铺所有窗口
	{ MODKEY|ShiftMask,             XK_Return, zoom,           {0} }, // 当前和上一个窗口切换

	{ MODKEY,                       XK_comma,  focusmon,       {.i = -1 } },
	{ MODKEY,                       XK_period, focusmon,       {.i = +1 } },
	{ MODKEY|ShiftMask,             XK_comma,  tagmon,         {.i = -1 } },
	{ MODKEY|ShiftMask,             XK_period, tagmon,         {.i = +1 } },

    // 1-9 tag 切换
	TAGKEYS(                        XK_1,                      0)
	TAGKEYS(                        XK_2,                      1)
	TAGKEYS(                        XK_3,                      2)
	TAGKEYS(                        XK_4,                      3)
	TAGKEYS(                        XK_5,                      4)
	TAGKEYS(                        XK_6,                      5)
	TAGKEYS(                        XK_7,                      6)
	TAGKEYS(                        XK_8,                      7)
	TAGKEYS(                        XK_9,                      8)


	// { MODKEY|Mod4Mask,              XK_h,      incrgaps,       {.i = +1 } },
	// { MODKEY|Mod4Mask,              XK_l,      incrgaps,       {.i = -1 } },
	// { MODKEY|Mod4Mask|ShiftMask,    XK_h,      incrogaps,      {.i = +1 } },
	// { MODKEY|Mod4Mask|ShiftMask,    XK_l,      incrogaps,      {.i = -1 } },
	// { MODKEY|Mod4Mask|ControlMask,  XK_h,      incrigaps,      {.i = +1 } },
	// { MODKEY|Mod4Mask|ControlMask,  XK_l,      incrigaps,      {.i = -1 } },


    // 调整gap
	// { MODKEY,                       XK_y,      incrihgaps,     {.i = +1 } },
	// { MODKEY,                       XK_o,      incrihgaps,     {.i = -1 } },
	// { MODKEY|ControlMask,           XK_y,      incrivgaps,     {.i = +1 } },
	// { MODKEY|ControlMask,           XK_o,      incrivgaps,     {.i = -1 } },
	// { MODKEY|Mod4Mask,              XK_y,      incrohgaps,     {.i = +1 } },
	// { MODKEY|Mod4Mask,              XK_o,      incrohgaps,     {.i = -1 } },
	// { MODKEY|ShiftMask,             XK_y,      incrovgaps,     {.i = +1 } },
	// { MODKEY|ShiftMask,             XK_o,      incrovgaps,     {.i = -1 } },

    // { MODKEY,                       XK_space,  setlayout,      {0} },
	// { MODKEY|ShiftMask,             XK_space,  togglefloating, {0} },
};

/* button definitions */
/* click can be ClkTagBar, ClkLtSymbol, ClkStatusText, ClkWinTitle, ClkClientWin, or ClkRootWin */
static Button buttons[] = {
	/* click                event mask      button          function        argument */
	{ ClkLtSymbol,          0,              Button1,        setlayout,      {0} },
	{ ClkLtSymbol,          0,              Button3,        setlayout,      {.v = &layouts[2]} },
	{ ClkWinTitle,          0,              Button1,        togglewin,      {0} },
	{ ClkWinTitle,          0,              Button2,        zoom,           {0} },
	{ ClkStatusText,        0,              Button2,        spawn,          {.v = termcmd } },
	{ ClkClientWin,         MODKEY,         Button1,        movemouse,      {0} },
	{ ClkClientWin,         MODKEY,         Button2,        togglefloating, {0} },
	{ ClkClientWin,         MODKEY,         Button3,        resizemouse,    {0} },
	{ ClkTagBar,            0,              Button1,        view,           {0} },
	{ ClkTagBar,            0,              Button3,        toggleview,     {0} },
	{ ClkTagBar,            MODKEY,         Button1,        tag,            {0} },
	{ ClkTagBar,            MODKEY,         Button3,        toggletag,      {0} },
};

