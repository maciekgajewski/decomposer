#pragma once

namespace Decomposer
{

struct Tone
{
	const char* name;
	int octave;
	double frequency;
	int index; // difference from A0
};

// Finds tone closest to the frequency
Tone findClosestTone(double freq);

}
