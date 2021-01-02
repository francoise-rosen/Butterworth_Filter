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
    
    template <typename T>
    class CascadeParameters
    {
    public:
        CascadeParameters() {}
        ~CascadeParameters() {}
        
        Order getOrder() const
        {
            return order;
        }
        void setOrder (const Order& rollOff)
        {
            order = rollOff;
        }
    private:
        Order order {Order::dB12};
        syfo::FilterParameters<T> filterParameters;
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
            filters.push_back (Butterworth<T>());
        }
        ~Cascade()
        {}
        T process (const T& sample)
        {
            
        }
    private:
        std::vector<Butterworth<T>> filters;
        JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (Cascade)
        
    };
}
