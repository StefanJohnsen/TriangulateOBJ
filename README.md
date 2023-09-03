# Triangulation
Triangulation of a polygon is the process of dividing a polygon into a series of triangles.

## Context

To illustrate the concept of triangulation, let's consider a straightforward OBJ file featuring a clock-like mesh. This mesh is constructed with vertices resembling a clock, where the 12 o'clock position naturally resides at the top.

clock-triangles.obj
<pre>
# .obj file for a circle using clock numbers as vertices

v 0.5 0.866 0.0     #  1 o'clock
v 0.866 0.5 0.0     #  2 o'clock
v 1.0 0.0 0.0       #  3 o'clock
v 0.866 -0.5 0.0    #  4 o'clock
v 0.5 -0.866 0.0    #  5 o'clock
v 0.0 -1.0 0.0      #  6 o'clock
v -0.5 -0.866 0.0   #  7 o'clock
v -0.866 -0.5 0.0   #  8 o'clock
v -1.0 0.0 0.0      #  9 o'clock
v -0.866 0.5 0.0    # 10 o'clock
v -0.5 0.866 0.0    # 11 o'clock
v 0.0 1.0 0.0       # 12 o'clock
v 0.0 0.0 0.0       # center clock

g triangles
f 13 1 2   
f 13 2 3   
f 13 3 4   
f 13 4 5   
f 13 5 6   
f 13 6 7   
f 13 7 8   
f 13 8 9   
f 13 9 10  
f 13 10 11 
f 13 11 12 
f 13 12 1  
</pre>

Open the file in **Visual Studio** and you will see the clock and all the triangles as shown below (without numbers).

![Clock-Triangles](https://github.com/StefanJohnsen/TriangulationOBJ/blob/main/Pictures/clock-triangles.jpg)
<br>*(PS: Hide the grid and turn on Wire frame in Visual Studio)*

The most widespread method for representing meshes in OBJ files is by using triangles. 

Let's examine an OBJ file where the faces are represented as polygons.

clock-polygon.obj
<pre>
# .obj file for a circle using clock numbers as vertices

v 0.5 0.866 0.0     #  1 o'clock
v 0.866 0.5 0.0     #  2 o'clock
v 1.0 0.0 0.0       #  3 o'clock
v 0.866 -0.5 0.0    #  4 o'clock
v 0.5 -0.866 0.0    #  5 o'clock
v 0.0 -1.0 0.0      #  6 o'clock
v -0.5 -0.866 0.0   #  7 o'clock
v -0.866 -0.5 0.0   #  8 o'clock
v -1.0 0.0 0.0      #  9 o'clock
v -0.866 0.5 0.0    # 10 o'clock
v -0.5 0.866 0.0    # 11 o'clock
v 0.0 1.0 0.0       # 12 o'clock

g polygon
f 1 2 3 4 5 6 7 8 9 10 11 12
</pre>

Notice that the center vertex has been omitted since it's unnecessary when the clock's is respresented as a polygon.

![Clock-Polygon](https://github.com/StefanJohnsen/TriangulationOBJ/blob/main/Pictures/clock-polygon.jpg)

It can be a problem when faces in an OBJ file are presented as polygons for some viewers. Not all OBJ viewers or software applications support polygonal faces, which can lead to compatibility issues or incorrect rendering. To ensure better compatibility and proper display, converting these polygonal faces into triangles through triangulation is a common solution.

Therefore, the significant question here is, how can we convert this polygon, and others, into triangles?

# Polygon Types

### Convex Polygon

A convex polygon is a polygon with the following characteristics:
- All interior angles are less than 180 degrees.
- Any line segment drawn between two points inside the polygon will always remain entirely inside the polygon.

### Concave Polygon

A concave polygon is a polygon with the following characteristics:
- It has at least one interior angle that measures more than 180 degrees.
- "Dents" or "indentations" in the shape result in some angles being greater than 180 degrees.

### Complex Polygon

A complex polygon is a polygon with the following characteristics:
- It contains both convex and concave regions within its boundary.
- It combines elements of both convex and concave shapes, resulting in a more intricate and irregular overall structure.

In summary, these terms describe the overall shape characteristics of polygons. Convex polygons have all interior angles less than 180 degrees, concave polygons have at least one angle greater than 180 degrees, and complex polygons combine both convex and concave features within their boundaries.

![Clock-Polygon](https://github.com/StefanJohnsen/TriangulationOBJ/blob/main/Pictures/polygons.jpg) 

# Fan Algorithm for Convex Polygon Triangulation

### Considerations and Limitations

The fan algorithm is indeed a common and efficient method for triangulating convex polygons, and it typically works well for this specific class of polygons. However, there are some important considerations and limitations to keep in mind:

- Convexity Requirement: The fan algorithm is designed specifically for convex polygons. It relies on the fact that all interior angles of a convex polygon are less than 180 degrees. If you apply the fan algorithm to a non-convex polygon (one with interior angles greater than 180 degrees), it may not produce correct results.

- Efficiency: The fan algorithm is efficient for convex polygons and has a time complexity of O(n), where n is the number of vertices in the polygon. This makes it suitable for real-time applications.

- Vertex Order: The algorithm assumes that the vertices of the convex polygon are provided in a specific order, such as in clockwise or counterclockwise order. If the vertices are not in the expected order, you may need to preprocess the input to ensure they are correctly ordered.

- Degenerate Cases: In some cases, such as when vertices are collinear or very close together, the algorithm may produce degenerate triangles (triangles with zero area). Handling such cases appropriately may require additional checks.

In conclusion, the fan algorithm is a reliable and fast choice for triangulating convex polygons. 

### Triangulation Algorithm using Indices

Face list : f(i) = {f0, f1, f2, ... pN},  0 <= i < N

Given a list of indices `f(i)` representing the vertices of a polygon, where `i` ranges from 0 to `N-1`, and `N` is the number of indices in the list, the following steps are conducted to perform triangulation:

1. **Start with the Initial Index:** Begin with the initial index, `f(0)`.

2. **Iterate over Index Range:** Iterate over the range of index `i` from 1 to `N-1`.

3. **Create Triangles:** For each index `i`, create a triangle using the indices `f(0)`, `f(i)`, and `f(i+1)`. This forms a triangle that connects the vertex represented by `f(0)`, the vertex represented by `f(i)`, and the vertex represented by `f(i+1)` in the list of indices.

4. **Repeat Triangle Creation:** Repeat the triangle creation process for each `i` within the specified range, effectively creating a series of triangles that approximate the original polygon based on the provided indices.





*Another algorithm in existence is the "ear clipping triangulation algorithm." This algorithm involves the process of identifying an "ear" within the current polygon and subsequently removing it. In its initial form, Meister's version of the ear clipping algorithm has a time complexity of O(n^3), with the majority of the time being allocated to verifying the validity of newly formed triangles.*

Our routine is straightforward and efficient, characterized by a time complexity of O(n). The procedure will prove effective and correct for all concave polygons. However, convex or intricate polygons may not yield accurate triangulation results. 
