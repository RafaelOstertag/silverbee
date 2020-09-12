#ifndef BACKGROUND_HH
#define BACKGROUND_HH

#include <gdkmm/pixbuf.h>
#include <gtkmm/image.h>

#include <random>
#include <string>

namespace silverbee {
class Background {
   public:
    Background(const std::string& image_directory, int width, int height);
    Gtk::Image& get();

   private:
    std::random_device rd;
    std::mt19937 random;
    std::string image_directory;
    int width;
    int height;
    Glib::RefPtr<Gdk::Pixbuf> current_pixbuf;
    Gtk::Image current_image;

    std::string get_random_image();
};
}  // namespace silverbee

#endif
