#include "alarmsettingswindow.hh"

#include <algorithm>
#include <stdexcept>

using namespace silverbee;

AlarmSettingsWindow::AlarmSettingsWindow(const AlarmSettings& alarm_settings)
    : set_button{"Set"},
      cancel_button{"Cancel"},
      button_box{},
      hour_label{"Hour"},
      hour_button{},
      minute_label{"Minute"},
      minute_button{},
      spinner_box{},
      days_box{},
      box{Gtk::ORIENTATION_VERTICAL},
      day_buttons{Gtk::CheckButton("Sun"), Gtk::CheckButton("Mon"),
                  Gtk::CheckButton("Tue"), Gtk::CheckButton("Wed"),
                  Gtk::CheckButton("Thu"), Gtk::CheckButton("Fri"),
                  Gtk::CheckButton("Sat")},
      alarm_event{0, 0} {
    move(0, 0);
    set_border_width(10);
    set_title("Alarm Settings");

    auto hour_adjustment = Gtk::Adjustment::create(0.0, 0.0, 23.0);
    hour_button.set_adjustment(hour_adjustment);
    hour_button.set_value(static_cast<double>(alarm_settings.get_hour()));

    auto minute_adjustment = Gtk::Adjustment::create(0.0, 0.0, 59.0);
    minute_button.set_adjustment(minute_adjustment);
    minute_button.set_value(static_cast<double>(alarm_settings.get_minute()));

    button_box.pack_start(set_button, Gtk::PACK_EXPAND_PADDING, 5);
    button_box.pack_end(cancel_button, Gtk::PACK_EXPAND_PADDING, 5);

    spinner_box.set_homogeneous(true);
    spinner_box.pack_start(hour_label, Gtk::PACK_SHRINK);
    spinner_box.pack_start(hour_button, Gtk::PACK_SHRINK);

    spinner_box.pack_start(minute_label, Gtk::PACK_SHRINK);
    spinner_box.pack_start(minute_button, Gtk::PACK_SHRINK);

    std::for_each(day_buttons.begin(), day_buttons.end(), [this](auto& button) {
        days_box.pack_end(button, Gtk::PACK_SHRINK);
        button.show();
    });

    box.pack_start(spinner_box, Gtk::PACK_SHRINK);
    box.pack_start(days_box, Gtk::PACK_SHRINK);
    box.pack_start(button_box, Gtk::PACK_SHRINK);

    for (int i = 0; i < 7; i++) {
        if (alarm_settings.is_day_set(int_to_day(i))) {
            day_buttons[i].set_active();
        }
    }

    set_button.show();
    cancel_button.show();
    button_box.show();

    hour_label.show();
    hour_button.show();
    minute_label.show();
    minute_button.show();

    spinner_box.show();
    days_box.show();

    box.show();

    add(box);

    cancel_button.signal_clicked().connect(
        sigc::mem_fun(this, &AlarmSettingsWindow::close_window));
    set_button.signal_clicked().connect(
        sigc::mem_fun(this, &AlarmSettingsWindow::set_button_clicked));
}

void AlarmSettingsWindow::set_button_clicked() {
    auto hour = hour_button.get_value();
    auto minute = minute_button.get_value();

    std::vector<DAY> selected_days;
    for (int i = 0; i < 7; i++) {
        if (day_buttons[i].get_active()) {
            selected_days.push_back(int_to_day(i));
        }
    }

    alarm_event = AlarmSettings{static_cast<t_hour>(hour),
                                static_cast<t_minute>(minute), selected_days};
    hide();
    alarm_updated.emit(alarm_event);
}
