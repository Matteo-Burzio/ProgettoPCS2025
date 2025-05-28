#pragma once

#include <gtest/gtest.h>

#include "Utils.hpp"


using namespace std;



// Input TEST

TEST(InputTest, InputCheck)
{
	
}


// Polyhedron TEST

TEST(PolyhedronTest, ValidTetrahedron)
{
	Polyhedron P = Tetrahedron();
	ASSERT_TRUE(P.checkFaces());
}


TEST(PolyhedronTest, ValidOctahedron)
{
	Polyhedron P = Octahedron();
	ASSERT_TRUE(P.checkFaces());
}


TEST(PolyhedronTest, ValidIcosahedron)
{
	Polyhedron P = Icosahedron();
	ASSERT_TRUE(P.checkFaces());
}


// Export TEST

TEST(ExportTest, ExportParaview)
{
	
}


// Outout Test

TEST(OutputTest, OutputWriting)
{
	
}