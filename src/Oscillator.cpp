#include <Arduino.h>
#include "Oscillator.h"
#include "Tables.h"

#define MIDI_START_NOTE 36
#define MIDI_TO_FCWIDX(m) (m - MIDI_START_NOTE)

void Oscillator::phaseIncrement(uint16_t modulationData) {
    phase += fcwTable[MIDI_TO_FCWIDX(midiNote)] + (modulationData * modulationRatio) + frequencyFineTuning;
}

uint16_t Oscillator::process(uint16_t data) {
    uint16_t output = static_cast<uint16_t>(PAC_Table[((phase >> 14)) % PACTABLE_SIZE] + 127);
    phaseIncrement(data);
    return output;
}