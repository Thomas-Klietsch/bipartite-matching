#include <iostream>
#include <vector>

#include "./bipartite_matching.hpp"

int main()
{
	// Overdetermined matrix
	Bipartite_Matching::Matrix nodes(5, 4);
	// Row 0 can be assigned to all columns
	nodes.set_row(0, { 1,1,1,1 });
	// Rows 1-4 can only be assigned to column 0-2
	nodes.set_row(1, { 1,1,1,0 });
	nodes.set_row(2, { 1,1,1,0 });
	nodes.set_row(3, { 1,1,1,0 });
	nodes.set_row(4, { 1,1,1,0 });

	auto [edge_list, n_edges] = Bipartite_Matching::Maximum(nodes);

	std::cout << "Solution:\n";
	std::cout << "Edges " << n_edges << "\n";

	for (uint16_t i{ 0 };i < edge_list.size();++i)
		std::cout << "Column " << i << " row " << edge_list[i] << "\n";

	return 0;
};
