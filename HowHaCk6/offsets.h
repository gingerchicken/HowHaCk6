#pragma once

// Thank you to Gaztoof's GMOD SDK for these offsets.
// I don't like your style of code, but I appreciate your work!

#ifdef _WIN64

#define OFFSET_VIEW_RENDER 0xC4
#define OFFSET_GLOBAL_VARIABLES 0x94
#define CLIENT_MODE_OFFSET 0x0

#endif

#ifdef _WIN32

#define OFFSET_VIEW_RENDER 0xA6
#define OFFSET_GLOBAL_VARIABLES 0x59
#define OFFSET_CLIENT_MODE 0x5

#endif