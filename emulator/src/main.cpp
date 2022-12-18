#include <iostream>
#include <string>
#include <gtkmm.h>

// #include "Machine.h"

using std::cin;
using std::cout;
using std::endl;

using namespace std;

void on_button_start_clicked (Gtk::Button test) {

}

void on_button_step_clicked (Gtk::Button test) {

}

void on_app_activate()
{
  // Load the GtkBuilder file and instantiate its widgets:
  auto refBuilder = Gtk::Builder::create();
  try
  {
    refBuilder->add_from_file("gui.glade");
  }
  catch(const Glib::FileError& ex)
  {
    std::cerr << "FileError: " << ex.what() << std::endl;
    return;
  }
  catch(const Glib::MarkupError& ex)
  {
    std::cerr << "MarkupError: " << ex.what() << std::endl;
    return;
  }
  catch(const Gtk::BuilderError& ex)
  {
    std::cerr << "BuilderError: " << ex.what() << std::endl;
    return;
  }
}

int main(int argc, char** argv) {

  auto app = Gtk::Application::create("org.gtkmm.examples.base");

  app->signal_activate().connect([] () { on_app_activate(); });

  return app->run(argc, argv);
  // return app->make_window_and_run<MainWin>(argc, argv);
}