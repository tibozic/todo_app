#include <iostream>
#include <list>
#include <list>

#include "Task.cpp"
#include <gtk/gtk.h>

#include "Task.cpp"
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
    GtkWidget *box_all_tasks;
    GtkWidget *box_uncompleted_header;
    GtkWidget *box_completed_header;
    GtkWidget *lbl_uncompleted;
    GtkWidget *lbl_completed;
    lbl_completed = gtk_label_new("Completed tasks");
    gtk_box_append(GTK_BOX (box_completed_header), lbl_completed);

    box_all_tasks = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 10);
    gtk_box_set_homogeneous(GTK_BOX (box_all_tasks), TRUE);
    gtk_window_set_child(GTK_WINDOW (window), box_all_tasks);

    box_uncompleted_tasks = gtk_box_new(GTK_ORIENTATION_VERTICAL, 5);
    gtk_box_set_homogeneous(GTK_BOX (box_uncompleted_tasks), FALSE);
    gtk_box_append(GTK_BOX (box_all_tasks), box_uncompleted_tasks);

    box_completed_tasks = gtk_box_new(GTK_ORIENTATION_VERTICAL, 5);
    gtk_box_set_homogeneous(GTK_BOX (box_completed_tasks), FALSE);
    gtk_box_append(GTK_BOX (box_all_tasks), box_completed_tasks);

    box_uncompleted_header = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 5);
    gtk_box_set_homogeneous(GTK_BOX (box_uncompleted_header), TRUE);
    gtk_box_append(GTK_BOX (box_uncompleted_tasks), box_uncompleted_header);

    box_completed_header = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 5);
    gtk_box_set_homogeneous(GTK_BOX (box_completed_header), TRUE);
    gtk_box_append(GTK_BOX (box_completed_tasks), box_completed_header);

    lbl_uncompleted = gtk_label_new("Uncompleted tasks");
    gtk_box_append(GTK_BOX (box_uncompleted_header), lbl_uncompleted);

    GtkWidget *btn_quit;
    GtkWidget *btn_add_task;

    /* Create the window */

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
