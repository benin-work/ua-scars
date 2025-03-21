#pragma once

#include "esphome/components/light/addressable_light_effect.h"
#include "tryzub.h"

namespace esphome
{
  namespace ua_scars
  {

    class AddressableUaTwinkleLightEffect : public light::AddressableLightEffect
    {
    public:
      AddressableUaTwinkleLightEffect(const std::string &name) : AddressableLightEffect(name) {};

      void apply(light::AddressableLight &it, const Color &current_color) override {
        const uint32_t now = millis();
        uint8_t pos_add = 0;
        if (now - this->last_progress_ > this->progress_interval_) {
          pos_add = (now - this->last_progress_) / this->progress_interval_;
          this->last_progress_ = now;
        }
        uint8_t subsine = ((8 * (now - this->last_progress_)) / this->progress_interval_) & 0b111;
        for (auto view : it) {
          if (view.get_effect_data() != 0) {
            const uint8_t x = (view.get_effect_data() >> 3) & 0b11111;
            const uint8_t color = view.get_effect_data() & 0b111;
            const uint16_t sine = light::half_sin8((x << 3) | subsine);
            if (color == 0) {
              view = current_color * sine;
            } else {
              view = Color(((color >> 2) & 1) * sine, ((color >> 1) & 1) * sine, ((color >> 0) & 1) * sine);
            }
            const uint8_t new_x = x + pos_add;
            if (new_x > 0b11111) {
              view.set_effect_data(0);
            } else {
              view.set_effect_data((new_x << 3) | color);
            }
          } else {
            view = Color(0, 0, 0, 0);
          }
        }
        while (random_float() < this->twinkle_probability_) {
          const size_t pos = random_uint32() % it.size();
          if (it[pos].get_effect_data() != 0)
            continue;
          //const uint8_t color = random_uint32() & 0b111;
          const uint8_t color = random_uint32() % 2 ? 0b110 : 0b001;
          it[pos].set_effect_data(0b1000 | color);
        }
        it.schedule_show();
      }
      void set_twinkle_probability(float twinkle_probability) { this->twinkle_probability_ = twinkle_probability; }
      void set_progress_interval(uint32_t progress_interval) { this->progress_interval_ = progress_interval; }
    
     protected:
      float twinkle_probability_{0.2f};
      uint32_t progress_interval_{32};
      uint32_t last_progress_{0};

    };

  } // namespace ua_scars
} // namespace esphome
