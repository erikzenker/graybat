/*******************************************************************************
 *
 * GRAPH TOPOLOGY GENERATORS
 *
 *******************************************************************************/

namespace topology {

    typedef unsigned                                                        VertexID;
    typedef std::pair<VertexID, VertexID>                                   EdgeDescription;
    typedef std::pair<std::vector<VertexID>, std::vector<EdgeDescription> > GraphDescription;

    GraphDescription fullyConnected(const unsigned verticesCount){
	std::vector<VertexID> vertices(verticesCount);

	assert(vertices.size() == verticesCount);

	std::vector<EdgeDescription> edges;

	for(unsigned i = 0; i < vertices.size(); ++i){
	    vertices.at(i) = i;
	    for(unsigned j = 0; j < vertices.size(); ++j){
		if(i == j){
		    continue;
		} 
		else {
		    edges.push_back(std::make_pair(i, j));
		}
	    }

	}

	return std::make_pair(vertices,edges);
    }


   GraphDescription star(const unsigned verticesCount){
       std::vector<VertexID> vertices(verticesCount);
    
	std::vector<EdgeDescription> edges;

	for(unsigned i = 0; i < vertices.size(); ++i){
	    vertices.at(i) = i;
	    if(i != 0){
		edges.push_back(std::make_pair(i, 0));
	    }
		
	}

	return std::make_pair(vertices,edges);
    }

    unsigned hammingDistance(unsigned a, unsigned b){
	unsigned abXor = a xor b;
	return (unsigned) __builtin_popcount(abXor);
    }

    GraphDescription hyperCube(const unsigned dimension){
	assert(dimension >= 1);
	std::vector<EdgeDescription> edges;

	unsigned verticesCount = pow(2, dimension);
	std::vector<VertexID> vertices(verticesCount);

	for(unsigned i = 0; i < vertices.size(); ++i){
	    vertices.at(i) = i;
	    for(unsigned j = 0; j < vertices.size(); ++j){
		if(hammingDistance(i, j) == 1){
		    edges.push_back(std::make_pair(i, j));
		}

	    }
	}
    
	return std::make_pair(vertices,edges);
    }

    
    GraphDescription grid(const unsigned height, const unsigned width){

	const unsigned verticesCount = height * width;
	std::vector<unsigned> vertices(verticesCount);
	std::vector<EdgeDescription> edges;

	for(unsigned i = 0; i < vertices.size(); ++i){
	    vertices.at(i) = i;
	    
	    if(i >= width){
		unsigned up   = i - width;
		edges.push_back(std::make_pair(i, up));
	    }

	    if(i < (verticesCount - width)){
		unsigned down = i + width;
		edges.push_back(std::make_pair(i,down));
	    }


	    if((i % width) != (width - 1)){
		int right = i + 1;
		edges.push_back(std::make_pair(i,right));
	    }

	    if((i % width) != 0){
		int left = i - 1;
		edges.push_back(std::make_pair(i, left));
	    }
	

	}

	return std::make_pair(vertices,edges);
    }


    GraphDescription gridDiagonal(const unsigned height, const unsigned width){
	const unsigned verticesCount = height * width;
	std::vector<unsigned> vertices(verticesCount);
	std::vector<EdgeDescription > edges;

	for(unsigned i = 0; i < vertices.size(); ++i){
	    vertices.at(i) = i;
	    
	    // UP
	    if(i >= width){
		unsigned up   = i - width;
		edges.push_back(std::make_pair(i, up));
	    }

	    // UP LEFT
	    if(i >= width and (i % width) != 0){
		unsigned up_left   = i - width - 1;
		edges.push_back(std::make_pair(i, up_left));
	    }

	    // UP RIGHT
	    if(i >= width and (i % width) != (width - 1)){
		unsigned up_right   = i - width + 1;
		edges.push_back(std::make_pair(i, up_right));
	    }

	    // DOWN
	    if(i < (verticesCount - width)){
		unsigned down = i + width;
		edges.push_back(std::make_pair(i, down));
	    }

	    // DOWN LEFT
	    if(i < (verticesCount - width) and (i % width) != 0){
		unsigned down_left = i + width - 1;
		edges.push_back(std::make_pair(i, down_left));
	    }

	    // DOWN RIGHT
	    if(i < (verticesCount - width) and (i % width) != (width - 1)){
		unsigned down_right = i + width + 1;
		edges.push_back(std::make_pair(i, down_right));
	    }

	    // RIGHT
	    if((i % width) != (width - 1)){
		int right = i + 1;
		edges.push_back(std::make_pair(i, right));
	    }

	    // LEFT
	    if((i % width) != 0){
		int left = i - 1;
		edges.push_back(std::make_pair(i, left));
	    }

	    

	}
	return std::make_pair(vertices,edges);
    }

} /* topology */
