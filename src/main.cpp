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
    GtkBuilder *builder_main;
    GtkWidget *window;
    GtkWidget *btn_add_task;
    GtkWidget *btn_quit;

    builder_main = gtk_builder_new_from_file("../../src/ui/todo_app.ui");
    builder_task_create = gtk_builder_new_from_file("../../src/ui/create_task_window.ui");

    window = GTK_WIDGET (gtk_builder_get_object(builder_main, "window"));
    box_uncompleted_tasks = GTK_WIDGET (gtk_builder_get_object(builder_main, "box_uncompleted_tasks"));
    box_completed_tasks = GTK_WIDGET (gtk_builder_get_object(builder_main, "box_completed_tasks"));
    gtk_window_set_application(GTK_WINDOW (window), GTK_APPLICATION (app));

    btn_add_task = GTK_WIDGET (gtk_builder_get_object(builder_main, "btn_add_task"));
    btn_quit = GTK_WIDGET (gtk_builder_get_object(builder_main, "btn_quit"));

    g_signal_connect(btn_add_task, "clicked", G_CALLBACK (window_task_create), NULL);
    g_signal_connect(btn_quit, "clicked", G_CALLBACK (app_quit), window);
    g_signal_connect(window, "close-request", G_CALLBACK (app_quit), window);

    gtk_widget_show(window);

    tasks_load();
}

static void app_quit(GtkButton *btn, gpointer user_data)
{
    GtkWindow *win = GTK_WINDOW (user_data);

    tasks_save();

    gtk_window_destroy(win);
}

static void window_task_create(GtkButton *btn, gpointer user_data)
{
    GtkWidget *window_task_create;
    GtkWidget *btn_task_save;
    GtkWidget *btn_task_cancel;

    window_task_create = GTK_WIDGET (gtk_builder_get_object(builder_task_create, "window_task_create"));
    btn_task_save = GTK_WIDGET (gtk_builder_get_object(builder_task_create, "btn_task_save"));
    btn_task_cancel = GTK_WIDGET (gtk_builder_get_object(builder_task_create, "btn_task_cancel"));

    g_signal_connect(btn_task_cancel, "clicked", G_CALLBACK (window_task_create_quit), window_task_create);
    g_signal_connect(btn_task_save, "clicked", G_CALLBACK (task_create), builder_task_create);

    gtk_widget_show(window_task_create);
}

static void task_create(GtkButton *btn, gpointer user_data)
{
    GtkWidget *entry_task_name;
    GtkWidget *entry_task_description;
    GtkWidget *window;

    GtkEntryBuffer *task_buffer_name;
    GtkEntryBuffer *task_buffer_description;

    const char *task_name;
    const char *task_description;

    window = GTK_WIDGET (gtk_builder_get_object(builder_task_create, "window_task_create"));

    entry_task_name = GTK_WIDGET (gtk_builder_get_object(builder_task_create, "entry_task_name"));
    entry_task_description = GTK_WIDGET (gtk_builder_get_object(builder_task_create, "entry_task_description"));

    task_buffer_name = gtk_entry_get_buffer(GTK_ENTRY (entry_task_name));
    task_buffer_description = gtk_entry_get_buffer(GTK_ENTRY (entry_task_description));

    task_name = gtk_entry_buffer_get_text(task_buffer_name);
    task_description = gtk_entry_buffer_get_text(task_buffer_description);

    Task new_task(task_name, task_description, false);

    all_tasks.push_back(new_task);

    gtk_window_destroy(GTK_WINDOW (window));
}

static void window_task_create_quit(GtkButton *btn, gpointer user_data)
{
    GtkWidget *win = GTK_WIDGET (user_data);
    gtk_widget_hide(win);
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

static void task_edit_open(GtkButton *btn, gpointer user_data)
{
    GtkWidget *window_task_create;
    GtkWidget *btn_task_save;
    GtkWidget *btn_task_cancel;
    GtkWidget *entry_task_name;
    GtkWidget *entry_task_description;
    GtkEntryBuffer *task_buffer_name;
    GtkEntryBuffer *task_buffer_description;

    int index = GPOINTER_TO_INT(user_data);
    Task *task = &all_tasks[index];

    std::cout << "Editing\n";
    std::cout << "Editing task with name: " << task->get_name() << std::endl;

    window_task_create = GTK_WIDGET (gtk_builder_get_object(builder_task_create, "window_task_create"));
    btn_task_save = GTK_WIDGET (gtk_builder_get_object(builder_task_create, "btn_task_save"));
    btn_task_cancel = GTK_WIDGET (gtk_builder_get_object(builder_task_create, "btn_task_cancel"));
    entry_task_name = GTK_WIDGET (gtk_builder_get_object(builder_task_create, "entry_task_name"));
    entry_task_description = GTK_WIDGET (gtk_builder_get_object(builder_task_create, "entry_task_description"));

    task_buffer_name = gtk_entry_get_buffer(GTK_ENTRY (entry_task_name));
    task_buffer_description = gtk_entry_get_buffer(GTK_ENTRY (entry_task_description));

    gtk_entry_buffer_set_text(task_buffer_name, task->get_name().c_str(), 255);
    gtk_entry_buffer_set_text(task_buffer_description, task->get_description().c_str(), 255);

    g_signal_connect(btn_task_cancel, "clicked", G_CALLBACK (window_task_create_quit), window_task_create);
    g_signal_connect(btn_task_save, "clicked", G_CALLBACK (task_save), GINT_TO_POINTER(task->get_index()));

    gtk_widget_show(window_task_create);
}

static void task_save(GtkButton *btn, gpointer user_data)
{
    int index = GPOINTER_TO_INT(user_data);

    GtkWidget *entry_task_name;
    GtkWidget *entry_task_description;
    GtkWidget *window;

    GtkEntryBuffer *task_buffer_name;
    GtkEntryBuffer *task_buffer_description;

    const char *task_name;
    const char *task_description;

    Task *task = &all_tasks[index];

    window = GTK_WIDGET (gtk_builder_get_object(builder_task_create, "window_task_create"));

    entry_task_name = GTK_WIDGET (gtk_builder_get_object(builder_task_create, "entry_task_name"));
    entry_task_description = GTK_WIDGET (gtk_builder_get_object(builder_task_create, "entry_task_description"));

    task_buffer_name = gtk_entry_get_buffer(GTK_ENTRY (entry_task_name));
    task_buffer_description = gtk_entry_get_buffer(GTK_ENTRY (entry_task_description));

    task_name = gtk_entry_buffer_get_text(task_buffer_name);
    task_description = gtk_entry_buffer_get_text(task_buffer_description);

    task->set_name(task_name);
    task->set_description(task_description);

    gtk_widget_hide(window);
}

static void task_delete(GtkButton *btn, gpointer user_data)
{
    int index = GPOINTER_TO_INT(user_data);
    Task *current;
    Task *next;

    current = &all_tasks[index];
    current->remove();

    for ( int i = index; i < all_tasks.size()-1; ++i)
    {
        next = &all_tasks[i+1];

        next->set_index(i);
        next->update();

        all_tasks[i] = *next;
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