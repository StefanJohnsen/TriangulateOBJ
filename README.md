# Triangulation
Triangulation of a polygon is the process of dividing a polygon into a series of triangles


To illustrate the concept of triangulation, let's consider a straightforward OBJ file featuring a clock-like polygon. This polygon is constructed with vertices resembling a clock, where the 12 o'clock position naturally resides at the top.
<pre>
# .obj file for a circle using clock numbers as vertices

v 0.0 1.0 0.0       # 12 o'clock
v 0.5 0.866 0.0     # 1 o'clock
v 0.866 0.5 0.0     # 2 o'clock
v 1.0 0.0 0.0       # 3 o'clock
v 0.866 -0.5 0.0    # 4 o'clock
v 0.5 -0.866 0.0    # 5 o'clock
v 0.0 -1.0 0.0      # 6 o'clock
v -0.5 -0.866 0.0   # 7 o'clock
v -0.866 -0.5 0.0   # 8 o'clock
v -1.0 0.0 0.0      # 9 o'clock
v -0.866 0.5 0.0    # 10 o'clock
v -0.5 0.866 0.0    # 11 o'clock

g Polygon
f 1 2 3 4 5 6 7 8 9 10 11 12
</pre>

As observed, a polygon is present.<br>

![Polygon](https://github.com/StefanJohnsen/TriangulationOBJ/blob/main/Pictures/triangulation.jpg)

When dealing with polygons within a .obj file, we can follow a routine to convert these polygons into triangles for better compatibility and rendering. 

Let's assume we have a face list denoted as f(n) = {f0, f1, f2, ... pN}. We want to perform a process that generates triangles using these indices.

For each index in the list, the following steps are conducted:

- We begin with the initial polygon, f(0), from the list.

- Iterate over the range of indices i from 0 to N-1 (where N is the total number of indices in the list).

- For each i, we create a triangle using the indices of three points: f(0), f(i), and f(i+1). 
This forms a triangle that connects the starting indices(0) of the polygon, the current indices(i), and the next polygon indices(i+1) in the list.

- Repeat the triangle creation process for each i within the specified range, effectively creating a series of triangles that approximate the original polygon.

Following this routine, we break down complex polygons into simpler triangular elements, making it easier to work with them in 3D rendering and other applications that expect triangles. This conversion process ensures that the resulting triangles provide a good representation of the original polygon's shape and structure.

*Another algorithm in existence is the "ear clipping triangulation algorithm." This algorithm involves the process of identifying an "ear" within the current polygon and subsequently removing it. In its initial form, Meister's version of the ear clipping algorithm has a time complexity of O(n^3), with the majority of the time being allocated to verifying the validity of newly formed triangles.*

Our routine is straightforward and efficient, characterized by a time complexity of O(n). The procedure will prove effective and correct for all concave polygons. However, convex or intricate polygons may not yield accurate triangulation results. 
