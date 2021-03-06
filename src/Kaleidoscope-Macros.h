#pragma once

#include <Kaleidoscope.h>

#include "MacroKeyDefs.h"
#include "MacroSteps.h"

const macro_t *macroAction(uint8_t macroIndex, uint8_t keyState);

class Macros_ : public KaleidoscopePlugin {
 public:
  Macros_(void);

  void begin(void) final;

  void play(const macro_t *macro_p);

  /* What follows below, is a bit of template magic that allows us to use
     Macros.type() with any number of arguments, without having to use a
     sentinel. See the comments on Kaleidoscope.use() for more details - this is
     the same trick.
   */
  inline const macro_t *type() {
    return MACRO_NONE;
  }
  const macro_t *type(const char *string);
  template <typename... Strings>
  const macro_t *type(const char *first, Strings&&... strings) {
    type(first);
    return type(strings...);
  }

  static byte row, col;

 private:
  Key lookupAsciiCode(uint8_t ascii_code);
};

extern Macros_ Macros;
