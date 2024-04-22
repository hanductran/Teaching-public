/*
An example to use disjoint sets data structure to generate 4-by-4 maze
*/
#include <iostream>
#include <vector>

std::vector<int> parent = {-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1};
int faces[36][2] = {
   {-1,1},
   {-1,2},
   {-1,3},
   {0,1},
   {1,2},
   {2,3},
   {3,-1},
   {0,4},
   {1,5},
   {2,6},
   {3,7},
   {-1,4},
   {4,5},
   {5,6},
   {6,7},
   {7,-1},
   {4,8},
   {5,9},
   {6,10},
   {7,11},
   {-1,8},
   {8,9},
   {9,10},
   {10,11},
   {11,-1},
   {8,12},
   {9,13},
   {10,14},
   {11,15},
   {-1,12},
   {12,13},
   {13,14},
   {14,15},
   {12,-1},
   {13,-1},
   {14,-1}
};

int find_noRecursive(int x) {
   while (parent[x] >= 0) {
      x = parent[x];
   }
   return x;
}

int find(int x) {
   if (parent[x] < 0) {
      return x;
   } else {
      return find(parent[x]);
   }
}

int find_pC(int x) {
   if (parent[x] < 0) {
      return x;
   } else {
      return parent[x] = find_pC(parent[x]);
   }
}

void unioBySize(int x_1, int x_2) {
   int root_1 = find_pC(x_1);
   int root_2 = find_pC(x_2);
   if (root_1 == root_2) {
      std::cout << "unioBySize:: x_1 and x_2 are in the same set! \n";
      return;
   }
   if (parent[root_2] < parent[root_1]) { // tree_1 is smaller
      parent[root_2] += parent[root_1]; // update size of tree_2
      parent[root_1] = root_2; // merge tree_1 to tree_2
   } else {
      parent[root_1] += parent[root_2];  // update size of tree_1
      parent[root_2] = root_1; // merge tree_2 to tree_1
   }
}

void unionByRank(int x_1, int x_2) {
   int root_1 = find(x_1);
   int root_2 = find(x_2);
   if (root_1 == root_2) {
      std::cout << "unionByRank:: x_1 and x_2 are in the same set! \n";
      return;
   }
   /*
   WRITE YOUR CODE HERE
   */
}

int main() {
   const int nCells = parent.size();
   const std::vector<unsigned int> randomFaces = {13,27,21,4,9,30,7,23,8,5,22,18,32,17,3,25,14};

   for (int i = 0; i < randomFaces.size(); i++) {
      int faceId = randomFaces[i];
      int cell_1 = faces[faceId][0];
      int cell_2 = faces[faceId][1];
      if ((cell_1 < 0) || (cell_2 < 0)) {
         std::cout << "error at face " << faceId << "\n";
         return 0;
      }
      unioBySize(cell_1, cell_2);
      //unionByRank(cell_1, cell_2);
   }

   std::cout << "parent = [ ";
   for (int i = 0; i < parent.size(); i++) {
      std::cout << parent[i] << ", ";
   }
   std::cout << "]\n";
   return 0;
}