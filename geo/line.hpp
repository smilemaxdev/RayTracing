#ifndef LINE_HPP
#define LINE_HPP

#include "polygon/triangle.hpp"
#include "geo/vector3d.hpp"
#include "geo/section.hpp"
#include "geo/plane.hpp"

#include <vector>

namespace rytg{

    class Line{
        Point P0_;
        Vector3D L_;

        double getParam(const Point& p) const noexcept;

        public:

        Line(const Plane& lhs, const Plane& rhs) noexcept;

        Vector3D getDirection() const noexcept;

        Point getConstant() const noexcept;

        Point getValue(double t) const noexcept;

        double intersection(const Section& sec, double s) const noexcept;

        std::vector<double> intersection(const Triangle& t, const Plane& oth) const noexcept;

    };

}
#endif
