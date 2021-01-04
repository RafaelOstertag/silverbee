#include "sound.hh"

#include <sstream>

using namespace silverbee;

namespace {
gboolean bus_callback(GstBus*, GstMessage* message, gpointer user_data) {
    if (GST_MESSAGE_TYPE(message) == GST_MESSAGE_EOS) {
        gst_element_set_state(GST_ELEMENT(user_data), GST_STATE_NULL);
        gst_element_set_state(GST_ELEMENT(user_data), GST_STATE_PLAYING);
    }

    return TRUE;
}
}  // namespace

Sound::Sound(const std::string& filename) { url += filename; }

Sound::~Sound() { stop(); }

void Sound::play() {
    if (play_ptr != nullptr) {
        return;
    }

    play_ptr = gst_element_factory_make("playbin", "play");
    g_object_set(G_OBJECT(play_ptr), "uri", url.c_str(), NULL);

    bus = gst_pipeline_get_bus(GST_PIPELINE(play_ptr));
    gst_bus_add_watch(bus, bus_callback, play_ptr);

    gst_element_set_state(play_ptr, GST_STATE_PLAYING);
}

void Sound::stop() {
    if (play_ptr != nullptr) {
        gst_element_set_state(play_ptr, GST_STATE_NULL);
        gst_bus_remove_watch(bus);
        gst_object_unref(GST_OBJECT(play_ptr));
        gst_object_unref(bus);
        play_ptr = nullptr;
        bus = nullptr;
    }
}
