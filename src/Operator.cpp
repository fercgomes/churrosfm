#include <Arduino.h>
#include "Operator.h"

uint16_t Operator::process(uint16_t data) {
    uint16_t output = super::process(data) * (envelope.getOutput() >> 14);
    envelope.process();
    return output;
}
