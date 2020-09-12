#ifndef MAINWINDOW_HH
#define MAINWINDOW_HH

#include <gtkmm/box.h>
#include <gtkmm/button.h>
#include <gtkmm/image.h>
#include <gtkmm/label.h>
#include <gtkmm/overlay.h>
#include <gtkmm/window.h>

#include <memory>

#include "alarmsettingswindow.hh"
#include "background.hh"
#include "state/alarmcontext.hh"

namespace silverbee {

class MainWindow : public Gtk::Window {
   public:
    MainWindow(state::AlarmContext& alarm_ctx,
               const AlarmSettings& alarm_settings,
               std::shared_ptr<Background> background);
    virtual ~MainWindow() = default;

    void show_alarm_buttons();
    void hide_alarm_buttons();

   private:
    state::AlarmContext& alarm_context;
    AlarmSettingsWindow alarm_settings_window;
    Gtk::Overlay overlay;
    Gtk::Image bg_image;
    Gtk::Box main_vbox;
    Gtk::Button settings_button;
    Gtk::Label time;
    Gtk::Box overlay_vbox;
    Gtk::Button snooze_button;
    Gtk::Button stop_button;
    std::shared_ptr<Background> background;

    void settings_button_clicked();
    void snooze_button_clicked();
    void stop_button_clicked();
    void alarm_event_updated(const AlarmSettings& alarm_event);
    void alarm_sounding();
    bool time_event();
    bool update_background();
    void update_displayed_time();
};

}  // namespace silverbee

#endif
