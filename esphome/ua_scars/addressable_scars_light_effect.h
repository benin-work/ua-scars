#pragma once

#include "esphome/components/light/addressable_light_effect.h"
#include "tryzub.h"

namespace esphome
{
  namespace ua_scars
  {

    class AddressableScarsLightEffect : public light::AddressableLightEffect
    {
    public:
      AddressableScarsLightEffect(const std::string &name) : AddressableLightEffect(name) {};

      void start() override { initial_run_ = true; };
      void apply(light::AddressableLight &it, const Color &current_color) override
      {
        if (initial_run_)
        {
          it.all() = Color::BLACK;
          initial_run_ = false;
          at_led_ = 0;
          scan_forward_ = true;
          at_segment_ = random_uint32() % all_segments.size();
        }

        const uint32_t now = millis();
        if (now - last_run_ < update_interval_)
          return;
        last_run_ = now;

        // Draw scars
        const auto current_segment = all_segments[at_segment_];
        it[current_segment[at_led_]] = at_segment_color_;
                
        if (scan_forward_ && at_led_ >= (current_segment.size() -1) || !scan_forward_ && at_led_ == 0)
        {
          at_segment_color_ = (at_segment_color_ == FLAG_COLOR_BLUE) ? FLAG_COLOR_YELLOW : FLAG_COLOR_BLUE;
          at_segment_ = random_uint32() % all_segments.size();
          scan_forward_ = random_uint32() % 2;
          at_led_ = scan_forward_ ? 0 : all_segments[at_segment_].size() - 1;
        } 
        else
        {
          at_led_ = scan_forward_ ? at_led_ + 1 : at_led_ - 1;
        }

        it.schedule_show();
      }

    protected:
      bool initial_run_{true};
      uint32_t update_interval_{30};
      uint32_t last_run_{0};
      bool scan_forward_{true};
      uint16_t at_led_{0};
      uint8_t at_segment_{0};
      Color at_segment_color_{FLAG_COLOR_BLUE};
    };

  } // namespace ua_scars
} // namespace esphome
