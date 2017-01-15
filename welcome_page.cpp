//
// Created by divyank on 12/26/16.
//

#include "welcome_page.h"

using namespace boost::filesystem;
using namespace std;

static GtkWidget* _container;

GtkWidget* welcome_page::create_top_menu(GtkWidget *hbox) {
    GtkWidget *button1,*button2,*button3,*button4,*button5,*pad,*separator;
    button1=gtk_button_new_with_label("file");
    button2=gtk_button_new_with_label("edit");
    button3=gtk_button_new_with_label("view");
    button4=gtk_button_new_with_label("code");
    button5=gtk_button_new_with_label("help");
    pad=gtk_box_new(GTK_ORIENTATION_HORIZONTAL,0);
    gtk_widget_set_size_request(pad,1100,10);
    gtk_box_pack_end(GTK_BOX(hbox),pad,0,0,0);
    gtk_box_pack_end(GTK_BOX(hbox),button5,0,0,0);
    gtk_box_pack_end(GTK_BOX(hbox),button4,0,0,0);
    gtk_box_pack_end(GTK_BOX(hbox),button3,0,0,0);
    gtk_box_pack_end(GTK_BOX(hbox),button2,0,0,0);
    gtk_box_pack_end(GTK_BOX(hbox),button1,0,0,0);

    gtk_widget_set_size_request(hbox,800,20);
    return hbox;
}

static void populate_content(GtkWidget *wid,GdkEvent *event,gpointer data){

    GtkWidget *tmpLabel,*folders,*img,*vbox,*hbox;
    //tmpLabel=gtk_label_new("change ho gaya");
    GList *children, *iter;

    img=gtk_image_new_from_file("/home/divyank/Desktop/fol.png");

    children = gtk_container_get_children(GTK_CONTAINER(_container));
    for(iter = children; iter != NULL; iter = g_list_next(iter))
        gtk_widget_destroy(GTK_WIDGET(iter->data));
    g_list_free(children);
    children = gtk_container_get_children(GTK_CONTAINER(wid));
    path p=((welcome_page::Data*)data)->label;
    int count=0;
    hbox=gtk_box_new(GTK_ORIENTATION_HORIZONTAL,0);
    for(auto& entry: boost::make_iterator_range(directory_iterator(p))){
        if(is_directory(entry.path())) {
            folders = gtk_button_new(/*entry.path().c_str()*/);
            vbox=gtk_box_new(GTK_ORIENTATION_VERTICAL,0);
            img=gtk_image_new_from_file("/home/divyank/Desktop/utils/fol.png");
            string str(entry.path().c_str());
            str=str.substr(str.find_last_of("/")+1);
            tmpLabel=gtk_label_new(str.c_str());
            gtk_box_pack_start(GTK_BOX(vbox),img,0,0,0);
            gtk_box_pack_start(GTK_BOX(vbox),tmpLabel,0,0,0);
            gtk_button_set_relief(GTK_BUTTON(folders),GTK_RELIEF_NONE);
            gtk_container_add(GTK_CONTAINER(folders),vbox);
            gtk_label_set_line_wrap(GTK_LABEL(tmpLabel),1);
            welcome_page::Data *d=new welcome_page::Data();
            d->label=entry.path().c_str();

            //gtk_button_set_image(GTK_BUTTON(folders),img);
            gtk_widget_set_size_request(folders,0,0);
            //gtk_button_set_image_position(GTK_BUTTON(folders),GTK_POS_LEFT);
            g_signal_connect(folders, "clicked", G_CALLBACK(populate_content),(gpointer)d);
            gtk_box_pack_start(GTK_BOX(hbox), folders, 0, 0, 0);
        }else{
            vbox=gtk_box_new(GTK_ORIENTATION_VERTICAL,0);
            img=gtk_image_new_from_file("/home/divyank/Desktop/utils/file.svg");
            string str(entry.path().c_str());
            str=str.substr(str.find_last_of("/")+1);
            tmpLabel=gtk_label_new(str.c_str());
            gtk_label_set_line_wrap(GTK_LABEL(tmpLabel),1);
            gtk_box_pack_start(GTK_BOX(vbox),img,0,0,0);
            gtk_box_pack_start(GTK_BOX(vbox),tmpLabel,0,0,0);
            gtk_box_pack_start(GTK_BOX(hbox),vbox,0,0,0);
        }
        count++;
        if(count==5){
            count=0;
            gtk_box_pack_start(GTK_BOX(_container),hbox,0,0,0);
            hbox=gtk_box_new(GTK_ORIENTATION_HORIZONTAL,0);
        }
    }
    if(count!=0)
        gtk_box_pack_start(GTK_BOX(_container),hbox,0,0,0);
    cout << "data received is " << ((welcome_page::Data*)data)->label << endl;
    g_list_free(children);
    gtk_widget_show_all(_container);

}

GtkWidget* welcome_page::create_side_menu(GtkWidget *vbox,string file_path="/") {
        GtkWidget *wid;
        boost::filesystem::path path = file_path;
        if (is_directory(path)) {
            for (auto &entry:boost::make_iterator_range(directory_iterator(path))) {
                if (is_directory(entry.path())) {
                    wid = gtk_button_new_with_label(entry.path().string().c_str());
                    gtk_box_pack_end(GTK_BOX(vbox), wid, 0, 0, 0);

                    Data *d = new Data();
                    d->label = entry.path().c_str();
                    g_signal_connect(wid, "clicked", G_CALLBACK(populate_content), (gpointer) d);
                } else {
                    wid = gtk_label_new(entry.path().string().c_str());
                    gtk_box_pack_end(GTK_BOX(vbox), wid, 0, 0, 0);
                }
            }
        }
        gtk_widget_set_size_request(vbox, 150, 100);

    return vbox;
}

GtkWidget* welcome_page::create_main_container(GtkWidget *hbox) {
    GtkWidget *tmpLabel;
    tmpLabel=gtk_label_new("main container");
    gtk_box_pack_end(GTK_BOX(hbox),tmpLabel,0,0,0);
    gtk_widget_set_size_request(hbox,800,800);
    return hbox;
}

GtkWidget* welcome_page::create_home(GtkWidget *window) {
    GtkWidget *scroll,*sidemenu,*topmenu,*vbox,*hbox,*separator;
    topmenu=gtk_box_new(GTK_ORIENTATION_HORIZONTAL,0);
    create_top_menu(topmenu);
    vbox=gtk_box_new(GTK_ORIENTATION_VERTICAL,0);
    sidemenu=gtk_box_new(GTK_ORIENTATION_VERTICAL,0);
    create_side_menu(sidemenu);
    _container=gtk_box_new(GTK_ORIENTATION_VERTICAL,0);
    create_main_container(_container);
    hbox=gtk_box_new(GTK_ORIENTATION_HORIZONTAL,0);
    scroll=gtk_scrolled_window_new(NULL,NULL);
    gtk_scrolled_window_set_policy(GTK_SCROLLED_WINDOW(scroll),GTK_POLICY_AUTOMATIC,GTK_POLICY_ALWAYS);

    gtk_container_add(GTK_CONTAINER(scroll),_container);

    gtk_widget_set_size_request(scroll,1200,800);

    separator=gtk_separator_new(GTK_ORIENTATION_VERTICAL);

    gtk_box_pack_end(GTK_BOX(hbox),scroll,0,0,0);
    gtk_box_pack_end(GTK_BOX(hbox),separator,0,0,0);
    gtk_box_pack_end(GTK_BOX(hbox),sidemenu,0,0,0);
    gtk_box_pack_end(GTK_BOX(vbox),hbox,0,0,0);
    gtk_box_pack_end(GTK_BOX(vbox),topmenu,0,0,0);
    gtk_container_add(GTK_CONTAINER(window),vbox);
    return window;
}

GtkWidget* welcome_page::get_container() {
    return _container;
}