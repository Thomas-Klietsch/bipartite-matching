// Copyright (c) 2024 Thomas Klietsch, all rights reserved.
//
// Licensed under the GNU Lesser General Public License, version 3.0 or later
//
// This program is free software: you can redistribute it and/or
// modify it under the terms of the GNU Lesser General Public License
// as published by the Free Software Foundation, either version 3 of
// the License, or ( at your option ) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.See the
// GNU Lesser General Public License for more details.
//
// You should have received a copy of the GNU Lesser General
// Public License along with this program.If not, see < https://www.gnu.org/licenses/>. 

#pragma once

#include <cstdint>
#include <vector>

namespace Bipartite_Matching
{

	class Matrix final
	{

	private:

		uint8_t n_rows{ 0 };
		uint8_t n_columns{ 0 };

		std::vector<std::vector<uint8_t>> cell{ false };

		// If row/column is out of range, dummy is referenced
		uint8_t dummy{ false };

	public:

		Matrix() {};

		Matrix(
			uint8_t const& rows,
			uint8_t const& columns)
		{
			if (!rows || !columns)
				return;
			
			n_rows = rows;
			n_columns = columns;

			cell = std::vector<std::vector<uint8_t>>(rows, std::vector<uint8_t>(columns, false));
		};

		// Read/Write the value at [row,column]
		uint8_t& operator () (
			uint8_t const& row,
			uint8_t const& column)
		{
			if ((row >= n_rows) || (column >= n_columns))
				return dummy;

			return cell[row][column];
		};

		// Get the value at [row,column]
		uint8_t operator () (
			uint8_t const& row,
			uint8_t const& column) const
		{
			if ((row >= n_rows) || (column >= n_columns))
				return false;

			return cell[row][column];
		};

		void set_row(
			uint8_t const& index,
			std::vector<uint8_t> const& data)
		{
			if ((!n_columns) || (data.size() != n_columns))
				return;

			cell[index] = data;
		};

		void set_column(
			uint8_t const& index,
			std::vector<uint8_t> const& data)
		{
			if ((!n_rows) || (data.size() != n_rows))
				return;

			for (uint16_t i{ 0 };i < n_rows;++i)
				cell[i][index] = data[i];
		};

		// Returns number of rows and columns
		std::tuple< uint8_t, uint8_t> size() const
		{
			return std::tuple(n_rows, n_columns);
		};

	};

	// Given a matrix (boolean) containing possible edges:
	// Return list of maximal possible number of connections/edges,
	// e.g.[column] = row, and number of matched edges.
	// If negative value for [column], no connection is possible
	std::tuple<std::vector<int16_t>, uint16_t> Maximum(
		Matrix const& nodes
	)
	{
		auto const [n_rows, n_columns] = nodes.size();

		// No edges by default
		std::vector<int16_t> edge_list(n_columns, -1);

		// Recursive (lambda) test for assigning an edge
		auto recursive = [&](
			// Self reference, needed for recursion, C++23
			this auto const& meta,
			uint16_t const& row,
			std::vector<bool>& used_list
			) -> bool
		{
			// Test all columns for input: row
			for (uint16_t column = 0; column < n_columns; ++column)
			{
				// Check if edge is possible, and not currently used
				if (nodes(row, column) && !used_list[column])
				{
					used_list[column] = true;

					// Assign edge:
					// If no edge has been assigned to column, or
					// if edge can be assigned to a later column
					if ((edge_list[column] < 0) || meta(edge_list[column], used_list))
					{
						edge_list[column] = row;
						return true;
					}
				}
			}
			return false;
		};

		// Find edges
		uint16_t edges{ 0 };
		for (uint16_t row = 0; row < n_rows; ++row)
		{
			// List of used columns 
			std::vector<bool> used_list(n_columns, false);

			// Test row for a column
			if (recursive(row, used_list))
				++edges;
		}

		return { edge_list, edges };
	};

};
