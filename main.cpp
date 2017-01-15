#include "welcome_page.h"

int main(int argc,char** argv) {
    std::cout << "Hello, World!" << std::endl;
    gtk_init(&argc,&argv);

    GtkWidget *window,*label,*hbox,*button;

    window=gtk_window_new(GTK_WINDOW_TOPLEVEL);



    label=gtk_label_new("this is the new shit");

    button=gtk_button_new_with_label("press me!!");

    hbox=gtk_box_new(GTK_ORIENTATION_HORIZONTAL,0);

    //gtk_widget_set_size_request(window,1000,1000);

    //gtk_box_pack_end(GTK_BOX(hbox),button,0,0,0);
    //gtk_box_pack_end(GTK_BOX(hbox),label,0,0,0);

    g_signal_connect(window,"delete-event",G_CALLBACK(gtk_main_quit),NULL);

    //gtk_container_add(GTK_CONTAINER(window),hbox);
    welcome_page page;
    page.create_home(window);
    gtk_widget_show_all(window);

    gtk_main();
    return 0;
}