# ConvexDecomposition
## What does this library do?
This is a header only C++ library, made for decomposing and slicing concave polygons into convex polygons. This library also allows for user defined polygon slicing (see usage). 

The ConcavePolygon class uses a recursive data structure to either store 0 or 2 sub polygons. When a polygon is sliced, two sub polygons are generated split along a defined line segment.

Credits: The algorithm for decomposing concave polygons to convex can be found here: https://mpen.ca/406/bayazit (Mark Bayazit). Convex decomposition is achieved in O(n*r) time, where n is the number of polygon vertices, r is the number of reflex polygon vertices.


## Installation
To install this library, simply copy ConcavePolygon.h into your project and #include "ConcavePolygon.h".


## Usage
Define a set of vertices by creating an std::vector<Vertex > with a list of 2D positions.
To create a polygon, feed the Vertex vector into the ConcavePolygon constructor.

To decompose a polygon, call polygon.convexDecomp().

To slice a polygon along a line segment, define the line segment with LineSegment(Vec2 startPosition, Vec2 finalPosition) and call polygon.slicePolygon(LineSegment l).