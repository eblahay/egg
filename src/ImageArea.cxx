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

#include "gdkmm/general.h"
#include "gdkmm/pixbuf.h"
#include "giomm/error.h"
#include "glibmm/error.h"
#include "gtkmm/drawingarea.h"
#include "gtkmm/enums.h"
#include <cstddef>
#include <eyren/ImageArea.hxx>

#include <filesystem>
#include <giomm/resource.h>

#include <glib/gerror.h>

#include <iostream>
#include <stdexcept>

eyren::ImageArea::ImageArea():
    f_loaded(false),
    curr_path_i(0)
{}

eyren::ImageArea::~ImageArea(){
    
}

void eyren::ImageArea::loadFromFile(const std::filesystem::path &path){
    try{
        if(!path.empty()){
            img = Gdk::Pixbuf::create_from_file(path);
            f_loaded = true;
        }
    }
    catch(const Gio::ResourceError &e){
        std::cerr << "ResourceError: " << e.what() << '\n';
    }
    catch(const Gdk::PixbufError &e){
        std::cerr << "PixbufError: " << e.what() << '\n';
    }
    catch(const Gio::Error &e){
        std::cerr << "Error: " << e.what() << '\n';
    }
    catch(const Glib::Error &e){
        std::cerr << "Error: " << e.what() << '\n';
    }
}

void eyren::ImageArea::load(){
    if(!paths.empty()) loadFromFile(paths[curr_path_i]);
    else{
        // this is where I'd write something to a log file— maybe.
    }
}

void eyren::ImageArea::setPaths(const std::vector<std::filesystem::path> &paths){
    this->paths = paths;

    curr_path_i = 0;
    f_loaded = false;
}

void eyren::ImageArea::nextImg(){
    if(++curr_path_i >= paths.size()) curr_path_i = 0;
    load();
}

void eyren::ImageArea::prevImg(){
    if(curr_path_i == 0) curr_path_i = paths.size() - 1;
    else curr_path_i--;
    load();
}

std::filesystem::path eyren::ImageArea::getCurrentPath()const{
    return paths[curr_path_i];
}

const std::size_t& eyren::ImageArea::getCurrPathIndex()const{
    return curr_path_i;
}

const std::vector<std::filesystem::path>& eyren::ImageArea::getPaths(){
    return paths;
}

bool eyren::ImageArea::on_draw(const Cairo::RefPtr<Cairo::Context>& cr){
    // check loaded flag
    if(!f_loaded) return true;

    // scale image based on widget's size
    int 
        scaled_img_width,
        scaled_img_height
    ;

    if(get_allocated_width() >= get_allocated_height()){
        // allocated width is greater than allocated height

        scaled_img_height = get_allocated_height();
        scaled_img_width = (int)((float)scaled_img_height / (float)img->get_height() * img->get_width());

        //
        if(scaled_img_width > get_allocated_width()){
            scaled_img_width = get_allocated_width();
            scaled_img_height = (int)((float)get_allocated_width() / (float)img->get_width() * img->get_height());
        }
    }
    else{
        // allocated height is greater than allocated width

        scaled_img_width = get_allocated_width();
        scaled_img_height = (int)((float)get_allocated_width() / (float)img->get_width() * img->get_height());

    }

    Glib::RefPtr<Gdk::Pixbuf> img_scaled = img->scale_simple(
        scaled_img_width, 
        scaled_img_height, 
        Gdk::INTERP_BILINEAR    
    );

    Gdk::Cairo::set_source_pixbuf(
        cr, img_scaled,
        (get_allocated_width() / 2) - (scaled_img_width / 2), 
        (get_allocated_height() / 2) - (scaled_img_height / 2)
    );
    
    cr->paint();

    return true;
}