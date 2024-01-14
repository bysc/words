#include "gtk_ui.h"
/*
**menu窗口构件变量——第二窗口
*/
static GtkWidget *menu_window = NULL;
static GtkWidget *menu_grid;
static GtkWidget *menu_button_addword;
static GtkWidget *menu_button_delword;
static GtkWidget *menu_button_addphrase;
static GtkWidget *menu_button_delphrase;
static GtkWidget *menu_button_showwords;
static GtkWidget *menu_button_showphrases;
static GtkWidget *menu_button_search;
static GtkWidget *menu_button_sort;
static GtkWidget *menu_button_quit;
static GtkWidget *menu_entry_spell;
static GtkWidget *menu_entry_item;
static GtkWidget *menu_entry_part;
static GtkWidget *menu_entry_meaning;
static GtkWidget *menu_show_view;
static GtkWidget *menu_show_sw;
static GtkTextBuffer *menu_show_buffer;
static PangoTabArray *menu_show_tabs;
//=====================================================
//=====================================================
void menu_Button_Init_Sensitive()
{
    gtk_widget_set_sensitive (menu_button_addword,FALSE);
    gtk_widget_set_sensitive (menu_button_delword,FALSE);
    gtk_widget_set_sensitive (menu_button_addphrase,FALSE);
    gtk_widget_set_sensitive (menu_button_delphrase,FALSE);
//    gtk_widget_set_sensitive (menu_button_showwords,FALSE);
//    gtk_widget_set_sensitive (menu_button_showphrases,FALSE);
    gtk_widget_set_sensitive (menu_button_search,FALSE);
//    gtk_widget_set_sensitive (menu_button_sort,FALSE);
}
static void
print_hello (GtkWidget *widget,
             gpointer   data)
{
    g_print ("Hello World\n");
}

static void update_password_button (GObject *object,
                                    GParamSpec *pspec,
                                    gpointer    data)
{
    //读文本
    LOGING *p=(LOGING*)data;
    const char *text = gtk_editable_get_text (GTK_EDITABLE (p->password_entry1));
    const char *text2 = gtk_editable_get_text (GTK_EDITABLE (p->password_entry2));
    gtk_widget_set_sensitive (p->password_button,g_str_equal (text,"account")&&g_str_equal(text2,"password"));
//    gtk_widget_set_sensitive (p->password_button,text[0] != '\0' && g_str_equal (text, text2));
    //不为零且相等时按键可点击
}
static void menu_AddWord(GtkWidget *widget,gpointer data)
{
    TOPCON *topcon=(TOPCON*)data;
    sys_AddWord(topcon);
    gtk_text_buffer_set_text (menu_show_buffer,"Add successfully!", -1);
    menu_Button_Init_Sensitive();
}
static void menu_DelWord(GtkWidget *widget,gpointer data)
{
    TOPCON *topcon=(TOPCON*)data;
    sys_DelWord(topcon);
    gtk_text_buffer_set_text (menu_show_buffer,"Delete successfully!", -1);
    menu_Button_Init_Sensitive();
}
static void menu_AddPhrase(GtkWidget *widget,gpointer data)
{
    TOPCON *topcon=(TOPCON*)data;
    sys_AddPhrase(topcon);
    gtk_text_buffer_set_text (menu_show_buffer,"Add successfully!", -1);
    menu_Button_Init_Sensitive();
}
static void menu_DelPhrase(GtkWidget *widget,gpointer data)
{
    TOPCON *topcon=(TOPCON*)data;
    sys_DelPhrase(topcon);
    gtk_text_buffer_set_text (menu_show_buffer,"Delete successfully!", -1);
    menu_Button_Init_Sensitive();
}

static void menu_ShowWords(GtkWidget *widget,gpointer data)
{
    TOPCON *topcon=(TOPCON*)data;
    words_Show(topcon->words);
    char *tmp=sys_ShowWords(topcon);
    gtk_text_buffer_set_text (menu_show_buffer, tmp, -1);
    free(tmp);
    menu_Button_Init_Sensitive();
}
static void menu_ShowPhrases(GtkWidget *widget,gpointer data)
{
    TOPCON *topcon=(TOPCON*)data;
    phrases_Show(topcon->phrases);
    char *tmp=sys_ShowPhrases(topcon);
    gtk_text_buffer_set_text (menu_show_buffer, tmp, -1);
    free(tmp);
    menu_Button_Init_Sensitive();
}
static void menu_SearchWord(GtkWidget *widget,gpointer data)
{
    TOPCON *topcon=(TOPCON*)data;
    char *tmp=sys_SearchWord(topcon);
    gtk_text_buffer_set_text (menu_show_buffer, tmp, -1);
    free(tmp);
    menu_Button_Init_Sensitive();
}
static void menu_SortWord(GtkWidget *widget,gpointer data)
{
    TOPCON *topcon=(TOPCON*)data;
    char *tmp=sys_SortWord(topcon);
    gtk_text_buffer_set_text (menu_show_buffer, tmp, -1);
    free(tmp);
    menu_Button_Init_Sensitive();
}

static void menu_Quit(GtkWidget *widget,gpointer data)
{
    TOPCON *topcon=(TOPCON*)data;
    sys_Save(topcon);
    if (!gtk_widget_get_visible (menu_window))
        gtk_widget_set_visible (menu_window, TRUE);
    else
        gtk_window_destroy (GTK_WINDOW (menu_window));
//销毁窗口退出
}
/*====================================================================
**====================================================================
*/
static void update_menu_buttopn(GObject *object,GParamSpec *pspec,gpointer data)
{
    TOPCON *tc=(TOPCON*)data;
    const char *spell=gtk_editable_get_text(GTK_EDITABLE(menu_entry_spell));
    const char *part=gtk_editable_get_text(GTK_EDITABLE(menu_entry_part));
    const char *item=gtk_editable_get_text(GTK_EDITABLE(menu_entry_item));
    const char *meaning=gtk_editable_get_text(GTK_EDITABLE(menu_entry_meaning));

    strcpy(tc->spell,spell);
    strcpy(tc->item,item);
    strcpy(tc->meaning,meaning);
    if(strcmp(part,"noun")==0) tc->part=NOUN;
    else if(strcmp(part,"adj")==0) tc->part=ADJ;
    else if(strcmp(part,"adv")==0) tc->part=ADV;
    else if(strcmp(part,"verb")==0) tc->part=VERB;
    else if(strcmp(part,"conj")==0) tc->part=CONJ;
    else if(strcmp(part,"num")==0) tc->part=NUM;
    else if(strcmp(part,"prep")==0) tc->part=PREP;
    else if(strcmp(part,"art")==0) tc->part=ART;
    else if(strcmp(part,"interj")==0) tc->part=INTERJ;
    else if(strcmp(part,"pron")==0) tc->part=PRON;
    else tc->part=0;

    gtk_widget_set_sensitive (menu_button_addword,
                              spell[0]&&tc->part&&meaning[0]&&(BSI_Search(tc->root,spell)==NULL));
    gtk_widget_set_sensitive (menu_button_delword,spell[0]&&(BSI_Search(tc->root,spell)!=NULL));
    gtk_widget_set_sensitive (menu_button_addphrase,spell[0]&&(BSI_Search(tc->root,spell)!=NULL));
    gtk_widget_set_sensitive (menu_button_delphrase,
                              spell[0]&&(BSI_Search(tc->root,spell)!=NULL));
//    gtk_widget_set_sensitive (menu_button_showwords,TRUE);
//    gtk_widget_set_sensitive (menu_button_showphrases,TRUE);
    gtk_widget_set_sensitive (menu_button_search,spell[0]&&(BSI_Search(tc->root,spell)!=NULL));
//    gtk_widget_set_sensitive (menu_button_sort,TRUE);
}
static void password_button_pressed (GtkButton *widget,
                                     GtkWidget *window)
{
    gtk_window_destroy (GTK_WINDOW (window));
    if (!gtk_widget_get_visible (menu_window))
        gtk_widget_set_visible (menu_window, TRUE);
    else
        gtk_window_destroy (GTK_WINDOW (menu_window));
}

GtkWidget *
do_password_entry (GtkApplication* app,gpointer user_data)
{
    TOPCON *topcon=(TOPCON*)user_data;//取参数
    sys_Init(topcon);

////*******************************/\*****************************************
////*******************************||*******************************************
//


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
    /**/

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

    gtk_widget_hide(menu_window);
    if (!gtk_widget_get_visible (window1))
        gtk_widget_set_visible (window1, TRUE);
    else
        gtk_window_destroy (GTK_WINDOW (window1));













    /*====================================================================
    ======================window 2======================================
    =====================================================================*/
    menu_window = gtk_application_window_new(app);
    gtk_window_set_title (GTK_WINDOW (menu_window), "MENU");
    gtk_window_set_default_size (GTK_WINDOW (menu_window),1500, 1500);
    /*grid*/
    menu_grid = gtk_grid_new ();

    gtk_grid_set_column_spacing(GTK_GRID(menu_grid), 10); // 设置列间距
    gtk_grid_set_row_spacing(GTK_GRID(menu_grid), 10); // 设置行间距
    gtk_grid_set_row_homogeneous(GTK_GRID(menu_grid), TRUE);
    gtk_grid_set_column_homogeneous(GTK_GRID(menu_grid), TRUE);

    gtk_window_set_child (GTK_WINDOW (menu_window), menu_grid);
    /*button*/
    menu_button_addword = gtk_button_new_with_label ("ADD words");
    g_signal_connect (menu_button_addword, "clicked", G_CALLBACK (menu_AddWord), topcon);
    gtk_widget_set_sensitive (menu_button_addword, FALSE);

    /* Place the first button in the grid cell (0, 0), and make it fill
     * just 1 cell horizontally and vertically (ie no spanning)
     */
    gtk_grid_attach (GTK_GRID (menu_grid), menu_button_addword, 0, 0, 2, 1);

    menu_button_delword = gtk_button_new_with_label ("DEL words");
    g_signal_connect (menu_button_delword, "clicked", G_CALLBACK (menu_DelWord), topcon);
    gtk_widget_set_sensitive (menu_button_delword, FALSE);
    /* Place the first button in the grid cell (0, 0), and make it fill
     * just 1 cell horizontally and vertically (ie no spanning)
     */
    gtk_grid_attach (GTK_GRID (menu_grid), menu_button_delword, 0, 1, 2, 1);

    menu_button_addphrase = gtk_button_new_with_label ("ADD phrases");
    g_signal_connect (menu_button_addphrase, "clicked", G_CALLBACK (menu_AddPhrase), topcon);
    gtk_widget_set_sensitive (menu_button_addphrase, FALSE);

    /* Place the first button in the grid cell (0, 0), and make it fill
     * just 1 cell horizontally and vertically (ie no spanning)
     */
    gtk_grid_attach (GTK_GRID (menu_grid), menu_button_addphrase, 0, 2, 2, 1);

    menu_button_delphrase = gtk_button_new_with_label ("DEL phrases");
    g_signal_connect (menu_button_delphrase, "clicked", G_CALLBACK (menu_DelPhrase), topcon);
    gtk_widget_set_sensitive (menu_button_delphrase, FALSE);

    /* Place the first button in the grid cell (0, 0), and make it fill
     * just 1 cell horizontally and vertically (ie no spanning)
     */
    gtk_grid_attach (GTK_GRID (menu_grid), menu_button_delphrase, 0, 3, 2, 1);

    menu_button_showwords = gtk_button_new_with_label ("SHOW words");
    g_signal_connect (menu_button_showwords, "clicked", G_CALLBACK (menu_ShowWords), topcon);
    gtk_widget_set_sensitive (menu_button_showwords, TRUE);

    /* Place the first button in the grid cell (0, 0), and make it fill
     * just 1 cell horizontally and vertically (ie no spanning)
     */
    gtk_grid_attach (GTK_GRID (menu_grid), menu_button_showwords, 0, 4, 2, 1);

    menu_button_showphrases = gtk_button_new_with_label ("SHOW phrases");
    g_signal_connect (menu_button_showphrases, "clicked", G_CALLBACK (menu_ShowPhrases), topcon);
    gtk_widget_set_sensitive (menu_button_showphrases, TRUE);

    /* Place the first button in the grid cell (0, 0), and make it fill
     * just 1 cell horizontally and vertically (ie no spanning)
     */
    gtk_grid_attach (GTK_GRID (menu_grid), menu_button_showphrases, 0, 5, 2, 1);

    menu_button_search = gtk_button_new_with_label ("SEARCH word");
    g_signal_connect (menu_button_search, "clicked", G_CALLBACK (menu_SearchWord), topcon);
    gtk_widget_set_sensitive (menu_button_search, FALSE);

    /* Place the first button in the grid cell (0, 0), and make it fill
     * just 1 cell horizontally and vertically (ie no spanning)
     */
    gtk_grid_attach (GTK_GRID (menu_grid), menu_button_search, 0, 6, 2, 1);

    menu_button_sort = gtk_button_new_with_label ("SORT words");
    g_signal_connect (menu_button_sort, "clicked", G_CALLBACK (menu_SortWord), topcon);
    gtk_widget_set_sensitive (menu_button_sort, TRUE);

    /* Place the first button in the grid cell (0, 0), and make it fill
     * just 1 cell horizontally and vertically (ie no spanning)
     */
    gtk_grid_attach (GTK_GRID (menu_grid), menu_button_sort, 0, 7, 2, 1);


    menu_button_quit = gtk_button_new_with_label ("QUIT");
    g_signal_connect (menu_button_quit, "clicked", G_CALLBACK (menu_Quit), topcon);
//    gtk_widget_set_sensitive (menu_button_quit, FALSE);
    /*quit button 应该永远可见*/

    /* Place the first button in the grid cell (0, 0), and make it fill
     * just 1 cell horizontally and vertically (ie no spanning)
     */
    gtk_grid_attach (GTK_GRID (menu_grid), menu_button_quit, 0, 8, 2, 1);

    /*======================================================================*/
    menu_entry_spell = gtk_entry_new ();
    g_object_set (menu_entry_spell,
                  "placeholder-text", "spell",
                  "activates-default", TRUE,
                  NULL);
    gtk_accessible_update_property (GTK_ACCESSIBLE (menu_entry_spell),
                                    GTK_ACCESSIBLE_PROPERTY_LABEL, "spell",
                                    -1);
    g_signal_connect (menu_entry_spell, "notify::text", G_CALLBACK (update_menu_buttopn), topcon);
    gtk_grid_attach (GTK_GRID (menu_grid), menu_entry_spell, 0, 9, 2, 1);


//------------------------------------------------------------------------------------

    menu_entry_item = gtk_entry_new ();
    g_object_set (menu_entry_item,
                  "placeholder-text", "item",
                  "activates-default", TRUE,
                  NULL);
    gtk_accessible_update_property (GTK_ACCESSIBLE (menu_entry_item),
                                    GTK_ACCESSIBLE_PROPERTY_LABEL, "item",
                                    -1);
    g_signal_connect (menu_entry_item, "notify::text", G_CALLBACK (update_menu_buttopn), topcon);
    gtk_grid_attach (GTK_GRID (menu_grid), menu_entry_item, 0, 10, 2, 1);

//------------------------------------------------------------------------------------

    menu_entry_part = gtk_entry_new ();
    g_object_set (menu_entry_part,
                  "placeholder-text", "part",
                  "activates-default", TRUE,
                  NULL);
    gtk_accessible_update_property (GTK_ACCESSIBLE (menu_entry_part),
                                    GTK_ACCESSIBLE_PROPERTY_LABEL, "part",
                                    -1);
    g_signal_connect (menu_entry_part, "notify::text", G_CALLBACK (update_menu_buttopn), topcon);

    gtk_grid_attach (GTK_GRID (menu_grid), menu_entry_part, 0, 11, 2, 1);

//------------------------------------------------------------------------------------

    menu_entry_meaning = gtk_entry_new ();
    g_object_set (menu_entry_meaning,
                  "placeholder-text", "meaning",
                  "activates-default", TRUE,
                  NULL);
    gtk_accessible_update_property (GTK_ACCESSIBLE (menu_entry_meaning),
                                    GTK_ACCESSIBLE_PROPERTY_LABEL, "meaning",
                                    -1);
    g_signal_connect (menu_entry_meaning, "notify::text", G_CALLBACK (update_menu_buttopn), topcon);

    gtk_grid_attach (GTK_GRID (menu_grid), menu_entry_meaning, 0, 12, 2, 1);

    /*=====================================================================*/
    /*=====================================================================*/
    /*=====================================================================*/

    menu_show_view = gtk_text_view_new ();
    gtk_text_view_set_editable(GTK_TEXT_VIEW(menu_show_view), FALSE); // 设置文本不可修改
    gtk_text_view_set_wrap_mode (GTK_TEXT_VIEW (menu_show_view), GTK_WRAP_WORD);
    gtk_text_view_set_top_margin (GTK_TEXT_VIEW (menu_show_view), 20);
    gtk_text_view_set_bottom_margin (GTK_TEXT_VIEW (menu_show_view), 20);
    gtk_text_view_set_left_margin (GTK_TEXT_VIEW (menu_show_view), 20);
    gtk_text_view_set_right_margin (GTK_TEXT_VIEW (menu_show_view), 20);

    menu_show_tabs = pango_tab_array_new (3, TRUE);
    pango_tab_array_set_tab (menu_show_tabs, 0, PANGO_TAB_LEFT, 0);
    pango_tab_array_set_tab (menu_show_tabs, 1, PANGO_TAB_DECIMAL, 150);
    pango_tab_array_set_decimal_point (menu_show_tabs, 1, '.');
    pango_tab_array_set_tab (menu_show_tabs, 2, PANGO_TAB_RIGHT, 290);
    gtk_text_view_set_tabs (GTK_TEXT_VIEW (menu_show_view), menu_show_tabs);
    pango_tab_array_free (menu_show_tabs);

    menu_show_buffer = gtk_text_view_get_buffer (GTK_TEXT_VIEW (menu_show_view));
    gtk_text_buffer_set_text (menu_show_buffer, "spell\tpart\tmeaning\n", -1);

//    gtk_text_buffer_set_text (menu_show_buffer, "one\t2.0\tthree\nfour\t5.555\tsix\nseven\t88.88\tnine\nab\t5.6\tha\n", -1);

    menu_show_sw = gtk_scrolled_window_new ();
    gtk_scrolled_window_set_policy (GTK_SCROLLED_WINDOW (menu_show_sw),
                                    GTK_POLICY_NEVER,
                                    GTK_POLICY_AUTOMATIC);
//    gtk_window_set_child (GTK_WINDOW (menu_window), menu_show_sw);
    gtk_grid_attach (GTK_GRID (menu_grid), menu_show_sw, 4, 0, 10, 10);
    gtk_scrolled_window_set_child (GTK_SCROLLED_WINDOW (menu_show_sw), menu_show_view);


    /*=====================================================================*/
    /*=====================================================================*/
    /*=====================================================================*/

//    if (!gtk_widget_get_visible (menu_window))
//        gtk_widget_set_visible (menu_window, TRUE);
//    else
//        gtk_window_destroy (GTK_WINDOW (menu_window));

    return menu_window;
    /*=================================================*/

}
