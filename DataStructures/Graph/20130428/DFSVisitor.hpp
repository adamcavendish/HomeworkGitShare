#pragma once

/**
 * Provided Interface:
 * ` initialize_vertex
 * ` start_vertex
 * ` discover_vertex
 * ` examine_edge
 * ` tree_edge
 * ` back_edge
 * ` forward_or_cross_edge
 * ` finish_vertex
 */


template <typename Graph>
class DFSVisitor
{
public:
	/**
	 * @brief This is invoked on every vertex of the graph before the start of the graph search.
	 */
	virtual bool
	initialize_vertex(const typename Graph::size_type L_s, Graph & L_g)
	{ return true; }

	/**
	 * @brief This is invoked on the source vertex once before the start of the search.
	 */
	virtual bool
	start_vertex(const typename Graph::size_type L_s, Graph & L_g)
	{ return true; }

	/**
	 * @brief This is invoked when a vertex is encountered for the first time.
	 */
	virtual bool
	discover_vertex(const typename Graph::size_type L_s, Graph & L_g)
	{ return true; }

	/**
	 * @brief This is invoked on every out-edge of each vertex after it is discovered.
	 */
	virtual bool
	examine_edge(
			const typename Graph::size_type L_source,
			const typename Graph::size_type L_target,
			Graph & L_g)
	{ return true; }

	/**
	 * @brief This is invoked on each edge as it becomes a member of the edges that form the search tree.
	 */
	virtual bool
	tree_edge(
			const typename Graph::size_type L_source,
			const typename Graph::size_type L_target,
			Graph & L_g)
	{ return true; }

	/**
	 * @brief This is invoked on the back edges in the graph. For an undirected graph there is some ambiguity between tree edges and back edges since the edge (u,v) and (v,u) are the same edge, but both the tree_edge() and back_edge() functions will be invoked. One way to resolve this ambiguity is to record the tree edges, and then disregard the back-edges that are already marked as tree edges. An easy way to record tree edges is to record predecessors at the tree_edge event point.
	 */
	virtual bool
	back_edge(
			const typename Graph::size_type L_source,
			const typename Graph::size_type L_target,
			Graph & L_g)
	{ return true; }

	/**
	 * @brief This is invoked on forward or cross edges in the graph. In an undirected graph this method is never called.
	 */
	virtual bool
	forward_or_cross_edge(const typename Graph::size_type L_s, Graph & L_g)
	{ return true; }

	/**
	 * @brief This is invoked on vertex u after finish_vertex has been called for all the vertices in the DFS-tree rooted at vertex u. If vertex u is a leaf in the DFS-tree, then the finish_vertex function is called on u after all the out-edges of u have been examined.
	 */
	virtual bool
	finish_vertex(const typename Graph::size_type L_s, Graph & L_g)
	{ return true; }
};//class DFSVisitor

