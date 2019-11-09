#ifndef ALGORITHM_H
#define ALGORITHM_H

#include "Operator.h"
#include "EnvelopeGenerator.h"

#define MAX_OPERATORS 6

/*
 * Implements a routing within Oscillators.
 */
class Algorithm {
  public:

    Operator* modulator;
    Operator* carrier;

    Algorithm() {
      modulator = new Operator();
      carrier = new Operator();
      modulator->envelope.setActive(false);
    }
  
    uint16_t process() {
      return carrier->process( modulator->process(0) );
    }

    void setNote(byte note) {
      carrier->setNote(note);
      modulator->setNote(note);
    }

    inline byte getNote() const { return carrier->getNote(); }

    bool active = false;
    inline void setActive() { active = true; }
    inline void unsetActive() { active = false; }
    inline bool isActive() const { return active; }
};


#endif
