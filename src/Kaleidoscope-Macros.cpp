#include "Kaleidoscope-Macros.h"

__attribute__((weak))
const macro_t *macroAction(uint8_t macroIndex, uint8_t keyState) {
    return MACRO_NONE;
}

byte Macros_::row, Macros_::col;

void Macros_::play(Macros_::lookup_t lookup, uint16_t position) {
    macro_t macro = END;
    uint8_t interval = 0;
    Key key;

    if (!position)
        return;

    while (true) {
        switch (macro = lookup(position++)) {
        case MACRO_ACTION_STEP_INTERVAL:
            interval = lookup(position++);
            break;
        case MACRO_ACTION_STEP_WAIT: {
            uint8_t wait = lookup(position++);
            delay(wait);
            break;
        }
        case MACRO_ACTION_STEP_KEYDOWN:
            key.flags = lookup(position++);
            key.keyCode = lookup(position++);
            handle_key_event(key, 255, 255, IS_PRESSED | INJECTED);
            Keyboard.sendReport();
            break;
        case MACRO_ACTION_STEP_KEYUP:
            key.flags = lookup(position++);
            key.keyCode = lookup(position++);
            handle_key_event(key, 255, 255, WAS_PRESSED | INJECTED);
            Keyboard.sendReport();
            break;
        case END:
        default:
            return;
        }

        delay(interval);
    }
}

void Macros_::play(const macro_t *macro_p) {
    play (lookupPROGMEM, (uint16_t)macro_p);
}

uint8_t Macros_::lookupPROGMEM(uint16_t address) {
    return pgm_read_byte (address);
}

static Key handleMacroEvent(Key mappedKey, byte row, byte col, uint8_t keyState) {
    if (mappedKey.flags != (SYNTHETIC | IS_MACRO))
        return mappedKey;

    Macros_::row = row;
    Macros_::col = col;
    const macro_t *m = macroAction(mappedKey.keyCode, keyState);

    Macros.play(m);
    return Key_NoKey;
}

Macros_::Macros_ (void) {
}

void
Macros_::begin (void) {
    event_handler_hook_use (handleMacroEvent);
}

Macros_ Macros;
