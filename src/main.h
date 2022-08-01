#ifndef MAIN_H
#define MAIN_H

GtkWidget *box_uncompleted_tasks;
GtkWidget *box_completed_tasks;
class Task;

static void app_activate(GApplication *app,
                      gpointer user_data);

static void app_quit(GtkButton *btn,
                            gpointer user_data);

static void task_create(GtkButton *btn,
                            gpointer user_data);

static void task_complete(GtkButton *btn,
                            gpointer user_data);

#endif