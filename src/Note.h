#ifndef NOTE_H
#define NOTE_H

#define MIDI_START_NOTE 36
#define MIDI_TO_FCWIDX(m) (m - MIDI_START_NOTE)

class MidiNote2 {
  public:
  byte note;
  byte velocity;

  MidiNote2() {
    note = 0;
    velocity = 0;
  }

  MidiNote2(byte inMidi) {
    note = inMidi;
    velocity = 127;
  }

  MidiNote2(byte inMidi, byte inVelocity) {
    note = inMidi;
    velocity = inVelocity;
  }

  inline uint32_t getFreq() const {
    return 0;
  }

  inline byte getMidiNote() const {
    return note;
  }

  inline byte getMidiVelocity() const {
    return velocity;
  }
};

#endif
