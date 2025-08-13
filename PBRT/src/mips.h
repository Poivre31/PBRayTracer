#pragma once
#include "computeShader.h"

void downsampleImage(unsigned int image, unsigned int output, unsigned int dataType, size_t width, size_t height, bool what);
void upsampleImage(unsigned int image, unsigned int output, unsigned int dataType, size_t width, size_t height);