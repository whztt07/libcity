/**
 * This code is part of libcity library.
 *
 * @file test/testRay.cpp
 * @date 15.04.2011
 * @author Radek Pazdera (xpazde00@stud.fit.vutbr.cz)
 *
 * @brief Unit test of Ray class
 *
 * Unit tests require UnitTest++ framework! See README
 * for more informations.
 */

/* Include UnitTest++ headers */
#include <UnitTest++.h>

// Includes
#include <iostream>
#include <string>
#include <stdexcept>

// Tested modules
#include "../src/geometry/ray.h"
#include "../src/geometry/vector.h"
#include "../src/geometry/point.h"
#include "../src/geometry/line.h"
#include "../src/debug.h"

SUITE(RayClass)
{
  TEST(Constructors)
  {
    Ray r1;
    CHECK(Point(0,0) == r1.origin());
    CHECK(Vector(1,0) == r1.direction());

    Ray r2(Point(1,1), Vector(1,1));
    CHECK(Point(1,1) == r2.origin());
    CHECK(Vector(1,1) == r2.direction());

    Ray r3(r2);
    CHECK(Point(1,1) == r3.origin());
    CHECK(Vector(1,1) == r3.direction());
  }

  TEST(SetMethods)
  {
    Ray r;

    r.setOrigin(Point(10,10));
    CHECK(Point(10,10) == r.origin());

    r.setDirection(Vector(10,10));
    CHECK(Vector(10,10) == r.direction());

    r.set(Point(2,3), Vector(4,5));
    CHECK(Point(2,3) == r.origin());
    CHECK(Vector(4,5) == r.direction());
  }

  TEST(IntersectionOfTwoRays)
  {
    Ray r1, r2;
    Point intersection;

    // Intersecting
    r1.set(Point(0,0), Vector(1,0));
    r2.set(Point(1,1), Vector(0,-1));
    CHECK(Ray::INTERSECTING == r1.intersection2D(r2, &intersection));
    CHECK(Point(1,0) == intersection);

    // Non intersecting
    r1.set(Point(0,0), Vector(1,0));
    r2.set(Point(1,1), Vector(0,1));
    CHECK(Ray::NONINTERSECTING == r1.intersection2D(r2, &intersection));

    // Paralel
    r1.set(Point(0,0), Vector(1,1));
    r2.set(Point(1,0), Vector(1,1));
    CHECK(Ray::NONINTERSECTING == r1.intersection2D(r2, &intersection));

  }
}