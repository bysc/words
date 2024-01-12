#include "gtk_ui.h"
static void update_password_button (GObject *object,
                                    GParamSpec *pspec,
                                    gpointer    data)
{
    //读文本
    LOGING *p=(LOGING*)data;
    const char *text = gtk_editable_get_text (GTK_EDITABLE (p->password_entry1));
    const char *text2 = gtk_editable_get_text (GTK_EDITABLE (p->password_entry2));
    gtk_widget_set_sensitive (p->password_button,g_str_equal (text,"bysc")&&g_str_equal(text2,"20216234"));
//    gtk_widget_set_sensitive (p->password_button,text[0] != '\0' && g_str_equal (text, text2));
    //不为零且相等时按键可点击
}

static void password_button_pressed (GtkButton *widget,
                                     GtkWidget *window)
{
    gtk_window_destroy (GTK_WINDOW (window));
}

GtkWidget *
do_password_entry (GtkApplication* app,gpointer user_data)
{
    static LOGING loging;
    GtkWidget *box;
    GtkWidget *header;
/*
**window1_loging ui
*/
    static GtkWidget *window1 = NULL;
    window1 = gtk_application_window_new(app);
    header = gtk_header_bar_new ();
    gtk_header_bar_set_show_title_buttons (GTK_HEADER_BAR (header), FALSE);
    gtk_window_set_titlebar (GTK_WINDOW (window1), header);
    gtk_window_set_title (GTK_WINDOW (window1), "please log first");
    gtk_window_set_resizable (GTK_WINDOW (window1), FALSE);
    gtk_window_set_deletable (GTK_WINDOW (window1), FALSE);
    g_object_add_weak_pointer (G_OBJECT (window1), (gpointer *)&window1);
/*window1_box*/
    box = gtk_box_new (GTK_ORIENTATION_VERTICAL, 6);
    gtk_widget_set_margin_start (box, 18);
    gtk_widget_set_margin_end (box, 18);
    gtk_widget_set_margin_top (box, 18);
    gtk_widget_set_margin_bottom (box, 18);
    gtk_window_set_child (GTK_WINDOW (window1), box);
/*window1 two entry account and password*/
//        loging.password_entry1 = gtk_password_entry_new ();
    loging.password_entry1 = gtk_entry_new ();
//        gtk_password_entry_set_show_peek_icon (GTK_PASSWORD_ENTRY (loging.password_entry1), TRUE);
    g_object_set (loging.password_entry1,
                  "placeholder-text", "Account",
                  "activates-default", TRUE,
                  NULL);
    gtk_accessible_update_property (GTK_ACCESSIBLE (loging.password_entry1),
                                    GTK_ACCESSIBLE_PROPERTY_LABEL, "Account",
                                    -1);
    g_signal_connect (loging.password_entry1, "notify::text", G_CALLBACK (update_password_button), &loging);
    gtk_box_append (GTK_BOX (box), loging.password_entry1);

    loging.password_entry2 = gtk_password_entry_new ();
    gtk_password_entry_set_show_peek_icon (GTK_PASSWORD_ENTRY (loging.password_entry2), TRUE);
    g_object_set (loging.password_entry2,
                  "placeholder-text", "Confirm",
                  "activates-default", TRUE,
                  NULL);
    gtk_accessible_update_property (GTK_ACCESSIBLE (loging.password_entry2),
                                    GTK_ACCESSIBLE_PROPERTY_LABEL, "Confirm",
                                    -1);
    g_signal_connect (loging.password_entry2, "notify::text", G_CALLBACK (update_password_button), &loging);
    gtk_box_append (GTK_BOX (box), loging.password_entry2);

    loging.password_button = gtk_button_new_with_mnemonic ("_Done");
    gtk_widget_add_css_class (loging.password_button, "suggested-action");
    g_signal_connect (loging.password_button, "clicked", G_CALLBACK (password_button_pressed), window1);
    gtk_widget_set_sensitive (loging.password_button, FALSE);
    gtk_header_bar_pack_end (GTK_HEADER_BAR (header), loging.password_button);

    gtk_window_set_default_widget (GTK_WINDOW (window1), loging.password_button);

    if (!gtk_widget_get_visible (window1))
        gtk_widget_set_visible (window1, TRUE);
    else
        gtk_window_destroy (GTK_WINDOW (window1));
    return window1;
}
