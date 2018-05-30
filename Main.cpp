//An interface to a graph through an adjacency matrix
//Created by: Ethan Reese
//May 29th, 2018

#include <cstdlib>
#include <cstring>
#include <iostream>
#include <sstream>
#include <fstream>
#include <deque>
#include <list>
#include <quene>

using namespace std;

struct Vertex{
     char* label;
     int index;
}

int main(){
     bool going = true;
     char* input;
     int x[20][20];
     //Clear the array to make sure all values are zeroes
     for(int i = 0; i < 20; i++){
          for(int j = 0; j < 20; j++){
             x[i][j] = 0; 
          }
     }
     vector<Vertex*> graph;
     while(going){
          cout << "Enter V to add vertex, E to add edge, R to remove vertex, A to remove edge, F to find shortest weighted path, P to print adjacency matrix, and N to quit." << endl;
          cout << ": ";
          input = new char[80];
          cin >> input;
          if(strcmp(input, "V") == 0){
               cout << "Enter label: ";
               char* input_1 = new char[80];
               cin >> input_1;
               //Find the location of the first free index of the array
               int find = -1;
               //The row column is set to negative 1 if the index is filled
               for(int i = 0; i < 20; i++){
                    if(x[i][i] != -1){
                         find = i;
                    }
               }
               //If find is unchanged then it means that there are already 20 things in the graph
               if(find == -1){
                    cout << "There are more than 20 items in the graph" << endl;
                    continue;
               }
               //Turn the data into a struct and add it to the vector
               struct Vertex* vertex = new struct Vertex();
               strcpy(vertex->label, input_1);
               vertex->index = find;
               vertex.at

          }
          else if(strcmp(input, "N") == 0){
               return 0;
          }

     }
}
