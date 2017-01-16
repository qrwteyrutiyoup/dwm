/* See LICENSE file for copyright and license details. */
#include <X11/XF86keysym.h>

static const char font[] =
  "qrwteyrutiyoup:size=11.5:style=bold";


static const char normbordercolor[] = "#444444";
static const char normbgcolor[]     = "#222222";
static const char normfgcolor[]     = "#bbbbbb";
static const char selbordercolor[]  = "#005577";
static const char selbgcolor[]      = "#005577";
static const char selfgcolor[]      = "#eeeeee";
static const char dmenufont[]       = "monospace:size=10";

/* Forward declarations. */
struct Arg;
void shiftview(const Arg*);


#define NUMCOLORS 17
static const char colors[NUMCOLORS][ColLast][21] = {
  /* border   foreground  background   index|hex  description */
  { "#282a2e", "#bcbcbc", "#585858" }, // 00|01 = normal / lys grå / koksgrå
  { "#cfcfcf", "#585858", "#cfcfcf" }, // 09|0a = dark grey on white
  { "#282a2e", "#ffaf00", "#586e75" }, // 02|03 = urgent
  { "#282a2e", "#ffffff", "#585858" }, // 03|04 = occupied
  { "#282a3e", "#585858", "#cfcfcf" }, // 04|05 = layout symbol
  { "#282a2e", "#ffffff", "#585858" }, // 10|06 = white on dark grey
  { "#282a2e", "#ffffff", "#586e75" }, // 06|07 = white on grey
  { "#282a2e", "#5f0000", "#586e75" }, // 07|08 = red on grey
  { "#282a2e", "#ffffff", "#5f0000" }, // 08|09 = white on red
  { "#282a2e", "#585858", "#cfcfcf" }, // 09|0a = dark grey on white
  { "#282a2e", "#cfcfcf", "#585858" }, // 10|0b = white on dark grey
  { "#282a2e", "#ffaf00", "#303030" }, // 11|0c = orange on dark grey
  { "#282a2e", "#303030", "#ffaf00" }, // 12|0d = dark grey on orange
  { "#282a2e", "#054b19", "#ffaf00" }, // 13|0e = dark green on orange
  { "#282a2e", "#14a060", "#054b19" }, // 14|0f = green on dark green
  { "#282a2e", "#258bd2", "#054b19" }, // 15|10 = blue on dark green
  { "#282a2e", "#ffffff", "#258bd2" }, // 16|11 = white on blue
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

static const char plopensym[]   = "";      /* powerline: left open glyph */
static const char plclosedsym[]   = "";      /* powerline: left closed glyph */
static const char plsystraysym[] = " ";      /* powerline: right closed glyph */

/* layout(s) */
static const float mfact      = 0.50;  /* factor of master area size [0.05..0.95] */
static const int nmaster      = 1;  /* number of clients in master area */
static const Bool resizehints = False;  /* True means respect size hints in tiled resizals */

static const Layout layouts[] = {
  /* symbol   gaps    arrange function */
  { "  ",    True,   tile },    /* first entry is default */
  { "[M]",    False,  monocle },
  { "  ",    False,  NULL },    /* no layout function means floating behavior */
};

/* tagging */
static Tag tags[] = {
  /* name     layout      mfact   nmaster */
  { "F",    &layouts[0], -1,    -1 },
  { "O",    &layouts[0], -1,    -1 },
  { "R",    &layouts[0], -1,    -1 },
  { "A",    &layouts[0], -1,    -1 },
  { "T",    &layouts[0], -1,    -1 },
  { "E",    &layouts[0], -1,    -1 },
  { "M",    &layouts[0], -1,    -1 },
  { "E",    &layouts[0], -1,    -1 },
  { "R",    &layouts[0], -1,    -1 },
};

static const Rule rules[] = {
  /* class      instance    title       tags mask     isfloating   monitor */
  { "Chromium", NULL,       NULL,       1 << 3,       False,       -1 },
  { "Skype",    NULL,       NULL,       0,      True,   -1 },
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

/* commands */
static char dmenumon[2] = "0"; /* component of dmenucmd, manipulated in spawn() */
static const char *dmenucmd[] = { "dmenu_run", "-m", dmenumon, "-fn", dmenufont, "-nb", normbgcolor, "-nf", normfgcolor, "-sb", selbgcolor, "-sf", selfgcolor, NULL };
static const char *termcmd[]  = {"urxvt", "-e", "tmux", NULL};
//static const char *termcmd[]  = {"cool-retro-term", "-e", "tmux", NULL};
static const char *termnotmuxcmd[]  = {"urxvt", NULL};
static const char *scrsavercmd[]  = {"screenlock", NULL};
static const char *browsercmd[] = {"google-chrome-stable", NULL};
static const char *irccmd[] = {"hexchat", NULL};
static const char *skypecmd[] = {"skype", NULL};
static const char *volumeupcmd[] = {"volumeup", NULL};
static const char *volumedowncmd[] = {"volumedown", NULL};
static const char *volumemutecmd[] = {"volumemute", NULL};
static const char *winampclonecmd[] = {"audacious", NULL};
static const char *filemgrcmd[] = {"pcmanfm", NULL};
static const char *printscrcmd[] = {"printscreen", NULL};
static const char *printscrgimpcmd[] = {"printscreen", "edit", NULL};
static const char *brightnessupcmd[] = {"brightnessup", NULL};
static const char *brightnessdowncmd[] = {"brightnessdown", NULL};


static Key keys[] = {
  /* modifier                key             function        argument */
  { MODKEY,                  XK_p,                spawn,          {.v = dmenucmd } },
  { MODKEY,                  XK_F2,               spawn,          {.v = dmenucmd } },
  { MODKEY|ShiftMask,        XK_Return,           spawn,          {.v = termcmd } },
  { MODKEY|ShiftMask,        XK_t,                spawn,          {.v = termnotmuxcmd } },
  { WINKEY,                  XK_l,                spawn,          {.v = scrsavercmd } },
  { WINKEY,                  XK_b,                spawn,          {.v = browsercmd } },
  { WINKEY,                  XK_Return,           spawn,          {.v = termcmd } },
  { WINKEY,                  XK_i,                spawn,          {.v = irccmd } },
  { WINKEY,                  XK_s,                spawn,          {.v = skypecmd } },
  { WINKEY,                  XK_plus,             spawn,          {.v = volumeupcmd } },
  { WINKEY,                  XK_equal,            spawn,          {.v = volumeupcmd } },
  { WINKEY,                  XK_F12,              spawn,          {.v = volumeupcmd } },
  { WINKEY,                  XK_minus,            spawn,          {.v = volumedowncmd } },
  { WINKEY,                  XK_underscore,       spawn,          {.v = volumedowncmd } },
  { WINKEY,                  XK_F11,              spawn,          {.v = volumedowncmd } },
  { WINKEY,                  XK_m,                spawn,          {.v = volumemutecmd } },
  { WINKEY,                  XK_F10,              spawn,          {.v = volumemutecmd } },
  { WINKEY,                  XK_w,                spawn,          {.v = winampclonecmd } },
  { WINKEY,                  XK_f,                spawn,          {.v = filemgrcmd } },
  { WINKEY,                  XK_Print,            spawn,          {.v = printscrcmd } },
  { WINKEY|ShiftMask,        XK_Print,            spawn,          {.v = printscrgimpcmd } },
  { WINKEY,                  XK_F5,               spawn,          {.v = brightnessdowncmd } },
  { WINKEY,                  XK_F6,               spawn,          {.v = brightnessupcmd } },
  { ShiftMask,               XK_Page_Down,   shiftview,      {.i = +1 } },
  { ShiftMask,               XK_Page_Up,     shiftview,      {.i = -1 } },
  { MODKEY,                  XK_b,           togglebar,      {0} },
  { MODKEY,                  XK_j,           focusstack,     {.i = +1 } },
  { MODKEY,                  XK_k,           focusstack,     {.i = -1 } },
  { MODKEY,                  XK_i,           incnmaster,     {.i = +1 } },
  { MODKEY,                  XK_d,           incnmaster,     {.i = -1 } },
  { MODKEY,                  XK_h,           setmfact,       {.f = -0.05} },
  { MODKEY,                  XK_l,           setmfact,       {.f = +0.05} },
  { MODKEY,                  XK_Return,      zoom,           {0} },
  { MODKEY,                  XK_Tab,         view,           {0} },
  { MODKEY|ShiftMask,        XK_c,           killclient,     {0} },
  { MODKEY,                  XK_t,           setlayout,      {.v = &layouts[0]} },
  { MODKEY,                  XK_f,           setlayout,      {.v = &layouts[1]} },
  { MODKEY,                  XK_m,           setlayout,      {.v = &layouts[2]} },
  { MODKEY,                  XK_space,       setlayout,      {0} },
  { MODKEY|ShiftMask,        XK_space,       togglefloating, {0} },
  { MODKEY,                  XK_0,           view,           {.ui = ~0 } },
  { MODKEY|ShiftMask,        XK_0,           tag,            {.ui = ~0 } },
  { MODKEY,                  XK_comma,       focusmon,       {.i = -1 } },
  { MODKEY,                  XK_period,      focusmon,       {.i = +1 } },
  { MODKEY|ShiftMask,        XK_comma,       tagmon,         {.i = -1 } },
  { MODKEY|ShiftMask,        XK_period,      tagmon,         {.i = +1 } },
  TAGKEYS(                   XK_1,                      0)
  TAGKEYS(                   XK_2,                      1)
  TAGKEYS(                   XK_3,                      2)
  TAGKEYS(                   XK_4,                      3)
  TAGKEYS(                   XK_5,                      4)
  TAGKEYS(                   XK_6,                      5)
  TAGKEYS(                   XK_7,                      6)
  TAGKEYS(                   XK_8,                      7)
  TAGKEYS(                   XK_9,                      8)
  { MODKEY|ShiftMask,        XK_q,           quit,           {0} },
}
;
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
