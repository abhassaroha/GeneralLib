class BaseGraph {
	virtual BaseGraph();
	virtual int* adj(uint);
	virtual int numVertices();
	virtual int numEdges();
	virtual ~BaseGraph();
};
