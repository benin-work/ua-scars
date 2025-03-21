import esphome.codegen as cg
from esphome.components.light.effects import register_addressable_effect
from esphome.components.light.types import AddressableLightEffect
import esphome.config_validation as cv
from esphome.const import CONF_ID, CONF_NAME

ua_scars_ns = cg.esphome_ns.namespace("ua_scars")

UAScarsComponent = ua_scars_ns.class_("UAScarsComponent", cg.Component)

CONF_UA_SCARS_ID = "ua_scars_id"
CONFIG_SCHEMA = cv.Schema(
    {
        cv.GenerateID(): cv.declare_id(UAScarsComponent),
    }
).extend(cv.COMPONENT_SCHEMA)

AddressableUaFlagLightEffect = ua_scars_ns.class_("AddressableUaFlagLightEffect", AddressableLightEffect)
@register_addressable_effect("ua_flag", AddressableUaFlagLightEffect, "Flag UA", {})
async def addressable_ua_flag_light_effect_to_code(config, effect_id):
    return cg.new_Pvariable(effect_id, config[CONF_NAME])

AddressableLibertyFlashLightEffect = ua_scars_ns.class_("AddressableLibertyFlashLightEffect", AddressableLightEffect)
@register_addressable_effect("liberty-flash", AddressableLibertyFlashLightEffect, "Liberty FLash", {})
async def addressable_liberty_flash_light_effect_to_code(config, effect_id):
    return cg.new_Pvariable(effect_id, config[CONF_NAME])

AddressableLibertyHandwritingLightEffect = ua_scars_ns.class_("AddressableLibertyHandwritingLightEffect", AddressableLightEffect)
@register_addressable_effect("liberty-handwriting", AddressableLibertyHandwritingLightEffect, "Liberty Writing", {})
async def addressable_liberty_handwriting_light_effect_to_code(config, effect_id):
    return cg.new_Pvariable(effect_id, config[CONF_NAME])

AddressableScarsLightEffect = ua_scars_ns.class_("AddressableScarsLightEffect", AddressableLightEffect)
@register_addressable_effect("scars-ua", AddressableScarsLightEffect, "Scars UA", {})
async def addressable_scars_light_effect_to_code(config, effect_id):
    return cg.new_Pvariable(effect_id, config[CONF_NAME])

AddressableScarsFadeLightEffect = ua_scars_ns.class_("AddressableScarsFadeLightEffect", AddressableLightEffect)
@register_addressable_effect("scars-fade", AddressableScarsFadeLightEffect, "Scars Fading", {})
async def addressable_scars_fade_light_effect_to_code(config, effect_id):
    return cg.new_Pvariable(effect_id, config[CONF_NAME])

AddressableUaTwinkleLightEffect = ua_scars_ns.class_("AddressableUaTwinkleLightEffect", AddressableLightEffect)
@register_addressable_effect("twinkle-ua", AddressableUaTwinkleLightEffect, "Twinkle UA", {})
async def addressable_twinkle_ua_light_effect_to_code(config, effect_id):
    return cg.new_Pvariable(effect_id, config[CONF_NAME])

AddressableWaterDropsLightEffect = ua_scars_ns.class_("AddressableWaterDropsLightEffect", AddressableLightEffect)
@register_addressable_effect("waterdrops", AddressableWaterDropsLightEffect, "Waterdrops", {})
async def addressable_waterdrops_effect_to_code(config, effect_id):
    return cg.new_Pvariable(effect_id, config[CONF_NAME])
