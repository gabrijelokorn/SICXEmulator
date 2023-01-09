#include <iostream>
#include <string>
#include <cstring>
#include <gtk/gtk.h>

using std::cin;
using std::cout;
using std::endl;

using namespace std;

static void on_button_step_clicked (GtkWidget* widget, gpointer window) {
    cout << "clicked\n";
}

static void menu_response(GtkWidget* menu_item, gpointer window)
{
    if(strcmp(gtk_menu_item_get_label(GTK_MENU_ITEM(menu_item)), "New") == 0)
    {
        GtkWidget *dialog;
        dialog = gtk_file_chooser_dialog_new("Choose a file", GTK_WINDOW(window), GTK_FILE_CHOOSER_ACTION_OPEN, GTK_STOCK_OK, GTK_RESPONSE_OK, GTK_STOCK_CANCEL, GTK_RESPONSE_CANCEL, NULL);
        gtk_widget_show_all(dialog);

        gint resp = GTK_RESPONSE_OK;
        if (resp == GTK_RESPONSE_OK) {
            g_print("%s\n", gtk_file_chooser_get_filename(GTK_FILE_CHOOSER(dialog)));
        } else {

        }
    }
    if(strcmp(gtk_menu_item_get_label(GTK_MENU_ITEM(menu_item)), "Speed") == 0)
    {
        g_print("You pressed Speed\n");
    }
}

int main(int argc, char **argv)
{

    gtk_init(&argc, &argv);

    GtkWidget *window;
    window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    g_signal_connect(window, "delete-event", G_CALLBACK(gtk_main_quit), NULL);

    GtkWidget *menu_bar, *menu_item, *file_menu, *settings_menu, *menu_vbox, *test_button;

    menu_bar = gtk_menu_bar_new();
    
    file_menu = gtk_menu_new();
    settings_menu = gtk_menu_new();

    menu_item = gtk_menu_item_new_with_label("File");
    gtk_menu_item_set_submenu(GTK_MENU_ITEM(menu_item), file_menu);
    gtk_menu_shell_append(GTK_MENU_SHELL(menu_bar), menu_item);

    menu_item = gtk_menu_item_new_with_label("Settings");
    gtk_menu_item_set_submenu(GTK_MENU_ITEM(menu_item), settings_menu);
    gtk_menu_shell_append(GTK_MENU_SHELL(menu_bar), menu_item);

    menu_item = gtk_menu_item_new_with_label("New");
    gtk_menu_shell_append(GTK_MENU_SHELL(file_menu), menu_item);
    g_signal_connect(menu_item, "activate", G_CALLBACK(menu_response), NULL);

    menu_item = gtk_menu_item_new_with_label("Speed");
    gtk_menu_shell_append(GTK_MENU_SHELL(settings_menu), menu_item);
    g_signal_connect(menu_item, "activate", G_CALLBACK(menu_response), NULL);

    menu_vbox = gtk_vbox_new(0, 0);
    test_button = gtk_button_new_with_label("hello");

    gtk_box_pack_start(GTK_BOX(menu_vbox), menu_bar, 0, 0, 0);
    gtk_box_pack_start(GTK_BOX(menu_vbox), test_button, 0, 0, 0);

    gtk_container_add(GTK_CONTAINER(window), menu_vbox);

    gtk_widget_set_size_request(window, 720, 480);
    gtk_window_set_title(GTK_WINDOW(window), "SicXEmulator");
    gtk_widget_show_all(window);

    gtk_main();

    return 0;
}