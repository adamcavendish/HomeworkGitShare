#pragma once

template <typename Graph>
class BFSVisitor
{
public:
	/**
	 * @brief This is invoked on every vertex of the graph before the start of the graph search.
	 */
	virtual bool
	initialize_vertex(const typename Graph::size_type L_s, Graph & L_g)
	{ return true; }

	/**
	 * @brief This is invoked when a vertex is encountered for the first time.
	 */
	virtual bool
	discover_vertex(const typename Graph::size_type L_s, Graph & L_g)
	{ return true; }

	/**
	 * @brief This is invoked on a vertex as it is popped from the queue. This happens immediately before examine_edge() is invoked on each of the out-edges of vertex u.
	 */
	virtual bool
	examine_vertex(const typename Graph::size_type L_s, Graph & L_g)
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
	 * @brief @TODO
	 */
	virtual bool
	non_tree_edge(
			const typename Graph::size_type L_source,
			const typename Graph::size_type L_target,
			Graph & L_g)
	{ return true; }
	
	/**
	 * @brief This invoked on a vertex after all of its out edges have been added to the search tree and all of the adjacent vertices have been discovered (but before the out-edges of the adjacent vertices have been examined).
	 */
	virtual bool
	finish_vertex(const typename Graph::size_type L_s, Graph & L_g)
	{ return true; }
};//class BFSVisitor

