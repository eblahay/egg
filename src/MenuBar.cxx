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

#include "gtkmm/aboutdialog.h"
#include <eyren/MenuBar.hxx>

eyren::MenuBar::MenuBar(){
    // file
    file.menu_item.set_label("File");

    file.open.set_label("Open");

    file.menu.add(file.open);

    file.menu_item.set_submenu(file.menu);

    add(file.menu_item);

    // help
    help.menu_item.set_label("Help");

    help.about.set_label("About");

    help.menu.add(help.about);

    help.menu_item.set_submenu(help.menu);

    add(help.menu_item);

    help.about_dialog.set_program_name("Eyren");
    help.about_dialog.set_version("alpha");
    help.about_dialog.set_license_type(Gtk::LICENSE_GPL_3_0);
    help.about_dialog.hide();

    help.about.signal_activate().connect(
        sigc::mem_fun(
            this->help.about_dialog, 
            &Gtk::AboutDialog::show
        )
    );
}