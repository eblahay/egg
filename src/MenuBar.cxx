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