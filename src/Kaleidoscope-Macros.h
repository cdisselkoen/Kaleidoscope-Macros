#pragma once

#include <Kaleidoscope.h>

#include "MacroKeyDefs.h"
#include "MacroSteps.h"

const macro_t *macroAction(uint8_t macroIndex, uint8_t keyState);

class Macros_ : public KaleidoscopePlugin {
  public:
    Macros_(void);

    virtual void begin(void) final;

    void play(const macro_t *macro_p);

    static byte row, col;

 private:
    typedef uint8_t (*lookup_t)(uint16_t position);
    void play(lookup_t lookup, uint16_t position);

    static uint8_t lookupPROGMEM(uint16_t address);
};

extern Macros_ Macros;
