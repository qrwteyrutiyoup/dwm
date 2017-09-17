/* See LICENSE file for copyright and license details. */
#include <X11/XF86keysym.h>

static const char font[] =
  "qrwteyrutiyoup:size=11.5:style=bold";

static const char normbordercolor[] = "#444444";
static const char normbgcolor[]     = "#222222";
static const char normfgcolor[]     = "#bbbbbb";
static const char selfgcolor[]      = "#eeeeee";
static const char dmenufont[]       = "monospace:size=10";

static char selbgcolor[]      = "#005577";

/* Forward declarations. */
struct Arg;
void shiftview(const Arg*);

#define THEME_FILE "current-theme"
#define DWM_PID_FILE "dwm.pid"
#define DWM_SOCKET_FILE "dwm.sock"
#define STATUS_PID_FILE "statusbar.pid"

#define BORDER "#0087af"
#define URGT "#daae35"
#define DARK "#414141"
#define LITE "#9e9e9e"
#define BUSY "#fafafa"

#define NUMCOLORS 6
static const char colors[NUMCOLORS][ColLast][21] = {
	/* border   foreground  background   index|hex  description */
	{ BORDER, BORDER, DARK }, // 00|01.
  { BORDER, URGT, DARK },   // 01|02.
  { BORDER, BUSY, DARK },   // 02|03.
	{ BORDER, DARK, LITE },   // 03|04.
	{ BORDER, LITE, DARK },   // 04|05.
  { BORDER, LITE, LITE },   // 05|06.
};


static const unsigned int borderpx  = 1;        /* border pixel of windows */
static const unsigned int gappx     = 0;        /* gap pixel between windows */
static const unsigned int snap      = 32;       /* snap pixel */
static const Bool showbar           = True;     /* False means no bar */
static const Bool topbar            = True;     /* False means bottom bar */
static const Bool showsystray       = False;     /* False means no systray */
static const char scratchpadname[]  = "Scratchpad";
static const unsigned int systrayspacing = 10;

//static const char clock_fmt[] = "%d/%m %H:%M";

static const char plopensym[]	 = "";	    /* powerline: left open glyph */
static const char layoutsym[]	 = " ";	    /* powerline: left open glyph */
static const char leftlayoutsym[]	 = "";	    /* powerline: left open glyph */
static const char leftthinsym[]	 = "";	    /* powerline: left open glyph */
static const char lefttagsym[] = "";


static const char rightlayoutsym[]	 = "";	    /* powerline: left open glyph */
static const char rightthinsym[]	 = "";	    /* powerline: left open glyph */




//static const char plclosedsym[]	 = "";	    /* powerline: left closed glyph */
static const char plclosedsym[]	 = "";	    /* powerline: left closed glyph */

static const char plsystraysym[] = " ";	    /* powerline: right closed glyph */

/* layout(s) */
static const float mfact      = 0.50;	/* factor of master area size [0.05..0.95] */
static const int nmaster      = 1;	/* number of clients in master area */
static const Bool resizehints = False;	/* True means respect size hints in tiled resizals */

static const Layout layouts[] = {
	/* symbol   gaps    arrange function */
	{ "",    True,   tile },    /* first entry is default */
	{ "[M]",    False,  monocle },
	{ "",    False,  NULL },    /* no layout function means floating behavior */
};

static const Rule rules[] = {
/* class      instance    title       tags mask     isfloating   monitor */
  { "Skype",    NULL,       NULL,       0,      True,   -1 },
};



/* tagging */
static Tag tags[] = {
  /* name     layout      mfact   nmaster */
  { "",    &layouts[0], -1,    -1 },
  { "",    &layouts[0], -1,    -1 },
  { "",    &layouts[0], -1,    -1 },
  { "",    &layouts[0], -1,    -1 },
  { "",    &layouts[0], -1,    -1 },
  { "",    &layouts[0], -1,    -1 },
  { "",    &layouts[0], -1,    -1 },
};

/* key definitions */
#define MODKEY Mod1Mask
#define WINKEY Mod4Mask
#define TAGKEYS(KEY,TAG) \
  { ControlMask,                  KEY,      view,           {.ui = 1 << TAG} }, \
  { MODKEY|ControlMask,           KEY,      toggleview,     {.ui = 1 << TAG} }, \
  { MODKEY|ShiftMask,             KEY,      tag,            {.ui = 1 << TAG} }, \
  { MODKEY|ControlMask|ShiftMask, KEY,      toggletag,      {.ui = 1 << TAG} },

/* helper for spawning shell commands in the pre dwm-5.0 fashion */
#define SHCMD(cmd) { .v = (const char*[]){ "/bin/sh", "-c", cmd, NULL } }

/* Keyboard shortcuts go in a seprate file. */
#include "keyboard-shortcuts.h"

/* button definitions */
/* click can be ClkLtSymbol, ClkStatusText, ClkWinTitle, ClkClientWin, or ClkRootWin */
static Button buttons[] = {
  /* click                event mask      button          function        argument */
  { ClkLtSymbol,          0,              Button1,        setlayout,      {0} },
  { ClkLtSymbol,          0,              Button3,        setlayout,      {.v = &layouts[2]} },
  { ClkStatusText,        0,              Button2,        spawn,          {.v = termcmd } },
  { ClkClientWin,         MODKEY,         Button1,        movemouse,      {0} },
  { ClkClientWin,         MODKEY,         Button2,        togglefloating, {0} },
  { ClkClientWin,         MODKEY,         Button3,        resizemouse,    {0} },
  { ClkTagBar,            0,              Button1,        view,           {0} },
  { ClkTagBar,            0,              Button3,        toggleview,     {0} },
  { ClkTagBar,            MODKEY,         Button1,        tag,            {0} },
  { ClkTagBar,            MODKEY,         Button3,        toggletag,      {0} },
};

/* vim:set ts=2 sw=2 et: */

