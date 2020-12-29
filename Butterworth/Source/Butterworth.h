/*
  ==============================================================================

    Butterworth.h
    Created: 29 Dec 2020 4:02:21pm
    Author:  syfo_dias

  ==============================================================================
*/

#pragma once

struct FilterParameters
{
    FilterParameters() {}
    ~FilterParameters() {}
    
    enum class FilterAlgorithm {LPF, HPF, BPF, BPS};
    FilterAlgorithm algorithm {FilterAlgorithm::LPF};
    int order;
    float frequency;
};
