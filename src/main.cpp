#include <iostream>
#include <gtk/gtk.h>
#include "main.h"


int main(int argc, char **argv) {
    GtkApplication *app;
    int status;

    app = gtk_application_new("my.app.todo", G_APPLICATION_FLAGS_NONE);

    g_signal_connect(app, "activate", G_CALLBACK (app_activate), NULL);

    status = g_application_run(G_APPLICATION (app), argc, argv);
    g_object_unref(app);
    return status;
}


static void app_activate(GApplication *app,
                            gpointer user_data)
{
    GtkWidget *window;

    window = gtk_application_window_new(GTK_APPLICATION (app));
    gtk_window_set_title(GTK_WINDOW (window), "My TODO App");
    gtk_window_set_default_size(GTK_WINDOW (window), 400, 300);

    gtk_widget_show(window);
    g_print("Application is now active.\n");
}
