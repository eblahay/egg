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

#include "cairomm/refptr.h"
#include "gdkmm/pixbuf.h"
#include <cstddef>
#include <gtkmm/drawingarea.h>

#include <filesystem>
#include <vector>
#include <array>

namespace eyren {
    class ImageArea: public Gtk::DrawingArea{    
        public:
            ImageArea();
            virtual ~ImageArea();

            enum ScalingMode {fit_to_widget, fractional};

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

            const float& getScaleFactor()const;

            void scaleUp();
            
            void scaleDown();

            void setScalingMode(const ScalingMode &mode);

            // scale by float; i.e. scale(0.25) scales to 25%
            void scale(const float &f);

        protected:
            void scaleFitToWidget();

            // Override default signal handler
            bool on_draw(const Cairo::RefPtr<Cairo::Context>& cr) override;
        
            // contains pixels which make up the image
            Glib::RefPtr<Gdk::Pixbuf> img;

            // img scaled dimensions
            std::array<unsigned int, 2> scaled_dm;

            std::vector<std::filesystem::path> paths;

            // current path index
            std::size_t curr_path_i; // defaults to [0]

            ScalingMode scaling_mode;

            bool f_loaded;

            float scale_factor;
    };
}