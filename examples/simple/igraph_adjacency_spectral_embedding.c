/* -*- mode: C -*-  */
/* 
   IGraph library.
   Copyright (C) 2013  Gabor Csardi <csardi.gabor@gmail.com>
   334 Harvard street, Cambridge, MA 02139 USA
   
   This program is free software; you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation; either version 2 of the License, or
   (at your option) any later version.
   
   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.
   
   You should have received a copy of the GNU General Public License
   along with this program; if not, write to the Free Software
   Foundation, Inc.,  51 Franklin Street, Fifth Floor, Boston, MA 
   02110-1301 USA

*/

#include <igraph.h>

/*
	
	R 
	library(igraph)
	g <- graph.tree(10, 3, mode="out")
	A <- get.adjacency(g)
	svd(A + .5 * degree(g) * diag(vcount(g)))

*/

int main() {

	igraph_t graph;
	igraph_vector_t D;
	igraph_matrix_t U, V;
	igraph_arpack_options_t options;
	
	igraph_tree(&graph, /*n=*/ 10, /*children=*/ 3, IGRAPH_TREE_OUT);

	igraph_vector_init(&D, 0);
	igraph_matrix_init(&U, 0, 0);
	igraph_matrix_init(&V, 0, 0);
	igraph_arpack_options_init(&options);

	igraph_adjacency_spectral_embedding(&graph, 4, &D, &U, &V, /*c=*/ .5, 
																			&options);
	
	igraph_vector_printf(&D, "%8.4f"); printf("--\n");
	igraph_matrix_printf(&U, "%8.4f"); printf("--\n");
	igraph_matrix_printf(&V, "%8.4f");
	
	igraph_matrix_destroy(&V);
	igraph_matrix_destroy(&U);
	igraph_vector_destroy(&D);

	return 0;
}
