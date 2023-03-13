#include "grayscale.h"

Color Grayscale::CountColor(Color color) {
    long double c = 0.299 * color.r + 0.587 * color.g + 0.114 * color.b;
    if (c < 0) {
        c = 0;
    } else if (c > 1) {
        c = 1;
    }
    return Color(c, c, c);
}