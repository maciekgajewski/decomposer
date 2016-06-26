#include "tone.hh"

#include <stdexcept>

namespace Decomposer {

const double A4_FREQ = 440.0;
const double TONE_RATIO			= 1.0594630943592952645;
const double TONE_RATIO_HALF	= 1.0293022366434920288;

const char* TONE_NAMES[] = {"C", "C#", "D", "D#", "E", "F", "F#", "G", "G#", "A" /*idx 9*/, "A#", "B"};

static bool near(double freq, double candidate)
{
	double low = candidate / TONE_RATIO_HALF;
	double high = candidate * TONE_RATIO_HALF;
	return (freq >= low && freq <= high);
}

static int findToneDiff(double freq, double& candidate)
{
	// are we there yet?
	if (near(freq, candidate))
	{
		return 0;
	}

	// are we more than octave away?
	if (freq < candidate/2)
	{
		candidate /= 2;
		return findToneDiff(freq, candidate) - 12;
	}
	if (freq > candidate*2)
	{
		candidate *= 2;
		return findToneDiff(freq, candidate) + 12;
	}

	// search tones below
	int diff = 0;
	while (freq < candidate && diff > -12)
	{
		candidate /= TONE_RATIO;
		diff--;
		if (near(freq, candidate))
			return diff;
	}
	// search above
	while (freq > candidate && diff < 12)
	{
		candidate *= TONE_RATIO;
		diff++;
		if (near(freq, candidate))
			return diff;
	}
	throw std::runtime_error("what happened?");
}

Tone findClosestTone(double freq)
{
	double candidate = A4_FREQ;

	int diff = findToneDiff(freq, candidate);

	int index_in_octave = diff + 9;
	int octave = index_in_octave/12;

	// correct for % rounding towards 0
	if (index_in_octave < (octave*12))
		octave--;

	int name_index = index_in_octave%12;
	if (name_index < 0)
		name_index += 12;

	Tone result;
	result.frequency = candidate;
	result.name = TONE_NAMES[name_index];

	result.octave = 4 + octave;

	return result;
}

}
