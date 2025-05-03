#define WIN32_LEAN_AND_MEAN

#include "../include/ini.hpp"
#include <plugin.h>
#include <string>
#include <windows.h>

extern CIniReader gConfig;

// Customize these here
#define MODNAME "$Audio-LEAR-cars-com"
#define MODNAME_EXT MODNAME ".asi"

// Popup
#define WINDOW_HEIGHT 250
#define WINDOW_WIDTH 450
#define LONG_MESSAGE "This is a test long message. This can be customized inside 'pch.h' file."
#define BUTTON1_TEXT "Button 1"
#define BUTTON2_TEXT "Button 2"
#define BUTTON3_TEXT "Button 3"

#define BUTTON1_LINK "https://www.lear-cars.com/"
#define BUTTON2_LINK "https://www.lear-cars.com/"
#define BUTTON3_LINK "https://www.lear-cars.com/"