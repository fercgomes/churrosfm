#include <Arduino.h>
#include <MIDI.h>
#include "noteList.h"
#include "Algorithm.h"
#include "PoliphonicContainer.h"
#include "Operator.h"

// These are the clock frequencies available to the timers /2,/8,/32,/128
// 84Mhz/2 = 42.000 MHz
// 84Mhz/8 = 10.500 MHz
// 84Mhz/32 = 2.625 MHz
// 84Mhz/128 = 656.250 KHz
//
// 42Mhz/44.1Khz = 952.38
// 10.5Mhz/44.1Khz = 238.09 
// 2.625Hmz/44.1Khz = 59.5
// 656Khz/44.1Khz = 14.88 // 131200 / 656000 = .2 (.2 seconds)

MIDI_CREATE_DEFAULT_INSTANCE();

/* Max polyphony of 8 */
static const byte maxPoly = 8;
static PolyphonicContainer<Algorithm> polyphonic;

void handleNoteOn(byte inChannel, byte inNote, byte inVelocity) {
  polyphonic.noteOn(inNote);
  Serial.println("Note on");
}

void handleNoteOff(byte inChannel, byte inNote, byte inVelocity) {
  polyphonic.noteOff(inNote);
  Serial.println("Note off");
}

void setup()
{
  Serial.begin(9600);

  pinMode(A0, INPUT);
  pinMode(A1, INPUT);
  pinMode(A2, INPUT);
  pinMode(A3, INPUT);
 
  /* Set up MIDI */
  MIDI.setHandleNoteOn(handleNoteOn);
  MIDI.setHandleNoteOff(handleNoteOff);
  MIDI.begin(MIDI_CHANNEL_OMNI);

  /* Disable write protection on PMC */
  pmc_set_writeprotect(false);

  /* Enable peripheral clock 7 */
  pmc_enable_periph_clk(ID_TC7);

  /* Configure TC */
  TC_Configure(
    TC2,                            /* Which timer */
    1,                              /* Channel 0 */
      TC_CMR_WAVE |                 /* Waveform mode */
      TC_CMR_WAVSEL_UP_RC |         /* Set counter to run up, and reset when it equals to RC */
      TC_CMR_TCCLKS_TIMER_CLOCK1    /* Run the clock at MCR/128 */
  );

  /* Set the interruption rate */
  TC_SetRC(TC2, 1, 1904);
  TC_Start(TC2, 1);

  /* Enable timer interrupts */
  TC2->TC_CHANNEL[1].TC_IER = TC_IER_CPCS;
  TC2->TC_CHANNEL[1].TC_IDR = ~TC_IER_CPCS;

  /* Enable nested vector interrupt controoler, which handles all inputs */
  NVIC_EnableIRQ(TC7_IRQn);
}

void loop()
{
  MIDI.read();
}
 
void TC7_Handler()
{ 
  TC_GetStatus(TC2, 1);
  
  uint16_t output = 0;
  output = polyphonic.getOutput();
  
  analogWriteResolution(12);
  analogWrite(DAC1, output);

  /* Process phase increments */
}
