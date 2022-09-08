/* See LICENSE file for copyright and license details. */

/* appearance */
static const unsigned int borderpx  = 1;        /* border pixel of windows */
static const unsigned int snap      = 32;       /* snap pixel */
static const unsigned int systraypinning = 0;   /* 0: sloppy systray follows selected monitor, >0: pin systray to monitor X */
static const unsigned int systrayonleft = 0;   	/* 0: systray in the right corner, >0: systray on left of status text */
static const unsigned int systrayspacing = 2;   /* systray spacing */
static const int systraypinningfailfirst = 1;   /* 1: if pinning fails, display systray on the first monitor, False: display systray on the last monitor*/
static const int showsystray        = 1;     /* 0 means no systray */
static const int showbar            = 1;     /* 0 means no bar */
static const int topbar             = 1;     /* 0 means bottom bar */
static const char *fonts[]          = { "DejaVuSansMono:size=9:antialias=true:autohint=true", "DejaVuSansMono Nerd Font:size=12:antialias=true:autohint=true"};
static const char dmenufont[]       = "DejaVuSansMono:size=9:antialias=true:autohint=true";
static const char col_bar[]         = "#2c1a1a";
static const char col_border[]      = "#2c1a1a";
static const char col_white[]       = "#efefef";
static const char col_title[]       = "#000000";
static const char col_cyan[]        = "#5cd5ff";
static const char *colors[][3]      = {
	/*               fg         bg         border   */
	[SchemeNorm] = { col_white, col_bar,   col_border },
	[SchemeSel]  = { col_title, col_cyan,  col_border  },
};

static const char *const autostart[] = {
        "slstatus", NULL,
        "gxkb", NULL,
        "/usr/lib/xfce4/notifyd/xfce4-notifyd", NULL,
        "pasystray", "--notify=sink_default", "--notify=source_default", NULL,
        "nm-applet", NULL,
        "xfce4-clipman", NULL,
        "sh", "/home/yan/git/github/unixStuff/xrandr.sh", "1", NULL,
        "keepassxc", NULL,
        "sh", "/home/yan/git/github/unixStuff/set_bg", "/home/yan/Pictures/bg", "2", NULL,
	NULL /* terminate */
};

/* tagging */
static const char *tags[] = { "1", "2", "3", "4", "5", "6", "7", "8", "9" };

static const char *tagsel[][2] = {
        { "#ffffff", "#00aaff" },
	{ "#ffffff", "#ff0000" },
	{ "#ffffff", "#ff7f00" },
        { "#000000", "#fff44f" },
	{ "#000000", "#a4f44f" },
	{ "#ffffff", "#ff55ff" },
	{ "#ffffff", "#9400d3" },
	{ "#ffffff", "#468368" },
	{ "#ffffff", "#ff8368" },
};

static const int tagurgbar[] = { 1, 3, 6, 5, 8, 7, 4, 1, 0 };

static const Rule rules[] = {
	/* xprop(1):
	 *	WM_CLASS(STRING) = instance, class
	 *	WM_NAME(STRING) = title
	 */
	/* class      instance    title       tags mask     isfloating   monitor */
	//{ "Gimp",     NULL,       NULL,       0,            1,           -1 },
	{ "KeePassXC",  NULL,       NULL,       1 << 8,       0,            0 },
};

/* layout(s) */
static const float mfact     = 0.55; /* factor of master area size [0.05..0.95] */
static const int nmaster     = 1;    /* number of clients in master area */
static const int resizehints = 1;    /* 1 means respect size hints in tiled resizals */
static const int lockfullscreen = 1; /* 1 will force focus on the fullscreen window */

static const Layout layouts[] = {
	/* symbol     arrange function */
	{ "[]=",      tile },    /* first entry is default */
	{ "><>",      NULL },    /* no layout function means floating behavior */
	{ "[M]",      monocle },
};

/* key definitions */
#define MODKEY Mod4Mask
#define TAGKEYS(KEY,TAG) \
	{ MODKEY,                       KEY,      view,           {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask,           KEY,      toggleview,     {.ui = 1 << TAG} }, \
	{ MODKEY|ShiftMask,             KEY,      tag,            {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask|ShiftMask, KEY,      toggletag,      {.ui = 1 << TAG} },

/* Media keys */
#include <X11/XF86keysym.h>

static const char *upvol[]   = { "/usr/bin/pactl", "set-sink-volume", "0", "+5%",     NULL };
static const char *downvol[] = { "/usr/bin/pactl", "set-sink-volume", "0", "-5%",     NULL };
static const char *mutevol[] = { "/usr/bin/pactl", "set-sink-mute",   "0", "toggle",  NULL };

static const char *uplight[] = { "sh", "/home/yan/git/github/unixStuff/brightness.sh", "up", NULL };
static const char *downlight[] = { "sh", "/home/yan/git/github/unixStuff/brightness.sh", "down", NULL };

/* Run the susppend script */
static const char *suspend[] = { "sh", "/home/yan/git/github/unixStuff/suspend.sh", NULL };

/* Lock screen */
static const char *slock[] = { "/usr/local/bin/slock", NULL };

/* Take a screenshot */
static const char *printscreen[] = { "/usr/bin/xfce4-screenshooter", NULL };

/* Open clipman */
static const char *clipman[] = { "/usr/bin/xfce4-popup-clipman", NULL };

/* Poweroff */
static const char *poweroff[] = { "/usr/bin/poweroff", NULL };

/* Update screen layout */
static const char *xrandr[] = { "sh", "/home/yan/git/github/unixStuff/xrandr.sh", "0", NULL };

/* Run Syncthing script */
static const char *syncthing[] = { "sh", "/home/yan/git/github/unixStuff/syncthing.sh", NULL };

/* commands */
static const char *dmenucmd[] = { "dmenu_run", "-fn", dmenufont, "-nb", col_gray1, "-nf", col_gray3, "-sb", col_cyan, "-sf", col_gray4, NULL };
static const char *termcmd[]  = { "st", NULL };

static const Key keys[] = {
	/* modifier                     key        function        argument */
	{ MODKEY,                       XK_p,      spawn,          {.v = dmenucmd } },
	{ MODKEY|ShiftMask,             XK_Return, spawn,          {.v = termcmd } },
	{ MODKEY,                       XK_j,      focusstack,     {.i = +1 } },
	{ MODKEY,                       XK_k,      focusstack,     {.i = -1 } },
	{ MODKEY,                       XK_i,      incnmaster,     {.i = +1 } },
	{ MODKEY,                       XK_d,      incnmaster,     {.i = -1 } },
	{ MODKEY,                       XK_h,      setmfact,       {.f = -0.05} },
	{ MODKEY,                       XK_l,      setmfact,       {.f = +0.05} },
	{ MODKEY,                       XK_Return, zoom,           {0} },
	{ MODKEY,                       XK_Tab,    view,           {0} },
	{ MODKEY|ShiftMask,             XK_c,      killclient,     {0} },
	{ MODKEY,                       XK_t,      setlayout,      {.v = &layouts[0]} },
	{ MODKEY,                       XK_f,      setlayout,      {.v = &layouts[1]} },
	{ MODKEY,                       XK_m,      setlayout,      {.v = &layouts[2]} },
	{ MODKEY,                       XK_space,  setlayout,      {0} },
	{ MODKEY|ShiftMask,             XK_space,  togglefloating, {0} },
	{ MODKEY,                       XK_0,      view,           {.ui = ~0 } },
	{ MODKEY|ShiftMask,             XK_0,      tag,            {.ui = ~0 } },
	{ MODKEY,                       XK_comma,  focusmon,       {.i = +1 } },
	{ MODKEY,                       XK_period, focusmon,       {.i = -1 } },
	{ MODKEY|ShiftMask,             XK_comma,  tagmon,         {.i = +1 } },
	{ MODKEY|ShiftMask,             XK_period, tagmon,         {.i = -1 } },
	TAGKEYS(                        XK_1,                      0)
	TAGKEYS(                        XK_2,                      1)
	TAGKEYS(                        XK_3,                      2)
	TAGKEYS(                        XK_4,                      3)
	TAGKEYS(                        XK_5,                      4)
	TAGKEYS(                        XK_6,                      5)
	TAGKEYS(                        XK_7,                      6)
	TAGKEYS(                        XK_8,                      7)
	TAGKEYS(                        XK_9,                      8)
	{ MODKEY|ShiftMask,             XK_q,      quit,           {0} },


        { 0,                            XF86XK_AudioLowerVolume, spawn, {.v = downvol } },
	{ 0,                            XF86XK_AudioMute,        spawn, {.v = mutevol } },
	{ 0,                            XF86XK_AudioRaiseVolume, spawn, {.v = upvol } },
	{ 0,                            XF86XK_MonBrightnessUp,  spawn, {.v = uplight } },
	{ 0,                            XF86XK_MonBrightnessDown,spawn, {.v = downlight } },
	{ 0,                            XF86XK_Sleep,            spawn, {.v = suspend } },

        { MODKEY,                       XK_slash,  spawn,          {.v = slock } },
        { 0,                            XK_Print,  spawn,          {.v = printscreen } },
        { ControlMask|Mod1Mask,         XK_c,      spawn,          {.v = clipman } },
        { ControlMask|Mod4Mask|Mod1Mask,XK_Home,   spawn,          {.v = poweroff } },
        { MODKEY,                       XK_x,      spawn,          {.v = xrandr } },
        { MODKEY,                       XK_s,      spawn,          {.v = syncthing } },
};

/* button definitions */
/* click can be ClkTagBar, ClkLtSymbol, ClkStatusText, ClkWinTitle, ClkClientWin, or ClkRootWin */
static const Button buttons[] = {
	/* click                event mask      button          function        argument */
	{ ClkTagBar,            MODKEY,         Button1,        tag,            {0} },
	{ ClkTagBar,            MODKEY,         Button3,        toggletag,      {0} },
	{ ClkWinTitle,          0,              Button2,        zoom,           {0} },
	{ ClkStatusText,        0,              Button2,        spawn,          {.v = termcmd } },
	{ ClkClientWin,         MODKEY,         Button1,        movemouse,      {0} },
	{ ClkClientWin,         MODKEY,         Button2,        togglefloating, {0} },
	{ ClkClientWin,         MODKEY,         Button3,        resizemouse,    {0} },
	{ ClkTagBar,            0,              Button1,        view,           {0} },
	{ ClkTagBar,            0,              Button3,        toggleview,     {0} },
};

