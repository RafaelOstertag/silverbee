#ifndef BACKGROUND_HH
#define BACKGROUND_HH

#include <gdkmm/pixbuf.h>
#include <gtkmm/image.h>

#include <random>
#include <string>

namespace silverbee {
class Background final {
   public:
    Background(const std::string& image_directory, int width, int height);
    void load_new();
    Glib::RefPtr<Gdk::Pixbuf> get();

   private:
    std::random_device rd{};
    std::mt19937 random;
    std::string image_directory;
    int width;
    int height;
    Glib::RefPtr<Gdk::Pixbuf> current_pixbuf{nullptr};
    std::mutex image_load_mutex{};

    std::string get_random_image();
};
}  // namespace silverbee

#endif
