# Triangulation ([new release](https://github.com/StefanJohnsen/TriangulateOBJ/releases))
A lightweight, header-only file that converts all polygons in a Wavefront OBJ file to triangles.

### Sample console application
We've developed a console application for a practical demonstration of its usage. 
This sample application is found in the [TriangulateOBJ-App](https://github.com/StefanJohnsen/TriangulateOBJ-App) repository. It serves as a guide on integrating and utilising the functions provided by our header-only file.

### Intended Users
1. **Game Developers**: Optimized models are key to performance in game development. Triangular polygons are computationally less intensive and are often preferred. With this tool, developers can easily ensure their 3D assets are optimized for real-time rendering.
2. **CAD Professionals**: Triangular polygons often provide smoother transitions when transitioning from CAD to visualization tools or VR platforms. This tool offers an easy step in the conversion process.
3. **3D Printing Enthusiasts**: Some 3D printing software may require models to be triangulated for accurate print outputs. Using this application, enthusiasts can ensure their models are ready for printing.
4. **Educators and Students**: Those teaching or learning about 3D modelling, graphics, or computer graphics algorithms can benefit from a lightweight tool to quickly triangulate models, helping in understanding the principles of 3D geometry.
5. **Software Developers**: For those integrating 3D features in their applications or looking to modify Wavefront OBJ files programmatically, this utility provides a no-fuss, dependency-free method to ensure models are triangulated.
6. **3D Artists and Designers**: Often, designers create complex models with various polygon types, but some rendering or game engines might only accept triangular polygons. This tool aids in preparing models to be compatible with such systems without the need for heavy-duty software.

### Compatibility and Dependencies
- C++ 11 Standard
- Standard Template Library (STL)

This project is designed to be compatible with C++11 and utilizes solely C++ Standard Template Library (STL) components. It has been thoughtfully engineered to function independently without the need for any external libraries or dependencies. This design ensures the project remains self-contained, promoting simplicity and ease of integration into your development environment.<br>

### OS Support
- Windows
- Linux
- macOS

### Usage
Copy `TriangulateOBJ.h` to your project and include the file.

```
#include <string>
#include "TriangulateOBJ.h"

int main()
{
   std::string source("C:\\temp\\your.obj");
   std::string target("C:\\temp\\your.triangulated.obj");

   return obj::Triangulate(source, target) ? 0 : 1;
}
```

# Context
Triangulation of a polygon is the process of dividing a polygon into a series of triangles.<br>
To illustrate the concept of triangulation, let's consider a straightforward OBJ file featuring a clock-like mesh. This mesh is constructed with vertices resembling a clock, where the 12 o'clock position naturally resides at the top.

clock.obj
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

Open the file in **Visual Studio**, and you will see the clock and all the triangles as shown below (without numbers).

![Clock](https://github.com/StefanJohnsen/TriangulateOBJ/blob/main/Pictures/clock.jpg)
<br>*(PS: Hide the grid and turn on Wire frame in Visual Studio)*

The most widespread method for representing meshes in OBJ files is by using triangles. 

Let's examine an OBJ file where the faces are represented as polygons.

convex.obj
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

g circle
f 1 2 3 4 5 6 7 8 9 10 11 12
</pre>

![convex](https://github.com/StefanJohnsen/TriangulateOBJ/blob/main/Pictures/convex.jpg)

It can be a problem when faces in an OBJ file are presented as polygons for some viewers. Not all OBJ viewers or software applications support polygonal faces, which can lead to compatibility issues or incorrect rendering. Converting these polygonal faces into triangles through triangulation is a common solution to ensure better compatibility and proper display.

Therefore, the fundamental question emerges: How can we triangulate this polygon, and others similar to it, solely using existing vertex points without introducing any new ones?

Before we proceed with the solution, we should explore the various types of polygons. If you're already knowledgeable about this topic, please skip the next section.

# Polygon Types

### Convex Polygon

A convex polygon is a polygon with the following characteristics:
- All interior angles are less than 180 degrees.
- Any line segment drawn between two points inside the polygon will always remain entirely inside the polygon.

### Concave Polygon

A concave polygon is a polygon with the following characteristics:
- It has at least one interior angle that measures more than 180 degrees.
- "Dents" or "indentations" in the shape result in some angles greater than 180 degrees.

### Complex Polygon

A complex polygon is a polygon with the following characteristics:
- It contains both convex and concave regions within its boundary.
- It combines elements of both convex and concave shapes, resulting in a more intricate and irregular overall structure.

In summary, these terms describe the overall shape characteristics of polygons. Convex polygons have all interior angles less than 180 degrees. Concave polygons have at least one angle greater than 180 degrees, and complex polygons combine convex and concave features within their boundaries.

![Clock-Polygon](https://github.com/StefanJohnsen/TriangulationOBJ/blob/main/Pictures/polygons.jpg) 

# Triangulation of **Convex Polygon** using **Fan Algorithm**

### Considerations and Limitations
The fan algorithm is a common and efficient method for triangulating convex polygons, and it typically works well for this specific class of polygons. However, there are some important considerations and limitations to keep in mind:

- Convexity Requirement: The fan algorithm is designed specifically for convex polygons. It relies on the fact that all interior angles of a convex polygon are less than 180 degrees. Applying the fan algorithm to a non-convex polygon (one with interior angles greater than 180 degrees) may not produce correct results.

- Efficiency: The fan algorithm is efficient for convex polygons and has a time complexity of O(n), where n is the number of vertices in the polygon. This makes it suitable for real-time applications.

- Vertex Order: The algorithm assumes that the vertices of the convex polygon are provided in a specific order, such as in clockwise or counterclockwise order. If the vertices are not in the expected order, you may need to preprocess the input to ensure they are correctly ordered.

- Degenerate Cases: In some cases, such as when vertices are collinear or very close together, the algorithm may produce degenerate triangles (triangles with zero areas). Handling such cases appropriately may require additional checks.

In conclusion, the fan algorithm is reliable and fast for triangulating convex polygons. 

### Triangulation Algorithm using Indices
f(i) = {f0, f1, f2, ... },  0 <= i < N

Given a list of indices `f(i)` representing the vertices of a polygon, where `i` ranges from 0 to `N-1`, and `N` is the number of indices in the list, the following steps are conducted to perform triangulation:

1. **Start with the Initial Index:** Begin with the initial index, `f(0)`.

2. **Iterate over Index Range:** Iterate over the range of index `i` from 1 to `N-1`.

3. **Create Triangles:** For each index `i`, create a triangle using the indices `f(0)`, `f(i)`, and `f(i+1)`. This forms a triangle that connects the vertex represented by `f(0)`, the vertex represented by `f(i)`, and the vertex represented by `f(i+1)` in the list of indices.

4. **Repeat Triangle Creation:** Repeat the triangle creation process for each `i` within the specified range, effectively creating a series of triangles that approximate the original polygon based on the provided indices.

# Example Triangulate convex.obj

Build or download a prebuild TriangulateOBJ.exe.<br>
Copy TriangulateOBJ.exe to the TriangulateOBJ/ObjFiles (having the exe in the same directory simplifies the path.)

Run as follows

   ```bash
   TriangulateOBJ convex.obj
   ```

   ```bash

   convex.obj has been triangulated

   --------------------------------------------------
   convex.triangulated.obj 1KB
   --------------------------------------------------
   Face metrics
   --------------------------------------------------
   Polygons triangulated : 1
   Existing triangles    : 0
   Created triangles     : 10  +757 bytes
   --------------------------------------------------
   Total triangles       : 10
   Total vertices        : 13
   --------------------------------------------------
   Execution time        : 8 milliseconds
   --------------------------------------------------
```

convex.triangulated.obj
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

g circle
f 1 2 3
f 1 3 4
f 1 4 5
f 1 5 6
f 1 6 7
f 1 7 8
f 1 8 9
f 1 9 10
f 1 10 11
f 1 11 12
</pre>

Open convex.triangulated.obj in Visual Studio.

![triangulation](https://github.com/StefanJohnsen/TriangulateOBJ/blob/main/Pictures/triangulation.jpg)
<br>*The polygon has been triangulated.*

# License
This software is released under the GNU General Public License v3.0 terms.<br> 
Details and terms of this license can be found at: https://www.gnu.org/licenses/gpl-3.0.html<br><br>
For those who require the freedom to operate without the constraints of the GPL,<br>
a commercial license can be obtained by contacting the author at stefan.johnsen@outlook.com
