#include "mainwindow.hh"

#include <glibmm/main.h>

#include <sstream>
#include <thread>

using namespace silverbee;

MainWindow::MainWindow(state::AlarmContext& alarm_ctx,
                       const AlarmSettings& alarm_settings,
                       std::shared_ptr<Background> background)
    : alarm_context{alarm_ctx},
      alarm_settings_window{alarm_settings},
      overlay{},
      bg_image(),
      main_vbox{Gtk::ORIENTATION_VERTICAL},
      settings_button{"Settings"},
      time{"time"},
      overlay_vbox{},
      snooze_button{"Snooze"},
      stop_button{"Leave me alone"},
      image_replace_dispatcher{},
      background{background} {
    set_title("SilverBee");
    set_border_width(0);
    set_default_size(400, 500);
    fullscreen();

    main_vbox.set_homogeneous(false);
    main_vbox.pack_start(settings_button, Gtk::PACK_SHRINK, 10);
    settings_button.set_halign(Gtk::ALIGN_END);

    main_vbox.pack_end(time, Gtk::PACK_EXPAND_WIDGET, 0);

    overlay_vbox.set_orientation(Gtk::ORIENTATION_VERTICAL);
    overlay_vbox.pack_start(stop_button, Gtk::PACK_EXPAND_WIDGET, 25);
    overlay_vbox.pack_start(snooze_button, Gtk::PACK_EXPAND_WIDGET, 25);

    this->background->load_new();

    bg_image.set(this->background->get());
    overlay.add(bg_image);
    overlay.add_overlay(main_vbox);
    overlay.add_overlay(overlay_vbox);

    add(overlay);

    settings_button.signal_clicked().connect(
        sigc::mem_fun(this, &MainWindow::settings_button_clicked));
    snooze_button.signal_clicked().connect(
        sigc::mem_fun(this, &MainWindow::snooze_button_clicked));
    stop_button.signal_clicked().connect(
        sigc::mem_fun(this, &MainWindow::stop_button_clicked));
    alarm_settings_window.on_alarm_updated().connect(
        sigc::mem_fun(this, &MainWindow::alarm_event_updated));
    alarm_context.on_alarm_sounding().connect(
        sigc::mem_fun(this, &MainWindow::alarm_sounding));

    bg_image.show();
    main_vbox.show_all();
    overlay.show();

    Glib::signal_timeout().connect(sigc::mem_fun(this, &MainWindow::time_event),
                                   250);
    Glib::signal_timeout().connect(
        sigc::mem_fun(this, &MainWindow::update_background), 5000);

    image_replace_dispatcher.connect(
        sigc::mem_fun(this, &MainWindow::on_image_replace));
}

bool MainWindow::time_event() {
    update_displayed_time();
    alarm_context.trigger();

    return true;
}

bool MainWindow::update_background() {
    std::thread load_thread([this] {
        background->load_new();
        image_replace_dispatcher.emit();
    });
    load_thread.detach();

    return true;
}

void MainWindow::update_displayed_time() {
    auto text_builder = std::stringstream{};
    text_builder
        << "<span font_desc=\"mono 80\" weight=\"bold\" color=\"white\">";
    auto current_time = Glib::DateTime::create_now_local();
    text_builder << current_time.format("%T");
    text_builder << "</span>";
    time.set_markup(text_builder.str());
}

void MainWindow::settings_button_clicked() {
    alarm_settings_window.show();
    alarm_settings_window.present();
}

void MainWindow::snooze_button_clicked() {
    alarm_context.snooze();
    hide_alarm_buttons();
}

void MainWindow::stop_button_clicked() {
    alarm_context.stop();
    hide_alarm_buttons();
}

void MainWindow::alarm_event_updated(const AlarmSettings& alarm_settings) {
    alarm_context.set_alarm_event(alarm_settings);
    alarm_settings.save();
}

void MainWindow::alarm_sounding() { show_alarm_buttons(); }

void MainWindow::show_alarm_buttons() { overlay_vbox.show_all(); }

void MainWindow::hide_alarm_buttons() { overlay_vbox.hide(); }

void MainWindow::on_image_replace() { bg_image.set(background->get()); }
