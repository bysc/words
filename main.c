#include <stdio.h>
#include <stdlib.h>
#include "systemManage.h"
#include "gtk_ui.h"
/*登录初始账户密码为account和password*/
int main (int argc,char **argv)
{
    static TOPCON topcon;
    GtkApplication *app;
    int status;
    app = gtk_application_new ("org.gtk.example", G_APPLICATION_DEFAULT_FLAGS);
    g_signal_connect (app, "activate", G_CALLBACK (do_password_entry), &topcon);
    status = g_application_run (G_APPLICATION (app), argc, argv);
    g_object_unref (app);
    return status;
}


