#pragma once

#include <iostream>
#include <vector>
#include <cmath>
#include <gtest/gtest.h>
#include "Utils.hpp"
#include "Polyhedron.hpp"

// https://google.github.io/googletest/

namespace SortLibrary {

	TEST(TestSorting, TestSelectionSort)
	{
		// normalizeVertex
		cout << "1) normalizeVertex() :" << endl;
		Vertex v = {0, 4.3, 5.0, 6.8};
		Vertex v0 = normalizeVertex(v);
		cout << "Modulo non normalizzato = " << sqrt(v.x * v.x + v.y * v.y + v.z * v.z) << endl;
		cout << "Modulo normalizzato = " << sqrt(v0.x * v0.x + v0.y * v0.y + v0.z * v0.z) << endl;
		
		// Tetrahedron, Octahedron, Icosahedron
		cout << "2) Tetrahedron(), Octahedron(), Icosahedron() :" << endl;
		Polyhedron P0 = Tetrahedron();
		if (P0.checkFaces())
			cout << "Tetraedro coerente" << endl;
		Polyhedron P1 = Octahedron();
		if (P1.checkFaces())
			cout << "Ottaedro coerente" << endl;
		Polyhedron P2 = Icosahedron();
		if (P2.checkFaces())
			cout << "Icosaedro coerente" << endl;
	}

}