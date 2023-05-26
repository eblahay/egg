#pragma once

#include "cairomm/refptr.h"
#include "gdkmm/pixbuf.h"
#include <gtkmm/drawingarea.h>

#include <filesystem>

namespace eyren {
    class ImageArea: public Gtk::DrawingArea{    
        public:
            ImageArea();
            virtual ~ImageArea();

            // load image from file
            void loadFromFile(const std::filesystem::path &path);
        
        protected:
            // Override default signal handler
            bool on_draw(const Cairo::RefPtr<Cairo::Context>& cr) override;
        
            // contains pixels which make up the image
            Glib::RefPtr<Gdk::Pixbuf> img;

            bool f_loaded;
    };
}