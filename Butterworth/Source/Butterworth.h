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
    enum class FilterOrder {dB12 = 2, dB18 = 3, dB24, dB36 = 6, dB48 = 8, dB72 = 12};
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
        FilterParameters (const Type& f, const int& algo, const int& rf)
        :frequency {f}, algorithm {static_cast<FilterType> (algo)}, order {static_cast<FilterOrder> (rf)}
        {}
        ~FilterParameters() {}
        
        FilterParameters (const FilterParameters& fp)
        {
            if (this == &fp)
                return;
            algorithm = fp.algorithm;
            frequency = fp.frequency;
            order = fp.order;
        }
        
        FilterParameters<Type>& operator=(const FilterParameters& params)
        {
            if (*this == params)
                return;
            this->algorithm = params.algorithm;
            this->frequency = params.frequency;
            this->order = params.order;
            return *this;
        }
        
        bool operator==(const FilterParameters& params);
        bool operator!=(const FilterParameters& params);
        bool isOrderOdd() const {return static_cast<int> (order) % 2; }
        int getOrderValue() const {return static_cast<int> (order); }
        
        Type frequency = static_cast<Type> (100.0);
        FilterType algorithm = FilterType::LPF;
        FilterOrder order {FilterOrder::dB12};
    };
    
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
            cascade.clear();
            cascade.push_back (std::make_unique<syfo::Biquad<T>> ());
        }
        
        Butterworth (FilterParameters<T> parameters, double sampleRate)
        :filterParameters {parameters}, currentSampleRate {sampleRate}
        {
            jassert (initialiseCascade() == true);
        }
        
        ~Butterworth() {}
        T process (const T& sample) noexcept
        {
            
        }
        
        /** initialise / populate cascade vector. */
        bool initialiseCascade()
        {
            cascade.clear();
            /** this will do only for LPF and HPF. */
            if ( (filterParameters.algorithm == FilterType::LPF) || (filterParameters.algorithm == FilterType::HPF))
            {
                int numOfBiquads = (filterParameters.isOrderOdd()) ? filterParameters.getOrderValue() / 2 + 1 : filterParameters.getOrderValue;
                for (int i = 0; i < numOfBiquads; ++i)
                {
                    cascade.push_back (std::make_unique<syfo::Biquad<T>> ());
                }
            }
            return (cascade.size() > 0);
        }
        
        /** reset all the biquads in cascade. */
        void resetAll()
        {
            
        }
        
        void setSampleRate (double sampleRate)
        {
            if (currentSampleRate == sampleRate)
                return;
            currentSampleRate = sampleRate;
            computeCoefficients();
        }
        
    private:
        FilterParameters<T> filterParameters;
        double currentSampleRate {0};
        std::vector<std::unique_ptr<Biquad<T>>> cascade;
        /** Coeffs for 1 (or 3) order topology. */
        T coeff1[numCoeffs];
        /** Coeffs for 2 order topology. */
        T coeff2[numCoeffs];
        void computeCoefficients()
        {
            
        }
        
        
        
        JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (Butterworth);
    };
}


