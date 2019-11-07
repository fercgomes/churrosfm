#ifndef BASEOSC_H
#define BASEOSC_H

#include "FCW_Table.h"
#include "Note.h"

class BaseOscillator {
  protected:
    uint32_t phase = 0;
    uint16_t output;
    MidiNote2 midiNote;

    uint32_t* fcwTable = FCW_Table;
    uint32_t fcwTableSize = FCWTABLE_SIZE;
    bool active = false;

    public:

    BaseOscillator(byte inMidi) {
      midiNote = MidiNote2(inMidi);
    }

    BaseOscillator() {
      midiNote = MidiNote2(69);
    }

    virtual void phaseInc();
    virtual uint16_t getOutput() const;
    virtual uint16_t process();

    inline void setNote(byte note) {
      midiNote = MidiNote2(note);
    }

    inline byte getNote() {
      return midiNote.getMidiNote();
    }

    inline byte getNote() const { return midiNote.getMidiNote(); }
    inline void setActive() { active = true; }
    inline void unsetActive() { active = false; }
    inline bool isActive() const { return active; }
  
};

#endif
