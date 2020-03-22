#pragma once

#ifdef AUDIO_ENABLE
#define STARTUP_SONG SONG(PLANCK_SOUND)

#define MIDI_BASIC

#define ENCODER_RESOLUTION 4
#endif

/*
  Set any config.h overrides for your specific keymap here.
  See config.h options at https://docs.qmk.fm/#/config_options?id=the-configh-file
*/
#define ORYX_CONFIGURATOR
#define FIRMWARE_VERSION u8"Jwwap/Pp0g9"


#define PLANCK_EZ_USER_LEDS

#define PLANCK_EZ_LED_LOWER 2
#define PLANCK_EZ_LED_RAISE 3
#define PLANCK_EZ_LED_ADJUST 4
