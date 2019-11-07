#ifndef ALGORITHM_H
#define ALGORITHM_H

#include "Note.h"
#include "Operator.h"

#define MAX_OPERATORS 6

/*
 * Implements a routing within Oscillators.
 */
class Algorithm {
  private:
    Operator* modulator;
    Operator* carrier;

  public:
    Algorithm() {
      modulator = new Operator();
      carrier = new Operator();
    }
  
    uint16_t process() {
      modulator->setFrequencyModulation(0);
      carrier->setFrequencyModulation( modulator->process() );
      return carrier->process();
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
