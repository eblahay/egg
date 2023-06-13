#include "eyren/ImageArea.hxx"
#include "sigc++/functors/mem_fun.h"
#include <eyren/MainWindow.hxx>
#include <filesystem>
#include <string>

#include <iostream>

eyren::MainWindow::MainWindow(std::vector<std::filesystem::path> paths){
    img_area.setPaths(paths);

    updateTitle();
    set_default_size(800, 600);

    // add widgets
    box_0.pack_start(menubar, false, false);

    img_area.load();
    box_0.add(img_area);

    add(box_0);

    // connect signal handlers
    this->signal_key_press_event().connect(
        sigc::mem_fun(*this, &MainWindow::onKeyPress),
        false
    );

    // display widgets
    show_all();
}

bool eyren::MainWindow::onKeyPress(GdkEventKey* e){
    switch (e->keyval) {
        case 65361: // Left-Arrow Key
            if(!img_area.getPaths().empty()){
                img_area.prevImg();
                img_area.queue_draw();

                updateTitle(true);
            }

            break;
        case 65363: // Right-Arrow Key
            if(!img_area.getPaths().empty()){
                img_area.nextImg();
                img_area.queue_draw();

                updateTitle(true);
            }

            break;
        case 113: // 'Q' Key
        case 65307: // Esc Key
            close();
            break;
        default:
            std::cout << e->keyval << '\n';
            break;
    }

    return false;
}

void eyren::MainWindow::updateTitle(bool override_emptiness_chk){
    std::string title_str = "Eyren";
    
    if(override_emptiness_chk || !img_area.getPaths().empty()){
        title_str += " [";
        title_str += std::to_string(img_area.getCurrPathIndex()+1);
        title_str += " of ";
        title_str += std::to_string(img_area.getPaths().size());
        title_str += "] - ";
        title_str += img_area.getCurrentPath();
    }

    set_title(title_str);
}
