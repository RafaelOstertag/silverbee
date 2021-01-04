#include "alarmsettings.hh"

#include <giomm/file.h>
#include <glibmm/fileutils.h>
#include <glibmm/keyfile.h>
#include <glibmm/miscutils.h>

#include <iostream>

using namespace silverbee;

namespace {
constexpr const char* CONFIG_FILENAME{"settings"};
constexpr const char* CONFIG_ALARM_SECTION{"alarm"};
constexpr const char* CONFIG_HOUR{"hour"};
constexpr const char* CONFIG_MINUTE{"minute"};
constexpr const char* CONFIG_DAYS{"days"};
constexpr const char* CONFIG_SNOOZE{"snooze"};

Glib::ustring get_silverbee_config_dir_name() {
    auto config_dir = Glib::get_user_config_dir();
    return config_dir += "/silverbee";
}

Glib::ustring get_silverbee_config_file_path() {
    return get_silverbee_config_dir_name() + "/" + CONFIG_FILENAME;
}

}  // namespace

AlarmSettings::AlarmSettings(t_hour h, t_minute m, std::vector<DAY> d)
    : hour{h}, minute{m} {
    days.reset();
    std::for_each(d.begin(), d.end(), [this](DAY _d) { days.set(static_cast<int>(_d), true); });
}

void AlarmSettings::save() const {
    Glib::KeyFile key_file{};

    key_file.set_uint64(CONFIG_ALARM_SECTION, CONFIG_HOUR, hour);
    key_file.set_uint64(CONFIG_ALARM_SECTION, CONFIG_MINUTE, minute);
    key_file.set_uint64(CONFIG_ALARM_SECTION, CONFIG_DAYS, days.to_ulong());
    key_file.set_uint64(CONFIG_ALARM_SECTION, CONFIG_SNOOZE, snooze);

    auto config_dir = get_silverbee_config_dir_name();

    if (!Glib::file_test(config_dir,
                         Glib::FILE_TEST_EXISTS | Glib::FILE_TEST_IS_DIR)) {
        auto config_dir_handle = Gio::File::create_for_path(config_dir);
        config_dir_handle->make_directory_with_parents();
    }

    auto config_file = get_silverbee_config_file_path();
    key_file.save_to_file(config_file);
}

void AlarmSettings::load() {
    auto settings_file_path = get_silverbee_config_file_path();
    try {
        Glib::KeyFile key_file{};
        key_file.load_from_file(settings_file_path);

        hour = static_cast<t_hour>(
            key_file.get_uint64(CONFIG_ALARM_SECTION, CONFIG_HOUR));
        minute = static_cast<t_minute>(
            key_file.get_uint64(CONFIG_ALARM_SECTION, CONFIG_MINUTE));
        days = std::bitset<7>{key_file.get_uint64(CONFIG_ALARM_SECTION, CONFIG_DAYS)};
        snooze = static_cast<t_minute>(
            key_file.get_uint64(CONFIG_ALARM_SECTION, CONFIG_SNOOZE));

    } catch (const Glib::Error& e) {
        std::cerr << "Cannot load settings file " << settings_file_path << ": "
                  << e.what() << "\n";
        std::cerr << "Load default settings instead\n";
        reset();
    }
}

void AlarmSettings::reset() {
    hour = 0;
    minute = 0;
    days.reset();
    snooze = 5;
}
