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

class AlarmSettingsWindow final: public Gtk::Window {
   public:
    explicit AlarmSettingsWindow(const AlarmSettings& alarm_settings);

    alarm_updated_event& on_alarm_updated() { return alarm_updated; }

   private:
    Gtk::Button set_button{"Set"};
    Gtk::Button cancel_button{"Cancel"};
    Gtk::ButtonBox button_box{};
    Gtk::Label hour_label{"Hour"};
    Gtk::SpinButton hour_button{};
    Gtk::Label minute_label{"Minute"};
    Gtk::SpinButton minute_button{};
    Gtk::Box spinner_box{};
    Gtk::ButtonBox days_box{};
    Gtk::Box box{Gtk::ORIENTATION_VERTICAL};
    std::array<Gtk::CheckButton, 7> day_buttons{
        Gtk::CheckButton("Sun"), Gtk::CheckButton("Mon"),
        Gtk::CheckButton("Tue"), Gtk::CheckButton("Wed"),
        Gtk::CheckButton("Thu"), Gtk::CheckButton("Fri"),
        Gtk::CheckButton("Sat")};
    AlarmSettings alarm_event{0,0};
    alarm_updated_event alarm_updated;

    void close_window() { hide(); }
    void set_button_clicked();
};

}  // namespace silverbee

#endif
