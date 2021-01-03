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
    enum class Order {dB12 = 2, dB18 = 3, dB24 = 4, dB36 = 6, db48 = 8, dB72 = 12};
    enum class CascadeType {LPF, HPF, BPF, BPS};
    
    template <typename T>
    struct CascadeParameters
    {
        CascadeParameters() {}
        ~CascadeParameters() {}
        
        Order order {Order::dB12};
        CascadeType type {CascadeType::LPF};
        T frequency {100.0};    
    };
    
    /** User declares an object of Cascade.
        User specifies:
        - frequency
        - order
        - type
        - dry / wet
     */
    template <typename T>
    class Cascade
    {
    public:
        Cascade()
        {
            filters.clear();
            filters.push_back (std::make_unique<syfo::Butterworth<T>>());
        }
        ~Cascade()
        {}
        T process (const T& sample)
        {
            
        }
    private:
        // will contain at most 6 filters
        std::vector<std::unique_ptr<Butterworth<T>>> filters;
        CascadeParameters<T> cascadeParameters;
        JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (Cascade)
        
    };
}
