/* See LICENSE file for copyright and license details. */

/* appearance */
static const unsigned int borderpx  = 2;        /* border pixel of windows */
static const unsigned int snap      = 32;       /* snap pixel */
static const int showbar            = 1;        /* 0 means no bar */
static const int topbar             = 1;        /* 0 means bottom bar */
static const unsigned int systraypinning = 0;   /* 0: sloppy systray follows selected monitor, >0: pin systray to monitor x */
static const unsigned int systrayspacing = 6;   /* systray spacing */
static const int systraypinningfailfirst = 1;   /* 1: if pinning fails, display systray on the first monitor, 0: display systray on the last monitor*/
static const int showsystray        = 1;        /* 0 means no systray */
static const char *fonts[]          = { "JetBrains Mono:size=12" };
static const char dmenufont[]       = "JetBrains Mono:size=12";
static const char col_black[]       = "#282C34";
static const char col_gray2[]       = "#ABB2BF";
static const char col_white[]       = "#f8f8f2";
static const char col_gray4[]       = "#eceff1";
static const char col_cyan[]        = "#c168DD";
static const char *colors[][3]      = {
	/*               fg         bg         border   */
	[SchemeNorm] = { col_white, col_black, col_gray2 },
	[SchemeSel]  = { col_black, col_gray2, col_cyan  },
};

/* tagging */
static const char *tags[] = { "1", "2", "3", "4", "5", "6", "7", "8", "9" };

static const Rule rules[] = {
	/* xprop(1):
	 *	WM_CLASS(STRING) = instance, class
	 *	WM_NAME(STRING) = title
	 */
	/* class      instance    title       tags mask     isfloating   monitor */
	{ "Gimp",     NULL,       NULL,       0,            1,           -1 },
	{ "Telegram", NULL,       NULL,       1 << 8,       1,           -1 },
  { "Spotify",  NULL,       NULL,       1 << 7,       0,           -1 },
  { "Upwork",   NULL,       NULL,       1 << 6,       1,           -1 },
  { "zoom",     NULL,       NULL,       1 << 2,       1,           -1 },
  { "Firefox",  NULL,       NULL,       NULL,         0,           -1 },
  { "Slack",    NULL,       NULL,       1 << 3,       0,           -1 },
  { "st-256color","st-256color",  "tmux",    NULL,    0,           -1 },
  { "st-256color","st-256color",  "gotop",    NULL,   1,           -1 },
};

/* layout(s) */
static const float mfact     = 0.55; /* factor of master area size [0.05..0.95] */
static const int nmaster     = 1;    /* number of clients in master area */
static const int resizehints = 0;    /* 1 means respect size hints in tiled resizals */

#include "layouts.c"
static const Layout layouts[] = {
	/* symbol     arrange function */
	{ "[]=",      tile },    /* first entry is default */
  { "><>",      NULL },    /* no layout function means floating behavior */
	{ "[M]",      monocle },
  { "HHH",      grid },
};

/* key definitions */
#define MODKEY Mod4Mask
#define TAGKEYS(KEY,TAG) \
	{ MODKEY,                       KEY,      view,           {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask,           KEY,      toggleview,     {.ui = 1 << TAG} }, \
	{ MODKEY|ShiftMask,             KEY,      tag,            {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask|ShiftMask, KEY,      toggletag,      {.ui = 1 << TAG} },

/* helper for spawning shell commands in the pre dwm-5.0 fashion */
#define SHCMD(cmd) { .v = (const char*[]){ "/bin/fish", "-c", cmd, NULL } }

/* commands */
static char dmenumon[2] = "0"; /* component of dmenucmd, manipulated in spawn() */
static const char *dmenucmd[] = { "/home/germes/code/dotfiles/scripts/dmenu" };
/* static const char *dmenucmd[] = { "dmenu_run", "-m", dmenumon, "-fn", dmenufont, "-nb", col_black, "-nf", col_white, "-sb", col_cyan, "-sf", col_gray4, NULL }; */
static const char *termcmd[]  = { "/home/germes/code/dotfiles/scripts/start_terminal" };
static const char scratchpadname[] = "scratchpad";
static const char *scratchpadcmd[] = {"st", "-t", scratchpadname, "-g", "120x34", "-e", "fish", NULL};

static Key keys[] = {
	/* modifier                     key        function        argument */
	{ MODKEY,                       XK_r,      spawn,          {.v = dmenucmd } },
	{ MODKEY|ShiftMask,             XK_Return, spawn,          {.v = termcmd } },
  { MODKEY,                       XK_grave,  togglescratch,  {.v = scratchpadcmd } },
	{ MODKEY,                       XK_b,      togglebar,      {0} },
	{ MODKEY,                       XK_j,      focusstack,     {.i = +1 } },
	{ MODKEY,                       XK_k,      focusstack,     {.i = -1 } },
	{ MODKEY,                       XK_i,      incnmaster,     {.i = +1 } },
	{ MODKEY,                       XK_d,      incnmaster,     {.i = -1 } },

  { MODKEY,                       XK_h,      focusstack,     {.i = +1 } },
  { MODKEY,                       XK_l,      focusstack,     {.i = -1 } },
  { MODKEY|ShiftMask,             XK_h,      setmfact,       {.f = -0.05} },
  { MODKEY|ShiftMask,             XK_l,      setmfact,       {.f = +0.05} },

  { MODKEY,					XK_Down,	moveresize,		{.v = (int []){ 0, 25, 0, 0 }}},
  { MODKEY,					XK_Up,		moveresize,		{.v = (int []){ 0, -25, 0, 0 }}},
  { MODKEY,					XK_Right,	moveresize,		{.v = (int []){ 25, 0, 0, 0 }}},
  { MODKEY,					XK_Left,	moveresize,		{.v = (int []){ -25, 0, 0, 0 }}},
  { MODKEY|ShiftMask,			XK_Down,	moveresize,		{.v = (int []){ 0, 0, 0, 25 }}},
  { MODKEY|ShiftMask,			XK_Up,		moveresize,		{.v = (int []){ 0, 0, 0, -25 }}},
  { MODKEY|ShiftMask,			XK_Right,	moveresize,		{.v = (int []){ 0, 0, 25, 0 }}},
  { MODKEY|ShiftMask,			XK_Left,	moveresize,		{.v = (int []){ 0, 0, -25, 0 }}},

	{ MODKEY,                       XK_Return, zoom,           {0} },
	{ MODKEY,                       XK_Tab,    view,           {0} },
	{ MODKEY|ShiftMask,             XK_q,      killclient,     {0} },
  { MODKEY,                       XK_t,      setlayout,      {.v = &layouts[0]} },
	{ MODKEY,                       XK_f,      setlayout,      {.v = &layouts[1]} },
	{ MODKEY,                       XK_m,      setlayout,      {.v = &layouts[2]} },
	{ MODKEY,                       XK_g,      setlayout,      {.v = &layouts[3]} },
	{ MODKEY,                       XK_space,  setlayout,      {0} },
	{ MODKEY|ShiftMask,             XK_space,  togglefloating, {0} },
	{ MODKEY,                       XK_0,      view,           {.ui = ~0 } },
	{ MODKEY|ShiftMask,             XK_0,      tag,            {.ui = ~0 } },
	{ MODKEY,                       XK_comma,  focusmon,       {.i = -1 } },
  { MODKEY,                       XK_period, focusmon,       {.i = +1 } },
  { MODKEY,                       XK_backslash, focusmon,       {.i = +1 } },
	{ MODKEY|ShiftMask,             XK_comma,  tagmon,         {.i = -1 } },
	{ MODKEY|ShiftMask,             XK_period, tagmon,         {.i = +1 } },
	TAGKEYS(                        XK_1,                      0)
	TAGKEYS(                        XK_2,                      1)
	TAGKEYS(                        XK_3,                      2)
	TAGKEYS(                        XK_4,                      3)
	TAGKEYS(                        XK_5,                      4)
	TAGKEYS(                        XK_6,                      5)
	TAGKEYS(                        XK_7,                      6)
	TAGKEYS(                        XK_8,                      7)
	TAGKEYS(                        XK_9,                      8)
	{ MODKEY|ShiftMask,             XK_c,      quit,           {0} },
};

/* button definitions */
/* click can be ClkTagBar, ClkLtSymbol, ClkStatusText, ClkWinTitle, ClkClientWin, or ClkRootWin */
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


/* useless gaps */
static const unsigned int gappx = 8;
