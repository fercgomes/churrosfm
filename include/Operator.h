#pragma once
#include <Arduino.h>
#include "EnvelopeGenerator.h"
#include "Oscillator.h"

class Operator : public Oscillator {
  private:

  public:
    typedef Oscillator super;
    EnvelopeGenerator envelope;

    uint16_t process(uint16_t data);

    void trigger() { envelope.setTrigger(true); }
    void setGate(bool gate) { envelope.setGate(gate); }
};
