#include "gdkmm/general.h"
#include "gdkmm/pixbuf.h"
#include "giomm/error.h"
#include "glibmm/error.h"
#include "gtkmm/drawingarea.h"
#include "gtkmm/enums.h"
#include <eyren/ImageArea.hxx>

#include <giomm/resource.h>

#include <glib/gerror.h>

#include <iostream>

eyren::ImageArea::ImageArea():
    f_loaded(false)
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