# Stewie410's DWM

This is my personal build of dwm, including _several_ patches to get the UX I'm
looking for.  Most importantly, I wanted to have parity with my i3-gaps config
where possible; while also getting away from manual tiling as a whole.

## Patches

* [bar height](https://dwm.suckless.org/patches/bar_height/dwm-bar-height-6.2.diff)
* [bottom stack](https://dwm.suckless.org/patches/bottomstack/)
  * Vanity Gaps variant
* [center](https://dwm.suckless.org/patches/center/dwm-center-6.2.diff)
* [centeredmaster](https://dwm.suckless.org/patches/centeredmaster/)
  * Vanity Gaps variant
* [colorbar](https://dwm.suckless.org/patches/colorbar/dwm-colorbar-6.2.diff)
* [combo](https://dwm.suckless.org/patches/combo/dwm-combo-6.1.diff)
* [cyclelayouts](https://dwm.suckless.org/patches/cyclelayouts/dwm-cyclelayouts-20180524-6.2.diff)
* [deck](https://dwm.suckless.org/patches/deck/dwm-deck-6.0.diff)
  * Vanity Gaps variant
* [fibonacci](https://dwm.suckless.org/patches/fibonacci/dwm-fibonacci-20200418-c82db69.diff)
  * Vanity Gaps variant
* [focusmaster](https://dwm.suckless.org/patches/focusmaster/dwm-focusmaster-20200717-bb2e722.diff)
* [hide vacant tags](https://dwm.suckless.org/patches/hide_vacant_tags/dwm-hide_vacant_tags-6.2.diff)
* [nodmenu](https://dwm.suckless.org/patches/nodmenu/dwm-nodmenu-6.2.diff)
* [pertag](https://dwm.suckless.org/patches/pertag/dwm-pertag-6.2.diff)
* [removeborder](https://dwm.suckless.org/patches/removeborder/dwm-removeborder-20200520-f09418b.diff)
* [sizehints](https://dwm.suckless.org/patches/sizehints/dwm-sizehints-isfreesize-6.2.diff)
* [statuscmd](https://dwm.suckless.org/patches/statuscmd/dwm-statuscmd-signal-6.2.diff)
* [sticky](https://dwm.suckless.org/patches/sticky/dwm-sticky-20160911-ab9571b.diff)
* [swallow](https://dwm.suckless.org/patches/swallow/dwm-swallow-20200807-b2de9b0.diff)
* [systray](https://dwm.suckless.org/patches/systray/dwm-systray-20200610-f09418b.diff)
* [three column](https://dwm.suckless.org/patches/three-column/tcl.c)
* [urgentborder](https://dwm.suckless.org/patches/urgentborder/dwm-6.2-urg-border.diff)
* [vanitygaps](https://dwm.suckless.org/patches/vanitygaps/)
  * Specifically [bakkeby's `vanitygaps.c` implementation](https://github.com/bakkeby/dwm-vanitygaps/blob/master/vanitygaps.c)

## TODO

* Update `tcl.c` to work with vanity gaps, or remove it
* Get click-events working for `dwmblocks`

## Layouts

* Tile (default)
* Bottom Stack Vertical
* Bottom Stack Horizontal
* Fibonacci Spiral
* Dwindle Spiral
* Deck
* Monocle (default)
* Centered Master
* Centered Floating Master
* Floating (default)

## Assumptions

* My dwmblocks build is used for the status bar
* My dmenu build is used for dmenu
* You prefer dracula as a theme

## Application Dependencies

* Firefox
* Alacritty
* Thunderbird
* ranger
* dwmblocks-stewie410
  * dwm scripts from dotfiles
* dmenu-stewie410
* pamixer
* playerctl
* xbrightness

## DWM README

```txt
dwm - dynamic window manager
============================
dwm is an extremely fast, small, and dynamic window manager for X.


Requirements
------------
In order to build dwm you need the Xlib header files.


Installation
------------
Edit config.mk to match your local setup (dwm is installed into
the /usr/local namespace by default).

Afterwards enter the following command to build and install dwm (if
necessary as root):

    make clean install


Running dwm
-----------
Add the following line to your .xinitrc to start dwm using startx:

    exec dwm

In order to connect dwm to a specific display, make sure that
the DISPLAY environment variable is set correctly, e.g.:

    DISPLAY=foo.bar:1 exec dwm

(This will start dwm on display :1 of the host foo.bar.)

In order to display status info in the bar, you can do something
like this in your .xinitrc:

    while xsetroot -name "`date` `uptime | sed 's/.*,//'`"
    do
        sleep 1
    done &
    exec dwm


Configuration
-------------
The configuration of dwm is done by creating a custom config.h
and (re)compiling the source code.
```
