#pragma once

#include <Kaleidoscope.h>

#include "MacroKeyDefs.h"
#include "MacroSteps.h"

const macro_t *macroAction(uint8_t macroIndex, uint8_t keyState);

class Macros_ : public KaleidoscopePlugin {
  public:
    Macros_(void);

    virtual void begin(void) final;

    static void play(const macro_t *macro_p);
    static void playEEPROM(uint8_t eepromIndex);
    static void useEEPROM(uint8_t macroSize, uint8_t maxMacro);
    static void useEEPROM(void) { useEEPROM (24, 4); };

    static byte row, col;

 private:
    typedef uint8_t (*lookup_t)(uint16_t position);
    static void play(lookup_t lookup, uint16_t position);

    static uint8_t lookupPROGMEM(uint16_t address);
    static uint8_t lookupEEPROM(uint16_t idx);

 public:
    static uint16_t macroBase;
    static uint8_t macroSize;
};

extern Macros_ Macros;
