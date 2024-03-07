#pragma once

// Thank you to Gaztoof's GMOD SDK for these offsets.
// I don't like your style of code, but I appreciate your work!

#ifdef _WIN64

#define OFFSET_VIEW_RENDER 0xC4
#define OFFSET_GLOBAL_VARIABLES 0x94
#define OFFSET_CLIENT_MODE 0x0
#define OFFSET_VIEWRENDER 0xC4

#define MODULE_PRESENT "gameoverlayrenderer"
#define PATTERN_PRESENT "\xFF\x15????\x8B\xF8\xEB\x1E"

#endif

#ifdef _WIN32

#define OFFSET_VIEW_RENDER 0xA6
#define OFFSET_GLOBAL_VARIABLES 0x59
#define OFFSET_CLIENT_MODE 0x5
#define OFFSET_VIEWRENDER 0xA6

#define MODULE_PRESENT "gameoverlayrenderer"
#define PATTERN_PRESENT "\xFF\x15????\x8B\xF0\x85\xFF"

#endif
