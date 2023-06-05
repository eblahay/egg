#pragma once

#include <gtkmm/menu.h>
#include <gtkmm/menubar.h>
#include <gtkmm/aboutdialog.h>

namespace eyren {
    /*
        a class which deals with the application's
        primary menubar
    */
    class MenuBar: public Gtk::MenuBar{
        public:
            MenuBar();

        private:
            struct FileMenu{
                Gtk::Menu menu;
                Gtk::MenuItem menu_item;
                Gtk::MenuItem
                    open    
                ;
            }file;

            struct HelpMenu{
                Gtk::Menu menu;
                Gtk::MenuItem menu_item;
                Gtk::MenuItem
                    about    
                ;
                Gtk::AboutDialog about_dialog;
            }help;
    };
}