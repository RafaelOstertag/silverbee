#include "silverbee.hh"

#include <gdkmm/screen.h>
#include <gst/gst.h>
#include <gtkmm/application.h>

#include <string>

#include "alarmsettings.hh"
#include "mainwindow.hh"
#include "state/alarmcontext.hh"

int main(int argc, char* argv[]) {
    auto app = Gtk::Application::create(argc, argv, "ch.guengel.silverbee");
    gst_init(&argc, &argv);

    std::string data_dir{DATA_DIR};

    silverbee::AlarmSettings alarm_settings{};
    alarm_settings.load();

    silverbee::state::AlarmContext alarm_context{
        alarm_settings, data_dir + "/sound/funkysynth.wav"};

    auto default_screen = Gdk::Screen::get_default();
    auto rectangle = default_screen->get_monitor_workarea(
        default_screen->get_primary_monitor());

    std::shared_ptr<silverbee::Background> background{new silverbee::Background(
        data_dir + "/background/", rectangle.get_width(),
        rectangle.get_height())};
    silverbee::MainWindow mainWindow{alarm_context, alarm_settings, background};

    auto ret_val = app->run(mainWindow);
    gst_deinit();
    return ret_val;
}
