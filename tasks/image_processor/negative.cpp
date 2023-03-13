#include "negative.h"

Color Negative::CountColor(Color color) {
    return Color(1 - color.r, 1 - color.g, 1 - color.b);
}