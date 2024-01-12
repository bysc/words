#ifndef GTK_UI_H_INCLUDED
#define GTK_UI_H_INCLUDED
#include "systemManage.h"
#include <gtk/gtk.h>
#include <glib/gi18n.h>
typedef struct
{
    GtkWidget *password_entry1;
    GtkWidget *password_entry2;
    GtkWidget *password_button;
}LOGING;
static void update_password_button (GObject    *object,
                                    GParamSpec *pspec,
                                    gpointer    data);
static void password_button_pressed (GtkButton *widget,
                                     GtkWidget *window);
GtkWidget *do_password_entry (GtkApplication* app,gpointer user_data);

#endif // GTK_UI_H_INCLUDED
