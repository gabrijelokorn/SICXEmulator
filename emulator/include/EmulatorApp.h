#ifndef SICXE_EMULATORAPP_H
#define SICXE_EMULATORAPP_H

#include <gtkmm.h>
class EmulatorApp : public Gtk::ApplicationWindow
{
private:
public:
    Gtk::Fixed *fixed;
    Glib::RefPtr<Gtk::Button> button_step;
    Glib::RefPtr<Gtk::Builder> ui;
    EmulatorApp();
};

#endif