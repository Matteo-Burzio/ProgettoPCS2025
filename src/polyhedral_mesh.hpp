#pragma once

#include <iostream>
#include "Eigen/Eigen"

using namespace std;
using namespace Eigen;


namespace PolyhedralLibrary {

struct polyhedral_mesh
{
    // Number of cells of each dimension
    unsigned int num_cell0D;
    unsigned int num_cell1D;
    unsigned int num_cell2D;
    unsigned int num_cell3D;

    // Vectors storing the Ids of each type cell
    vector<unsigned int> id_cell0D;
    vector<unsigned int> id_cell1D;
    vector<unsigned int> id_cell2D;
    vector<unsigned int> id_cell3D;

    // 0D cells are points
    // Matrix which stores the (X,Y,Z) coordinates for each point (as doubles)
    Eigen::MatrixXd coords_cell0D;

    // 1D cells are segments
    // Matrix which stores the IDs of the two points at the ends of each segment (as integers)
    Eigen::MatrixXi extrema_cell1D;

    // 2D cells are polygons
    // Vector of vectors storing the IDs of the vertices of each polygon
    vector<vector<unsigned int>> vertices_cell2D;
    // Vector of vectors storing the Ids of the edges of each polygon
    vector<vector<unsigned int>> edges_cell2D;

    // 3D cells are polyhedra
    // Vector of vectors storing the IDs of the vertices of each polyhedra
    vector<vector<unsigned int>> vertices_cell3D;
    // Vector of vectors storing the Ids of the edges of each polyhedra
    vector<vector<unsigned int>> edges_cell3D;
    // Vector of vectors storing the Ids of the faces of each polyhedra
    vector<vector<unsigned int>> faces_cell3D;

    // Markers for shortest path algorythm
};

}
