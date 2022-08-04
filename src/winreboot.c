#include "winreboot.h"

extern int boot_entry;
extern gboolean use_pkexec;

gboolean button_pressed(GtkWidget* button, GdkEventButton *event, gpointer plugin) {
    if (event->type == GDK_BUTTON_PRESS) {
        // check if left clicked
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
            return TRUE;
        }
    }
    
    return FALSE;
}

gboolean dialog_response(GtkDialog *dialog, gint response_id, gpointer user_data) {
    switch (response_id) {
        case GTK_RESPONSE_YES:
            if (system(NULL)) {
                // TODO: make sure to have grub-reboot run without password when using sudo, else use pkexec
                // like as a failsafe option || this might be hard as /etc/sudoers usually is only readable by root
                char cmd[255];
                if (use_pkexec)
                    sprintf(cmd, "pkexec grub-reboot %i && reboot", boot_entry);
                else 
                    sprintf(cmd, "sudo grub-reboot %i && reboot", boot_entry);
                system(cmd);
            }
            gtk_widget_destroy(GTK_WIDGET(dialog));
            break;
        case GTK_RESPONSE_NO:
        case GTK_RESPONSE_DELETE_EVENT:
            gtk_widget_destroy(GTK_WIDGET(dialog));
            break;
    }
    return TRUE;
}
