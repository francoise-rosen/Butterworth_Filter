/*
  ==============================================================================

    Cascade.h
    Created: 29 Dec 2020 4:02:49pm
    Author:  syfo_dias

  ==============================================================================
*/

#pragma once
#include "Butterworth.h"



namespace syfo
{
    template <typename T>
    class Cascade
    {
    public:
        Cascade()
        {}
        ~Cascade()
        {}
    private:
        int order;
        JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (Cascade)
        
    };
}
