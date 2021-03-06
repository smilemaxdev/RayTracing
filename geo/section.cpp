#include "geo/section.hpp"
#include <cmath>
#include <algorithm>

namespace rytg{

    Section::Section(const Point& p1, const Point& p2) noexcept : p_({p1, p2}){}

    double Section::intersection(const Plane& p) const noexcept {
        double d_u0 = p.getValue(p_[0]);
        double d_u1 = p.getValue(p_[1]);
        if(Double::eq(d_u1, d_u0)) return NAN;
        double s = - d_u0 / (d_u1 - d_u0);
        return s;
    }

    Point Section::get(std::size_t idx) const noexcept{
        switch(idx){
            case 0: return p_[0];
            case 1: return p_[1];
            default: return Point{};
        }
    }

    bool Section::isIntersection(const std::vector<double>& t1,
                                 const std::vector<double>& t2){

        if (t1.size() == 1 && t2.size() == 1)
            return t1[0] == t2[0];

        if (t1.size() == 1 && t2.size() == 2)
            if(t1[0] >= t2[0] && t1[0] <= t2[1]) return true;

        if (t1.size() == 2 && t2.size() == 1)
            if(t2[0] >= t1[0] && t2[0] <= t1[1]) return true;

        if (t1.size() == 2 && t2.size() == 2){
            if(t1[0] <= t2[0] && t1[1] >= t2[0]) return true;
            if(t2[0] <= t1[0] && t2[1] >= t1[0]) return true;
        }

        return false;

    }

    bool Section::isInSection(const Point& p) const noexcept{
        for(wint_t i = 0; i < 3; i++){
            double max = std::max(p_[0].get(i), p_[1].get(i));
            double min = std::min(p_[0].get(i), p_[1].get(i));
            if(Double::eq(max, p.get(i))) continue;
            if(Double::eq(min, p.get(i))) continue;
            if(p.get(i) < min || max < p.get(i)) return false;

        }
        return true;
    }

}
