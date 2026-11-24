#include QMK_KEYBOARD_H
#include "version.h"
#define MOON_LED_LEVEL LED_LEVEL
#ifndef ZSA_SAFE_RANGE
#define ZSA_SAFE_RANGE SAFE_RANGE
#endif

enum custom_keycodes {
  RGB_SLD = ZSA_SAFE_RANGE,
  PLAY_EVANGELION,
};

// Opening melody excerpt transcribed from the score the user supplied.
// Durations use 1/64-beat units; playback sets the score's tempo of 76 BPM.
float evangelion_theme[][2] = SONG(
  M__NOTE(_DF5, 64), M__NOTE(_EF5, 64),
  M__NOTE(_F5, 48), M__NOTE(_EF5, 48), M__NOTE(_F5, 32),
  M__NOTE(_F5, 32), M__NOTE(_F5, 32), M__NOTE(_AF5, 32), M__NOTE(_G5, 32),
  M__NOTE(_F5, 16), M__NOTE(_EF5, 32), M__NOTE(_G5, 48), M__NOTE(_REST, 16),
  M__NOTE(_G5, 64), M__NOTE(_AF5, 64), M__NOTE(_BF5, 48),
  M__NOTE(_F5, 48), M__NOTE(_EF5, 32),
  M__NOTE(_AF5, 32), M__NOTE(_AF5, 32), M__NOTE(_G5, 32), M__NOTE(_AF5, 32),
  M__NOTE(_AF5, 48), M__NOTE(_BF5, 16), M__NOTE(_BF5, 141)
);

static bool evangelion_tempo_active = false;



const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [0] = LAYOUT_moonlander(
    KC_ESCAPE,      KC_1,           KC_2,           KC_3,           KC_4,           KC_5,           KC_RBRC,                                        KC_EQUAL,       KC_6,           KC_7,           KC_8,           KC_9,           KC_0,           KC_BSPC,        
    KC_TAB,         KC_Q,           KC_W,           KC_E,           KC_R,           KC_T,           KC_LBRC,                                        KC_MINUS,       KC_Y,           KC_U,           KC_I,           KC_O,           KC_P,           KC_QUOTE,       
    KC_BSPC,        KC_A,           KC_S,           KC_D,           KC_F,           KC_G,           LALT(LSFT(KC_LEFT_CTRL)),                                                                KC_DELETE,      KC_H,           KC_J,           KC_K,           KC_L,           KC_SCLN,        KC_ENTER,       
    KC_LEFT_SHIFT,  KC_Z,           KC_X,           KC_C,           KC_V,           KC_B,                                           KC_N,           KC_M,           KC_COMMA,       KC_DOT,         KC_SLASH,       KC_GRAVE,       
    KC_LEFT_CTRL,   KC_LEFT_GUI,    KC_LEFT_ALT,    KC_LEFT,        KC_RIGHT,       TG(2),                                                                                                          MU_TOGG,        KC_UP,          KC_DOWN,        KC_HOME,        KC_END,         KC_BSLS,        
    KC_SPACE,       KC_BSPC,        KC_DELETE,                      MO(1),          KC_BSPC,        KC_ENTER
  ),
  [1] = LAYOUT_moonlander(
    KC_NO,          KC_NO,          KC_NO,          KC_NO,          KC_NO,          KC_NO,          KC_NO,                                          KC_NO,          KC_NO,          KC_NO,          KC_NO,          KC_NO,          KC_NO,          PLAY_EVANGELION,
    KC_NO,          KC_NO,          KC_MS_UP,       KC_NO,          KC_NO,          KC_NO,          KC_NO,                                          KC_NO,          KC_NO,          KC_NO,          KC_NO,          KC_NO,          KC_NO,          KC_NO,          
    KC_NO,          KC_MS_LEFT,     KC_MS_DOWN,     KC_MS_RIGHT,    KC_NO,          KC_NO,          KC_NO,                                                                          KC_NO,          KC_NO,          KC_MS_WH_UP,    KC_NO,          KC_NO,          KC_NO,          KC_NO,          
    KC_NO,          KC_NO,          KC_NO,          KC_NO,          KC_NO,          KC_NO,                                          KC_MS_WH_LEFT,  KC_MS_WH_DOWN,  KC_MS_WH_RIGHT, KC_NO,          KC_NO,          KC_NO,          
    KC_ESCAPE,      KC_NO,          KC_NO,          KC_NO,          KC_NO,          KC_NO,                                                                                                          KC_TRANSPARENT, KC_NO,          KC_NO,          KC_NO,          KC_NO,          KC_ESCAPE,      
    KC_MS_BTN1,     KC_MS_BTN3,     KC_TRANSPARENT,                 KC_TRANSPARENT, KC_NO,          KC_NO
  ),
  [2] = LAYOUT_moonlander(
    KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT,                                 KC_NO,          KC_NO,          KC_NO,          KC_NO,          KC_NO,          KC_NO,          KC_NO,          
    KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT,                                 KC_NO,          KC_NO,          KC_NO,          KC_NO,          KC_NO,          KC_NO,          KC_NO,          
    KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT,                                                                 KC_NO,          KC_NO,          KC_NO,          KC_NO,          KC_NO,          KC_NO,          KC_NO,          
    KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT,                                 KC_NO,          KC_NO,          KC_NO,          KC_NO,          KC_NO,          KC_NO,          
    KC_TRANSPARENT, KC_NO,          KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT,                                                                                                 KC_NO,          KC_NO,          KC_NO,          KC_NO,          KC_NO,          KC_NO,          
    KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT,                 KC_NO,          KC_NO,          KC_NO
  ),
};





extern rgb_config_t rgb_matrix_config;

RGB hsv_to_rgb_with_value(HSV hsv) {
  RGB rgb = hsv_to_rgb( hsv );
  float f = (float)rgb_matrix_config.hsv.v / UINT8_MAX;
  return (RGB){ f * rgb.r, f * rgb.g, f * rgb.b };
}

void keyboard_post_init_user(void) {
  rgb_matrix_enable();
}

const uint8_t PROGMEM ledmap[][RGB_MATRIX_LED_COUNT][3] = {
    [0] = { {14,255,234}, {14,255,234}, {14,255,234}, {14,255,234}, {14,255,234}, {14,255,234}, {14,255,234}, {14,255,234}, {14,255,234}, {14,255,234}, {14,255,234}, {14,255,234}, {14,255,234}, {14,255,234}, {14,255,234}, {14,255,234}, {14,255,234}, {14,255,234}, {14,255,234}, {14,255,234}, {14,255,234}, {14,255,234}, {14,255,234}, {14,255,234}, {14,255,234}, {14,255,234}, {14,255,234}, {14,255,234}, {14,255,234}, {14,255,234}, {14,255,234}, {14,255,234}, {14,255,234}, {14,255,234}, {14,255,234}, {14,255,234}, {14,255,234}, {14,255,234}, {14,255,234}, {14,255,234}, {14,255,234}, {14,255,234}, {14,255,234}, {14,255,234}, {14,255,234}, {14,255,234}, {14,255,234}, {14,255,234}, {14,255,234}, {14,255,234}, {14,255,234}, {14,255,234}, {14,255,234}, {14,255,234}, {14,255,234}, {14,255,234}, {14,255,234}, {14,255,234}, {14,255,234}, {14,255,234}, {14,255,234}, {14,255,234}, {14,255,234}, {14,255,234}, {14,255,234}, {14,255,234}, {14,255,234}, {14,255,234}, {14,255,234}, {14,255,234}, {14,255,234}, {14,255,234} },

    [1] = { {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {173,247,215}, {0,0,0}, {0,0,0}, {173,247,215}, {0,0,0}, {0,0,0}, {0,0,0}, {173,247,215}, {173,247,215}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {173,247,215}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {61,69,96}, {61,69,96}, {61,69,96}, {252,255,255}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {173,247,215}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {173,247,215}, {0,0,0}, {0,0,0}, {0,0,0}, {173,247,215}, {173,247,215}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {173,247,215}, {0,0,0}, {0,0,0}, {0,0,0}, {61,69,96}, {61,69,96}, {61,69,96}, {252,255,255} },

    [2] = { {41,255,255}, {41,255,255}, {41,255,255}, {41,255,255}, {41,255,255}, {41,255,255}, {41,255,255}, {41,255,255}, {41,255,255}, {0,245,245}, {41,255,255}, {41,255,255}, {41,255,255}, {41,255,255}, {41,255,255}, {41,255,255}, {41,255,255}, {41,255,255}, {41,255,255}, {41,255,255}, {41,255,255}, {41,255,255}, {41,255,255}, {41,255,255}, {41,255,255}, {41,255,255}, {41,255,255}, {41,255,255}, {41,255,255}, {41,255,255}, {41,255,255}, {41,255,255}, {41,255,255}, {41,255,255}, {41,255,255}, {41,255,255}, {0,245,245}, {0,245,245}, {0,245,245}, {0,245,245}, {0,245,245}, {0,245,245}, {0,245,245}, {0,245,245}, {0,245,245}, {0,245,245}, {0,245,245}, {0,245,245}, {0,245,245}, {0,245,245}, {0,245,245}, {0,245,245}, {0,245,245}, {0,245,245}, {0,245,245}, {0,245,245}, {0,245,245}, {0,245,245}, {0,245,245}, {0,245,245}, {0,245,245}, {0,245,245}, {0,245,245}, {0,245,245}, {0,245,245}, {0,245,245}, {0,245,245}, {0,245,245}, {0,245,245}, {0,245,245}, {0,245,245}, {0,245,245} },

};

void set_layer_color(int layer) {
  for (int i = 0; i < RGB_MATRIX_LED_COUNT; i++) {
    HSV hsv = {
      .h = pgm_read_byte(&ledmap[layer][i][0]),
      .s = pgm_read_byte(&ledmap[layer][i][1]),
      .v = pgm_read_byte(&ledmap[layer][i][2]),
    };
    if (!hsv.h && !hsv.s && !hsv.v) {
        rgb_matrix_set_color( i, 0, 0, 0 );
    } else {
        RGB rgb = hsv_to_rgb_with_value(hsv);
        rgb_matrix_set_color(i, rgb.r, rgb.g, rgb.b);
    }
  }
}

bool rgb_matrix_indicators_user(void) {
  if (!audio_is_playing_melody() && evangelion_tempo_active) {
    audio_set_tempo(120);
    evangelion_tempo_active = false;
  }
  if (rawhid_state.rgb_control) {
      return false;
  }
  if (audio_is_playing_melody()) {
    uint16_t step = timer_read() / 100;
    uint8_t pulse = step % 32;
    if (pulse > 15) {
      pulse = 31 - pulse;
    }
    uint8_t value = 120 + pulse * 8;

    for (int i = 0; i < RGB_MATRIX_LED_COUNT; i++) {
      HSV hsv = {.s = 255, .v = value};
      switch ((i / 5 + step / 3) % 3) {
        case 0:
          hsv.h = 205;  // EVA purple
          break;
        case 1:
          hsv.h = 88;   // EVA green
          break;
        default:
          hsv.h = 222;  // violet accent
          break;
      }
      RGB rgb = hsv_to_rgb_with_value(hsv);
      rgb_matrix_set_color(i, rgb.r, rgb.g, rgb.b);
    }
    return true;
  }
  if (!keyboard_config.disable_layer_led) { 
    switch (biton32(layer_state)) {
      case 0:
        set_layer_color(0);
        break;
      case 1:
        set_layer_color(1);
        break;
      case 2:
        set_layer_color(2);
        break;
     default:
        if (rgb_matrix_get_flags() == LED_FLAG_NONE) {
          rgb_matrix_set_color_all(0, 0, 0);
        }
    }
  } else {
    if (rgb_matrix_get_flags() == LED_FLAG_NONE) {
      rgb_matrix_set_color_all(0, 0, 0);
    }
  }

  return true;
}




bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) {
  case QK_MODS ... QK_MODS_MAX:
    // Mouse and consumer keys (volume, media) with modifiers work inconsistently across operating systems,
    // this makes sure that modifiers are always applied to the key that was pressed.
    if (IS_MOUSE_KEYCODE(QK_MODS_GET_BASIC_KEYCODE(keycode))) {
      if (record->event.pressed) {
        add_mods(QK_MODS_GET_MODS(keycode));
        send_keyboard_report();
        wait_ms(2);
        register_code(QK_MODS_GET_BASIC_KEYCODE(keycode));
        return false;
      } else {
        wait_ms(2);
        del_mods(QK_MODS_GET_MODS(keycode));
      }
    }
    break;

    case RGB_SLD:
        if (rawhid_state.rgb_control) {
            return false;
        }
        if (record->event.pressed) {
            rgblight_mode(1);
        }
        return false;

    case PLAY_EVANGELION:
        if (record->event.pressed) {
            if (audio_is_playing_melody()) {
                audio_stop_all();
                audio_set_tempo(120);
                evangelion_tempo_active = false;
            } else {
                audio_set_tempo(76);
                evangelion_tempo_active = true;
                PLAY_SONG(evangelion_theme);
            }
        }
        return false;
  }
  return true;
}

