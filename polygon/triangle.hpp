#ifndef TRIANGLE_HPP
#define TRIANGLE_HPP
#include "polygon.hpp"
#include "../geo/vector3d.hpp"
#include "../geo/point.hpp"
#include <array>

namespace rytg{

    class Triangle : public Polygon{

        std::array<Point, 3> p_;

        public:

        Triangle() = default;

        ~Triangle() = default;

        Triangle(Point p1, Point p2, Point p3);

        Triangle(const Triangle& other) = default;

        Point getPoint(std::size_t v) const noexcept;

        bool isPointInTriangle(const Point& p) const noexcept;

        bool isPlaneIntersection(const Triangle* t) const noexcept;

        bool isIntersection(const Triangle* other) const noexcept;

        bool isIntersection(const Polygon* p) const override;

        size_t getID() const override;

        Plane getPlane() const override;

        static std::array<Polygon*, 2> splitToChunks(Triangle* t, const Plane& p);

        static Triangle* mergeChunks(const Polygon* lhs, const Polygon* rhs);

        static bool isTriangle(const Polygon* p);

    };
}

#endif
