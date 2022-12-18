#include <gtkmm.h>
#include <iostream>

#include "EmulatorApp.h"

using namespace std;

EmulatorApp::EmulatorApp() {
    this->ui = Gtk::Builder::create_from_file("emulator.glade");

    if (this->ui) {
        // cout << "checkpoint\n";
        ui->get_widget<Gtk::Fixed>("Page", fixed);
        button_step = Glib::RefPtr<Gtk::Button>::cast_dynamic(
            ui->get_object("button_step")
        );

    }
    set_title("SicXEmulator");
    show_all();
}