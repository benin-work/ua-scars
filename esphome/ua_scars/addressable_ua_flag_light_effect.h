#pragma once

#include "esphome/components/light/addressable_light_effect.h"

namespace esphome
{
  namespace ua_scars
  {

    class AddressableUaFlagLightEffect : public light::AddressableLightEffect
    {
    public:
      AddressableUaFlagLightEffect(const std::string &name);

      void apply(light::AddressableLight &it, const Color &current_color) override;

    protected:
      bool initial_run_{true};
      uint32_t last_run_{0};
      uint32_t speed_{20};
    };

  } // namespace ua_scars
} // namespace esphome
