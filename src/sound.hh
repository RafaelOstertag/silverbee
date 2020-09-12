#ifndef SOUND_HH
#define SOUND_HH

#include <gst/gst.h>

#include <string>

namespace silverbee {
class Sound {
   public:
    Sound(const std::string& filename);
    ~Sound();
    Sound(const Sound&) = delete;

    void play();
    void stop();

   private:
    std::string url;
    GstElement* play_ptr;
    GstBus* bus;
};
}  // namespace silverbee

#endif
