
Debian
====================
This directory contains files used to package vestxd/vestx-qt
for Debian-based Linux systems. If you compile vestxd/vestx-qt yourself, there are some useful files here.

## vestx: URI support ##


vestx-qt.desktop  (Gnome / Open Desktop)
To install:

	sudo desktop-file-install vestx-qt.desktop
	sudo update-desktop-database

If you build yourself, you will either need to modify the paths in
the .desktop file or copy or symlink your vestx-qt binary to `/usr/bin`
and the `../../share/pixmaps/vestx128.png` to `/usr/share/pixmaps`

vestx-qt.protocol (KDE)

