#include <eyren/MainWindow.hxx>

eyren::MainWindow::MainWindow(std::filesystem::path path){
    std::string title_str;
    if(!path.empty()){
        title_str += path;
        title_str += " — ";
    }
    title_str += "Eyren";

    set_title(title_str);

    // add widgets

    img_area.loadFromFile(path);
    box_0.add(img_area);

    add(box_0);
    show_all();
}
