# Fast addressable RGB library

Currently in beta.

Compatible with Arduino uno and nano boards, revisions 1 through 4.

## Example

```c++
#include <FastRGB.h>

// Logic LED strip
FastRGB::LEDSeries * series;
// What pin to output on
FastRGB::LEDPin * outputPin;
// Effect
FastRGB::Effect * effect;

void setup() {
	// Set up series of ten LEDs
	series = new FastRGB::LEDSeries(10);
	// Set up all 10 LEDs to output on pin 8
	outputPin = new FastRGB::LEDPin(series->getLEDs(0, 10), 8);
	// Set up rainbow effect
	// Increments by 1 hue per tick, & 3 per LED in the strip
	effect = new FastRGB::EffectRainbow(1, 3);
}

void loop() {
	// Apply effect to LED series
	effect->next(series->getLEDs());
	// Trigger display on pin
	outputPin->display();
	// tick() the effect
	effect->tick();
	// Delay by a resonable ammount
	delay(25);
}
```