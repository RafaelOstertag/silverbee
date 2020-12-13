#include "background.hh"

#include <glibmm/fileutils.h>

#include <algorithm>
#include <vector>

using namespace silverbee;

Background::Background(const std::string& image_directory, int width,
                       int height)
    : rd{},
      random{rd()},
      image_directory{image_directory},
      width{width},
      height{height},
      current_pixbuf{nullptr},
      image_load_mutex{} {}

void Background::load_new() {
    try {
        auto random_image = get_random_image();

        auto file_pixbuf = Gdk::Pixbuf::create_from_file(random_image);
        auto file_pixbuf_width = file_pixbuf->get_width();

        std::unique_lock<std::mutex> lock{image_load_mutex};
        current_pixbuf = Gdk::Pixbuf::create(
            file_pixbuf->get_colorspace(), file_pixbuf->get_has_alpha(),
            file_pixbuf->get_bits_per_sample(), width, height);

        

        double  scale = static_cast<double>(width) /
                    static_cast<double>(file_pixbuf_width);

        file_pixbuf->scale(current_pixbuf, 0, 0, width, height, 0.0, 0.0, scale,
                           scale, Gdk::INTERP_HYPER);

    } catch (Glib::FileError& e) {
        current_pixbuf =
            Gdk::Pixbuf::create(Gdk::COLORSPACE_RGB, false, 8, width, height);
    }
}

Glib::RefPtr<Gdk::Pixbuf> Background::get() {
    std::unique_lock<std::mutex> lock{image_load_mutex};
    return current_pixbuf;
}

std::string Background::get_random_image() {
    Glib::Dir dir{image_directory};

    std::vector<std::string> filenames;
    std::for_each(dir.begin(), dir.end(),
                  [&filenames](auto item) { filenames.push_back(item); });

    if (filenames.size() == 0) {
        return "";
    }

    std::uniform_int_distribution<> distrib(0, filenames.size() - 1);
    auto random_number = distrib(random);
    return image_directory + "/" + filenames[random_number];
}
