#pragma once
#include <Arduino.h>

class BaseBlock {
    public:
        virtual uint16_t process(uint16_t data);

};