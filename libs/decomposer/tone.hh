#pragma once

namespace Decomposer
{

struct Tone
{
	const char* name;
	int octave;
	double frequency;
};

// Finds tone closest to the frequency
Tone findClosestTone(double freq);

}
