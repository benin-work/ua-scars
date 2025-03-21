#pragma once

#include <vector>
#include <map>
#include <ranges>
#include "esphome/components/light/esp_hsv_color.h"

namespace esphome
{
  namespace ua_scars_112
  {
    // Colors
    const auto FLAG_COLOR_YELLOW = light::ESPHSVColor(60, 255, 255).to_rgb();
    const auto FLAG_COLOR_BLUE = light::ESPHSVColor(160, 255, 255).to_rgb();

    typedef std::vector<uint8_t> Segment;

    // Liberty Letters for ВОЛЯ (VOLYA)
    const Segment LETTER_V{25, 24, 23, 22, 21, 20, 19, 18, 17, 16, 15, 14, 13, 11, 11, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30, 31, 32, 33, 34, 35, 36, 37, 38, 39, 40, 41, 42, 6, 9, 10, 11};
    const Segment LETTER_O{6, 7, 8, 40, 43, 44, 45, 69, 70, 73, 105, 106, 107, 108, 109, 110, 111, 112, 0, 1, 2, 3, 4, 5, 6, 7, 8, 40, 43, 44, 45};
    const Segment LETTER_L{
        46, 47, 48, 49, 50, 51, 52, 53, 54, 55, 56,
        57, 58, 59, 60, 61, 62, 63, 64, 65, 66, 67, 68};
    const Segment LETTER_YA{
        88, 89, 90, 91, 92, 93, 94, 95, 96, 97, 98, 99, 100,
        100, 99, 98, 97, 96, 95, 94, 93, 92, 91, 90, 89, 88,
        87, 86, 85, 84, 83, 82, 81, 80, 79, 78, 77, 76, 75, 74, 72, 71};

    const std::vector<Segment> word_VOLYA{LETTER_V, LETTER_O, LETTER_L, LETTER_YA};
    const auto VIEW_VOLYA = std::ranges::join_view(word_VOLYA);
    const Segment LETTERS_VOLYA(VIEW_VOLYA.begin(), VIEW_VOLYA.end());

    // Scars (Segments)
    const Segment s0{0, 1, 2, 3, 4, 5, 6, 7, 8};
    const Segment s1{6, 9, 10, 11, 12};
    const Segment s2{11, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25};
    const Segment s3{26, 27, 28, 29, 30, 31, 32, 33};
    const Segment s4{46, 34, 35, 36, 37, 15};
    const Segment s5{37, 38, 39, 40, 41, 42};
    const Segment s6{7, 40, 43, 44, 45};
    const Segment s7{46, 47, 48, 49, 50, 51, 52, 53, 54, 55, 56, 57};
    const Segment s8{56, 57, 58, 59, 60, 61, 62, 63, 64, 65, 66, 67, 68};
    const Segment s9{69, 70, 73, 106};
    const Segment s10{71, 72, 73, 74, 75, 76};
    const Segment s11{98, 76, 77, 78, 79};
    const Segment s12{80, 81, 82, 83, 84, 85, 86, 87};
    const Segment s13{88, 89, 90, 91, 92, 93, 94, 95, 96, 97, 98, 99, 100};
    const Segment s14{101, 102, 103, 104, 107};
    const Segment s15{105, 106, 107, 108, 109, 110, 111, 112};

    const std::vector<Segment> all_segments{s0, s1, s2, s3, s4, s5, s6, s7, s8, s9, s10, s11, s12, s13, s14, s15};

    // Vertical Segments for Water/Blood Drops Effect (reverse, top to bottom order)
    const Segment ws0{6, 5, 4, 3, 2, 1, 0};
    const Segment ws1{12, 11, 10, 9, 6, 7};
    const Segment ws2_1{16, 15, 14, 13, 11};
    const Segment ws2_2{25, 24, 23, 22, 21, 20, 19, 18, 17};
    const Segment ws3{26, 27, 28, 29, 30, 31, 32, 33};
    const Segment ws4{46, 34, 35, 36};
    const Segment ws5{37, 38, 39};
    const Segment ws6_1{40, 7};
    const Segment ws6_2{45, 44, 43, 40};
    const Segment ws7{57, 56, 55, 54, 53, 52, 51, 50, 49, 48, 47, 46};
    const Segment ws8{57, 58, 59, 60, 61, 62, 63, 64, 65, 66, 67};
    const Segment ws9_1{73, 106};
    const Segment ws9_2{69, 70};
    const Segment ws10{76, 75, 74};
    const Segment ws11{79, 78, 77};
    const Segment ws12{87, 86, 85, 84, 83, 82, 81, 80};
    const Segment ws13_1{88, 89, 90, 91, 92, 93, 94, 95, 96};
    const Segment ws13_2{97, 98, 99, 100};
    const Segment ws14{102, 103, 104, 106};
    const Segment ws15{107, 108, 109, 110, 111, 112};

    // water line views
    const auto wlv0 = std::ranges::join_view(std::vector<Segment>{ws2_2, ws2_1, ws1, ws0});
    const auto wlv1 = std::ranges::join_view(std::vector<Segment>{ws2_2, ws5, ws6_1, ws0});
    const auto wlv2 = std::ranges::join_view(std::vector<Segment>{ws3, ws4, ws2_1, ws1, ws0});
    const auto wlv3 = std::ranges::join_view(std::vector<Segment>{ws3, ws4, ws5, ws6_1, ws0});
    const auto wlv4 = std::ranges::join_view(std::vector<Segment>{ws7, ws4, ws2_1, ws1, ws0});
    const auto wlv5 = std::ranges::join_view(std::vector<Segment>{ws7, ws4, ws5, ws6_1, ws0});
    const auto wlv6 = std::ranges::join_view(std::vector<Segment>{ws8, ws11, ws10, ws9_1, ws15});
    const auto wlv7 = std::ranges::join_view(std::vector<Segment>{ws8, ws11, ws13_2, ws14, ws15});
    const auto wlv8 = std::ranges::join_view(std::vector<Segment>{ws13_1, ws10, ws9_1, ws15});
    const auto wlv9 = std::ranges::join_view(std::vector<Segment>{ws13_1, ws13_2, ws14, ws15});
    const auto wlv10 = std::ranges::join_view(std::vector<Segment>{ws7, ws6_2, ws6_1, ws0});
    const auto wlv11 = std::ranges::join_view(std::vector<Segment>{ws8, ws9_2, ws9_1, ws15});

    // water line views as vectors
    const std::vector<Segment> all_water_lines{
        Segment(wlv0.begin(), wlv0.end()),
        Segment(wlv1.begin(), wlv1.end()),
        Segment(wlv2.begin(), wlv2.end()),
        Segment(wlv3.begin(), wlv3.end()),
        Segment(wlv4.begin(), wlv4.end()),
        Segment(wlv5.begin(), wlv5.end()),
        Segment(wlv6.begin(), wlv6.end()),
        Segment(wlv7.begin(), wlv7.end()),
        Segment(wlv8.begin(), wlv8.end()),
        Segment(wlv9.begin(), wlv9.end()),
        Segment(wlv10.begin(), wlv10.end()),
        Segment(wlv11.begin(), wlv11.end())
    };
  } // namespace ua_scars
} // namespace esphome