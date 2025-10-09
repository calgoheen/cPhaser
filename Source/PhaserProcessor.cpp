#include "PhaserProcessor.h"

PhaserProcessor::PhaserProcessor()
    : foleys::MagicProcessor (BusesProperties().withInput ("Input", juce::AudioChannelSet::stereo(), true)
                                               .withOutput ("Output", juce::AudioChannelSet::stereo(), true)),
    vts (*this, nullptr, "PARAMS", { parameters.notches.release(),
                                     parameters.center.release(),
                                     parameters.spread.release(),
                                     parameters.feedback.release(),
                                     parameters.flipFeedback.release(),
                                     parameters.shape.release(),
                                     parameters.sync.release(),
                                     parameters.rateFree.release(),
                                     parameters.rateSync.release(),
                                     parameters.amount.release(),
                                     parameters.blend.release(),
                                     parameters.offset.release(),
                                     parameters.safeBass.release(),
                                     parameters.warmth.release(),
                                     parameters.output.release(),
                                     parameters.mix.release() }),
    phaser (parameters)
{
    magicState.setGuiValueTree (BinaryData::layout_xml, BinaryData::layout_xmlSize);
}

bool PhaserProcessor::isBusesLayoutSupported (const juce::AudioProcessor::BusesLayout& layouts) const
{
    if (layouts.getMainOutputChannelSet() != juce::AudioChannelSet::mono()
        && layouts.getMainOutputChannelSet() != juce::AudioChannelSet::stereo())
        return false;

    if (layouts.getMainOutputChannelSet() != layouts.getMainInputChannelSet())
        return false;

    return true;
}

void PhaserProcessor::prepareToPlay (double sampleRate, int samplesPerBlock)
{
    phaser.prepareToPlay (sampleRate, samplesPerBlock, getTotalNumOutputChannels());
}

void PhaserProcessor::processBlock (juce::AudioBuffer<float>& buffer, juce::MidiBuffer& midi)
{
    juce::ScopedNoDenormals noDenormals;
    phaser.processBlock (buffer, midi, getPlayHead());
}

void PhaserProcessor::releaseResources() 
{
}

juce::AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new PhaserProcessor();
}
