/* See LICENSE file for copyright and license details. */
#include <X11/XF86keysym.h>

/* appearance */
static const char font[]            = "DejaVu Sans Mono for Powerline:size=9";


#define NUMCOLORS 14
static const char colors[NUMCOLORS][ColLast][21] = {
	/* border   foreground  background   index|hex  description */
	{ "#282a2e", "#bcbcbc", "#586e75" }, // 00|01 = normal / lys grå / koksgrå
	{ "#268bd2", "#ffffff", "#258bd2" }, // 01|02 = selected
	{ "#282a2e", "#ffaf00", "#586e75" }, // 02|03 = urgent
	{ "#282a2e", "#ffffff", "#586e75" }, // 03|04 = occupied
	{ "#282a3e", "#585858", "#002b36" }, // 04|05 = layout symbol
	{ "#282a2e", "#585858", "#002b36" }, // 05|06 = clock / orange /mørkeblå
	{ "#282a2e", "#ffaf00", "#002b36" }, // 06|07 = systray / hvid /orange
	{ "#268bd2", "#000000", "#ffaf00" }, // 07|08 = status titles / sort / orange 
	{ "#282a2e", "#258bd2", "#ffaf00" }, // 08|09 = status / lysblaa / orange 
	{ "#282a2e", "#ffffff", "#258bd2" }, // 09|0a = status urgent / hvid / lys blå
	{ "#282a2e", "#586e75", "#258bd2" }, // 10|0b = battery title / koksgrå / lysblå
	{ "#282a2e", "#ffffff", "#586e75" }, // 11|0c = battery text / hvid / koksgrå
	{ "#282a2e", "#d7ff00", "#586e75" }, // 12|0d = battery urgent / snot / koksgrå
	{ "#282a2e", "#000000", "#d7ff00" }, // 13|0e = battery plsym / sort / snot 
};


/* #bcbcbc = lys grå
 * #586e75 = koksgrå
 * #258bd2 = lys blå
 * #ffaf00 = orange
 * #585858 = mellem grå
 * #002236 = Mørke blå
 * #d7ff00 = snot grøn
 */


static const unsigned int borderpx  = 1;        /* border pixel of windows */
static const unsigned int gappx     = 0;        /* gap pixel between windows */
static const unsigned int snap      = 32;       /* snap pixel */
static const Bool showbar           = True;     /* False means no bar */
static const Bool topbar            = True;     /* False means bottom bar */
static const Bool showsystray       = False;     /* False means no systray */
static const char scratchpadname[]  = "Scratchpad";
static const unsigned int systrayspacing = 10;

static const char clock_fmt[] = "%d/%m %H:%M";

static const char plopensym[]	 = "";	    /* powerline: left open glyph */
static const char plclosedsym[]	 = "";	    /* powerline: left closed glyph */
static const char plsystraysym[] = "";	    /* powerline: right closed glyph */

/* layout(s) */
static const float mfact      = 0.50;	/* factor of master area size [0.05..0.95] */
static const int nmaster      = 1;	/* number of clients in master area */
static const Bool resizehints = False;	/* True means respect size hints in tiled resizals */

static const Layout layouts[] = {
	/* symbol   gaps    arrange function */
	{ "[]=",    True,   tile },    /* first entry is default */
	{ "[M]",    False,  monocle },
	{ "><>",    False,  NULL },    /* no layout function means floating behavior */
};

/* tagging */
static Tag tags[] = {
	/* name     layout      mfact   nmaster */
	{ "web",   &layouts[0], -1,    -1 },
	{ "term",   &layouts[0], -1,    -1 },
	{ "code",   &layouts[0], -1,    -1 },
	{ "files",    &layouts[0], -1,    -1 },
	{ "misc",   &layouts[0], -1,    -1 },
};

static const Rule rules[] = {
	/* class      instance    title       tags mask     isfloating   monitor */
	{ "Chromium", NULL,       NULL,       1 << 3,       False,       -1 },
	{ "Skype",    NULL,       NULL,       0,	    True,	 -1 },
};

/* key definitions */
#define MODKEY Mod1Mask
#define WINKEY Mod4Mask
#define TAGKEYS(KEY,TAG) \
	{ MODKEY,                       KEY,      view,           {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask,           KEY,      toggleview,     {.ui = 1 << TAG} }, \
	{ MODKEY|ShiftMask,             KEY,      tag,            {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask|ShiftMask, KEY,      toggletag,      {.ui = 1 << TAG} },

/* helper for spawning shell commands in the pre dwm-5.0 fashion */
#define SHCMD(cmd) { .v = (const char*[]){ "/bin/sh", "-c", cmd, NULL } }

/* commands */
static const char *dmenu[]	= { "dmenu_run", "-fn", font, "-nb", colors[0][ColBG], "-nf", colors[0][ColFG], "-sb", colors[1][ColBG], "-sf", colors[1][ColFG], NULL };
static const char *scratchpad[] = { "urxvt", "-title", scratchpadname, "-geometry", "70x20", NULL };
static const char *term[]	= { "st", "-e", "tmux" };
static const char *volup[]	= { "amixer", "-q", "set", "Master", "5%+", NULL };
static const char *voldown[]	= { "amixer", "-q", "set", "Master", "5%-", NULL };
static const char *volmute[]	= { "amixer", "-q", "set", "Master", "toggle", NULL };
static const char *lock[]	= { "slock", NULL };
static const char *suspend[]	= { "systemctl", "suspend", NULL };
static const char *play[]	= { "ncmpcpp", "toggle", NULL };
static const char *next[]	= { "ncmpcpp", "next", NULL };
static const char *prev[]	= { "ncmpcpp", "prev", NULL };

static Key keys[] = {
	/* modifier                 key        function        argument */
	{ MODKEY,		XK_p,			    spawn,          {.v = dmenu } },
	{ MODKEY,		XK_Return,		    spawn,          {.v = term } },
	{ 0,			XK_F12,			    togglescratch,  {.v = scratchpad } },
	{ 0,			XF86XK_AudioRaiseVolume,    spawn,	    {.v = volup } },
	{ 0,			XF86XK_AudioLowerVolume,    spawn,	    {.v = voldown } },
	{ 0,			XF86XK_AudioMute,	    spawn,	    {.v = volmute } },
	{ 0,			XF86XK_AudioPlay,	    spawn,	    {.v = play } },
	{ 0,			XF86XK_AudioNext,	    spawn,	    {.v = next } },
	{ 0,			XF86XK_AudioPrev,	    spawn,	    {.v = prev } },
	{ WINKEY,		XK_Escape,		    spawn,	    {.v = suspend } },
	{ WINKEY,		XK_l,			    spawn,	    {.v = lock } },
	{ MODKEY,		XK_b,			    togglebar,      {0} },
	{ MODKEY,		XK_j,			    focusstack,     {.i = +1 } },
	{ MODKEY,		XK_k,			    focusstack,     {.i = -1 } },
	{ MODKEY,		XK_i,			    incnmaster,     {.i = +1 } },
	{ MODKEY,		XK_d,			    incnmaster,     {.i = -1 } },
	{ MODKEY,		XK_h,			    setmfact,       {.f = -0.05} },
	{ MODKEY,		XK_l,			    setmfact,       {.f = +0.05} },
	{ MODKEY,		XK_Return,		    zoom,           {0} },
	{ MODKEY,		XK_Tab,			    focusstack,     {.i = +1 } },
	{ MODKEY,		XK_q,			    killclient,     {0} },
	{ MODKEY,		XK_t,			    setlayout,      {.v = &layouts[0]} },
	{ MODKEY,		XK_f,			    setlayout,      {.v = &layouts[2]} },
	{ MODKEY,		XK_m,			    setlayout,      {.v = &layouts[1]} },
	{ MODKEY,		XK_space,		    setlayout,      {0} },
	{ MODKEY|ShiftMask,	XK_space,		    togglefloating, {0} },
	{ MODKEY,		XK_0,			    view,           {.ui = ~0 } },
	{ MODKEY|ShiftMask,	XK_0,			    tag,            {.ui = ~0 } },
	{ MODKEY,		XK_comma,		    focusmon,       {.i = -1 } },
	{ MODKEY,		XK_period,		    focusmon,       {.i = +1 } },
	{ MODKEY|ShiftMask,	XK_comma,		    tagmon,         {.i = -1 } },
	{ MODKEY|ShiftMask,	XK_period,		    tagmon,         {.i = +1 } },
	TAGKEYS(		XK_1,			    0)
	TAGKEYS(		XK_2,			    1)
	TAGKEYS(		XK_3,			    2)
	TAGKEYS(		XK_4,			    3)
	TAGKEYS(		XK_5,			    4)
	{ MODKEY|ShiftMask,	XK_q,			    quit,	    {0} },
};

/* button definitions */
/* click can be ClkLtSymbol, ClkStatusText, ClkClock, ClkClientWin, or ClkRootWin */
static Button buttons[] = {
	/* click                event mask      button          function        argument */
	{ ClkLtSymbol,          0,              Button1,        setlayout,      {0} },
	{ ClkLtSymbol,          0,              Button3,        setlayout,      {.v = &layouts[2]} },
//	{ ClkWinTitle,          0,              Button2,        zoom,           {0} },
	{ ClkStatusText,        0,              Button2,        spawn,          {.v = term } },
	{ ClkClientWin,         MODKEY,         Button1,        movemouse,      {0} },
	{ ClkClientWin,         MODKEY,         Button2,        togglefloating, {0} },
	{ ClkClientWin,         MODKEY,         Button3,        resizemouse,    {0} },
	{ ClkTagBar,            0,              Button1,        view,           {0} },
	{ ClkTagBar,            0,              Button3,        toggleview,     {0} },
	{ ClkTagBar,            MODKEY,         Button1,        tag,            {0} },
	{ ClkTagBar,            MODKEY,         Button3,        toggletag,      {0} },
};
