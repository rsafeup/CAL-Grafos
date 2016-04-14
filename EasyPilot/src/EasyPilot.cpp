
#include "EasyPilot.h"

EasyPilot::EasyPilot() {

	GraphViewer *gv = new GraphViewer(600, 600, true);
	gv->createWindow(600, 600);
	gv->defineVertexColor("blue");
	gv->defineEdgeColor("black");

	for(unsigned int i = 0; i < graph.getNumVertex(); i++)
		gv->addNode(graph.getVertexSet()[i]->getNodeId());

	for(unsigned int i = 0; i < graph.getNumVertex(); i++)
	{
		for(unsigned int j = 0; j < graph.getVertexSet()[i]->getAdj().size(); j++)
		{
			if(graph.getVertexSet()[i]->getAdj()[j].getTtwoWays())
				gv->addEdge(graph.getVertexSet()[i]->getAdj()[j].getId(), graph.getVertexSet()[i]->getNodeId(), graph.getVertexSet()[i]->getAdj()[j].getDest()->getNodeId(), EdgeType::UNDIRECTED);
			else
				gv->addEdge(graph.getVertexSet()[i]->getAdj()[j].getId(), graph.getVertexSet()[i]->getNodeId(), graph.getVertexSet()[i]->getAdj()[j].getDest()->getNodeId(), EdgeType::DIRECTED);

			gv->setEdgeLabel(graph.getVertexSet()[i]->getAdj()[j].getId(), graph.getVertexSet()[i]->getAdj()[j].getName());
		}
	}
}

EasyPilot::~EasyPilot() {
	// TODO Auto-generated destructor stub
}

bool readOSM(string filename) {
	string edgesFile = filename + "Edges.txt";
	string connectionsFile = filename + "Connections.txt";
	string nodesFile = filename + "Nodes.txt";

	ifstream nodes, edges, connections;
	string line, aux;
	size_t firstSemicolon, lastSemicolon;
	long nodeId, latitudeInDegrees, longitudeInDegrees;

	nodes.exceptions(ifstream::failbit | ifstream::badbit);

	try {
		nodes.open(nodesFile.c_str(), ifstream::in);
		while (nodes >> line) {
			firstSemicolon = line.find(';');
			lastSemicolon = line.find(';', firstSemicolon + 1);
			aux = line.substr(0, firstSemicolon);
			nodeId = atol(aux.c_str());
			aux = line.substr(firstSemicolon + 1, lastSemicolon - 1);
			latitudeInDegrees = atol(aux.c_str());
			aux = line.substr(lastSemicolon + 1, line.size());
			longitudeInDegrees = atol(aux.c_str());
		}
	} catch (ifstream::failure &e) {
		cout << "Error while opening " << nodesFile << endl;
	}

	nodes.close();

	line.clear();
	aux.clear();
	long roadId;
	string roadName;
	bool isTwoWay;

	edges.exceptions(ifstream::failbit | ifstream::badbit);

	try {
		edges.open(edgesFile.c_str(), ifstream::in);
		while (edges >> line) {
			firstSemicolon = line.find(';');
			lastSemicolon = line.find(';', firstSemicolon + 1);
			aux = line.substr(0, firstSemicolon);
			roadId = atol(aux.c_str());
			aux = line.substr(firstSemicolon + 1, lastSemicolon - 1);
			roadName = aux.c_str();
			aux = line.substr(lastSemicolon + 1, line.size());
			if(aux == "False")
				isTwoWay = false;
			else isTwoWay = true;
		}
	} catch (ifstream::failure &e) {
		cout << "Error while opening " << edgesFile << endl;
	}

	edges.close();

	line.clear();
	aux.clear();
	long node1Id, node2Id;

	connections.exceptions(ifstream::failbit | ifstream::badbit);

	try {
		connections.open(connectionsFile.c_str(), ifstream::in);
		while (connections >> line) {
			firstSemicolon = line.find(';');
			lastSemicolon = line.find(';', firstSemicolon + 1);
			aux = line.substr(0, firstSemicolon);
			roadId = atol(aux.c_str());
			aux = line.substr(firstSemicolon + 1, lastSemicolon - 1);
			node1Id = atol(aux.c_str());
			aux = line.substr(lastSemicolon + 1, line.size());
			node2Id = atol(aux.c_str());
		}
	} catch (ifstream::failure &e) {
		cout << "Error while opening " << connectionsFile << endl;
	}

	connections.close();
	return true;
}
