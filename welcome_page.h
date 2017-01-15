//
// Created by divyank on 12/26/16.
//

#ifndef GTKGUI_WELCOME_PAGE_H
#define GTKGUI_WELCOME_PAGE_H

#include "app.h"

class welcome_page {

private:
    GtkWidget* create_top_menu(GtkWidget* hbox);
    GtkWidget* create_side_menu(GtkWidget* vbox,std::string file_path);
    GtkWidget* create_main_container(GtkWidget* hbox);
    //static void populate_content();
    GtkWidget* get_container();
public:
    GtkWidget* create_home(GtkWidget* window);
    struct Data{
        std::string label;
    };
};


#endif //GTKGUI_WELCOME_PAGE_H
