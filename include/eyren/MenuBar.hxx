/*
    Eyren — a simple image-viewing application
    Copyright (C) 2023 Ethan Blahay

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <https://www.gnu.org/licenses/>.
*/

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