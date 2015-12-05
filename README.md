# FM Synthesizer #

This was my second c++ project and needs some drastic reworking. But
here it is on Github, mainly for my own convenience.

## Wishlist ##
* velocity sensitivity control
* LFO tempo sync
* Envelope stages (AR, D1R, D1L, D2R, RR)?
* output level
* aftertouch
* transpose knob
* Mono legato mode
  * portamento
  * note priority
* less ghetto UI
* midi CC

## Bugs ##
* make undo/redo work, possibly without buying a commercial license for
  PluginParameters
* voices not engaged when modwheel has changed do not know its setting.
* carriers over the nyquist should probably be omitted
