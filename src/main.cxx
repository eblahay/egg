#include "giomm/application.h"
#include <boost/program_options/positional_options.hpp>
#include <exception>
#include <iostream>
#include <filesystem>
#include <vector>

#include <boost/program_options.hpp>

#include <eyren/MainWindow.hxx>

namespace po = boost::program_options;

int main(int argc, char* argv[]){
    try{

        // parse command-line arguments
        po::options_description cmdln_opts("Options");
        cmdln_opts.add_options()
            ("help", "prints this message")
            ("version", "prints program version information")
            ("path", po::value<std::vector<std::string>>(), "filepath to image file to be loaded")
        ;

        po::positional_options_description p;
        p.add("path", -1);

        po::variables_map vm;
        po::store(po::command_line_parser(argc, argv).options(cmdln_opts).positional(p).run(), vm);
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
        std::vector<std::filesystem::path> paths;
        if(vm.count("path")){
            /*
                This is a work-around for what I assume is an error in
                boost::program_options version 1.74.0, where std::filesystem::path (unlike std::string)
                does not have a parsing operation capable of handling arguments which have spaces.
            */

            auto arr = vm["path"].as<std::vector<std::string>>();
            for(auto it = arr.begin(); it != arr.end(); it++){
                paths.push_back({*it});
            }
        }

        // set up window
        argc = 1;
        Glib::RefPtr<Gtk::Application> app =
            Gtk::Application::create(argc, argv, "application.eyren")
        ;
        
        app->set_flags(Gio::APPLICATION_NON_UNIQUE);

        eyren::MainWindow window(paths);

        return app->run(window);
    }
    catch(std::exception &e){
        std::cerr << "Error: " << e.what() << '\n';
        return 1;
    }
    catch(...){
        std::cerr << "Exception of Unknown Type\n";
        return 1;
    }
}