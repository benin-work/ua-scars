#pragma once

#include "esphome/core/log.h"
#include "esphome/core/component.h"

namespace esphome {
namespace ua_scars {

class UAScarsComponent : public Component {
 public:
  void dump_config() override { ESP_LOGCONFIG("ua_scars.component", "UA Scars component"); };
};

}  // namespace ua_scars
}  // namespace esphome