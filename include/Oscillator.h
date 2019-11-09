#pragma once

#include <Arduino.h>
#include "BaseBlock.h"
#include "Tables.h"

class Oscillator : public BaseBlock  {
  private:
    uint32_t phase = 0;

    uint32_t* fcwTable = FCW_Table;
    uint32_t fcwTableSize = FCWTABLE_SIZE;

    byte midiNote;
    byte midiVelocity;

    uint16_t frequencyFineTuning = 0;
    uint16_t modulationRatio = 1;

    void phaseIncrement(uint16_t data);

  public:

    Oscillator(byte inMidi) : midiNote(inMidi) {}
    Oscillator(byte inMidi, byte inVelocity) : midiNote(inMidi), midiVelocity(inVelocity) {}
    Oscillator() { midiNote = 69; midiVelocity = 127; }

    uint16_t process(uint16_t data);

    inline void setNote(byte note) { midiNote = note; }
    inline void setVelocity(byte vel) { midiVelocity = vel; }
    inline byte getNote() const { return midiNote; }
    inline byte getVelocity() const { return midiVelocity; }
};
