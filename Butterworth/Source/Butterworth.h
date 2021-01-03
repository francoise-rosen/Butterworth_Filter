/*
  ==============================================================================

    Butterworth.h
    Created: 29 Dec 2020 4:02:21pm
    Author:  syfo_dias

  ==============================================================================
*/

#pragma once
#include "Biquad.h"
#include <vector>

namespace syfo
{

    using Math = juce::MathConstants<double>;
    enum class FilterType {LPF, HPF, BPF, BSF, numTypes};
    enum class FilterRollOff {dB12 = 2, dB18 = 3, dB24, dB36 = 6, dB48 = 8, dB72 = 12};
    namespace ButterworthID
    {
        static const juce::StringArray butterworthFilterAlgorithmIDs {"LPF", "HPF", "BPF", "BPS"};
        static const juce::StringArray butterworthFilterOrderIDs {"12dB", "18dB", "24dB", "36dB", "48dB", "72dB"};
    }

    //==============================================================================
    template <typename Type>
    struct FilterParameters
    {
        FilterParameters() {}
        ~FilterParameters() {}
        
        FilterParameters& operator=(const FilterParameters& params);
        inline bool operator==(const FilterParameters& params);
        inline bool operator!=(const FilterParameters& params);
        
        FilterType algorithm = FilterType::LPF;
        Type frequency = static_cast<Type> (100.0);
        FilterRollOff order {FilterRollOff::dB12};
    };
    
    template <typename Type>
    FilterParameters<Type>& FilterParameters<Type>::operator=(const FilterParameters& params)
    {
        algorithm = params.algorithm;
        frequency = params.frequency;
        order = params.order;
        return *this;
    }
    
    template <typename Type>
    inline bool FilterParameters<Type>::operator==(const FilterParameters& params)
    {
        return ((algorithm == params.algorithm) && (frequency == params.freq) && (order == params.order));
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
        Butterworth()
        {
        }
        
        Butterworth (FilterParameters<T> parameters, double sampleRate)
        :filterParameters {parameters}, currentSampleRate {sampleRate}
        {
            
        }
        ~Butterworth() {}
        T process (const T& sample) noexcept
        {
            
        }
        
    private:
        FilterParameters<T> filterParameters;
        double currentSampleRate {0};
        std::vector<std::unique_ptr<Biquad<T>>> cascade;
        JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (Butterworth);
    };
}


