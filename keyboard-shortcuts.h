/* Commands */
static char dmenumon[2] = "0"; /* component of dmenucmd, manipulated in spawn() */
static const char *dmenucmd[] = { "dmenu_run", "-m", dmenumon, "-fn", dmenufont, "-nb", normbgcolor, "-nf", normfgcolor, "-sb", selbgcolor, "-sf", selfgcolor, NULL };
static const char *termcmd[]  = {"urxvt", NULL};
static const char *termnotmuxcmd[]  = {"urxvt", NULL};
static const char *scrsavercmd[]  = {"screenlock", NULL};
static const char *browsercmd[] = {"run-browser", NULL};
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
static const char *telegramcmd[] = {"telegram-desktop", NULL};

/* Key mapping. */
static Key keys[] = {
  /* modifier                key                  function        argument */
  { MODKEY,                  XK_p,                spawn,          {.v = dmenucmd } },
  { MODKEY,                  XK_F2,               spawn,          {.v = dmenucmd } },
  { MODKEY|ShiftMask,        XK_Return,           spawn,          {.v = termcmd } },
  { MODKEY|ShiftMask,        XK_t,                spawn,          {.v = termnotmuxcmd } },
  { WINKEY,                  XK_l,                spawn,          {.v = scrsavercmd } },
  { WINKEY,                  XK_b,                spawn,          {.v = browsercmd } },
  { WINKEY,                  XK_Return,           spawn,          {.v = termcmd } },
  { WINKEY,                  XK_i,                spawn,          {.v = irccmd } },
  { WINKEY,                  XK_s,                spawn,          {.v = skypecmd } },
  { WINKEY,                  XK_t,                spawn,          {.v = telegramcmd } },
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
  { ShiftMask,               XK_Page_Down,        shiftview,      {.i = +1 } },
  { ShiftMask,               XK_Page_Up,          shiftview,      {.i = -1 } },
  { MODKEY,                  XK_b,                togglebar,      {0} },
  { MODKEY,                  XK_j,                focusstack,     {.i = +1 } },
  { MODKEY,                  XK_k,                focusstack,     {.i = -1 } },
  { MODKEY,                  XK_i,                incnmaster,     {.i = +1 } },
  { MODKEY,                  XK_d,                incnmaster,     {.i = -1 } },
  { MODKEY,                  XK_h,                setmfact,       {.f = -0.05} },
  { MODKEY,                  XK_l,                setmfact,       {.f = +0.05} },
  { MODKEY,                  XK_Return,           zoom,           {0} },
  { MODKEY,                  XK_Tab,              view,           {0} },
  { MODKEY|ShiftMask,        XK_c,                killclient,     {0} },
  { MODKEY,                  XK_t,                setlayout,      {.v = &layouts[0]} },
  { MODKEY,                  XK_f,                setlayout,      {.v = &layouts[1]} },
  { MODKEY,                  XK_m,                setlayout,      {.v = &layouts[2]} },
  { MODKEY,                  XK_space,            setlayout,      {0} },
  { MODKEY|ShiftMask,        XK_space,            togglefloating, {0} },
  { MODKEY,                  XK_0,                view,           {.ui = ~0 } },
  { MODKEY|ShiftMask,        XK_0,                tag,            {.ui = ~0 } },
  { MODKEY,                  XK_comma,            focusmon,       {.i = -1 } },
  { MODKEY,                  XK_period,           focusmon,       {.i = +1 } },
  { MODKEY|ShiftMask,        XK_comma,            tagmon,         {.i = -1 } },
  { MODKEY|ShiftMask,        XK_period,           tagmon,         {.i = +1 } },
  TAGKEYS(                   XK_1,                      0)
  TAGKEYS(                   XK_2,                      1)
  TAGKEYS(                   XK_3,                      2)
  TAGKEYS(                   XK_4,                      3)
  TAGKEYS(                   XK_5,                      4)
  TAGKEYS(                   XK_6,                      5)
  TAGKEYS(                   XK_7,                      6)
  { MODKEY|ShiftMask,        XK_q,           quit,           {0} },
};

/* vim:set ts=2 sw=2 et: */

