#ifndef TUTORIAL_SANDBOX_MESH_DATA_STRUCT_H
#define TUTORIAL_SANDBOX_MESH_DATA_STRUCT_H


#include <igl/edge_flaps.h>
#include <igl/shortest_edge_and_midpoint.h>
#include <igl/read_triangle_mesh.h>
#include <Eigen/Core>
#include <iostream>
#include <set>
#include <vector>


#pragma once
class Mesh_Data_Struct
{
public:
	Eigen::MatrixXd V, OV;
	Eigen::MatrixXi F, OF;
	// Prepare array-based edge data structures and priority queue
	Eigen::VectorXi EMAP;
	Eigen::MatrixXi E, EF, EI;
	typedef std::set<std::pair<double, int> > PriorityQueue;
	PriorityQueue* Q = new PriorityQueue();
	std::vector<PriorityQueue::iterator >* Qit = new std::vector<PriorityQueue::iterator>();
	// If an edge were collapsed, we'd collapse it to these points:
	Eigen::MatrixXd C;
	int num_collapsed; // ??
	Mesh_Data_Struct(std::string filename); //constructor
	~Mesh_Data_Struct(); //destructor

};
#endif // !Mesh_Data_Struct_HEADER