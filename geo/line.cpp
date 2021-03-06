#include "geo/line.hpp"
#include <cmath>
#include <algorithm>

namespace rytg{

Line::Line(const Plane& lhs, const Plane& rhs) noexcept{
    L_ = lhs.getNormal().cross(rhs.getNormal());
    if(L_.isNull()) return;
    double x, y, z;
    Vector3D lhs_N = lhs.getNormal();
    Vector3D rhs_N = rhs.getNormal();
    if (!Double::isNull(L_.get(0))){
        x = 0;
        double det = lhs_N.get(1) * rhs_N.get(2) - lhs_N.get(2) * rhs_N.get(1);
        y = (rhs.getConstant() * lhs_N.get(2) - rhs_N.get(2) * lhs.getConstant()) / det;
        z = (lhs.getConstant() * rhs_N.get(1) - lhs_N.get(1) * rhs.getConstant()) / det;
    }
    else if(!Double::isNull(L_.get(1))){
        y = 0;
        double det = lhs_N.get(0) * rhs_N.get(2) - lhs_N.get(2) * rhs_N.get(0);
        x = (rhs.getConstant() * lhs_N.get(2) - rhs_N.get(2) * lhs.getConstant()) / det;
        z = (lhs.getConstant() * rhs_N.get(0) - lhs_N.get(0) * rhs.getConstant()) / det;
    }
    else{
        z = 0;
        double det = lhs_N.get(0) * rhs_N.get(1) - lhs_N.get(1) * rhs_N.get(0);
        x = (rhs.getConstant() * lhs_N.get(1) - rhs_N.get(1) * lhs.getConstant()) / det;
        y = (lhs.getConstant() * rhs_N.get(0) - lhs_N.get(0) * rhs.getConstant()) / det;
    }
    P0_ = {x, y, z};
}

Vector3D Line::getDirection() const noexcept{
    return L_;
}

Point Line::getConstant() const noexcept{
    return P0_;
}

Point Line::getValue(double t) const noexcept{
    return {L_.get(0) * t + P0_.x, L_.get(1) * t + P0_.y, L_.get(2) * t + P0_.z};
}

double Line::getParam(const Point& p) const noexcept{
    double check = NAN;
    for(wint_t j = 0; j < 3; ++j){
        double numer = p.get(j) - P0_.get(j);
        if(!Double::isNull(L_.get(j))){
            double tmp = numer / L_.get(j);
            if(!std::isnan(check) && !Double::eq(tmp, check)) return NAN;
            check = tmp;
        }
        else if(!Double::isNull(numer)){
            return NAN;
        }
    }
    return check;
}

std::vector<double> Line::intersection(const Triangle& t, const Plane& p) const noexcept{
    Section s[3] = {Section(t.getPoint(0), t.getPoint(1)),
                    Section(t.getPoint(1), t.getPoint(2)),
                    Section(t.getPoint(2), t.getPoint(0))};
    std::vector<double> res;
    res.reserve(3);
    for(wint_t i = 0; i < 3; ++i){
        double s_param = s[i].intersection(p);
        if(!std::isnan(s_param)){
            double param = intersection(s[i], s_param);
            if(!std::isnan(param))
                res.push_back(param);
        }
    }

    if(res.size() >= 3){
        std::sort(res.begin(), res.end());
        auto it = std::unique(res.begin(), res.end(), Double::eq);
        res.erase(it, res.end());
    }
    else if(res.size() == 2 && res[0] > res[1]){
        std::swap(res[0], res[1]);
    }
    return res;
}

double Line::intersection(const Section& sec, double s) const noexcept{

    Point pr = {sec.get(0).get(0) + s * (sec.get(1).get(0) - sec.get(0).get(0)),
                sec.get(0).get(1) + s * (sec.get(1).get(1) - sec.get(0).get(1)),
                sec.get(0).get(2) + s * (sec.get(1).get(2) - sec.get(0).get(2))};
    double param = getParam(pr);

    if(!std::isnan(param) && sec.isInSection(getValue(param)))
        return param;
    return NAN;
}

}
