#ifndef MAIN_H
#define MAIN_H

#include <vector>
#include <fstream>
#include <gtk/gtk.h>

using std::string;
using std::vector;
using std::ofstream;
using std::ifstream;

class Task;

GtkWidget *box_uncompleted_tasks;
GtkWidget *box_completed_tasks;
vector<Task> all_tasks;

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

void tasks_save();

void tasks_load();

vector<string> split(string in, char del);

#endif