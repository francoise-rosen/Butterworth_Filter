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
    enum class Order {dB12, dB16, dB18, dB24, dB36, dB72};
    
    template <typename T>
    class Cascade
    {
    public:
        Cascade()
        {}
        ~Cascade()
        {}
        T process (const T& sample)
        {
            
        }
    private:
        Order order {Order::dB12};
        JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (Cascade)
        
    };
}
