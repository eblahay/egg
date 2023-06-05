#pragma once

#include "cairomm/refptr.h"
#include "gdkmm/pixbuf.h"
#include <cstddef>
#include <gtkmm/drawingarea.h>

#include <filesystem>
#include <vector>

namespace eyren {
    class ImageArea: public Gtk::DrawingArea{    
        public:
            ImageArea();
            virtual ~ImageArea();

            // load image from specified file (note: does NOT save specified path)
            void loadFromFile(const std::filesystem::path &path);

            // load image from current file
            void load();

            void nextImg();
            
            void prevImg();

            // set the value of img paths
            //
            // note: also resets current path index to [0]
            void setPaths(const std::vector<std::filesystem::path> &paths);

            std::filesystem::path getCurrentPath()const;

            const std::size_t& getCurrPathIndex()const;

            const std::vector<std::filesystem::path>& getPaths();
        
        protected:
            // Override default signal handler
            bool on_draw(const Cairo::RefPtr<Cairo::Context>& cr) override;
        
            // contains pixels which make up the image
            Glib::RefPtr<Gdk::Pixbuf> img;

            std::vector<std::filesystem::path> paths;

            // current path index
            std::size_t curr_path_i; // defaults to [0]

            bool f_loaded;
    };
}