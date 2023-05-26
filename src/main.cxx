#include <iostream>
#include <filesystem>

#include <boost/program_options.hpp>

#include <eyren/MainWindow.hxx>

namespace po = boost::program_options;

int main(int argc, char* argv[]){

    // parse command-line arguments
    po::options_description cmdln_opts("Options");
    cmdln_opts.add_options()
        ("help", "prints this message")
        ("version", "prints program version information")
        ("path", po::value<std::filesystem::path>(), "filepath to image file to be loaded")
    ;

    po::variables_map vm;
    po::store(po::command_line_parser(argc, argv).options(cmdln_opts).run(), vm);
    po::notify(vm);

    if(vm.count("help")){
        std::cout << cmdln_opts << '\n';
        //return 0;
    }
    else if(vm.count("version")){
        std::cout << "Eyren Image-Viewer version 0.1.0\n";
        return 0;
    }

    //
    std::filesystem::path path;
    if(vm.count("path")) path = vm.at("path").as<std::filesystem::path>();

    // set up window
    argc = 1;
    Glib::RefPtr<Gtk::Application> app =
        Gtk::Application::create(argc, argv, "application.eyren")
    ;
    
    eyren::MainWindow window(path);

    return app->run(window);
}