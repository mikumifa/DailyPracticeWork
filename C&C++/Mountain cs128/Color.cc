#include "color.hpp"
#include <stdexcept>

Color::Color(int r, int g, int b): red_(r), green_(g), blue_(b) {
    // need to ensure valid color has been constructed...
    if(!(betweenMinAndMAx(r)&& betweenMinAndMAx(g)&& betweenMinAndMAx(b)))
        throw std::invalid_argument("Color: invalid color");
}

bool Color::betweenMinAndMAx(int color){
    if(color>=kColorValueMin&&color<=kColorValueMax)
        return true;
    else
        return false;
}
// do not modify
bool operator==(const Color& rhs, const Color& lhs) {
    return (rhs.Red() == lhs.Red() && rhs.Green() == lhs.Green() &&
            rhs.Blue() == lhs.Blue());
}
