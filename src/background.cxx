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
      current_image{} {}

Gtk::Image& Background::get() {
    try {
        auto random_image = get_random_image();

        current_pixbuf =
            Gdk::Pixbuf::create_from_file(random_image, width, height, false);
        current_image.set(current_pixbuf);

    } catch (Glib::FileError& e) {
        current_image.clear();
    }

    return current_image;
}

std::string Background::get_random_image() {
    Glib::Dir dir{image_directory};

    std::vector<std::string> filenames;
    std::for_each(dir.begin(), dir.end(),
                  [&filenames](auto item) { filenames.push_back(item); });

    std::uniform_int_distribution<> distrib(0, filenames.size() - 1);
    auto random_number = distrib(random);
    return image_directory + "/" + filenames[random_number];
}
