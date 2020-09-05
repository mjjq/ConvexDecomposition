# ConvexDecomposition
## What does this library do?
This is a header only C++ library, made for decomposing and slicing concave polygons into convex polygons. This library also allows for user defined polygon slicing (see usage). 

The ConcavePolygon class uses a recursive data structure to either store 0 or 2 sub polygons. When a polygon is sliced, two sub polygons are generated split along a defined line segment.

Credits: The algorithm for decomposing concave polygons to convex can be found here: https://mpen.ca/406/bayazit (Mark Bayazit). Convex decomposition is achieved in O(n*r) time, where n is the number of polygon vertices, r is the number of reflex polygon vertices.


## Installation
To install this library, simply copy ConcavePolygon.h into your project and #include "ConcavePolygon.h".

### Example Usage: Creating a concave polygon, decomposing, and acquiring convex subpolygons

```
#include "ConcavePolygon.h"

#include <vector>

int main()
{
    // Create a vector of vertices
    std::vector<cxd::Vertex > vertices =
    {
        cxd::Vec2({0.0f, 1.0f}),
        cxd::Vec2({-1.0f, 0.0f}),
        cxd::Vec2({0.0f, 0.5f}),
        cxd::Vec2({1.0f, 0.0f})
    };

    // Create polygon from these vertices
    cxd::ConcavePolygon concavePoly(vertices);

    // Perform convex decomposition on polygon
    concavePoly.convexDecomp();

    // Retrieve a decomposed convex subpolygon by index
    // We still use the concave poly type here
    cxd::ConcavePolygon subPolygon = concavePoly.getSubPolygon(0);

    // Retrieve vertices from the subpolygon (also applies to the
    // concave polygon we defined earlier)
    std::vector<cxd::Vertex > subPolyVerts = subPolygon.getVertices();

    // Create a vector and retrieve all convex subpolygons
    // as a single list
    std::vector<cxd::ConcavePolygon > subPolygonList;
    concavePoly.returnLowestLevelPolys(subPolygonList);


    return 0;
}
```

### Example Usage: Creating a polygon and slicing it along a defined line segment
```
#include "ConcavePolygon.h"

#include <vector>

int main()
{
    // Create a vector of vertices
    std::vector<cxd::Vertex > vertices =
    {
        cxd::Vec2({0.0f, 1.0f}),
        cxd::Vec2({-1.0f, 0.0f}),
        cxd::Vec2({0.0f, -1.0f}),
        cxd::Vec2({1.0f, 0.0f})
    };

    // Create polygon from these vertices
    cxd::ConcavePolygon concavePoly(vertices);

    // Create a valid line segment to slice the polygon.
    // Note: The line segment must pass through two polygon
    // edges in order to slice. Here we define the start
    // and end positions of the line segment.
    cxd::LineSegment line(cxd::Vec2({-2.0f, 0.0f}),
                          cxd::Vec2({ 2.0f, 0.0f}));

    // Slice the polygon along this line segment
    concavePoly.slicePolygon(line);

    // Retrieve a decomposed subpolygons by index
    // This works exactly the same when retrieving subpolygons
    // after convex decomposition
    cxd::ConcavePolygon subPolygon = concavePoly.getSubPolygon(0);

    // Retrieve vertices from the subpolygon (also applies to the
    // concave polygon we defined earlier)
    std::vector<cxd::Vertex > subPolyVerts = subPolygon.getVertices();

    // Create a vector and retrieve all convex subpolygons
    // as a single list
    std::vector<cxd::ConcavePolygon > subPolygonList;
    concavePoly.returnLowestLevelPolys(subPolygonList);

    return 0;
}
```
