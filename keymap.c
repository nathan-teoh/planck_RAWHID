#include QMK_KEYBOARD_H
#include "muse.h"
#include "raw_hid.h"


extern keymap_config_t keymap_config;

enum planck_layers {
  _QWERTY,
  _LOWER,
  _FN,
  _RAISE,
  _ADJUST
};

enum planck_keycodes {
  QWERTY = SAFE_RANGE,
  FN,
  BACKLIT,
  EXT_PLV
};


enum {
  TD_ESC_CAPS=0,
  TD_WINKEY = 1,
  TD_ALTFOUR = 2
};

int layerselector = 0;  //variable to choose which layer for my encoder
int audioFlag =0; //variable to enable or disable beepign for encoder

//Tap Dance Definitions
qk_tap_dance_action_t tap_dance_actions[] = {
  //Tap once for Esc, twice for Caps Lock
  [TD_ESC_CAPS]  = ACTION_TAP_DANCE_DOUBLE(KC_ESC, KC_CAPS),
  [TD_WINKEY] = ACTION_TAP_DANCE_DOUBLE(KC_LGUI, LGUI(KC_E)),
  [TD_ALTFOUR] = ACTION_TAP_DANCE_DOUBLE(KC_F4, LALT(KC_F4))
// Other declarations would go here, separated by commas, if you have them
};


#define LOWER MO(_LOWER)
#define RAISE MO(_RAISE)
#define FN MO(_FN)

#define SHRP_LFT_ARROW LSFT(KC_COMM) //For <
#define SHRP_RGHT_ARROW LSFT(KC_DOT) //for >
#define TASKMGR C(S(KC_ESC)) //to start task manager in fn layer
#define UNTAB C(S(KC_T)) //to untab in chrome in fn layer


const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

/* Qwerty
 * ,-----------------------------------------------------------------------------------.
 * | Tab  |   Q  |   W  |   E  |   R  |   T  |   Y  |   U  |   I  |   O  |   P  | Bksp |
 * |------+------+------+------+------+-------------+------+------+------+------+------|
 * | Esc  |   A  |   S  |   D  |   F  |   G  |   H  |   J  |   K  |   L  |   ;  |  "   |
 * |------+------+------+------+------+------|------+------+------+------+------+------|
 * | Shift|   Z  |   X  |   C  |   V  |   B  |   N  |   M  |   ,  |   .  |   UP |Enter |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * | CTRL | GUI  |  FN  | ALT  |    SPACE   | Lower |Raise |   /  | LEFT | DOWN |Right |
 * `-----------------------------------------------------------------------------------'
 */
[_QWERTY] = LAYOUT_planck_grid(
    XXXXXXX,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_BSPC,
    TD(TD_ESC_CAPS),  KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOT,
    KC_LSFT, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, KC_ENT ,
    KC_LCTL, KC_LGUI, FN, KC_LALT, KC_SPC,   KC_SPC,  LOWER,  RAISE,   KC_LEFT, KC_DOWN, KC_UP,   KC_RGHT
),

/* Lower
 * ,-----------------------------------------------------------------------------------.
 * |      |   !  |   @  |   #  |   $  |   %  |   ^  |   &  |   *  |      |      | Bksp |
 * |------+------+------+------+------+-------------+------+------+------+------+------|
 * | Del  |   ~  |      |      |      |      |      |   -  |   +  |      |      |  |   |
 * |------+------+------+------+------+------|------+------+------+------+------+------|
 * |      |      |      |      |      |      |      |   _  |  =   | Home | End  |      |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |      |      |      |             |      |      |      |      |      |      |
 * `-----------------------------------------------------------------------------------'
 */
[_LOWER] = LAYOUT_planck_grid(
    _______, KC_EXLM, KC_AT,   KC_HASH, KC_DLR,  KC_PERC, KC_CIRC, KC_AMPR,    KC_ASTR,    _______, _______, KC_BSPC,
    KC_DEL,  KC_TILD,   XXXXXXX,   XXXXXXX,   XXXXXXX,   XXXXXXX,   XXXXXXX,   KC_MINS,    KC_PLUS,    _______, _______, KC_PIPE,
    _______, XXXXXXX,   XXXXXXX,   XXXXXXX,   XXXXXXX,  XXXXXXX,  XXXXXXX,  KC_UNDS, KC_EQL, KC_HOME, KC_END,  _______,
    _______, _______, KC_TILD, _______, _______, _______, _______, _______,    _______,    _______, _______, _______
),

/* FN
 * ,-----------------------------------------------------------------------------------.
 * |      |   F1 |   F2 |  F3  |      |      |      |      |      |      |      | Play |
 * |------+------+------+------+------+-------------+------+------+------+------+------|
 * |TSKMGR|  F4  |  F5  |  F6  |      |      |      |      |      |      |      |      |
 * |------+------+------+------+------+------|------+------+------+------+------+------|
 * |      |  F7  |  F8  |  F9  |      |      |      |      |      |      |      |      |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |      |      |      |             |      |      | Prev | Vol+ | Vol- | Next |
 * `-----------------------------------------------------------------------------------'
 */
[_FN] = LAYOUT_planck_grid(
    KC_MUTE, KC_F1, KC_F2, KC_F3, _______,  _______, _______, _______,    _______,    _______, _______,KC_MEDIA_PLAY_PAUSE,
    KC_TAB, TD(TD_ALTFOUR), KC_F5, KC_F6,_______,_______,_______,_______,_______,_______,_______,_______,
    TASKMGR, KC_F7, KC_F8, KC_F9,_______,_______,_______,_______,_______,_______,_______,  _______,
    UNTAB, _______, _______, _______, _______, _______, _______, _______,KC_MEDIA_PREV_TRACK,KC_VOLD, KC_VOLU, KC_MEDIA_NEXT_TRACK
),

/* Raise
 * ,-----------------------------------------------------------------------------------.
 * |  MUTE|   1  |   2  |   3  |   4  |   5  |   6  |   7  |   8  |   9  |   0  | Bksp |
 * |------+------+------+------+------+-------------+------+------+------+------+------|
 * | Del  |   (  |   )  |   {  |   }  |      |      |   4  |   5  |   6  |      |  \   |
 * |------+------+------+------+------+------|------+------+------+------+------+------|
 * |      |   <  |   >  |   [  |   ]  |      |      |   1  |   2  |   3  |      |      |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |      |      |      |             |      |      |      |      |      |      |
 * `-----------------------------------------------------------------------------------'
 */
[_RAISE] = LAYOUT_planck_grid(
    _______,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_P8,    KC_P9,    KC_P0,    KC_BSPC,
    KC_DEL,  KC_LPRN,   KC_RPRN,   KC_LCBR,   KC_RCBR,   XXXXXXX,   XXXXXXX,   KC_P4, KC_P5,  KC_P6, _______, KC_BSLS,
    _______, SHRP_LFT_ARROW,   SHRP_RGHT_ARROW,   KC_LBRC,   KC_RBRC,  XXXXXXX,  XXXXXXX,  KC_P1, KC_P2, KC_P3, _______, _______,
    _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,_______, KC_NLCK
),


/* Adjust (Lower + Raise)
 * ,-----------------------------------------------------------------------------------.
 * |      |      |      |      |      |      |      |      |      |      |      |  Del |
 * |------+------+------+------+------+-------------+------+------+------+------+------|
 * |      |      |      |Aud on|Audoff|AGnorm|AGszwap|Qwerty|      |      |      |      |
 * |------+------+------+------+------+------|------+------+------+------+------+------|
 * |      |Voice-|Voice+|Mus on|Musoff|MIDIon|MIDIof|      |      |      |      |RESET |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |      |      |      |      |             |      |      |      |      |CLICKY|
 * `-----------------------------------------------------------------------------------'
 */
[_ADJUST] = LAYOUT_planck_grid(
    _______, _______,   DEBUG,   RGB_TOG, RGB_MOD, RGB_HUI, RGB_HUD, RGB_SAI, RGB_SAD,  RGB_VAI, RGB_VAD, KC_DEL ,
    _______, _______, MU_MOD,  AU_ON,   AU_OFF,  AG_NORM, AG_SWAP, QWERTY,  _______,  _______,  _______,  _______,
    _______, MUV_DE,  MUV_IN,  MU_ON,   MU_OFF,  MI_ON,   MI_OFF,  TERM_ON, TERM_OFF, _______, _______, RESET,
    _______, _______, _______, _______, _______, _______, _______, _______, _______,  _______, _______, CLICKY_TOGGLE
),


};

#ifdef AUDIO_ENABLE
  float plover_song[][2]     = SONG(PLOVER_SOUND);
  float plover_gb_song[][2]  = SONG(PLOVER_GOODBYE_SOUND);
#endif

   void setHSV(int h, int s, int v){
    rgblight_sethsv(h, s, v);
  }


  void hidChooser(uint8_t *data){
    switch((int)data[0]){
      case 01: //change rgb mode
              break;
      case 2: setHSV((int)data[1],(int)data[2],(int)data[3]);//change rgb color. anim depends on HSV, not RGB.
              break;
      case 3: break;
    }
  }

 
  void raw_hid_receive(uint8_t *data, uint8_t length) {
    hidChooser(data); //hid controller. index 0 of data determines what type of function should be called
    raw_hid_send(data, length); //return for debugging purposes
  }

uint32_t layer_state_set_user(uint32_t state) {
  return update_tri_layer_state(state, _LOWER, _RAISE, _ADJUST);
}


bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) {
    case CLICKY_TOGGLE:
      if(record->event.pressed){
        if(audioFlag==0){//default is off, as clicky toggle is off by default
          audioFlag=1;//if we enable the toggle, enable clicky encoder flag
        }else{
          audioFlag=0;  //if it's enabled and clicked again, disable it
        }
      }
      break;

    case KC_LALT:   //for left alt and encoder
      if(record->event.pressed){  //if pressed
        register_code(KC_LALT);   //start left alt holdx
        layerselector = 1;
      }else{
        unregister_code(KC_LALT);   //stop the key hold
        layerselector = 0;
      }
      break;

      case KC_LCTL:
        if(record->event.pressed){
          register_code(KC_LCTL);
          layerselector=2;
        }else{
          unregister_code(KC_LCTL);
          layerselector = 0;
        }
        break;

      case RAISE:
      if (record->event.pressed){
        layer_on(_RAISE);
        layerselector=3;
      }else{
        layer_off(_RAISE);
        layerselector=0;
      }
      break;


    case QWERTY:
      if (record->event.pressed) {
        print("mode just switched to qwerty and this is a huge string\n");
        set_single_persistent_default_layer(_QWERTY);
      }
      return false;
      break;
    case BACKLIT:
      if (record->event.pressed) {
        register_code(KC_RSFT);
        #ifdef BACKLIGHT_ENABLE
          backlight_step();
        #endif
        #ifdef KEYBOARD_planck_rev5
          PORTE &= ~(1<<6);
        #endif
      } else {
        unregister_code(KC_RSFT);
        #ifdef KEYBOARD_planck_rev5
          PORTE |= (1<<6);
        #endif
      }
      return false;
      break;
  }
  return true;
}

bool muse_mode = false;
uint8_t last_muse_note = 0;
uint16_t muse_counter = 0;
uint8_t muse_offset = 70;
uint16_t muse_tempo = 50;

void encoder_update(bool clockwise) {
  uint16_t held_keycode_timer = timer_read();
  if (index == 0) { /* First encoder */
    switch(layerselector){
      case 1:   //left alt
          if (clockwise) {
            if(audioFlag==1){ //if the flag is enabled
              clicky_play();
            }
            tap_code(KC_LEFT);
          } else {
            if(audioFlag==1){ //if the flag is enabled
              clicky_play();
            }
            tap_code(KC_TAB);
          }
      break;

      case 2:   //left ctrl
        if (clockwise) {//turn to the left
          if(audioFlag==1){
            clicky_play();
          }
          tap_code(KC_TAB);
        } else {
          if(audioFlag==1){
            clicky_play();
          }
          tap_code(KC_TAB);
        }
        break;

      case 3: //raise
      if (clockwise) {
        clicky_freq_down();
        register_code(KC_VOLD);
        while(timer_elapsed(held_keycode_timer)< 10){
          //nothing
        }
        unregister_code(KC_VOLD);
        clicky_play();
      } else {
        clicky_freq_up();
        register_code(KC_VOLU);
        while(timer_elapsed(held_keycode_timer)<10){
          //nothing
        }
        unregister_code(KC_VOLU);
        clicky_play();
      }
      break;

        default:  //default, scroll
        if (clockwise) {
          if(audioFlag==1){
            clicky_play();
          }
            tap_code(KC_MS_WH_UP);
        } else {
          if(audioFlag==1){
            clicky_play();
          }
            tap_code(KC_MS_WH_DOWN);
        }
          break;
    }
  }
}


void dip_switch_update_user(uint8_t index, bool active) {
    switch (index) {
        case 0: {
            static bool play_sound = false;
            if (active) {
                #ifdef AUDIO_ENABLE
                if (play_sound) {
                  PLAY_SONG(plover_song);
                }
                #endif
                layer_on(_ADJUST);
            } else {
              #ifdef AUDIO_ENABLE
                if (play_sound) {
                  PLAY_SONG(plover_gb_song);
                }
                #endif
                layer_off(_ADJUST);
            }
            play_sound = true;
            break;
        }
        case 1:
            if (active) {
                muse_mode = true;
            } else {
                muse_mode = false;
            }
    }
}

void matrix_scan_user(void) {
#ifdef AUDIO_ENABLE
    if (muse_mode) {
        if (muse_counter == 0) {
            uint8_t muse_note = muse_offset + SCALE[muse_clock_pulse()];
            if (muse_note != last_muse_note) {
                stop_note(compute_freq_for_midi_note(last_muse_note));
                play_note(compute_freq_for_midi_note(muse_note), 0xF);
                last_muse_note = muse_note;
            }
        }
        muse_counter = (muse_counter + 1) % muse_tempo;
    } else {
        if (muse_counter) {
            stop_all_notes();
            muse_counter = 0;
        }
    }
#endif
}

bool music_mask_user(uint16_t keycode) {
  switch (keycode) {
    case RAISE:
    case LOWER:
      return false;
    default:
      return true;
  }


}
