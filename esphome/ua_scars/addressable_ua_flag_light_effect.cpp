#include "addressable_ua_flag_light_effect.h"
#include "esphome/components/light/esp_hsv_color.h"
#include "esphome/core/log.h"
#include "tryzub.h"

namespace esphome {
namespace ua_scars {

static const char *const TAG = "addressable_ua_flag_light_effect";

AddressableUaFlagLightEffect::AddressableUaFlagLightEffect(const std::string &name) : AddressableLightEffect(name) {}

void AddressableUaFlagLightEffect::apply(light::AddressableLight &it, const Color &current_color) {
  
  if (this->initial_run_) {
    it.all() = Color::BLACK;
    this->initial_run_ = false;
  }
  const uint32_t now = millis();
  if (now - this->last_run_ < this->speed_) {
    return;
  }
  this->last_run_ = now;
  // Fade out all LEDs
  
  for (auto led : FLAG_TOP) {
    it[led] = FLAG_COLOR_BLUE;
  }

  for (auto led : FLAG_BOTTOM) {
    it[led] = FLAG_COLOR_YELLOW;
  }
  
  it.schedule_show();
}

}  // namespace ua_scars
}  // namespace esphome
