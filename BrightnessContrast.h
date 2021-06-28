#pragma once
#include "ImageProcessing.h"
namespace myNamespace {
    class BrightnessContrast :
        public ImageProcessing
    {
    public:
        BrightnessContrast();
        BrightnessContrast(float c, int b);
        virtual void process(Image& src, Image& dst);
    private:
        float m_contrast;
        int m_brightness;
    };

}


