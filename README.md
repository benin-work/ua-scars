# UA Scars

**A Ukrainian trident made of scars, light, and a lot of trial and error.**

I wanted to light up and animate one piece of an art. The design is based on the Ukrainian **Tryzub** (trident). Its scars can light up in different colors and sequences - including an animation that reveals **ВОЛЯ** (*Volia*, “freedom”).

<p align="center"><img src="docs/results/PXL_20250321_220857271.jpg" alt="Finished artwork illuminated blue and yellow" width="31%"> <img src="docs/results/PXL_20250321_221127998.jpg" alt="Finished artwork illuminated red" width="31%">
<img src="docs/results/PXL_20261104_194120693.jpg" alt="Finished artwork with blue and yellow light" width="31%">
</p>


And the animations in action:

<p align="center">
<img src="docs/results/video/
PXL_20250322_021350717_FHD.webp" alt="Animation of the trident scars glowing in red" width="46%">
<img src="docs/results/video/PXL_20261104_194422570_FHD.webp" alt="Animation of the trident scars glowing in red" width="46%">
</p>

It looks way better in person. The colors are much more vibrant and saturated, and the details are noticeably sharper. The camera really doesn't do it justice.

## How I built it

### 0. Idea

I saw a piece of wall art one day and thought, "What if I could bring this thing to life?"
So I decided to turn a static picture into an animated LED wall decoration.
<p align="center"><img src="docs/idea_source.jpg" alt="Initial graphic concept" width="32%"></p>

### 1. Turned the sketch into cut lines

Started with a trident illustration, vectorized it, and used the same geometry for the laser-cut mask and the markings on the backing and diffuser. That alignment is what makes the thin glowing cuts work. The full laser project is included in this repository - see [Vector source (LightBurn)](#vector-source-lightburn).

<p align="center"><img src="docs/process/PXL_20250315_195836458.jpg" alt="Flying Bear Lazerman marking black foam board" width="46%"> <img src="docs/process/PXL_20250316_210702443.jpg" alt="Laser cut and marked pattern" width="46%"></p>

### 2. Marked the backing and laid out the LEDs

The 5 W laser wasn't just for cutting. I also used it to mark the LED positions on the hardboard and to add fine alignment marks to the salvaged TV diffuser. I attached the LED strip **beside the openings, not directly underneath them**. The offset helps keep individual LED chips out of direct view.

<p align="center">
<img src="docs/process/PXL_20250317_173046491.jpg" alt="Laser-marked fiberboard backing" width="32%">
<img src="docs/process/PXL_20250317_210129848.jpg" alt="LED strip installation begins" width="32%">
<img src="docs/process/PXL_20250317_220743885.jpg" alt="Installed trident LED strip" width="32%">
</p>


### 3. Power in

<p align="center">
<img src="docs/process/PXL_20250319_190038151.jpg" alt="Cable routing through frame" width="46%">
<img src="docs/process/PXL_20250319_190900555.jpg" alt="Cable routing through frame" width="46%">
<img src="docs/process/PXL_20250319_190918416.jpg" alt="Close-up of wire routing" width="46%">
<img src="docs/process/PXL_20250318_233820730.jpg" alt="Installed trident LED strip" width="46%">
</p>

### 4. Testing the light before closing it up

Checked the addressable strip and different colors while everything was still accessible. Light is spread by the diffuser, while the front mask defines the visible scar lines.

<p align="center">
<img src="docs/process/PXL_20250318_233736029.jpg" alt="Blue and yellow LED test" width="46%">
<img src="docs/process/PXL_20250318_233729779.jpg" alt="Blue and yellow LED test" width="46%">
</p>


### 5. Cut the scars into black foam board

The laser cut the complete pattern. The clean and narrow cuts. The foam-board mask sits(glued) **on top of the diffuser**, which touches the LED strip. The LEDs remain offset from the visible cuts.

<p align="center">
<img src="docs/process/PXL_20250319_215247715.jpg" alt="Laser-cut foam board offcuts and negative space" width="46%"><img src="docs/process/PXL_20250425_143430352.jpg" alt="Unlit completed artwork" width="46%">
</p>


### 6. Stacked the layers and framed it

From back to front: **hardboard + mounted LEDs → reused TV diffuser → black laser-cut foam-board mask → glass or plexiglass**. Then everything went into the 11 × 17 in frame.

<p align="center">
<img src="docs/process/PXL_20250319_201608046.jpg" alt="Frame, diffuser and mask components" width="32%">
<img src="docs/process/PXL_20261104_211950911.jpg" alt="Rear of finished frame" width="32%">
<img src="docs/process/PXL_20250321_221629657.jpg" alt="Rear of finished frame" width="32%">
</p>

### 7. Led mappings

Initial drawing to put led strips in the order of sequence and the leds mapping ID's for effects in code.

<p align="center">
<img src="docs/scars_led_initial_plan.png" alt="Initial idea of led 
strip parts order" width="46%">
<img src="docs/scars_led_indexing.jpg" alt="Final indexing" width="46%">
</p>


## Control & animations

The first firmware was written in **C++ with ESP-IDF**. I later switched to **ESPHome** so the artwork could be controlled directly from **Home Assistant**: **effect selection, color, and brightness**. The animations run on the ESP32-C3 itself.

### Firmware

The firmware lives in [esphome/](esphome/):

- [ua-scars.yaml](esphome/ua-scars.yaml) - the ESPHome configuration (ESP-IDF framework). It drives the WS2812 strip through the ESP32 RMT peripheral (`esp32_rmt_led_strip`, GPIO8, GRB order) and exposes the light to Home Assistant via the native API, plus a built-in web server as a fallback UI. A physical push button on GPIO10 cycles through the effects, and the last selected effect is restored after a power cycle.
- [esphome/ua_scars/](esphome/ua_scars/) - a custom **external component** written in C++. [\_\_init\_\_.py](esphome/ua_scars/__init__.py) registers the custom effects with ESPHome's code generator, and each effect is an `AddressableLightEffect` subclass in its own header. [tryzub.h](esphome/ua_scars/tryzub.h) is the heart of it: the hand-made LED index map that groups the LEDs into named segments - the blue/yellow flag halves, each scar line, the letters of **ВОЛЯ**, and the vertical "water" lines (see the LED mapping diagrams above). The map for the first 113-LED build is kept in [tryzub_112.h](esphome/ua_scars/tryzub_112.h) - see [Project versions](#project-versions) below.

To build and flash:

```
esphome run ua-scars.yaml --device COM5
```

### Effects

Seven custom effects, plus a few stock ESPHome ones:

| Effect | What it does |
| --- | --- |
| **Flag UA** | Static Ukrainian flag - the top half of the trident glows blue, the bottom half yellow |
| **Liberty Flash** | Flashes the letters **В-О-Л-Я** one after another, each fading out before the next appears |
| **Liberty Writing** | "Handwrites" ВОЛЯ - a short bright dot runs along the letter strokes LED by LED, leaving a fading trail, then pauses and starts over |
| **Scars UA** | Traces a randomly picked scar segment end to end (in a random direction), alternating blue and yellow strokes |
| **Scars Fading** | Same scar-tracing motion, but in the color selected in Home Assistant and with a fade-out trail |
| **Twinkle UA** | Random twinkles across the whole piece in blue and yellow |
| **Waterdrops** | Drops of the selected color run down the predefined vertical lines of the trident, fading as they fall |
| Rainbow, Fireworks, Random Twinkle | Stock ESPHome addressable effects, kept for fun |

## Vector source (LightBurn)

The complete laser project is in [ua_scars.lbrn2](vector/ua_scars.lbrn2) - a LightBurn 2 (`.lbrn2`) project file, created with LightBurn 1.2.04. Keeping everything in a single project is what guarantees the alignment between the layers: the mask cuts, the LED positions, and the diffuser marks all share the same origin and geometry.

<p align="center"><img src="docs/light_burn_project.png" alt="LightBurn project showing the layered trident geometry and cut settings" width="90%"></p>

The project is organized into layers:

| Layer | Settings | Purpose |
| --- | --- | --- |
| `blue`, `yellow` | 50% power, 3000 mm/min, line mode | The trident scar geometry, split into the blue and yellow halves of the design |
| `box` | 50% power, 3000 mm/min, line mode | Outer boundary matching the frame, for positioning and alignment |
| `debug` | 100% power, 700–800 mm/min | Small rectangular window to have access to the usb-c of esp32
| `debug` | 100% power, 700–800 mm/min | Small test shape (and hexagon) for dialing in cut settings on scrap material |

Open the file in [LightBurn](https://lightburnsoftware.com/) to view or re-cut the design. The power and speed values are tuned for the 5 W Flying Bear Lazerman - adjust them for a different laser or material.

## Parts & tools

| Part | What I used |
| --- | --- |
| Frame and backing | 11 × 17 in photo frame with hardboard (fiberboard) back panel |
| Front mask | Black foam board (paper-faced foam core), laser-cut |
| Diffuser | Reused diffuser sheet from an old TV |
| LEDs | **113 × WS2812B 5050**, individually addressable, 5 V |
| Controller | **ESP32-C3 Mini** |
| Laser | **Flying Bear Lazerman, 5 W** |
| Cover | Original frame glass or plexiglass, depending on the build |
| Software | Started with **ESP-IDF / C++**, later moved to **ESPHome** for Home Assistant integration |

## Project versions

There are two versions of this project:

- **Version 1 (this document)** - built with **113 × WS2812B 5050** individually addressable LEDs. Its LED index map is [tryzub_112.h](esphome/ua_scars/tryzub_112.h).
- **Version 2 (latest)** - rebuilt with an addressable **COB LED strip** of **300 LEDs** for a smoother, more continuous light line. Its LED index map is [tryzub.h](esphome/ua_scars/tryzub.h), which the current [ESPHome configuration](esphome/ua-scars.yaml) uses (`num_leds: 300`). This version will be described in a separate document.

---

*DIY art project, March–April 2025. Built around a very simple idea: the scars stay visible, and the light gives them motion.*
