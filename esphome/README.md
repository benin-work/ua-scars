# UA Scars firmware (ESPHome)

Firmware for the UA Scars light artwork - see the [project README](../README.md) for the full build story.

The firmware is built with [ESPHome](https://esphome.io/) on the **ESP-IDF** framework, targeting an **ESP32-C3**. It consists of:

- [ua-scars.yaml](ua-scars.yaml) - the ESPHome configuration. It drives the addressable LED strip via the ESP32 RMT peripheral (`esp32_rmt_led_strip`, GPIO8, GRB order), exposes the light to **Home Assistant** through the native API, serves a built-in **web UI** as a fallback, and handles a physical **push button on GPIO10** that cycles through the effects (the active effect index is stored in a restored global, so it survives power cycles).
- [ua_scars/](ua_scars/) - a custom ESPHome **external component** (C++). [\_\_init\_\_.py](ua_scars/__init__.py) registers seven custom addressable light effects (Flag UA, Liberty Flash, Liberty Writing, Scars UA, Scars Fading, Twinkle UA, Waterdrops); each effect is an `AddressableLightEffect` subclass in its own header. The effects render onto named LED segments (flag halves, scar lines, the letters of **ВОЛЯ**, water lines) defined in a hand-made LED index map.

## Two hardware versions

The artwork exists in two versions with different LED counts, and each has its own LED index map:

| | Version 1 | Version 2 (current) |
| --- | --- | --- |
| LEDs | 113 × WS2812B 5050 discrete LEDs | Addressable COB LED strip, 300 LEDs |
| LED index map | [ua_scars/tryzub_112.h](ua_scars/tryzub_112.h) (namespace `ua_scars_112`) | [ua_scars/tryzub.h](ua_scars/tryzub.h) (namespace `ua_scars`) |
| `num_leds` in yaml | 113 | 300 |

The configuration and effects in this folder currently target **version 2**: all effect headers include `tryzub.h`, and [ua-scars.yaml](ua-scars.yaml) sets `num_leds: 300`. The version-1 map is kept in `tryzub_112.h` for reference; to build firmware for the 113-LED piece, point the effects at that map (or copy its segment definitions into `tryzub.h`) and set `num_leds: 113`.

## Building and flashing

Create a `secrets.yaml` with your Wi-Fi credentials (see [secrets.yaml.example](secrets.yaml.example)):

```yaml
wifi_ssid: "WiFi-SSID"
wifi_password: "Password123"
```

Compile only:

```
esphome compile .\ua-scars.yaml
```

Compile and flash over USB (adjust the COM port):

```
esphome run .\ua-scars.yaml --no-logs --device COM5
```

After the first flash, updates can be pushed over the air (OTA) via Wi-Fi. If the device can't join Wi-Fi, it starts a fallback hotspot (`Ua-Scars`) with a captive portal for reconfiguration.
