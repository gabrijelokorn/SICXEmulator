#include <iostream>
#include <string>
#include <gtkmm.h>

#include "EmulatorApp.h"
// #include "Machine.h"

using std::cin;
using std::cout;
using std::endl;

using namespace std;

class HelloWindow : public Gtk::ApplicationWindow {
    Gtk::Box *cont;
    Glib::RefPtr<Gtk::Label> display_label;
    Glib::RefPtr<Gtk::Button> display_btn;
    Glib::RefPtr<Gtk::Builder> ui;
public:
    HelloWindow()
    : ui{Gtk::Builder::create_from_file("gui.glade")} {
        if(ui) {
            ui->get_widget<Gtk::Box>("cont", cont);
            display_label = Glib::RefPtr<Gtk::Label>::cast_dynamic(
                ui->get_object("display_label")
            );
            display_btn = Glib::RefPtr<Gtk::Button>::cast_dynamic(
                ui->get_object("display_button")
            );
            if(cont && display_label && display_btn) {
                display_btn->signal_clicked().connect(
                [this]() {
                    display_label->set_text("Hello World");
                });
                add(*cont);
            }
        }
        set_title("Simple Gtk::Builder demo");
        set_default_size(400, 400);
        show_all();
    }
};

int main(int argc, char** argv) {

  auto app = Gtk::Application::create("org.gtkmm.examples.base");

  EmulatorApp emulator_app;

  return app->run(emulator_app);
}