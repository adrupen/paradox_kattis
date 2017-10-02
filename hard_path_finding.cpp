#include <iostream>
#include <algorithm>
#include <vector>
#include <iterator>

using std::vector;
using std::cout;
using std::endl;

struct GraphNode{
	int index;
	int x;
	int y;
	int weight;
	GraphNode(int i, int _x, int _y, int w){
		index = i;
		x = _x;
		y = _y;
		weight = w;
	}
	bool operator==(const int other_index) {
    	return index == other_index;
	}
};

struct PathNode{
	int distance;
	int parent;
	PathNode(int d, int p){
		distance = d;
		parent = p;
	}
};

bool cmp(const GraphNode &a, const GraphNode &b);

int FindPath(const int nStartX, const int nStartY,
             const int nTargetX, const int nTargetY, 
             const unsigned char* pMap, const int nMapWidth, const int nMapHeight,
             int* pOutBuffer, const int nOutBufferSize);

int main(){

	// Test case 1 - success
	unsigned char pMap[] = {1, 1, 1, 1, 0, 1, 0, 1, 0, 1, 1, 1};
	int pOutBuffer[12];
	int result = FindPath(0, 0, 1, 2, pMap, 4, 3, pOutBuffer, 12);

	cout << "distance: " << result << endl;
	cout << "path: ";
	for(int i=0;i<result;i++)
		cout << pOutBuffer[i] << " ";
	cout << endl;

	// Test case 2 - Buffer size abort
	unsigned char pMap2[] = {0, 0, 1, 0, 1,
							 1, 1, 0, 1, 1,
							 1, 1, 1, 1, 1,
							 0, 0, 1, 1, 1,
							 1, 1, 1, 1, 1};
	int pOutBuffer2[2];
	result = FindPath(5, 0, 0, 5, pMap2, 5, 5, pOutBuffer2, 2);

	cout << "result: " << result << endl;
	cout << "path: ";
	for(int i=0;i<result;i++)
		cout << pOutBuffer2[i] << " ";
	cout << endl;

	// Test case 3 - Unreachable
	unsigned char pMap3[] = {0, 0, 1, 0, 1, 1, 1, 0, 1};
	int pOutBuffer3[22];
	result = FindPath(2, 0, 0, 2, pMap3, 3, 3, pOutBuffer3, 22);

	cout << "result: " << result << endl;
	cout << "path: ";
	for(int i=0;i<result;i++)
		cout << pOutBuffer3[i] << " ";
	cout << endl;

	// Test case 2 - Big ass maze
	unsigned char pMap4[] = {1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
							 1, 0, 0, 0, 0, 0, 0, 0, 0, 0,
							 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
							 0, 0, 0, 0, 0, 0, 0, 0, 0, 1,
							 1, 1, 1, 1, 1, 1, 1, 1, 1, 1};
	int pOutBuffer4[32];
	result = FindPath(9, 0, 0, 4, pMap4, 10, 5, pOutBuffer4, 32);

	cout << "result: " << result << endl;
	cout << "path: ";
	for(int i=0;i<result;i++)
		cout << pOutBuffer4[i] << " ";
	cout << endl;

	return 0;
}

int FindPath(const int nStartX, const int nStartY,
             const int nTargetX, const int nTargetY, 
             const unsigned char* pMap, const int nMapWidth, const int nMapHeight,
             int* pOutBuffer, const int nOutBufferSize){

	vector<GraphNode> min_heap;
	vector<PathNode> dist;

	int source_index = nStartY * nMapWidth + nStartX;
	int target_index = nTargetY * nMapWidth + nTargetX;

	// Init nodes
	for(int y = 0; y < nMapHeight; y++){
		for(int x = 0; x < nMapWidth; x++){
			min_heap.push_back(GraphNode(y * nMapWidth + x, x, y, INT_MAX));
			dist.push_back(PathNode(INT_MAX, -1));
		}
	}

	// Set source weight to 0
	dist[source_index].distance = 0;
	min_heap[source_index].weight = 0;
	std::make_heap(min_heap.begin(), min_heap.end(), cmp);

	while(!min_heap.empty()){

		// Pick node with smallest distance
		std::pop_heap(min_heap.begin(), min_heap.end(), cmp);
		GraphNode current_node = min_heap.back();
		min_heap.pop_back();

		//cout <<  "current_node: " << current_node.index << " (" << current_node.x << ", " << current_node.y << ") w: " << current_node.weight << endl;

		// Exceeded buffer size or node unreachable
		if(current_node.weight > nOutBufferSize){
			return -1;
		}
		// Success we are at target
		if(current_node.index == target_index){
			int p = current_node.index;
			for(int i=current_node.weight - 1; i >= 0; i--){
				pOutBuffer[i] = p;
				p = dist[p].parent;
			}
			return dist[current_node.index].distance;
		}

		// Check which neighbors can be accessed
		vector<int> neighbor;
		if(current_node.x != 0)
			if(pMap[current_node.index - 1] != 0)
				neighbor.push_back(-1);

		if(current_node.x != nMapWidth-1)
			if(pMap[current_node.index + 1] != 0)
				neighbor.push_back(1);

		if(current_node.y != 0)
			if(pMap[current_node.index - nMapWidth] != 0)
				neighbor.push_back(-nMapWidth);

		if(current_node.y != nMapHeight-1)
			if(pMap[current_node.index + nMapWidth] != 0)
				neighbor.push_back(nMapWidth);

		// Loop all neighbor
		while(!neighbor.empty()){
			auto itr = std::find(min_heap.begin(), min_heap.end(), current_node.index + neighbor.back()); neighbor.pop_back();
			if(itr != min_heap.end()){

				if(dist[current_node.index].distance != INT_MAX && dist[current_node.index].distance + 1 < dist[itr->index].distance){
					itr->weight = dist[current_node.index].distance + 1;
					dist[itr->index].distance = dist[current_node.index].distance + 1;
					dist[itr->index].parent = current_node.index;
				}
			}
		}
		// Reorder Heap
		std::make_heap(min_heap.begin(), min_heap.end(), cmp);
	}

	return -1;
}

bool cmp(const GraphNode &a, const GraphNode &b){
	return a.weight > b.weight;
}