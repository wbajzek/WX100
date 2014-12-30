/*
  ==============================================================================

    Wx100.h
    Created: 27 Dec 2014 7:42:55pm
    Author:  William Bajzek

  ==============================================================================
*/

#ifndef WX100_H_INCLUDED
#define WX100_H_INCLUDED

#include "Scales.h"

const int numOperators = 4;

enum params
{
    AMP_0,
    AMP_1,
    AMP_2,
    AMP_3,
    COARSE_0,
    COARSE_1,
    COARSE_2,
    COARSE_3,
    TUNING_0,
    TUNING_1,
    TUNING_2,
    TUNING_3,
    ATTACK_0,
    ATTACK_1,
    ATTACK_2,
    ATTACK_3,
    DECAY_0,
    DECAY_1,
    DECAY_2,
    DECAY_3,
    SUSTAIN_0,
    SUSTAIN_1,
    SUSTAIN_2,
    SUSTAIN_3,
    RELEASE_0,
    RELEASE_1,
    RELEASE_2,
    RELEASE_3,
    PHASE_0,
    PHASE_1,
    PHASE_2,
    PHASE_3,
    FEEDBACK_3,
    ALGORITHM,
    SCALE,
    SCALE_ROOT,
    LFO_FREQ,
    LFO_SHAPE,
    LFO_AMP_AMOUNT,
    LFO_PITCH_AMOUNT,
    LFO_INIT_PHASE,
    NUMBER_OF_PARAMETERS
};

enum MidiControls {
    MOD_WHEEL_CONTROL = 1
};

#endif  // WX100_H_INCLUDED
