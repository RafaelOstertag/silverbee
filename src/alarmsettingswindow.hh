#ifndef ALARMSETTINSWINDOW_HH
#define ALARMSETTINSWINDOW_HH

#include <gtkmm/box.h>
#include <gtkmm/button.h>
#include <gtkmm/buttonbox.h>
#include <gtkmm/checkbutton.h>
#include <gtkmm/label.h>
#include <gtkmm/spinbutton.h>
#include <gtkmm/window.h>

#include <array>

#include "alarmsettings.hh"

namespace silverbee {
using alarm_updated_event = sigc::signal<void, const AlarmSettings&>;

class AlarmSettingsWindow : public Gtk::Window {
   public:
    AlarmSettingsWindow(const AlarmSettings& alarm_settings);
    virtual ~AlarmSettingsWindow() = default;

    alarm_updated_event& on_alarm_updated() { return alarm_updated; }

   private:
    Gtk::Button set_button;
    Gtk::Button cancel_button;
    Gtk::ButtonBox button_box;
    Gtk::Label hour_label;
    Gtk::SpinButton hour_button;
    Gtk::Label minute_label;
    Gtk::SpinButton minute_button;
    Gtk::Box spinner_box;
    Gtk::ButtonBox days_box;
    Gtk::Box box;
    std::array<Gtk::CheckButton, 7> day_buttons;
    AlarmSettings alarm_event;
    alarm_updated_event alarm_updated;

    void close_window() { hide(); }
    void set_button_clicked();
};

}  // namespace silverbee

#endif
