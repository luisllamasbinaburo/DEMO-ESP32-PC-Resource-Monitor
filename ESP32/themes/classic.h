#pragma once

uint32_t APP_BACKGROUND = 0x0005;
uint32_t WIDGET_BACKGROUND = 0x0000;

uint32_t FOREGROUND = 0xFFFF;
uint32_t FOREGROUND_75 = 0xDF3D;
uint32_t FOREGROUND_50 = 0xBE9B;
uint32_t FOREGROUND_25 = 0x95D9;

ESP_Color::Palette<uint16_t> barPalette(ESP_Color::Palettes64::JET_64, 64);
ESP_Color::Palette<uint16_t> circularPalette(ESP_Color::Palettes64::COOL_WARM_64, 64);