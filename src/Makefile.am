## plugin 

plugindir = $(libdir)/xfce4/panel/plugins

plugin_LTLIBRARIES = libwinbootbutton.la
libwinbootbutton_la_SOURCES = \
	winbootbutton.c winbootbutton.h \
	winreboot.c winreboot.h \
	_gresources.xml _dialogs.xml \
	_gresources.c

_gresources.c: _gresources.xml _dialogs.xml 
	glib-compile-resources --generate-source --target _gresources.c _gresources.xml

libwinbootbutton_la_CFLAGS = @LIBXFCE4PANEL_CFLAGS@ @LIBXFCE4UTIL_CFLAGS@ @GLIB_CFLAGS@ $(X11_CFLAGS)
libwinbootbutton_la_LDFLAGS = -avoid-version -module -no-undefined -export-symbols-regex '^xfce_panel_module_(preinit|init|construct)'
libwinbootbutton_la_LIBADD = @LIBXFCE4PANEL_LIBS@ @LIBXFCE4UTIL_LIBS@ @GLIB_LIBS@ $(GTK_LIBS) $(X11_LIBS)

## desktop file
desktopdir = $(datadir)/xfce4/panel/plugins

dist_desktop_DATA = winbootbutton.desktop
