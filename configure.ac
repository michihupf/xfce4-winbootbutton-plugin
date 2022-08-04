AC_CONFIG_MACRO_DIR([m4])
AC_INIT([xfce4-winbootbutton-plugin], [1.1.0], [https://github.com/michihupf/xfce4-winbootbutton-plugin], [xfce4-winbootbutton-plugin])

dnl | Initialize automake
AM_INIT_AUTOMAKE([foreign])
AM_MAINTAINER_MODE()
AC_CONFIG_HEADERS([config.h])

dnl | Initialize libtool
LT_PREREQ([2.2.6])
LT_INIT([disable-static])

dnl | Check for basic programs
AC_PROG_CC()
AC_PROG_CC_C_O()
AC_PROG_LD()
AC_PROG_INSTALL()

dnl | Check for X11 installed
XDT_CHECK_LIBX11_REQUIRE()

dnl | Check for required packages
XDT_CHECK_PACKAGE([LIBXFCE4PANEL], [libxfce4panel-2.0])
XDT_CHECK_PACKAGE([LIBXFCE4UTIL], [libxfce4util-1.0])
XDT_CHECK_PACKAGE([GLIB], [glib-2.0])

AC_CONFIG_FILES([
    Makefile
    icons/Makefile
    icons/48x48/Makefile
    icons/scalable/Makefile
    src/Makefile
])
AC_OUTPUT
