#ifndef OSCILLATOR2_H
#define OSCILLATOR2_H

#include "FCW_Table.h"
#include "Note.h"
#include "BaseOscillator.h"

class Operator : public BaseOscillator {
  private:
    uint16_t frequencyFineTuning = 0;
    uint32_t frequencyModulationData = 0;

    /* TODO: envelope generator, with inputs for modulators */

  public:
  
    void setFrequencyModulation(uint32_t data) {
      frequencyModulationData = data;
    }

    uint16_t getOutput() const {
      return output;
    }

    void phaseInc() {
      phase += FCW_Table[MIDI_TO_FCWIDX(midiNote.getMidiNote())] + (frequencyModulationData) + frequencyFineTuning;
    
      /* TODO: modulation amplitude */
    }

    uint16_t process() {
      /* TODO: apply amplitude envelope */
      output = ((uint16_t)(PAC_Table[((phase >> 14)) % PACTABLE_SIZE] + 127));
      phaseInc();
      /* inc phase here? */
      return output;
    }

};
#endif
