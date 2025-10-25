#include "figure.h"

std::ostream& operator<<(std::ostream& os, const Figure& fig) {
    return fig.output(os);
}

std::istream& operator>>(std::istream& is, Figure& fig) {
    return fig.input(is);
}
