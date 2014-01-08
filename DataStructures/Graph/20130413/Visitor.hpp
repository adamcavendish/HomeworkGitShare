#pragma once

template <typename Graph>
class Visitor
{
public:
	/**
	 * @brief This is invoked on every vertex of the graph before the start of the graph search.
	 */
	virtual void
	initialize_vertex(Graph::size_type & L_s, Graph & L_g);

	/**
	 * @brief This is invoked when a vertex is encountered for the first time.
	 */
	virtual void
	discover_vertex(Graph::size_type & L_s, Graph & L_g);

	/**
	 * @brief This is invoked on a vertex as it is popped from the queue. This happens immediately before examine_edge() is invoked on each of the out-edges of vertex u.
	 */
	virtual void
	examine_vertex(Graph::size_type & L_s, Graph & L_g);

	/**
	 * @brief This is invoked on every out-edge of each vertex after it is discovered.
	 */
	virtual void
	examine_edge(
			Graph::size_type L_source,
			Graph::size_type L_target,
			Graph & L_g);
	
	/**
	 * @brief This invoked on a vertex after all of its out edges have been added to the search tree and all of the adjacent vertices have been discovered (but before the out-edges of the adjacent vertices have been examined).
	 */
	virtual void
	finish_vertex(Graph::size_type & L_s, Graph & L_g);
};//class BFSVisitor

