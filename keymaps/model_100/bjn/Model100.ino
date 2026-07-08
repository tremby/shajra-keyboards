// vim: vts=26,23,28,39,25,23,20,17,17 noet sw=0 sts=-1 ts=16
// Copyright 2016-2022 Keyboardio, inc. <jesse@keyboard.io>
// See "LICENSE" for license details

/**
 * These #include directives pull in the Kaleidoscope firmware core,
 * as well as the Kaleidoscope plugins we use in the Model 100's firmware
 */

// The Kaleidoscope core
#include "Kaleidoscope.h"

// Support for communicating with the host via a simple Serial protocol
#include "Kaleidoscope-FocusSerial.h"

// Support for querying the firmware version via Focus
#include "Kaleidoscope-FirmwareVersion.h"

// Support for keys that move the mouse
#include "Kaleidoscope-MouseKeys.h"

// Support for macros
#include "Kaleidoscope-Macros.h"

// Support for controlling the keyboard's LEDs
#include "Kaleidoscope-LEDControl.h"

// Support for "Numpad" mode, which is mostly just the Numpad specific LED mode
#include "Kaleidoscope-NumPad.h"

// Support for an LED mode that lights up the keys as you press them
#include "Kaleidoscope-LED-Stalker.h"

// Support for turning the LEDs off after a certain amount of time
#include "Kaleidoscope-IdleLEDs.h"

// Support for setting and saving the default LED mode
#include "Kaleidoscope-DefaultLEDModeConfig.h"

// Support for host power management (suspend & wakeup)
#include "Kaleidoscope-HostPowerManagement.h"

// Support for magic combos (key chords that trigger an action)
#include "Kaleidoscope-MagicCombo.h"

// Support for USB quirks, like changing the key state report protocol
#include "Kaleidoscope-USB-Quirks.h"

// Support for secondary actions on keys
#include "Kaleidoscope-Qukeys.h"

// Support for one-shot modifiers and layer keys
#include "Kaleidoscope-OneShot.h"
#include "Kaleidoscope-Escape-OneShot.h"

// Support for dynamic, Chrysalis-editable macros
#include "Kaleidoscope-DynamicMacros.h"

// Support for SpaceCadet keys
#include "Kaleidoscope-SpaceCadet.h"

// Support for the GeminiPR Stenography protocol
#include "Kaleidoscope-Steno.h"

// Digital Rain LED plugin
#include <Kaleidoscope-LEDEffect-DigitalRain.h>

// Turbo plugin
#include <Kaleidoscope-Turbo.h>

/** This 'enum' is a list of all the macros used by the Model 100's firmware
  * The names aren't particularly important. What is important is that each
  * is unique.
  *
  * These are the names of your macros. They'll be used in two places.
  * The first is in your keymap definitions. There, you'll use the syntax
  * `M(MACRO_NAME)` to mark a specific keymap position as triggering `MACRO_NAME`
  *
  * The second usage is in the 'switch' statement in the `macroAction` function.
  * That switch statement actually runs the code associated with a macro when
  * a macro key is pressed.
  */

enum {
  MACRO_VERSION_INFO,
};


/** The Model 100's key layouts are defined as 'keymaps'. By default, there are three
  * keymaps: The standard QWERTY keymap, the "Function layer" keymap and the "Numpad"
  * keymap.
  *
  * Each keymap is defined as a list using the 'KEYMAP_STACKED' macro, built
  * of first the left hand's layout, followed by the right hand's layout.
  *
  * Keymaps typically consist mostly of `Key_` definitions. There are many, many keys
  * defined as part of the USB HID Keyboard specification. You can find the names
  * (if not yet the explanations) for all the standard `Key_` defintions offered by
  * Kaleidoscope in these files:
  *    https://github.com/keyboardio/Kaleidoscope/blob/master/src/kaleidoscope/key_defs/keyboard.h
  *    https://github.com/keyboardio/Kaleidoscope/blob/master/src/kaleidoscope/key_defs/consumerctl.h
  *    https://github.com/keyboardio/Kaleidoscope/blob/master/src/kaleidoscope/key_defs/sysctl.h
  *    https://github.com/keyboardio/Kaleidoscope/blob/master/src/kaleidoscope/key_defs/keymaps.h
  *
  * Additional things that should be documented here include
  *   using ___ to let keypresses fall through to the previously active layer
  *   using XXX to mark a keyswitch as 'blocked' on this layer
  *   using ShiftToLayer() and LockLayer() keys to change the active keymap.
  *   keeping NUM and FN consistent and accessible on all layers
  *
  * The PROG key is special, since it is how you indicate to the board that you
  * want to flash the firmware. However, it can be remapped to a regular key.
  * When the keyboard boots, it first looks to see whether the PROG key is held
  * down; if it is, it simply awaits further flashing instructions. If it is
  * not, it continues loading the rest of the firmware and the keyboard
  * functions normally, with whatever binding you have set to PROG. More detail
  * here: https://community.keyboard.io/t/how-the-prog-key-gets-you-into-the-bootloader/506/8
  *
  * The "keymaps" data structure is a list of the keymaps compiled into the firmware.
  * The order of keymaps in the list is important, as the ShiftToLayer(#) and LockLayer(#)
  * macros switch to key layers based on this list.
  *
  *

  * A key defined as 'ShiftToLayer(FUNCTION)' will switch to FUNCTION while held.
  * Similarly, a key defined as 'LockLayer(NUMPAD)' will switch to NUMPAD when tapped.
  */

/**
  * Layers are "0-indexed" -- That is the first one is layer 0. The second one is layer 1.
  * The third one is layer 2.
  * This 'enum' lets us use names like QWERTY, FUNCTION, and NUMPAD in place of
  * the numbers 0, 1 and 2.
  *
  */

enum {
  PRIMARY,
  FUNCTION,
  DOUBLE_FUNCTION,
  NUMPAD,
};  // layers


/**
  * To change your keyboard's layout from QWERTY to DVORAK or COLEMAK, comment out the line
  *
  * #define PRIMARY_KEYMAP_QWERTY
  *
  * by changing it to
  *
  * // #define PRIMARY_KEYMAP_QWERTY
  *
  * Then uncomment the line corresponding to the layout you want to use.
  *
  */



/* This comment temporarily turns off astyle's indent enforcement
 *   so we can make the keymaps actually resemble the physical key layout better
 */
// clang-format off

KEYMAPS(
  [PRIMARY] = KEYMAP_STACKED(

/* left */
Key_Pause,	Key_1,	Key_2,	Key_3,	Key_4,	Key_5,	Key_LEDEffectNext,
Key_Backtick,	Key_Quote,	Key_Comma,	Key_Period,	Key_P,	Key_Y,	Key_Tab,
Key_PageUp,	Key_A,	Key_O,	Key_E,	Key_U,	Key_I,	/* no-key */
Key_PageDown,	Key_Semicolon,	Key_Q,	Key_J,	Key_K,	Key_X,	Key_Escape,
			/* thumbs */	Key_LeftShift,	Key_Backspace,	Key_LeftControl,	Key_LeftGui,
			/* palm */	Key_KeymapNext_Momentary,


/* right */
	Key_Execute,	Key_6,	Key_7,	Key_8,	Key_9,	Key_0,	LockLayer(NUMPAD),
	Key_Enter,	Key_F,	Key_G,	Key_C,	Key_R,	Key_L,	Key_Slash,
	/* no-key */	Key_D,	Key_H,	Key_T,	Key_N,	Key_S,	Key_Minus,
	Key_RightAlt,	Key_B,	Key_M,	Key_W,	Key_V,	Key_Z,	Key_Equals,
Key_LeftAlt,	Key_RightControl,	Key_Spacebar,	Key_RightShift, /* thumbs */
			Key_KeymapNext_Momentary /* palm */
  ),

  [FUNCTION] = KEYMAP_STACKED(

/* left */
Key_ScrollLock,	Key_F1,	Key_F2,	Key_F3,	Key_F4,	Key_F5,	Key_F11,
___,	___,	Key_mouseBtnL,	Key_mouseUp,	Key_mouseBtnR,	Key_mouseWarpEnd,	Key_mouseWarpNE,
Key_Home,	___,	Key_mouseL,	Key_mouseDn,	Key_mouseR,	Key_mouseWarpNW,	/* no-key */
Key_End,	Key_PrintScreen,	Key_Insert,	Key_DownArrow,	Key_UpArrow,	Key_mouseWarpSW,	Key_mouseWarpSE,
			/* thumbs */	___,	Key_Delete,	___,	___,
			/* palm */	Key_KeymapNext_Momentary,

/* right */
	Key_F12,	Key_F6,	Key_F7,	Key_F8,	Key_F9,	Key_F10,	Key_CapsLock,
	___,	Key_PageDown,	Key_LeftCurlyBracket,	Key_UpArrow,	Key_RightCurlyBracket,	Key_RightArrow,	Key_Backslash,
	/* no-key */	___,	Key_LeftArrow,	Key_DownArrow,	Key_RightArrow,	___,	Key_Pipe,
	___,	Key_PageUp,	Key_LeftBracket,	___,	Key_RightBracket,	___,	___,
___,	___,	___,	___, /* thumbs */
			Key_KeymapNext_Momentary /* palm */
  ),

  [DOUBLE_FUNCTION] = KEYMAP_STACKED(

/* left */
Key_Turbo,	Key_F21,	Key_F22,	Key_F13,	Key_F14,	Key_F15,	Key_F23,
___,	Consumer_Stop,	Consumer_ScanPreviousTrack,	Consumer_ScanNextTrack,	Consumer_PlaySlashPause,	___,	___,
Consumer_VolumeIncrement,	___,	___,	___,	___,	___,	/* no-key */
Consumer_VolumeDecrement,	___,	___,	___,	___,	___,	___,
			/* thumbs */	___,	___,	___,	___,
			/* palm */	___,

/* right */
	Key_F24,	Key_F16,	Key_F17,	Key_F18,	Key_F19,	Key_F20,	___,
	___,	___,	___,	___,	___,	LGUI(LALT(Key_L)),	___,
	/* no-key */	Consumer_Mute,	___,	___,	___,	System_Sleep,	___,
	___,	___,	Consumer_StartOrStopMicrophoneCapture,	___,	___,	___,	___,
___,	___,	___,	___, /* thumbs */
			___ /* palm */
  ),

  [NUMPAD] = KEYMAP_STACKED(

/* left */
___,	XXX,	XXX,	XXX,	XXX,	XXX,	XXX,
XXX,	XXX,	XXX,	Key_UpArrow,	XXX,	XXX,	Key_Tab,
___,	XXX,	Key_LeftArrow,	Key_DownArrow,	Key_RightArrow,	LSHIFT(Key_Tab),	/* no-key */
___,	XXX,	XXX,	Key_DownArrow,	Key_UpArrow,	XXX,	___,
			/* thumbs */	___,	___,	___,	___,
			/* palm */	___,

/* right */
	M(MACRO_VERSION_INFO),	XXX,	Key_KeypadNumLock,	Key_KeypadDivide,	Key_KeypadMultiply,	Key_KeypadSubtract,	___,
	___,	XXX,	Key_Keypad7,	Key_Keypad8,	Key_Keypad9,	Key_KeypadAdd,	___,
	/* no-key */	Key_KeypadDot,	Key_Keypad4,	Key_Keypad5,	Key_Keypad6,	Key_KeypadAdd,	___,
	___,	XXX,	Key_Keypad1,	Key_Keypad2,	Key_Keypad3,	Key_KeypadEnter,	___,
XXX,	XXX,	Key_Keypad0,	Key_KeypadDot, /* thumbs */
			___ /* palm */
  )
) // KEYMAPS(

/* Re-enable astyle's indent enforcement */
// clang-format on

/** versionInfoMacro handles the 'firmware version info' macro
 *  When a key bound to the macro is pressed, this macro
 *  prints out the firmware build information as virtual keystrokes
 */

static void versionInfoMacro(uint8_t key_state) {
  if (keyToggledOn(key_state)) {
    Macros.type(PSTR("Keyboardio Model 100 - Firmware version "));
    Macros.type(PSTR(KALEIDOSCOPE_FIRMWARE_VERSION));
  }
}

/** macroAction dispatches keymap events that are tied to a macro
    to that macro. It takes two uint8_t parameters.

    The first is the macro being called (the entry in the 'enum' earlier in this file).
    The second is the state of the keyswitch. You can use the keyswitch state to figure out
    if the key has just been toggled on, is currently pressed or if it's just been released.

    The 'switch' statement should have a 'case' for each entry of the macro enum.
    Each 'case' statement should call out to a function to handle the macro in question.

 */

const macro_t *macroAction(uint8_t macro_id, KeyEvent &event) {
  switch (macro_id) {

  case MACRO_VERSION_INFO:
    versionInfoMacro(event.state);
    break;

  }
  return MACRO_NONE;
}


/** toggleLedsOnSuspendResume toggles the LEDs off when the host goes to sleep,
 * and turns them back on when it wakes up.
 */
void toggleLedsOnSuspendResume(kaleidoscope::plugin::HostPowerManagement::Event event) {
  switch (event) {
  case kaleidoscope::plugin::HostPowerManagement::Suspend:
    LEDControl.disable();
    break;
  case kaleidoscope::plugin::HostPowerManagement::Resume:
    LEDControl.enable();
    break;
  case kaleidoscope::plugin::HostPowerManagement::Sleep:
    break;
  }
}

/** hostPowerManagementEventHandler dispatches power management events (suspend,
 * resume, and sleep) to other functions that perform action based on these
 * events.
 */
void hostPowerManagementEventHandler(kaleidoscope::plugin::HostPowerManagement::Event event) {
  toggleLedsOnSuspendResume(event);
}

/** This 'enum' is a list of all the magic combos used by the Model 100's
 * firmware The names aren't particularly important. What is important is that
 * each is unique.
 *
 * These are the names of your magic combos. They will be used by the
 * `USE_MAGIC_COMBOS` call below.
 */
enum {
  // Toggle between Boot (6-key rollover; for BIOSes and early boot) and NKRO
  // mode.
  COMBO_TOGGLE_NKRO_MODE
};

/** Wrappers, to be used by MagicCombo. **/

/**
 * This simply toggles the keyboard protocol via USBQuirks, and wraps it within
 * a function with an unused argument, to match what MagicCombo expects.
 */
static void toggleKeyboardProtocol(uint8_t combo_index) {
  USBQuirks.toggleKeyboardProtocol();
}


/** Magic combo list, a list of key combo and action pairs the firmware should
 * recognise.
 */
USE_MAGIC_COMBOS({.action = toggleKeyboardProtocol,
                  // Left Fn + Esc + Shift
                  .keys = {R3C6, R2C6, R3C7}});

// First, tell Kaleidoscope which plugins you want to use.
// The order can be important. For example, LED effects are
// added in the order they're listed here.
KALEIDOSCOPE_INIT_PLUGINS(
  // SpaceCadet can turn your shifts into parens on tap, while keeping them as
  // Shifts when held. SpaceCadetConfig lets Chrysalis configure some aspects of
  // the plugin.
  SpaceCadet,
  SpaceCadetConfig,

  // Focus allows bi-directional communication with the host, and is the
  // interface through which the keymap in EEPROM can be edited.
  Focus,

  // LEDControl provides support for other LED modes
  LEDControl,

  // We start with the LED effect that turns off all the LEDs.
  LEDOff,

  // The stalker effect lights up the keys you've pressed recently
  StalkerEffect,

  // Digital Rain
  LEDDigitalRainEffect,

  // Turbo
  Turbo,

  // The numpad plugin is responsible for lighting up the 'numpad' mode
  // with a custom LED effect
  NumPad,

  // The macros plugin adds support for macros
  Macros,

  // The MouseKeys plugin lets you add keys to your keymap which move the mouse.
  MouseKeys,

  // The HostPowerManagement plugin allows us to turn LEDs off when then host
  // goes to sleep, and resume them when it wakes up.
  HostPowerManagement,

  // The MagicCombo plugin lets you use key combinations to trigger custom
  // actions - a bit like Macros, but triggered by pressing multiple keys at the
  // same time.
  MagicCombo,

  // The USBQuirks plugin lets you do some things with USB that we aren't
  // comfortable - or able - to do automatically, but can be useful
  // nevertheless. Such as toggling the key report protocol between Boot (used
  // by BIOSes) and Report (NKRO).
  USBQuirks,

  // The Qukeys plugin enables the "Secondary action" functionality in
  // Chrysalis. Keys with secondary actions will have their primary action
  // performed when tapped, but the secondary action when held.
  Qukeys,

  // Enables the "Sticky" behavior for modifiers, and the "Layer shift when
  // held" functionality for layer keys.
  OneShot,
  EscapeOneShot,
  EscapeOneShotConfig,

  // Turns LEDs off after a configurable amount of idle time.
  IdleLEDs,
  PersistentIdleLEDs,

  // Enables dynamic, Chrysalis-editable macros.
  DynamicMacros,

  // The FirmwareVersion plugin lets Chrysalis query the version of the firmware
  // programmatically.
  FirmwareVersion,

  // Enables setting, saving (via Chrysalis), and restoring (on boot) the
  // default LED mode.
  DefaultLEDModeConfig,

  // Enables the GeminiPR Stenography protocol. Unused by default, but with the
  // plugin enabled, it becomes configurable - and then usable - via Chrysalis.
  GeminiPR);

/** The 'setup' function is one of the two standard Arduino sketch functions.
 * It's called when your keyboard first powers up. This is where you set up
 * Kaleidoscope and any plugins.
 */
void setup() {
  // First, call Kaleidoscope's internal setup function
  Kaleidoscope.setup();

  // While we hope to improve this in the future, the NumPad plugin
  // needs to be explicitly told which keymap layer is your numpad layer
  NumPad.numPadLayer = NUMPAD;

  // The LED Stalker mode has a few effects. The one we like is called
  // 'BlazingTrail'. For details on other options, see
  // https://github.com/keyboardio/Kaleidoscope/blob/master/docs/plugins/LED-Stalker.md
  StalkerEffect.variant = STALKER(BlazingTrail);

  // For Dynamic Macros, we need to reserve storage space for the editable
  // macros. A kilobyte is a reasonable default.
  DynamicMacros.reserve_storage(1024);

  // To avoid any surprises, SpaceCadet is turned off by default. However, it
  // can be permanently enabled via Chrysalis, so we should only disable it if
  // no configuration exists.
  SpaceCadetConfig.disableSpaceCadetIfUnconfigured();

  // Turbo toggle
  Turbo.interval(25);
  Turbo.sticky(true);
  Turbo.flash(true);
  Turbo.flashInterval(69);
  Turbo.activeColor(CRGB(0x64, 0x96, 0xed));

  // Start stalker effect
  StalkerEffect.activate();
}

/** loop is the second of the standard Arduino sketch functions.
  * As you might expect, it runs in a loop, never exiting.
  *
  * For Kaleidoscope-based keyboard firmware, you usually just want to
  * call Kaleidoscope.loop(); and not do anything custom here.
  */

void loop() {
  Kaleidoscope.loop();
}
