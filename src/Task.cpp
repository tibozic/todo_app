#include <string>
#include "main.h"

class Task {
    public: 
        Task();

        int get_index(void);
        string get_name(void);
        string get_description(void);
        GtkWidget * get_task(void);
        bool get_is_completed(void);

        void switch_completeness(void);

    private:
        int index;
        GtkWidget *box_task;
        string name;
        string description;
        bool is_completed;

};

Task::Task()
{
    GtkWidget *btn_mark_completed;
    GtkWidget *task_name;

    index = all_tasks.size();
    name = "Task" + std::to_string(index);
    description = "Task description";
    is_completed = false;

    box_task = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 5);

    btn_mark_completed = gtk_button_new_with_label("[ ]");
    g_signal_connect(btn_mark_completed, "clicked", G_CALLBACK (task_complete), GINT_TO_POINTER (index));
    gtk_box_append(GTK_BOX (box_task), btn_mark_completed);

    task_name = gtk_label_new(name.c_str());

    gtk_box_append(GTK_BOX (box_task), task_name);

    gtk_box_append(GTK_BOX (box_uncompleted_tasks), box_task);

    all_tasks.push_back(*this);
}

int Task::get_index(void)
{
    return index;
}

string Task::get_name(void)
{
    return name;
}

string Task::get_description(void)
{
    return description;
}

GtkWidget * Task::get_task(void)
{
    return box_task;
}

bool Task::get_is_completed(void)
{
    return is_completed;
}

void Task::switch_completeness()
{
    g_print("Checking in which direction to switch.\n");
    std::cout << "Current: " << get_is_completed() << "\n";
    std::cout << "Thingy: " << get_name() << "\n";
    if ( is_completed )
    {
        g_print("Removing from completed tasks.\n");
        gtk_box_remove(GTK_BOX (box_completed_tasks), box_task);
        g_print("Appending to uncompleted tasks.\n");
        gtk_box_append(GTK_BOX (box_uncompleted_tasks), box_task);
    }
    else 
    {
        g_print("Removing from uncompleted tasks.\n");
        gtk_box_remove(GTK_BOX (box_uncompleted_tasks), box_task);
        g_print("Appending to completed tasks.\n");
        gtk_box_append(GTK_BOX (box_completed_tasks), box_task);
    }

    is_completed = !is_completed;
    g_print("Task successfully switched.\n");
}