#pragma once

#include "esphome/components/light/addressable_light_effect.h"
#include "tryzub.h"

namespace esphome
{
  namespace ua_scars
  {

    class AddressableLibertyHandwritingLightEffect : public light::AddressableLightEffect
    {
    public:
      AddressableLibertyHandwritingLightEffect(const std::string &name) : AddressableLightEffect(name) {};

      void start() override { this->initial_run_ = true; }
      void apply(light::AddressableLight &it, const Color &current_color) override
      {
        if (initial_run_)
        {
          it.all() = Color::BLACK;
          initial_run_ = false;
          at_led_ = 0;
        }

        const uint32_t now = millis();
        if (now - last_run_ < update_interval_)
          return;
        last_run_ = now;

        // Fade out all LEDs
        for (uint32_t i = 0; i < it.size(); i++)
        {
          it[i] = it[i].get() * (255 - fade_out_rate_);
        }

        if (at_led_ >= (LETTERS_VOLYA.size() - 1) && now - cycle_pause_ < cycle_pause_interval_)
        {
          // Pause before starting the next cycle
          it.schedule_show();
          return;
        }
        cycle_pause_ = now;
        
        at_led_++;
        if (at_led_ >= LETTERS_VOLYA.size())
        {
          at_led_ = 0;
        }

        for (uint32_t i = 0; i < this->scan_width_; i++)
        {
          it[LETTERS_VOLYA[at_led_] + i] = current_color;
        }

        it.schedule_show();
      }

    protected:
      bool initial_run_{true};
      uint32_t update_interval_{15};
      uint32_t last_run_{0};
      uint32_t cycle_pause_{0};
      uint32_t cycle_pause_interval_{1000};
      uint8_t scan_width_{2};
      uint16_t at_led_{9};
      uint8_t fade_out_rate_{10};
    };

  } // namespace ua_scars
} // namespace esphome
