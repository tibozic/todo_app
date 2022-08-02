#include <iostream>

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


static void app_activate(GApplication *app,
                            gpointer user_data)
{
    GtkWidget *window;
    GtkWidget *box_all_tasks;
    GtkWidget *box_uncompleted_header;
    GtkWidget *box_completed_header;
    GtkWidget *lbl_uncompleted;
    GtkWidget *lbl_completed;
    GtkWidget *btn_quit;
    GtkWidget *btn_add_task;

    /* Create the window */
    window = gtk_application_window_new(GTK_APPLICATION (app));
    gtk_window_set_title(GTK_WINDOW (window), "My TODO App");
    gtk_window_set_default_size(GTK_WINDOW (window), 400, 300);

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

    /* Add task button */
    btn_add_task = gtk_button_new_with_label("New task");
    g_signal_connect(btn_add_task, "clicked", G_CALLBACK (task_create), NULL);
    gtk_box_append(GTK_BOX (box_uncompleted_header), btn_add_task);

    lbl_completed = gtk_label_new("Completed tasks");
    gtk_box_append(GTK_BOX (box_completed_header), lbl_completed);

    /* Quit button */
    btn_quit = gtk_button_new_with_label("Quit");
    g_signal_connect(btn_quit, "clicked", G_CALLBACK (app_quit), window);
    gtk_box_append(GTK_BOX (box_completed_header), btn_quit);

    gtk_widget_show(window);
    g_print("Application is now active.\n");
}

static void app_quit(GtkButton *btn, gpointer user_data)
{
    GtkWindow *win = GTK_WINDOW (user_data);

    tasks_save();

    gtk_window_destroy(win);
}

static void task_create(GtkButton *btn, gpointer user_data)
{
    Task new_task;
    std::cout << "Created task: " << new_task.get_name() << "\n";
    std::cout << "Completness: " << new_task.get_is_completed() << "\n";
    std::cout << "New task on index: " << new_task.get_index() << "\n";
}

static void task_complete(GtkButton *btn, gpointer user_data)
{
    int index = GPOINTER_TO_INT (user_data);
    Task *task = &all_tasks[index];

    std::cout << "Task name: " << task->get_name() << "\n";
    // std::cout << "Clicked task at index: " << (index) << "\n";
    g_print("Switching task completness.\n");
    task->switch_completeness();
}

void tasks_save()
{
    ofstream file("tasks.txt");

    for ( Task task : all_tasks )
    {
        task.save_to_file(&file);
    }

    file.close();
}

vector<string> split(string in, char del)
{
    vector<string> tokens;
    string current;

    for ( char c : in )
    {
        if ( c == del )
        {
            tokens.push_back(current);
            current = "";
        }
        else
        {
            current += c;
        }
    }

    return tokens;
} 