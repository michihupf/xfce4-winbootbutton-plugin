#include "winbootbutton.h"
#include "winreboot.h"

static void 
plugin_construct(XfcePanelPlugin *plugin);

XFCE_PANEL_PLUGIN_REGISTER(plugin_construct);

int boot_entry = 2; // fallsback boot entry will always be 2
gboolean use_pkexec = 0; // sudo will always be the default option. This might change in future versions!

XfcePanelPlugin *self;

static void plugin_construct(XfcePanelPlugin *plugin) {
	TRACE("enter static void plugin_construct(XfcePanelPlugin *plugin)");
    self = plugin;
    g_debug("winbootbutton-plugin initialized.");
    read_settings();

    GtkWidget *box = gtk_box_new(xfce_panel_plugin_get_orientation(plugin), 0);

    gtk_widget_set_size_request(box, 30, 30);

    GtkWidget *button = gtk_button_new_from_icon_name("xfce4-winbootbutton-plugin", GTK_ICON_SIZE_LARGE_TOOLBAR);
    GtkStyleContext *context = gtk_widget_get_style_context(button);
    gtk_style_context_add_class(context, "win-boot-button");

    g_signal_connect(G_OBJECT(button), "button-press-event", G_CALLBACK(button_pressed), plugin);
    g_signal_connect(G_OBJECT(GTK_WIDGET(plugin)), "configure-plugin", G_CALLBACK(plugin_configure), NULL);

    gtk_container_add(GTK_CONTAINER(box), button);
    gtk_widget_show_all(button);

    gtk_widget_set_size_request(GTK_WIDGET(plugin), 30, 30);

    gtk_container_add(GTK_CONTAINER(plugin), box);

    xfce_panel_plugin_menu_show_configure(plugin);
    gtk_widget_show_all(box);

	TRACE("leave static void plugin_construct(XfcePanelPlugin *plugin)");
}


GKeyFile* get_config_file() {
	TRACE("enter GKeyFile* get_config_file()");
    gchar *file_path = xfce_panel_plugin_save_location(self, TRUE);

    g_debug("Retrieving config file from %s", file_path);

    if (!file_path)
        return NULL;

    GKeyFile *conf = g_key_file_new();

    if (g_file_test(file_path, G_FILE_TEST_IS_REGULAR))
        g_key_file_load_from_file(conf, file_path, G_KEY_FILE_NONE, NULL);
    // check for a default config provided
    else {
        // winbutton_debug("Checking for default config.");
        gchar *default_conf = xfce_resource_lookup(XFCE_RESOURCE_CONFIG, "xfce4/panel/winbootbutton.rc");

        if (g_file_test(default_conf, G_FILE_TEST_IS_REGULAR))
            g_key_file_load_from_file(conf, default_conf, G_KEY_FILE_NONE, NULL);

        g_free(default_conf);
    }
    g_free(file_path);

	TRACE("leave GKeyFile* get_config_file()");
    return conf;
}

void read_settings() {
	TRACE("enter void read_settings()");
    GKeyFile *file = get_config_file();

    // winbutton_debug("Reading settings from config file");

    if (!file)
        return;

    g_debug("has_bootEntry: %i, has_usePkexec: %i", g_key_file_has_key(file, "user", "bootEntry", NULL), 
            g_key_file_has_key(file, "user", "usePkexec", NULL));

    if (g_key_file_has_key(file, "user", "bootEntry", NULL))
        boot_entry = g_key_file_get_integer(file, "user", "bootEntry", NULL);
    if (g_key_file_has_key(file, "user", "usePkexec", NULL))
        use_pkexec = g_key_file_get_boolean(file, "user", "usePkexec", NULL);

    g_debug("Read values from config file if possible: bootEntry: %i, usePkexec: %i", boot_entry, use_pkexec);

	TRACE("leave void read_settings()");
}

void save_settings() {
	TRACE("enter void save_settings()");
    gchar *file_path = xfce_panel_plugin_save_location(self, TRUE);
    GKeyFile *file = get_config_file();
    if (!file)
        file = g_key_file_new();

    g_key_file_set_integer(file, "user", "bootEntry", boot_entry);
    g_key_file_set_boolean(file, "user", "usePkexec", use_pkexec);

    // winbutton_debug("Saving settings to file: %s", file_path);

    g_debug("Saving settings to %s: bootEntry: %i - usePkexec: %i", file_path, boot_entry, use_pkexec);

    g_key_file_save_to_file(file, file_path, NULL);
    g_free(file_path);

	TRACE("leave void save_settings()");
}

// this is the callback to produce the "Properties" dialog when the corresponding button 
// is pressed in the right click menu of the plugin.
gboolean plugin_configure() {
	TRACE("enter gboolean plugin_configure()");
    GtkBuilder *builder = gtk_builder_new_from_resource("/_dialogs.xml");
    Settings settings;
    
    settings.dialog = (GtkWidget *) gtk_builder_get_object(builder, "dialog");

    settings.boot_entry_obj = gtk_builder_get_object(builder, "t_bootEntry");
    char str[5];
    sprintf(str, "%d", boot_entry);
    gtk_entry_set_text(GTK_ENTRY(settings.boot_entry_obj), str);
    g_signal_connect(settings.boot_entry_obj, "changed", G_CALLBACK(boot_entry_changed), NULL);

    settings.use_pkexec_obj = gtk_builder_get_object(builder, "sw_usePKE");
    gtk_switch_set_state(GTK_SWITCH(settings.use_pkexec_obj), use_pkexec);
    gtk_widget_set_sensitive(GTK_WIDGET(settings.use_pkexec_obj), TRUE);
    g_signal_connect(settings.use_pkexec_obj, "state-set", G_CALLBACK(pkexec_changed), NULL);

    gtk_widget_show(settings.dialog);

	TRACE("leave gboolean plugin_configure()");
    return TRUE;
}

void boot_entry_changed(GtkEntry *boot_entry_obj) {
	TRACE("enter void boot_entry_changed(GtkEntry *boot_entry_obj)");
    g_debug("Boot Entry changed!");
    const char *text = gtk_entry_get_text(GTK_ENTRY(boot_entry_obj));
    for (int i = 0; text[i] != '\0'; ++i) {
        if (!isdigit(text[i]))
            return;
    }
    boot_entry = atoi(text);

    save_settings();

	TRACE("leave void boot_entry_changed(GtkEntry *boot_entry_obj)");
}

gboolean pkexec_changed(GtkSwitch *use_pkexec_obj) {
	TRACE("enter gboolean pkexec_changed(GtkSwitch *use_pkexec_obj)");
    g_debug("Pkexec changed!");
    use_pkexec = gtk_switch_get_active(GTK_SWITCH(use_pkexec_obj));

    save_settings();

	TRACE("leave gboolean pkexec_changed(GtkSwitch *use_pkexec_obj)");
    return FALSE;
}
