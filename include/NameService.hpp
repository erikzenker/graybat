#pragma once
#include <map> /* map */

template <typename T_Graph, typename T_Communicator>
struct NameService {
    typedef T_Communicator                   Communicator;
    typedef T_Graph                          Graph;
    typedef typename Graph::Vertex           Vertex;
    typedef typename Communicator::CommID    CommID;
    typedef typename Vertex::ID              VertexID;
    typedef unsigned                         GraphContext;
    typedef typename Communicator::Context   CommunicatorContext;
    typedef typename Communicator::ContextID CommunicatorContextID;
    typedef typename Communicator::BinaryOperations BinaryOperations;

    NameService(Graph& graph, Communicator& communicator) : 
	graph(graph),
	communicator(communicator),
	graphContextCount(0){
	
	contextMap[graphContextCount] = communicator.getInitialContext().getContextID();

    }

    std::map<VertexID, CommID> commMap;
    std::map<GraphContext, CommunicatorContextID> contextMap;
    Graph& graph;
    Communicator& communicator;
    unsigned graphContextCount;


    void announce(const std::vector<Vertex> vertices){
	CommunicatorContext communicatorContext = communicator.getInitialContext();

    	// Each announces how many nodes it manages
    	std::array<unsigned, 1> myVerticesCount {{(unsigned) vertices.size()}};
    	std::array<unsigned, 1> maxVerticesCount  {{0}};
    	communicator.allReduce(communicatorContext, BinaryOperations::MAX, myVerticesCount, maxVerticesCount);
	 
	
    	for(unsigned i = 0; i < maxVerticesCount[0]; ++i){
    	    const size_t communicatorContextSize = communicatorContext.size();
    	    std::array<int, 1> sendData{{-1}};
    	    std::vector<int> recvData(communicatorContextSize);

    	    if(i < vertices.size()){
    	    	sendData[0] = vertices.at(i).id;
    	    }
    	    else{
    	    	sendData[0] = -1;
    	    }

    	    communicator.allGather(communicatorContext, sendData, recvData);

    	    for(unsigned commID = 0; commID < communicatorContextSize; ++commID){
    	    	if(recvData[commID] != -1){
    		    VertexID vertexID = (VertexID) recvData[commID];
    		    commMap[vertexID] = commID;
		    
    	    	}
    	    }

    	}

    }

    GraphContext createGraphContext(const std::vector<Vertex> vertices, const GraphContext oldGraphContext){
	// Collect communicator which manage vertices
	std::vector<CommID> commIDs;
	for(Vertex vertex : vertices){
	    commIDs.push_back(commMap[vertex]);
	}

	// Create new communicator context
	CommunicatorContext oldCommunicatorContext = contextMap[oldGraphContext];
	CommunicatorContext newCommunicatorContext = communicator.getContext(commIDs, oldCommunicatorContext);
	GraphContext newGraphContext(++graphContextCount);
	
	contextMap[newGraphContext] = newCommunicatorContext;
	
	return newGraphContext;
    }

    GraphContext getGlobalGraphContext(){
	return contextMap[0];
    }

    // void announce(const Vertex vertex, const Context context){
    // 	std::vector<Vertex> vertices;
    // 	vertices.push_back(vertex);
    // 	announce(vertices, context, communicator);
    // }

    // CommID getCommID(Vertex vertex, Context context){
    // 	CommID commID = commMap.at(context.getContextID()).at(vertex.id);
    // 	return commID;
	
    // }

};
