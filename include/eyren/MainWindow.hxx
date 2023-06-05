#pragma once

#include <filesystem>
#include <gtkmm/hvbox.h>
#include <gtkmm/applicationwindow.h>
#include <gtkmm/box.h>

#include <vector>

#include <eyren/ImageArea.hxx>
#include <eyren/MenuBar.hxx>

namespace eyren{
	class MainWindow: public Gtk::ApplicationWindow {
		public:
			MainWindow(std::vector<std::filesystem::path> paths);

			

		protected:
			// Signal Handlers //
			// signal handler for all key presses
			bool onKeyPress(GdkEventKey* e);

			// other functs
			// updates window title
			void updateTitle(bool override_emptiness_chk=false);

			// Member Widgets
			Gtk::VBox box_0;

			eyren::MenuBar menubar;

			eyren::ImageArea img_area;

	};
}

