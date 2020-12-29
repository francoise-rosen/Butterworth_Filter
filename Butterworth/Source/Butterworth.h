/*
  ==============================================================================

    Butterworth.h
    Created: 29 Dec 2020 4:02:21pm
    Author:  syfo_dias

  ==============================================================================
*/

#pragma once
#include "Biquad.h"

namespace syfo
{
    using Math = juce::MathConstants<double>;
    enum class FilterType {LPF2, HPF2, BPF2, BSF2, LPF3, HPF3, BPF3, BSF3};
    
    //==============================================================================
    template <typename Type>
    struct FilterParameters
    {
        FilterParameters() {}
        ~FilterParameters() {}
        
        FilterParameters& operator=(const FilterParameters& params);
        inline bool operator==(const FilterParameters& params);
        inline bool operator!=(const FilterParameters& params);
        
        FilterType algorithm = FilterType::LPF2;
        Type freq = 100.0;
    };
    
    template <typename Type>
    FilterParameters<Type>& FilterParameters<Type>::operator=(const FilterParameters& params)
    {
        algorithm = params.algorithm;
        freq = params.freq;
        return *this;
    }
    
    template <typename Type>
    inline bool FilterParameters<Type>::operator==(const FilterParameters& params)
    {
        return ((algorithm == params.algorithm) && (freq == params.freq));
    }
    
    template <typename Type>
    inline bool FilterParameters<Type>::operator!=(const FilterParameters& params)
    {
        return !(this == params);
    }
    
    //==============================================================================
    
    template <typename T>
    class Butterworth
    {
    public:
        Butterworth() {}
        Butterworth (FilterParameters<T> parameters, double sampleRate)
        :filterParameters {parameters}, currentSampleRate {sampleRate}
        {}
        ~Butterworth() {}
        T process (const T& sample) noexcept
        {
            
        }
    private:
        FilterParameters<T> filterParameters;
        double currentSampleRate;
        Biquad<T> biquad;
        JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (Butterworth);
    };
}
