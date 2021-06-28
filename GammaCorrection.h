#pragma once
#include "ImageProcessing.h"

namespace myNamespace {
    class GammaCorrection : public ImageProcessing
    {
    public:
        GammaCorrection();
        GammaCorrection(float gamma);
        virtual void process(Image& src, Image& dst);
    private:
        float m_gamma;
    };
}


