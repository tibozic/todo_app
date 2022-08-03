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
    GtkBuilder *builder;
    GtkWidget *window;

    builder = gtk_builder_new_from_file("../../src/ui/todo_app.ui");
    window = GTK_WIDGET (gtk_builder_get_object(builder, "window"));
    box_uncompleted_tasks = GTK_WIDGET (gtk_builder_get_object(builder, "box_uncompleted_tasks"));
    box_completed_tasks = GTK_WIDGET (gtk_builder_get_object(builder, "box_completed_tasks"));
    gtk_window_set_application(GTK_WINDOW (window), GTK_APPLICATION (app));

    gtk_widget_show(window);

    tasks_load();
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

    all_tasks.push_back(new_task);
}

static void task_complete(GtkButton *btn, gpointer user_data)
{
    int index = GPOINTER_TO_INT (user_data);
    Task *task = &all_tasks[index];

    if (task->get_is_completed())
    {
        task->set_is_completed(0);
    }
    else
    {
        task->set_is_completed(1);
    }
}

void tasks_save()
{
    if (all_tasks.size() == 0)
    {
        return;
    }

    ofstream file("tasks.txt");

    for ( Task task : all_tasks )
    {
        task.save_to_file(&file);
    }

    file.close();
}

void tasks_load()
{
    ifstream file("tasks.txt");

    if (!file)
    {
        file.close();
        return;
    }

    string line;

    while ( getline(file, line) )
    {
        if ( !line.empty() )
        {
            Task::load_from_file(line);
        }
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

    tokens.push_back(current);

    return tokens;
} 