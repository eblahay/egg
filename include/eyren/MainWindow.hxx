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

