#pragma once

#include "effect.hh"

#include "../convert/hsltorgb.hh"

namespace FastRGB {

/* Structure which manages data about one of the four sine waves in EffectHueshift */
struct EffectHueshiftWave {
	/* Current theta [0, 2π] */
	float theta = 0;
	/* Width scale [0, ∞) */
	float scale = 1;
	/* Current "velocity" from left to right [-1, 1] */
	float velocity = 0;
	/* Current "acceleration" from left to right [-1, 1] */
	float acceleration = 0;
};

/* Structure which represents an HSL color */
struct EffectHueshiftHSL {
	float h;
	float s;
	float l;
};


/* Stochastic effect which outputs colors interpreted linearly between 2 HSL
   color points */
   
class EffectHueshift : public Effect {
	protected:
		/* Effect uses 4 sine waves */
		EffectHueshiftWave waves[4];
		/* Effect uses 2 HSL colors */
		EffectHueshiftHSL colors[2];
		
		/* Wave velocity is only updated every 50 frames for smoothness */
		unsigned frameNumber = 0;
		
		/* The maximum absolute value to generate for this->waves[].velocity */
		float maxVelocityABV = 1.0;
		
		/* Gets a random number [0, 1] with 9 decimal digits of precision */
		float getRandom() {return ((float)(random(1000000000)))/1000000000;}
		
	public:
		/* Stochastic effect which outputs colors interpreted linearly between 2 HSL
		   color points */
		EffectHueshift(
			/* First color point */
			EffectHueshiftHSL hue1,
			/* Second color point */
			EffectHueshiftHSL hue2,
			/* How much to scale each sine wave's width by (samaller numbers
			   create a more bumpy effect) */
			float thetaScale,
			/* The maximum absolute value to generate for this->waves[].velocity
			   Lower to make the effect slow down */
			float maxVelocityABV
		) {
			// Set up all sine waves
			for (int i = 0; i < 4; i ++) {
				this->waves[i].scale = (1+i) / thetaScale;
				this->waves[i].theta = this->getRandom()*6.28316;
				this->waves[i].velocity = this->getRandom()*2 - 1;
				this->waves[i].acceleration =
				(this->getRandom()*2 - 1) * this->maxVelocityABV;
			}
			
			this->colors[0] = hue1;
			this->colors[1] = hue2;
			
			this->maxVelocityABV = maxVelocityABV;
		}
		
		void apply(Slice<Color> leds) {
			
			float currentTheta = 0;
			
			for (int i = 0; i < leds.length(); i ++) {
				float total = 0.0;
				
				// For all four waves
				for (int i = 0; i < 4; i ++) {
					float tempTheta = this->waves[i].scale *
					(this->waves[i].theta + currentTheta);
					
					total += (sin(tempTheta) + 1)/8;
				}
				
				if (total > 1) {total = 1;}
				if (total < 0) {total = 0;}
				
				// Get colors and mix linearly
				float h = this->colors[0].h*(1-total) + this->colors[1].h*(total);
				if (h > 1) {h--;} else if (h < 0) {h ++;}
				float s = this->colors[0].s*(1-total) + this->colors[1].s*(total);
				float l = this->colors[0].l*(1-total) + this->colors[1].l*(total);
				
				leds[i] = hslToRGB(h, s, l);
				
				currentTheta += 0.05;
			}
			
		}
		
		void tick() {
			for (int i = 0; i < 4; i ++) {
				waves[i].velocity += waves[i].acceleration * this->maxVelocityABV;
				if (waves[i].velocity < -1*this->maxVelocityABV) {
					waves[i].velocity = this->maxVelocityABV;
				}
				if (waves[i].velocity > this->maxVelocityABV) {
					waves[i].velocity = this->maxVelocityABV;
				}
				
				waves[i].theta += waves[i].velocity/60;
				if (waves[i].theta < 0) {waves[i].theta += 6.28316;}
				if (waves[i].theta >  6.28316) {waves[i].velocity -= 6.28316;}
			}
			
			this->frameNumber ++;
			if (this->frameNumber > 50) {
				this->frameNumber = 0;
				for (int i = 0; i < 2; i ++) {
					this->waves[i].acceleration =
					(this->getRandom()*2 - 1) / this->maxVelocityABV;
				}
			}
		}
};

} // end namespace FastRGB