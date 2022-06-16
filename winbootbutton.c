#include <libxfce4panel/libxfce4panel.h>

static void 
plugin_construct(XfcePanelPlugin *plugin);

XFCE_PANEL_PLUGIN_REGISTER(plugin_construct);

gboolean button_pressed(GtkWidget*,GdkEventButton*,gpointer);
gboolean dialog_response(GtkDialog*,gint,gpointer);

static void plugin_construct(XfcePanelPlugin *plugin) {
    GtkWidget *box = gtk_box_new(xfce_panel_plugin_get_orientation(plugin), 0);

    gtk_widget_set_size_request(box, 30, 30);

    GtkWidget *button = gtk_button_new_from_icon_name("application-x-ms-dos-executable", GTK_ICON_SIZE_LARGE_TOOLBAR);
    GtkStyleContext *context = gtk_widget_get_style_context(button);
    gtk_style_context_add_class(context, "win-boot-button");

    g_signal_connect(G_OBJECT(button), "button-press-event", G_CALLBACK(button_pressed), (gpointer *)plugin);

    gtk_container_add(GTK_CONTAINER(box), button);
    gtk_widget_show_all(button);

    gtk_widget_set_size_request(GTK_WIDGET(plugin), 30, 30);

    gtk_container_add(GTK_CONTAINER(plugin), box);
    gtk_widget_show_all(box);
    xfce_panel_plugin_set_expand(XFCE_PANEL_PLUGIN(plugin), FALSE);
}

gboolean button_pressed(GtkWidget* button, GdkEventButton *event, gpointer plugin) {
    // check if left clicked
    if (event->type == GDK_BUTTON_PRESS) {
        if (event->button == 1) {
            GtkWidget *dialog, *label, *content_area;
            GtkDialogFlags flags;

            flags = GTK_DIALOG_DESTROY_WITH_PARENT;
            dialog = gtk_dialog_new_with_buttons("Boot Windows?", NULL, flags, "Reboot", GTK_RESPONSE_YES, "Cancel", GTK_RESPONSE_NO, NULL);
            GtkWidget *header_bar = gtk_dialog_get_header_bar(GTK_DIALOG(dialog));
            gtk_header_bar_set_show_close_button(GTK_HEADER_BAR(header_bar), FALSE);

            content_area = gtk_dialog_get_content_area(GTK_DIALOG(dialog));
            label = gtk_label_new("Do you really want to reboot to Windows now?\n\n");

            g_signal_connect_swapped(dialog, "response", G_CALLBACK(dialog_response), dialog);

            gtk_container_add(GTK_CONTAINER(content_area), label);
            gtk_widget_show_all(dialog);
        }
    }
    
    return TRUE;
}

gboolean dialog_response(GtkDialog *dialog, gint response_id, gpointer user_data) {
    switch (response_id) {
        case GTK_RESPONSE_YES:
            if (system(NULL))
                // TO-IMPLEMENT: make sure to have grub-reboot run without password when using sudo, else use pkexec
                system("sudo grub-reboot 2 && xfce4-session-logout --reboot --fast");
            gtk_widget_destroy(GTK_WIDGET(dialog));
            break;
        case GTK_RESPONSE_NO: 
        case GTK_RESPONSE_DELETE_EVENT:
            gtk_widget_destroy(GTK_WIDGET(dialog));
            break;
    }
    return TRUE;
}
