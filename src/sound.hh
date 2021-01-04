#ifndef SOUND_HH
#define SOUND_HH

#include <gst/gst.h>

#include <string>

namespace silverbee {
class Sound final {
   public:
    explicit Sound(const std::string& filename);
    ~Sound();
    Sound(const Sound&) = delete;
    Sound& operator=(const Sound&) = delete;
    
    void play();
    void stop();

   private:
    std::string url{"file://"};
    GstElement* play_ptr{nullptr};
    GstBus* bus{nullptr};
};
}  // namespace silverbee

#endif
