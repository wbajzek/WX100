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

const int numRatios = 65;
const double ratios[numRatios] = {
    0.25, 0.5, 0.71, 0.78, 0.87, 1.00, 1.41,
    1.57, 1.73, 2.0, 2.82, 3.0, 3.14,
    3.46, 4.0, 4.24, 4.71, 5.0, 5.19,
    5.65, 6.0, 6.28, 6.92, 7.0, 7.07,
    7.85, 8.0, 8.48, 8.65, 9.0, 9.42,
    9.89, 10.0, 10.38, 10.99, 11.0, 11.3,
    12.0, 12.11, 12.56, 12.72, 13.0, 13.84,
    14.0, 14.1, 14.13, 15.0, 15.55, 15.57,
    15.7, 16.96, 17.27, 17.3, 18.37, 18.84,
    19.03, 19.78, 20.41, 20.76, 21.20, 21.98,
    22.49, 23.55, 24.22, 25.95
};

enum MidiControls {
    MOD_WHEEL_CONTROL = 1
};

#endif  // WX100_H_INCLUDED
