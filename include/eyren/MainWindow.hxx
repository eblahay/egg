#pragma once

#include <gtkmm/hvbox.h>
#include <gtkmm/applicationwindow.h>
#include <gtkmm/box.h>

#include <eyren/ImageArea.hxx>

namespace eyren{
	class MainWindow: public Gtk::ApplicationWindow {
		public:
			MainWindow(std::filesystem::path path);

		protected:
			// Signal Handlers

			// Member Widgets
			Gtk::VBox box_0;

			eyren::ImageArea img_area;

	};
}

