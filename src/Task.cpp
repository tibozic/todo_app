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

        void set_index(int task_index);
        void set_name(string task_name);
        void set_description(string task_description);
        void set_is_completed(bool status);

        void update(void);
        void remove(void);
        void switch_completeness(void);
        void save_to_file(ofstream *file);
        static void load_from_file(string line);

    private:
        GtkWidget *box_task;
        GtkWidget *btn_mark_completed;
        GtkWidget *btn_task_edit;
        GtkWidget *btn_task_delete;
        GtkWidget *lbl_task_name;

        int index;
        string name;
        string description;
        bool is_completed;

        int btn_task_mark_completed_id;
        int btn_task_edit_id;
        int btn_task_delete_id;
};

Task::Task(string task_name="",
            string task_description="",
            bool task_is_completed=false)
{
    GtkWidget *box_control_btns;

    box_control_btns = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 5);
    gtk_box_set_homogeneous(GTK_BOX (box_control_btns), true);

    box_task = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 5);
    gtk_box_set_homogeneous(GTK_BOX (box_task), true);

    index = all_tasks.size();

    name = task_name;
    description = task_description;
    is_completed = task_is_completed;

    btn_task_edit = gtk_button_new_from_icon_name(ICON_TASK_EDIT);
    btn_task_edit_id = g_signal_connect(btn_task_edit,
                                                "clicked",
                                                G_CALLBACK (task_edit_open),
                                                GINT_TO_POINTER(index));

    btn_task_delete = gtk_button_new_from_icon_name(ICON_TASK_DELETE);
    btn_task_delete_id = g_signal_connect(btn_task_delete,
                                            "clicked",
                                            G_CALLBACK (task_delete),
                                            GINT_TO_POINTER(index));


    if ( task_name == "" )
    {
        name = "Task" + std::to_string(index);
    }

    if ( task_description == "" )
    {
        description = "Task description";
    }

    if ( is_completed )
    {
        btn_mark_completed = gtk_button_new_from_icon_name(ICON_TASK_UNCOMPLETE);
    }
    else
    {
        btn_mark_completed = gtk_button_new_from_icon_name(ICON_TASK_COMPLETE);
    }

    btn_task_mark_completed_id = g_signal_connect(btn_mark_completed,
                                                    "clicked",
                                                    G_CALLBACK (task_complete),
                                                    GINT_TO_POINTER (index));

    gtk_box_append(GTK_BOX (box_control_btns), btn_task_edit);
    gtk_box_append(GTK_BOX (box_control_btns), btn_task_delete);

    lbl_task_name = gtk_label_new(name.c_str());

    gtk_box_append(GTK_BOX (box_task), btn_mark_completed);
    gtk_box_append(GTK_BOX (box_task), lbl_task_name);
    gtk_box_append(GTK_BOX (box_task), box_control_btns);

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

void Task::set_index(int task_index)
{
    index = task_index;
    this->update();
}

void Task::set_name(string task_name)
{
    name = task_name;
    gtk_label_set_label(GTK_LABEL (lbl_task_name), name.c_str());
}

void Task::set_description(string task_description)
{
    description = task_description;
}

void Task::set_is_completed(bool status)
{
    std::cout << "Completing task with index: " << index << std::endl;
    is_completed = status;

    if ( status )
    {
        gtk_box_remove(GTK_BOX (box_uncompleted_tasks), box_task);
        gtk_box_append(GTK_BOX (box_completed_tasks), box_task);

        // gtk_button_set_label(GTK_BUTTON (btn_mark_completed), "[ ]");
        gtk_button_set_icon_name(GTK_BUTTON (btn_mark_completed), ICON_TASK_UNCOMPLETE);
    }
    else
    {
        gtk_box_remove(GTK_BOX (box_completed_tasks), box_task);
        gtk_box_append(GTK_BOX (box_uncompleted_tasks), box_task);

        // gtk_button_set_label(GTK_BUTTON (btn_mark_completed), "[X]");
        gtk_button_set_icon_name(GTK_BUTTON (btn_mark_completed), ICON_TASK_COMPLETE);
    }
}

void Task::remove(void)
{
    if (is_completed)
    {
        gtk_box_remove(GTK_BOX (box_completed_tasks), box_task);
    }
    else
    {
        gtk_box_remove(GTK_BOX (box_uncompleted_tasks), box_task);
    }
}

void Task::update(void)
{
    // All buttons send index via user data, this index has to be updated

    g_signal_handler_disconnect(btn_mark_completed, btn_task_mark_completed_id);
    g_signal_handler_disconnect(btn_task_edit, btn_task_edit_id);
    g_signal_handler_disconnect(btn_task_delete, btn_task_delete_id);

    btn_task_mark_completed_id = g_signal_connect(btn_mark_completed,
                                                    "clicked",
                                                    G_CALLBACK (task_complete),
                                                    GINT_TO_POINTER (index));

    btn_task_edit_id = g_signal_connect(btn_task_edit,
                                                "clicked",
                                                G_CALLBACK (task_edit_open),
                                                GINT_TO_POINTER(index));

    btn_task_delete_id = g_signal_connect(btn_task_delete,
                                            "clicked",
                                            G_CALLBACK (task_delete),
                                            GINT_TO_POINTER(index));
}

void Task::save_to_file(ofstream *file)
{
    (*file) << name << ";" << description << ";" << is_completed << "\n";
}

void Task::load_from_file(string line)
{
    int index = all_tasks.size();
    string task_name;
    string task_description;
    bool task_is_completed;

    task_name = split(line, ';')[0];
    task_description = split(line, ';')[1];
    task_is_completed = atoi(split(line, ';')[2].c_str());

    Task new_task(task_name, task_description, task_is_completed);

    all_tasks.push_back(new_task);
}