#pragma once

#include "esphome/components/light/addressable_light_effect.h"
#include "tryzub.h"
#include <algorithm>

namespace esphome
{
  namespace ua_scars
  {

    class AddressableWaterDropsLightEffect : public light::AddressableLightEffect
    {
    public:
      AddressableWaterDropsLightEffect(const std::string &name) : AddressableLightEffect(name) {};

      void start() override { initial_run_ = true; };
      void apply(light::AddressableLight &it, const Color &current_color) override
      {
        if (initial_run_)
        {
          it.all() = Color::BLACK;
          initial_run_ = false;
        }

        const uint32_t now = millis();
        if (now - last_run_ < update_interval_)
          return;
        last_run_ = now;
        
        for (size_t i = 0; i < it.size(); i++)
        {
          // Check if the LED has an effect data set and it's not from the current update cycle
          if (it[i].get_effect_data() != 0 && !(it[i].get_effect_data() & 0b10000000))
          {
            // set color effect
            it[i].set(current_color);

            const uint8_t line = (it[i].get_effect_data()) & 0b01111111;
            const auto &current_line = all_water_lines[line];
            auto current_led_it = std::find(current_line.begin(), current_line.end(), i);

            if (current_led_it != current_line.end())
            {
              if (++current_led_it != current_line.end())
              {
                it[*current_led_it].set_effect_data(0b10000000 | line);
              }

              it[i].set_effect_data(0);
            }
          }
        }

        ///
        for (auto view : it)
        {
          if (view.get_effect_data() != 0 && view.get_effect_data() & 0b10000000)
          {
            // clear the 1st bit
            view.set_effect_data(view.get_effect_data() & 0b01111111);
          }
        }        

        // Fade out all LEDs
        for (auto i = 0; i < it.size(); i++)
        {
          it[i] = it[i].get() * (255 - fade_out_rate_);
        }

        while (random_float() < this->probability_) {
          const auto line = random_uint32() % all_water_lines.size();
          //const auto led_pos = random_uint32() % (all_water_lines[line].size());          
          //const auto first_led = all_water_lines[line][led_pos];
          const auto first_led = all_water_lines[line][0];          
          it[first_led].set_effect_data(line); // set line number in effect data
        }

        it.schedule_show();
      }

    protected:
      float probability_{0.15f};
      bool initial_run_{true};
      uint32_t update_interval_{50};
      uint32_t last_run_{0};
      uint8_t fade_out_rate_{10};
    };

  } // namespace ua_scars
} // namespace esphome
