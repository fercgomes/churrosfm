#include "EnvelopeGenerator.h"
#include <Arduino.h>

EnvelopeGenerator::EnvelopeGenerator() {
    /* In milliseconds */
    setAttack(500);
    setDecay(200);
    setSustain(32767);
    setRelease(500);

    currentState = OFF;
}

EnvelopeGenerator::EnvelopeGenerator(uint32_t attack, uint32_t decay, uint32_t sustain, uint32_t release) {
    setAttack(attack);
    setDecay(decay);
    setSustain(sustain);
    setRelease(release);
    currentState = OFF; 
}

void EnvelopeGenerator::process() {
    /* The state machine is traversed */
    switch(currentState) {
        case OFF:
            output = 0;

            /* State transition */
            if(gate || trigger) {
                setState(ATTACK);
                break;
            }

            break;

        case ATTACK:
            /* Process attack increment */
            trigger = false;

            output += attackIncrement;

            /* State transition */
            if(!gate)  {
                setState(RELEASE);
                break;
            }

            if(output >= MAXU16BIT) {
                setState(DECAY);
                break;
            }

            break;

        case DECAY:
            /* Process decay increment */
            output -= decayIncrement;

            /* State transition */
            if(trigger) {
                setState(ATTACK);
                break;
            } 

            if(!gate) {
                setState(RELEASE);
                break;
            }

            if(output <= (int32_t)(sustainLevel)) {
                setState(SUSTAIN);
                break;
            }
            break;
        
        case SUSTAIN:
            /* Process sustain */
            output = sustainLevel;

            /* State transition */
            if(trigger) {
                setState(ATTACK);
                break;
            }
            else if(!gate) {
                setState(RELEASE);
                break;
            }
            
            break;

        case RELEASE:
            /* Process release */
            output -= releaseIncrement;

            /* State transition */
            if(gate || trigger) {
                setState(ATTACK);
                break;
            }

            if(output <= 0) {
                setState(OFF);
                break;
            }

            break;
    }
}

uint16_t EnvelopeGenerator::getOutput() const {
    if(active)
        return static_cast<uint16_t>(output);
    else
        return 0; 
}

void EnvelopeGenerator::setAttack(uint32_t attack) {
    attackTime = attack;
    attackIncrement = MAXU16BIT / (22 * attack);
}

void EnvelopeGenerator::setDecay(uint32_t decay) {
    decayTime = decay;
    decayIncrement = (MAXU16BIT - sustainLevel) / (22 *  decay);
}

void EnvelopeGenerator::setSustain(uint32_t sustain) {
    sustainLevel = sustain;
}

void EnvelopeGenerator::setRelease(uint32_t release) {
    releaseTime = release;
    releaseIncrement = sustainLevel / (22 * release);
}

void EnvelopeGenerator::setGate(bool gate) {
    this->gate = gate;
}

void EnvelopeGenerator::setTrigger(bool trigger) {
    this->trigger = trigger;
}

void EnvelopeGenerator::setTriggerMode(EnTriggerMode triggerMode) {
    this->triggerMode = triggerMode;
}

inline void EnvelopeGenerator::setState(EnvelopeState newState) {
    resetCounter();
    currentState = newState;
}