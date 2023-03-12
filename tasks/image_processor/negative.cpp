#include "negative.h"
#pragma once

Color Negative::CountColor(Color color) {
    return Color(1 - color.r, 1 - color.g, 1 - color.b);
}