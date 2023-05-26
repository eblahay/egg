#include <eyren/MainWindow.hxx>

eyren::MainWindow::MainWindow(std::filesystem::path path){
    set_title("Eyren");

    // add widgets

    img_area.loadFromFile(path);
    box_0.add(img_area);

    add(box_0);
    show_all();
}
