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

static void print_hello (GtkWidget *widget,gpointer   data);

//更新菜单按键状态
static void update_menu_buttopn(GObject *object,GParamSpec *pspec,gpointer data);
/*
**重置部分按键的不可按下状态
*/
void menu_Button_Init_Sensitive();
static void menu_AddWord(GtkWidget *widget,gpointer data);
static void menu_DelWord(GtkWidget *widget,gpointer data);
static void menu_AddPhrase(GtkWidget *widget,gpointer data);
static void menu_DelPhrase(GtkWidget *widget,gpointer data);

static void menu_ShowWords(GtkWidget *widget,gpointer data);
static void menu_ShowPhrases(GtkWidget *widget,gpointer data);
static void menu_SearchWord(GtkWidget *widget,gpointer data);
static void menu_SortWord(GtkWidget *widget,gpointer data);

static void menu_Quit(GtkWidget *widget,gpointer data);
#endif // GTK_UI_H_INCLUDED
