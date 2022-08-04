#ifndef WINBOOTBUTTON_H_
#define WINBOOTBUTTON_H_
#pragma once

#include <libxfce4panel/libxfce4panel.h>
#include <libxfce4util/libxfce4util.h>
#include <ctype.h>
#include <config.h>
#include <glib.h>

static void plugin_construct(XfcePanelPlugin*);
GKeyFile* get_config_file();
void read_settings();
void save_settings();

typedef struct {
    GObject *boot_entry_obj;
    GObject *use_pkexec_obj;

    GtkWidget *dialog;
} Settings;

gboolean plugin_configure();
void boot_entry_changed(GtkEntry *boot_entry_obj);
gboolean pkexec_changed(GtkSwitch *use_pkexec_obj);
void plugin_configure_save();

#endif
