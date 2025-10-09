#pragma once

#include <JuceHeader.h>

class PhaserProcessor : public foleys::MagicProcessor
{
public:
    PhaserProcessor();
    ~PhaserProcessor() override = default;

    bool isBusesLayoutSupported (const juce::AudioProcessor::BusesLayout& layouts) const override;
    void prepareToPlay (double sampleRate, int samplesPerBlock) override;
    void processBlock (juce::AudioBuffer<float>&, juce::MidiBuffer&) override;
    void releaseResources() override;

private:
    cgo::Phaser::Params parameters;
    juce::AudioProcessorValueTreeState vts;
    cgo::Phaser phaser;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(PhaserProcessor)
};
