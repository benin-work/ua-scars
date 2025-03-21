#pragma once

#include "esphome/components/light/addressable_light_effect.h"
#include "tryzub.h"

namespace esphome
{
  namespace ua_scars
  {

    class AddressableLibertyFlashLightEffect : public light::AddressableLightEffect
    {
    public:
      AddressableLibertyFlashLightEffect(const std::string &name) : AddressableLightEffect(name) {};

      void start() override { initial_run_ = true; };
      void apply(light::AddressableLight &it, const Color &current_color) override
      {
        if (initial_run_)
        {
          it.all() = Color::BLACK;
          initial_run_ = false;
          at_letter_ = 0;
        }

        const uint32_t now = millis();
        if (now - last_run_ < update_interval_)
          return;

        // Increment the letter index
        if (now - last_letter_flash_ > letter_flash_interval_ + (at_letter_ == 0 ? letter_flash_interval_ : 0))
        {
          last_letter_flash_ = now;

          const auto currrent_letter = WORD_VOLYA[at_letter_];
          for (uint32_t i = 0; i < currrent_letter.size(); i++)
          {
            it[currrent_letter[i]] = current_color;
          }

          at_letter_++;
          if (at_letter_ >= WORD_VOLYA.size())
          {
            at_letter_ = 0;
          }
        }

        // Fade out all LEDs
        for (uint32_t i = 0; i < it.size(); i++)
        {
          it[i] = it[i].get() * (255 - fade_out_rate_);
        }
        
        last_run_ = now;

        it.schedule_show();
      };

  protected : 
    bool initial_run_{true};
    uint32_t update_interval_{30};    
    uint32_t letter_flash_interval_{500};
    uint32_t last_letter_flash_{0};
    uint32_t last_run_{0};
    uint8_t at_letter_{0};
    uint8_t fade_out_rate_{5};
  };

} // namespace ua_scars
} // namespace esphome
