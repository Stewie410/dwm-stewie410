/* See LICENSE file for copyright and license details. */

/* appearance */
static const unsigned int borderpx  = 1;        /* border pixel of windows */
static const unsigned int snap      = 32;       /* snap pixel */
static const unsigned int gappih    = 5;        /* horiz inner gap between windows */
static const unsigned int gappiv    = 5;        /* vert inner gap between windows */
static const unsigned int gappoh    = 5;        /* horiz outer gap between windows & edge */
static const unsigned int gappov    = 5;        /* vert outer gap between windows & edge */
static const unsigned int smartgaps = 1;        /* 1 means no outer gap w/ single window */
static const int showbar            = 1;        /* 0 means no bar */
static const int topbar             = 1;        /* 0 means bottom bar */
static const int user_bh            = 0;        /* 0: dwm calculates; >=1: user user_bh */
//static const char *fonts[]          = { "monospace:size=10" };
static const char *fonts[]          = {
    "DejaVuSans-Regular:fontformat=true:pixelsize=10:antialias=true",
    "monospace:size=10",
    "unifont:fontformat=true:size=10:antialias=false",
    "siji:pixelsize=10",
    "Font Awesome 5 Free:fontformat=true:pixelsize=9:antialias=true:style=solid",
    "Font Awesome 5 Brands:fontformat=true:pixelsize=9:antialias=true:style=solid",
};
static const char dmenufont[]       = "Fira Code Regular:fontformat=true:pixelsize=10:antialias=true";
static const char col_gray1[]       = "#222222";
static const char col_gray2[]       = "#444444";
static const char col_gray3[]       = "#bbbbbb";
static const char col_gray4[]       = "#eeeeee";
static const char col_cyan[]        = "#005577";
static const char col_urgborder[]   = "#ff0000";
static const char *colors[][3]      = {
	/*               fg         bg         border   */
	[SchemeNorm] = { col_gray3, col_gray1, col_gray2 },
	[SchemeSel]  = { col_gray4, col_cyan,  col_cyan  },
    [SchemeUrg]  = { col_gray4, col_cyan,  col_urgborder },
};

/* tagging */
static const char *tags[] = { "1", "2", "3", "4", "5", "6", "7", "8", "9" };

static const Rule rules[] = {
	/* xprop(1):
	 *	WM_CLASS(STRING) = instance, class
	 *	WM_NAME(STRING) = title
	 */
	/* class      instance    title       tags mask     iscentered      isfloating   monitor */
	{ "Gimp",     NULL,       NULL,       0,            0,              1,           -1 },
	{ "Firefox",  NULL,       NULL,       1 << 8,       0,              0,           -1 },
};

/* layout(s) */
static const float mfact     = 0.50; /* factor of master area size [0.05..0.95] */
static const int nmaster     = 1;    /* number of clients in master area */
static const int resizehints = 1;    /* 1 means respect size hints in tiled resizals */

#define FORCE_VSPLIT 1 /* nrowgrid layout: force two clients to always split vertically */
#include "tcl.c"
//#include "fibonacci.c"
#include "vanitygaps.c"

static const Layout layouts[] = {
    // Master-Stack                 Left:Master         Right:Stack
    { "[]=", tile },

    // Three Column                 Center:Master       LeftRight:Stack
    //{ "TCL", tcl },

    // BStack                       Top:Master          Bottom:Stack (vert split)
    // BStackHoriz                  Top:Master          Bottom:Stack (horiz split)
    { "BSV", bstack },
    { "BSH", bstackhoriz },

    // Spiral                       Left:Master         Right:Stack (fibonacci spiral)
    // Dwindle                      Left:Master         Right:Stack (spiral down-right)
    { "FIB", spiral },
    { "DWI", dwindle },

    // Deck                         Left:Master         Right:Stack (monocle)
    { "DEK", deck },

    // Monocle                      Fullscreen:Master-Stack // Layout switch cycles masters before continuing
    { "[M]", monocle },

    // Centered Master              Center:Master       LeftRight:Stack
    // Centered Floating Master     Center:Master(F)    LeftRight:Stack
    { "CTM", centeredmaster },
    { "CFM", centeredfloatingmaster },

    // Floating                     Fullscreen:Master-Stack(F)
    { "FLT", NULL },

    // Terminate/Return to layouts[0]
    { NULL, NULL },
};

/* key definitions */
#define MODKEY Mod1Mask
#define TAGKEYS(KEY,TAG) \
	{ MODKEY,                       KEY,      view,           {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask,           KEY,      toggleview,     {.ui = 1 << TAG} }, \
	{ MODKEY|ShiftMask,             KEY,      tag,            {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask|ShiftMask, KEY,      toggletag,      {.ui = 1 << TAG} }, \

/* helper for spawning shell commands in the pre dwm-5.0 fashion */
#define SHCMD(cmd) { .v = (const char*[]){ "/bin/sh", "-c", cmd, NULL } }

/* commands */
static char dmenumon[2] = "0"; /* component of dmenucmd, manipulated in spawn() */
static const char *dmenucmd[] = { "dmenu_run", "-m", dmenumon, "-fn", dmenufont, "-nb", col_gray1, "-nf", col_gray3, "-sb", col_cyan, "-sf", col_gray4, NULL };
static const char *termcmd[]  = { "alacritty", NULL };

#include <X11/XF86keysym.h>

static Key keys[] = {
    // Application Hotkeys
	{ MODKEY,                       XK_d,      spawn,          {.v = dmenucmd } },
    { MODKEY,                       XK_Return, spawn,          {.v = termcmd } },
    { MODKEY,                       XK_F2,     spawn,          SHCMD("firefox") },
    { MODKEY,                       XK_F3,     spawn,          SHCMD("alacritty -e ranger ~/") },
    { MODKEY,                       XK_F8,     spawn,          SHCMD("thunderbird") },
    { 0,                            XK_Print,  spawn,          SHCMD("autoscrot.sh") },

    // Toggle Panel
	{ MODKEY,                       XK_b,      togglebar,      {0} },

    // Stack
	{ MODKEY,                       XK_j,      focusstack,     {.i = +1 } },
	{ MODKEY,                       XK_k,      focusstack,     {.i = -1 } },
    { MODKEY|ShiftMask,             XK_j,      incnmaster,     {.i = -1 } },

    { MODKEY|ShiftMask,             XK_k,      incnmaster,     {.i = +1 } },
	{ MODKEY,                       XK_h,      setmfact,       {.f = -0.05} },
	{ MODKEY,                       XK_l,      setmfact,       {.f = +0.05} },
	{ MODKEY|ShiftMask,             XK_Return, zoom,           {0} },
	{ MODKEY,                       XK_Tab,    view,           {0} },

    // Gaps
    /* all-gaps                     incrgaps
     * toggle                       togglegaps
     * reset                        defaultgaps
     * inner/outer all              incrigaps/incrogaps
     * inner/outer horiz            incrihgaps/incrohgaps
     * inner/outer vert             incrivgaps/incrovgaps
     */
    { MODKEY|Mod4Mask,              XK_h,      incrgaps,       {.i = +1 } },
    { MODKEY|Mod4Mask,              XK_l,      incrgaps,       {.i = -1 } },
    { MODKEY|Mod4Mask,              XK_g,      togglegaps,     {0} },
    { MODKEY|Mod4Mask|ShiftMask,    XK_g,      defaultgaps,    {0} },

    // Kill
	{ MODKEY|ShiftMask,             XK_q,      killclient,     {0} },

    // Layouts
    { MODKEY,                       XK_backslash, cyclelayout, {.i = +1} },
    { MODKEY|ShiftMask,             XK_backslash, cyclelayout, {.i = -1} },

    // Floating
	//{ MODKEY,                       XK_space,  setlayout,      {0} },
	{ MODKEY|ShiftMask,             XK_space,  togglefloating, {0} },
    { MODKEY|ShiftMask,             XK_s,      togglesticky,   {0} },
	{ MODKEY,                       XK_0,      view,           {.ui = ~0 } },
	{ MODKEY|ShiftMask,             XK_0,      tag,            {.ui = ~0 } },

    // Monitors
	{ MODKEY,                       XK_comma,  focusmon,       {.i = -1 } },
	{ MODKEY,                       XK_period, focusmon,       {.i = +1 } },
	{ MODKEY|ShiftMask,             XK_comma,  tagmon,         {.i = -1 } },
	{ MODKEY|ShiftMask,             XK_period, tagmon,         {.i = +1 } },

    // Tags
	TAGKEYS(                        XK_1,                      0)
	TAGKEYS(                        XK_2,                      1)
	TAGKEYS(                        XK_3,                      2)
	TAGKEYS(                        XK_4,                      3)
	TAGKEYS(                        XK_5,                      4)
	TAGKEYS(                        XK_6,                      5)
	TAGKEYS(                        XK_7,                      6)
	TAGKEYS(                        XK_8,                      7)
	TAGKEYS(                        XK_9,                      8)

    // Exit
	{ MODKEY|ShiftMask,             XK_Escape,  quit,           {0} },

    // Media
    { 0, XF86XK_AudioMute,          spawn, SHCMD("pamixer --toggle-mute") },
    { 0, XF86XK_AudioLowerVolume,   spawn, SHCMD("pamixer --decrease 1") },
    { 0, XF86XK_AudioRaiseVolume,   spawn, SHCMD("pamixer --increase 1") },
    { 0, XF86XK_AudioPrev,          spawn, SHCMD("playerctl previous") },
    { 0, XF86XK_AudioPlay,          spawn, SHCMD("playerctl play-pause") },
    { 0, XF86XK_AudioNext,          spawn, SHCMD("playerctl next") },

    // Brightness
    { 0, XF86XK_MonBrightnessDown,  spawn, SHCMD("xbrightness.sh --decrease 5") },
    { 0, XF86XK_MonBrightnessUp,    spawn, SHCMD("xbrightness.sh --increase 5") },

    // Various
    //{ 0, XF86XK_Search, NULL, NULL },
    //{ 0, XF86XK_RFKill, NULL, NULL },
};

/*
 * Things to bring in from i3
 *
 * Mod == Mod1 (Alt)
 * Sup == Mod4 (Win)
 *
 * Mod+Shift+j              Push master into stack
 * Mod+Shift+k              Push stack into master
 *
 * Mod+Shift+F11            Toggle Fullscreen
 * Mod+Shift+Backslash      Cycle Layouts
 *
 * Sup+Return               Show Scratchpad
 * Sup+Shift+Return         Move application to Scratchpad
 *
 * Mod+Shift+r              Restart dwm
 *
 * Function-Keys            Various Functions
 */

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

