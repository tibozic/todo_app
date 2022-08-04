#ifndef MAIN_H
#define MAIN_H

#include <vector>
#include <fstream>
#include <gtk/gtk.h>

#define ICON_TASK_COMPLETE "object-select-symbolic"
#define ICON_TASK_UNCOMPLETE "edit-undo-symbolic"
#define ICON_TASK_EDIT "document-edit-symbolic"
#define ICON_TASK_DELETE "edit-delete-symbolic"

using std::string;
using std::vector;
using std::ofstream;
using std::ifstream;

class Task;

GtkBuilder *builder_task_create;
GtkWidget *box_uncompleted_tasks;
GtkWidget *box_completed_tasks;
vector<Task> all_tasks;
bool window_task_create_exists = false;

static void app_activate(GApplication *app,
                      gpointer user_data);

static void app_quit(GtkButton *btn,
                            gpointer user_data);

static void window_task_create(GtkButton *btn,
                            gpointer user_data);

static void window_task_create_quit(GtkButton *btn,
                            gpointer user_data);

static void task_create(GtkButton *btn,
                        gpointer user_data);

static void task_complete(GtkButton *btn,
                            gpointer user_data);

static void task_edit_open(GtkButton *btn,
                            gpointer user_data);

static void task_save(GtkButton *btn,
                        gpointer user_data);

static void task_delete(GtkButton *btn,
                        gpointer user_data);

void tasks_save();

void tasks_load();

vector<string> split(string in, char del);

#endif