#ifndef EG_H
#define EG_H

#include <Arduino.h>
#include "Config.h"

#define MAXU16BIT 65535

static const uint32_t fracWidth = 9;
/* Fixed for 22050 hz */
static const uint32_t envelopeStep = 2978; /* TODO: sample rate as parameter */

enum EnTriggerMode {
    TRIG1
};

enum EnvelopeState {
    OFF,
    ATTACK,
    DECAY,
    SUSTAIN,
    RELEASE
};

class EnvelopeGenerator {
    private:
        /* Phases */
        uint32_t attackTime;
        uint32_t decayTime;
        uint32_t sustainLevel;
        uint32_t releaseTime;

        /* Value increments */
        uint32_t attackIncrement;
        uint32_t decayIncrement;
        uint32_t sustainIncrement;
        uint32_t releaseIncrement;

        /* Main counter */
        uint32_t counter;

        /* Saved output, only processed once */
        int32_t output;

        /* State machine */
        EnvelopeState currentState = OFF;

        bool gate = false;
        bool trigger = false;
        EnTriggerMode triggerMode;

        bool active = true;

    public:
        /* Constructors */
        EnvelopeGenerator();
        EnvelopeGenerator(uint32_t attack, uint32_t decay, uint32_t sustain, uint32_t release);

        void process();
        uint16_t getOutput() const;
        void setAttack(uint32_t attack);
        void setDecay(uint32_t decay);
        void setSustain(uint32_t sustain);
        void setRelease(uint32_t release);
        void setGate(bool gate);
        void setTrigger(bool trigger);
        void setTriggerMode(EnTriggerMode triggerMode);

        inline void resetCounter() { counter = 0; };
        inline void resetAttack() { attackIncrement = 0; }
        inline void resetDecay() { decayIncrement = 0; }
        inline void resetRelease() { releaseIncrement = 0; }

        inline void setState(EnvelopeState newState);
        inline void setActive(bool b) { active = b; }
};

#endif