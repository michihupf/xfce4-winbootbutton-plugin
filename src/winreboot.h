#ifndef WINREBOOT_H_
#define WINREBOOT_H_
#pragma once

#include<libxfce4panel/libxfce4panel.h>

gboolean button_pressed(GtkWidget *button, GdkEventButton*,gpointer);
gboolean dialog_response(GtkDialog*,gint,gpointer);

#endif
