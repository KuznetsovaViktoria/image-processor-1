#include "filter.h"

void Filter::NormalizeColor(Color& i) {
    if (i.r < 0) {
        i.r = 0;
    } else if (i.r > 1) {
        i.r = 1;
    }
    if (i.g < 0) {
        i.g = 0;
    } else if (i.g > 1) {
        i.g = 1;
    }
    if (i.b < 0) {
        i.b = 0;
    } else if (i.b > 1) {
        i.b = 1;
    }
}
