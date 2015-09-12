/* See LICENSE file for copyright and license details. */

/* appearance */
#define NUMCOLORS 7
static const char colors[NUMCOLORS][ColLast][8] = {
	// border foreground background
	{ "#bbb", "#bbb", "#000" },  // normal
	{ "#78c", "#78c", "#000" },  // selected
	{ "#ca6", "#ca6", "#000" },  // warning
	{ "#c55", "#c55", "#000" },  // error
	{ "#000", "#78c", "#000" },  // statuscolors
	{ "#4c4", "#4c4", "#000" },  // ok
	{ "#cc4", "#cc4", "#000" },  // bad
	// add more here
};

static const char font[]            = "-*-stlarch-medium-r-*-*-10-*-*-*-*-*-*-*" "," "-*-profont-*-*-*-*-12-*-*-*-*-*-*-*"; // "-*-terminus-medium-r-*-*-16-*-*-*-*-*-*-*";
static const char normbordercolor[] = "#444444";
static const char normbgcolor[]     = "#000000";
static const char normfgcolor[]     = "#7788cc";
static const char selbordercolor[]  = "#005577";
static const char selbgcolor[]      = "#3355cc";
static const char selfgcolor[]      = "#eeeeee";
static const unsigned int borderpx  = 1;        /* border pixel of windows */
static const unsigned int gappx     = 3;        /* gap between windows */
static const unsigned int snap      = 32;       /* snap pixel */
static const Bool showbar           = True;     /* False means no bar */
static const Bool topbar            = True;     /* False means bottom bar */
static const Bool clicktofocus      = False;    /* Change focus only on click */
static const int systrayspacing     = 1;        /* for systray-patch*/
static const Bool systray_enable    = True;     /* for systray-patch*/
static const Bool showsystray       = True;     /* False means no systray */

/* tagging */

static const char *tags[] = { "term", "web", "comm", "coding", "media", "file", "misc", "game"};
//xprop
static const Rule rules[] = {
	/* class		instance	title		tags mask	isfloating	iscentred	monitor */
	{ "adom",		NULL,		NULL,		1 << 7,		True,		False,		-1 },
	{ "Angband",		NULL,		NULL,		1 << 7,		True,		False,		-1 },
	{ "atom",	NULL,		NULL,		1 << 3,		False,		False,		-1 },
	{ "Audacious",		NULL,		NULL,		1 << 4,		False,		False,		-1 },
	{ "BitThief",		NULL,		NULL,		0,		True,		True,		-1 },
	{ "bluej-Boot",		NULL,		NULL,		1 << 3,		True,		True,		-1 },
	{ "brogue",		NULL,		NULL,		1 << 7,		True,		False,		-1 },
	{ "Clementine",		NULL,		NULL,		1 << 4,		False,		False,		-1 },
	{ "Chromium",		NULL,		NULL,		1 << 1,		False,		False,		-1 },
	{ "crawl-tiles",	NULL,		NULL,		1 << 7,		True,		False,		-1 },
	{ "Deadbeef",		NULL,		NULL,		1 << 4,		False,		False,		-1 },
	{ "Diffuse",		NULL,		NULL,		1 << 3,		False,		False,		-1 },
	{ "doomrl",		NULL,		NULL,		1 << 7,		True,		False,		-1 },
	{ "dosbox",		NULL,		NULL,		0,		True,		True,		-1 },
	{ "Eclipse",		NULL,		NULL,		1 << 3,		False,		False,		-1 },
	{ "Firefox",		NULL,		NULL,		1 << 1,		False,		False,		-1 },
	{ "FTL",		NULL,		NULL,		1 << 7,		True,		False,		-1 },
	{ "Geany",		NULL,		NULL,		1 << 3,		False,		False,		-1 },
	{ "Gimp",		NULL,		NULL,		1 << 6,		True,		False,		-1 },
	{ "Gnome-mplayer",	NULL,		NULL,		1 << 4,		True,		False,		-1 },
	{ "Gvim",		NULL,		NULL,		1 << 3,		False,		False,		-1 },
	{ "Kdiff3",		NULL,		NULL,		1 << 3,		False,		False,		-1 },
	{ "Midori",		NULL,		NULL,		1 << 1,		False,		False,		-1 },
	{ "mono-sgen",		NULL,		NULL,		1 << 7,		True,		False,		-1 },
	{ "MPlayer",		NULL,		NULL,		1 << 4,		True,		False,		-1 },
	{ "Pcmanfm",		NULL,		NULL,		1 << 5,		False,		False,		-1 },
	{ "PCSXR",		NULL,		NULL,		1 << 7,		True,		False,		-1 },
	{ "Pidgin",		NULL,		NULL,		1 << 2,		False,		False,		-1 },
	{ "powder",		NULL,		NULL,		1 << 7,		True,		False,		-1 },
	{ "Qtfm",		NULL,		NULL,		1 << 5,		False,		False,		-1 },
	{ "rl",			NULL,		NULL,		1 << 7,		True,		False,		-1 },
	{ "sil",		NULL,		NULL,		1 << 7,		True,		False,		-1 },
	{ "Spacefm",		NULL,		NULL,		1 << 5,		False,		False,		-1 },
	{ "sublime_text",	NULL,		NULL,		1 << 3,		False,		False,		-1 },
	{ "stalonetray",	NULL,		NULL,		0,		True,		False,		-1 },
	{ "Steam",		NULL,		NULL,		1 << 6,		True,		False,		-1 },
	{ "Skype",	NULL,		NULL,		1 << 2,		False,		False,		-1 },
	{ "t-engine",		NULL,		NULL,		1 << 7,		True,		False,		-1 },
	{ "Thunderbird",	NULL,		NULL,		1 << 2,		False,		False,		-1 },
	{ "urw3-bin",		NULL,		NULL,		1 << 7,		True,		False,		-1 },
	{ "Vlc",		NULL,		NULL,		1 << 4,		False,		False,		-1 },
	{ "Xchat",		NULL,		NULL,		1 << 2,		False,		False,		-1 },
	{ "zsnes",		NULL,		NULL,		0,		True,		True,		-1 },
};

/* layout(s) */
static const float mfact      = 0.555555; /* factor of master area size [0.05..0.95] */
static const int nmaster      = 1;    /* number of clients in master area */
static const Bool resizehints = True; /* True means respect size hints in tiled resizals */

static const Layout layouts[] = {
	/* symbol     arrange function */
	{ "[T]",      tile },    /* first entry is default */
	{ "[F]",      NULL },    /* no layout function means floating behavior */
	{ "[M]",      monocle },
};

/* key definitions */
#define MODKEY Mod4Mask
#define TAGKEYS(KEY,TAG) \
	{ MODKEY,                       KEY,      view,           {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask,           KEY,      toggleview,     {.ui = 1 << TAG} }, \
	{ MODKEY|ShiftMask,             KEY,      tag,            {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask|ShiftMask, KEY,      toggletag,      {.ui = 1 << TAG} },

/* helper for spawning shell commands in the pre dwm-5.0 fashion */
#define SHCMD(cmd) { .v = (const char*[]){ "/bin/sh", "-c", cmd, NULL } }

/* commands */
static const char *volpcmd[] = { "amixer", "-c", "0", "set", "Master", "3+", "unmute", NULL };
static const char *volmcmd[] = { "amixer", "-c", "0", "set", "Master", "3-", "unmute", NULL };
static const char *volmutecmd[] = { "amixer", "set", "Master", "toggle", NULL };
static const char *dmenucmd[] = { "dmenu_run", "-fn", font, "-nb", normbgcolor, "-nf", normfgcolor, "-sb", selbgcolor, "-sf", selfgcolor, NULL };
static const char *lockcmd[]  = { "xscreensaver-command", "--lock", NULL};
static const char *idecmd[]  = { "geany", NULL};
//static const char *browsercmd[]  = { "firefox", NULL};
static const char *browsercmd[]  = { "chromium", NULL};
static const char *clickrcmd[]  = { "clickr.sh", NULL};
static const char *mailcmd[]  = { "thunderbird", NULL};
static const char *filebrowsercmd[]  = { "pcmanfm", NULL};
static const char *termcmd[]  = { "urxvtc", NULL};
static const char *screenbrightnesspcmd[] = { "sudo", "xbacklight", "-inc", "40", NULL };
static const char *screenbrightnessmcmd[] = { "sudo", "xbacklight", "-dec", "40", NULL };
static const char *screenbrightnessmaxcmd[] = { "sudo", "xbacklight", "-set", "100", NULL };
static const char *screenbrightnessmincmd[] = { "sudo", "xbacklight", "-set", "0", NULL };

#include </usr/include/X11/XF86keysym.h> //XF86XK_*
static Key keys[] = {
	/* modifier                     key                      function        argument */
	{ MODKEY,                       XK_p,                    spawn,          {.v = dmenucmd } },
	{ MODKEY|ShiftMask,             XK_Return,               spawn,          {.v = termcmd } },
	{ MODKEY|ShiftMask|ControlMask, XK_l,                    spawn,          {.v = lockcmd } },
	{ MODKEY|ShiftMask|ControlMask, XK_c,                    spawn,          {.v = clickrcmd } },
	{ MODKEY|ShiftMask,             XK_b,                    spawn,          {.v = browsercmd } },
	{ MODKEY|ShiftMask,             XK_g,                    spawn,          {.v = idecmd } },
	{ MODKEY|ShiftMask,             XK_m,                    spawn,          {.v = mailcmd } },
	{ MODKEY|ShiftMask,             XK_f,                    spawn,          {.v = filebrowsercmd } },
	//{ 0,                            XF86XK_MonBrightnessUp,  spawn,          {.v = screenbrightnesspcmd } },
	{ MODKEY,                       XK_Right,                spawn,          {.v = screenbrightnesspcmd } },
	//{ 0,                            XF86XK_MonBrightnessDown,spawn,          {.v = screenbrightnessmcmd } },
	{ MODKEY,                       XK_Left,                 spawn,          {.v = screenbrightnessmcmd } },
	{ MODKEY,                       XK_Up,                   spawn,          {.v = screenbrightnessmaxcmd } },
	{ MODKEY,                       XK_Down,                 spawn,          {.v = screenbrightnessmincmd } },
	{ 0,                            XF86XK_AudioRaiseVolume, spawn,          {.v = volpcmd } },
	{ 0,                            XF86XK_AudioLowerVolume, spawn,          {.v = volmcmd } },
	{ 0,                            XF86XK_AudioMute,        spawn,          {.v = volmutecmd } },
	{ MODKEY,                       XK_Tab,                  view,           {0} },
	{ MODKEY,                       XK_b,                    togglebar,      {0} },
	{ MODKEY,                       XK_r,                    focusstack,     {.i = +1 } },
	{ MODKEY,                       XK_g,                    focusstack,     {.i = -1 } },
	//{ MODKEY,                       XK_i,             incnmaster,     {.i = +1 } },
	//{ MODKEY,                       XK_d,             incnmaster,     {.i = -1 } },
	{ MODKEY,                       XK_n,                    setmfact,       {.f = -0.05} },
	{ MODKEY,                       XK_t,                    setmfact,       {.f = +0.05} },
	{ MODKEY,                       XK_Return,               zoom,           {0} },
	{ MODKEY,                       XK_Tab,                  view,           {0} },
	{ MODKEY|ShiftMask,             XK_c,                    killclient,     {0} },
	{ MODKEY,                       XK_t,                    setlayout,      {.v = &layouts[0]} },
	{ MODKEY,                       XK_f,                    setlayout,      {.v = &layouts[1]} },
	{ MODKEY,                       XK_m,                    setlayout,      {.v = &layouts[2]} },
	{ MODKEY,                       XK_space,                setlayout,      {0} },
	{ MODKEY|ShiftMask,             XK_space,                togglefloating, {0} },
	{ MODKEY,                       XK_0,                    view,           {.ui = ~0 } },
	{ MODKEY|ShiftMask,             XK_0,                    tag,            {.ui = ~0 } },
	{ MODKEY,                       XK_comma,                focusmon,       {.i = -1 } },
	{ MODKEY,                       XK_period,               focusmon,       {.i = +1 } },
	{ MODKEY|ShiftMask,             XK_comma,                tagmon,         {.i = -1 } },
	{ MODKEY|ShiftMask,             XK_period,               tagmon,         {.i = +1 } },
	TAGKEYS(                        XK_1,                                    0)
	TAGKEYS(                        XK_2,                                    1)
	TAGKEYS(                        XK_3,                                    2)
	TAGKEYS(                        XK_4,                                    3)
	TAGKEYS(                        XK_5,                                    4)
	TAGKEYS(                        XK_6,                                    5)
	TAGKEYS(                        XK_7,                                    6)
	TAGKEYS(                        XK_8,                                    7)
	TAGKEYS(                        XK_9,                                    8)
	{ MODKEY|ShiftMask|ControlMask, XK_q,                    quit,           {0} },
};

/* button definitions */
/* click can be ClkLtSymbol, ClkStatusText, ClkWinTitle, ClkClientWin, or ClkRootWin */
static Button buttons[] = {
	/* click                event mask      button          function        argument */
	{ ClkLtSymbol,          0,              Button1,        setlayout,      {0} },
	{ ClkLtSymbol,          0,              Button3,        setlayout,      {.v = &layouts[2]} },
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

