/*
  ==============================================================================

    Biquad.h
    Created: 29 Dec 2020 11:15:52pm
    Author:  syfo_dias

  ==============================================================================
*/

#pragma once

namespace syfo

{
    
    enum state {x_z1, x_z2, y_z1, y_z2, numStates};
    enum biquadCoeff {a0, a1, a2, b1, b2, c0, d0, numCoeffs};
    
    
    template <typename Type>
    class Biquad
    {
    public:
        Biquad();
        Biquad(Type* coefficients, const int& num);
        
        ~Biquad();
        
        void setCoefficients (Type* coefficients);
        Type process (const Type& inputSample) noexcept;
        
        void reset();
        
    private:
        Type coeffArray[numCoeffs];
        Type zArray[numStates];
        
        JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(Biquad)
    };
    
    template <typename Type>
    Biquad<Type>::Biquad()
    {
        reset();
        memset (&coeffArray[0], 0, sizeof (Type) * numCoeffs);
        
    }
    
    template <typename Type>
    Biquad<Type>::Biquad (Type* coefficients, const int& num)
    {
        reset();
        assert (num == numCoeffs);
        std::copy (coefficients, coefficients + numCoeffs, coeffArray);
    }
    
    template <typename Type>
    void Biquad<Type>::reset()
    {
        memset (&zArray[0], 0, sizeof(Type)*numStates);
        
    }
    template <typename Type>
    Biquad<Type>::~Biquad()
    {
        
    }
    
    template <typename Type>
    void Biquad<Type>::setCoefficients (Type* coefficients)
    {
        memset(&coeffArray[0], 0, sizeof(Type)*numCoeffs); // clear coeffs
        std::copy(coefficients, coefficients + numCoeffs, coeffArray);
    }
    
    template <typename Type>
    Type Biquad<Type>::process (const Type& inputSample) noexcept
    {
        // biquad algorithm - direct forms
        Type outputSample = coeffArray[a0] * inputSample + coeffArray[a1] * zArray[x_z1] + coeffArray[a2] * zArray[x_z2] - coeffArray[b1] * zArray[y_z1] - coeffArray[b2] * zArray[y_z2];
        
        
        // update registers
        zArray[x_z2] = zArray[x_z1];
        zArray[x_z1] = inputSample;
        zArray[y_z2] = zArray[y_z1];
        zArray[y_z1] = outputSample;
        
        return outputSample;
    }
}
