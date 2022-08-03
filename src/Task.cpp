#include <string>
#include "main.h"

class Task {
    public: 
        Task(string task_name,
                string task_description,
                bool task_is_complete);

        int get_index(void);
        string get_name(void);
        string get_description(void);
        GtkWidget * get_task(void);
        bool get_is_completed(void);

        void switch_completeness(void);
        void save_to_file(ofstream *file);

    private:
        int index;
        GtkWidget *box_task;
        GtkWidget *btn_mark_completed;
        string name;
        string description;
        bool is_completed;

};

Task::Task(string task_name="",
            string task_description="",
            bool task_is_completed=false)
{
    GtkWidget *lbl_task_name;

    index = all_tasks.size();

    name = task_name;
    description = task_description;
    is_completed = task_is_completed;

    if ( task_name == "" )
    {
        name = "Task" + std::to_string(index);
    }

    if ( task_description == "" )
    {
        description = "Task description";
    }

    box_task = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 5);

    if ( is_completed )
    {
        btn_mark_completed = gtk_button_new_with_label("[ ]");
    }
    else
    {
        btn_mark_completed = gtk_button_new_with_label("[X]");
    }

    g_signal_connect(btn_mark_completed, "clicked", G_CALLBACK (task_complete), GINT_TO_POINTER (index));
    gtk_box_append(GTK_BOX (box_task), btn_mark_completed);

    lbl_task_name = gtk_label_new(name.c_str());

    gtk_box_append(GTK_BOX (box_task), lbl_task_name);

    if ( is_completed )
    {
        gtk_box_append(GTK_BOX (box_completed_tasks), box_task);
    }
    else 
    {
        gtk_box_append(GTK_BOX (box_uncompleted_tasks), box_task);
    }
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
    if ( is_completed )
    {
        gtk_box_remove(GTK_BOX (box_completed_tasks), box_task);
        gtk_box_append(GTK_BOX (box_uncompleted_tasks), box_task);
    }
    else 
    {
        gtk_box_remove(GTK_BOX (box_uncompleted_tasks), box_task);
        gtk_box_append(GTK_BOX (box_completed_tasks), box_task);
    }

    is_completed = !is_completed;
}

void Task::save_to_file(ofstream *file)
{
    (*file) << name << ";" << description << ";" << is_completed << "\n";
}