#pragma once

template<typename T>
class PolyphonicContainer {
  private:
    T** ptr;
    int listSize = 8; /* Max polyphony */

  public:

    PolyphonicContainer() {
        ptr = (T**) malloc(listSize * sizeof(T*));
        for(int i = 0; i < listSize; i++) {
          ptr[i] = new T;
        }
    }

    /*
     * Looks for a free oscillator, sets it up and returns true.
     * If no oscillator is available (maximum poliphony), returns false.
     */
    bool noteOn(byte midiNote) {
      T* osc;
      bool found = false;
      
      for(int i = 0; i < listSize && !found; i++) {
        osc = ptr[i];

        /* Oscillator not being used */
        if(!osc->isActive()) {
          found = true;

          osc->setActive();
          osc->setNote(midiNote);
          (osc->carrier)->setGate(true);
        }
      }

      return found;
    }

    /*
     * Frees an oscillator with the given midi note.
     */
    bool noteOff(byte midiNote) {
      bool found = false;
      T* osc;
      
      for(int i = 0; i < listSize && !found; i++) {
        osc = ptr[i];
        if(osc->getNote() == midiNote) {
          osc->unsetActive();
          (osc->carrier)->setGate(false);
          found = true;
        }
      }
      
      return found;
    }

    uint16_t getOutput() {
      T* osc;
      uint16_t output = 0;;

      for(int i = 0; i < listSize; i++) {
        osc = ptr[i];
        if(osc->isActive()) {
          output += osc->process();
        }
      }

      return output;
    }

    void print() {
      T* osc;
      for(int i = 0; i < listSize; i++) {
        osc = ptr[i];
        Serial.println(osc->isActive());
        Serial.println(osc->getNote());
      }
    }
       
};