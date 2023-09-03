#include <iostream>
#include <vector>

// Function to triangulate a polygon represented by a list of indices
std::vector<std::vector<int>> triangulatePolygon(const std::vector<int>& indices)
{
    if (indices.size() < 3) return {};

    std::vector<std::vector<int>> triangles;

        for (int i = 1; i < indices.size() - 1; ++i)
            triangles.push_back({ indices[0], indices[i], indices[i + 1] });

        return triangles;
}

int main()
{
    std::vector<int> polygonIndices = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12 };

    std::vector<std::vector<int>> triangles = triangulatePolygon(polygonIndices);

    for (const auto& triangle : triangles)
    {
        std::cout << "f ";
        for (const auto& index : triangle)
            std::cout << index << " ";
        std::cout << std::endl;
    }

    return 0;
}