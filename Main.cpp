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
#include <vector>

using namespace std;

struct Vertex* lookUp(vector<Vertex*>, char*);
int path(vector<Vertex*> graph, int x[20][20], struct Vertex* start, struct Vertex* end);

struct Vertex{
     char* label;
     int index;
     int solved;
};

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
     for(int i = 0; i<20; i++){
          graph.push_back(NULL);
     }
     while(going){
          cout << "Enter V to add vertex, E to add edge, R to remove edge, A to remove vertex, F to find shortest weighted path, P to print adjacency matrix, and N to quit." << endl;
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
                         break;
                    }
               }
               //If find is unchanged then it means that there are already 20 things in the graph
               if(find == -1){
                    cout << "There are more than 20 items in the graph" << endl;
                    continue;
               }
               //Turn the data into a struct and add it to the vector
               struct Vertex* vertex = new struct Vertex();
               vertex->label = new char[80];
               strcpy(vertex->label, input_1);
               vertex->index = find;
               vertex->solved = 0;
               graph.at(find) = vertex;
               x[find][find] = -1;
               delete[] input_1;
          }
          //Remove a vertex
          else if(strcmp(input, "A") == 0){
               char* input_1 = new char[80];
               //Get the name of the node that they would like to delete
               cout << "Name of Node to delete: ";
               cin >> input_1;
               Vertex* start = lookUp(graph, input_1);
               if(start == NULL){
                       cout << "That is not a valid node name" << endl;
                       continue;
               }
               //Delete everything in both its column and row.
               for(int i = 0; i < 20; i++){
                    x[start->index][i] = 0;
                    x[i][start->index] = 0;
               }
               graph.at(start->index) = NULL;
               delete start;
          }
          //Remove a link
          else if(strcmp(input, "R") == 0){ 
               char* input_1 = new char[80];
               char* input_2 = new char[80];
               //Get the node names and find the struct from the lookup function
               cout << "Starting Node Name: " << endl;
               cin >> input_1;
               Vertex* start = lookUp(graph, input_1);
               if(start == NULL){
                    cout << "That is not a valid node name" << endl;
                    continue;
               }
               cout << "Ending Node Name: " << endl;
               cin >> input_2;
               Vertex* end = lookUp(graph, input_2);
               if(end == NULL){
                    cout << "That is not a valid node name" << endl;
                    continue;
               }
               x[start->index][end->index] = 0;
               delete[] input_1;
          }
          //Add an edge with a numerical value into the graph
          else if(strcmp(input, "E") == 0){
               char* input_1 = new char[80];
               char* input_2 = new char[80];
               char* input_3 = new char[80];
               //Get the node names and find the struct from the lookup function
               cout << "Starting Node Name: " << endl;
               cin >> input_1;
               Vertex* start = lookUp(graph, input_1);
               if(start == NULL){
                    cout << "That is not a valid node name" << endl;
                    continue;
               }
               cout << "Ending Node Name: " << endl;
               cin >> input_2;
               Vertex* end = lookUp(graph, input_2);
               if(end == NULL){
                    cout << "That is not a valid node name" << endl;
                    continue;
               }
               cout << "Please enter the weight of the node." << endl;
               cin >> input_3;
               int weight = 0;
               stringstream convert;
               convert << input_3;
               convert >> weight;
               delete[] input_3;
               //Enter the weight into the adjacency matrix
               x[start->index][end->index] = weight;
               delete[] input_2;
               delete[] input_1;
          }
          else if(strcmp(input, "N") == 0){
               return 0;
          }
          //Find the shortest weighted path using djitsktra's algorithm
          else if(strcmp(input, "F") == 0){ 
               char* input_1 = new char[80];
               char* input_2 = new char[80];
               //Get the node names and find the struct from the lookup function
               cout << "Starting Node Name: " << endl;
               cin >> input_1;
               Vertex* start = lookUp(graph, input_1);
               if(start == NULL){
                    cout << "That is not a valid node name" << endl;
                    continue;
               }
               cout << "Ending Node Name: " << endl;
               cin >> input_2;
               Vertex* end = lookUp(graph, input_2);
               if(end == NULL){
                    cout << "That is not a valid node name" << endl;
                    continue;
               }
               cout << path(graph, x, start, end) << endl;
               delete[] input_1;
               delete[] input_2;
          }
          else if(strcmp(input, "P") == 0){
               //Honestly its easiest to just do the for loop without a function dedicated
               for(int i=0; i < 20; i++){
                    for(int j=0; j < 20; j++){
                         cout << x[i][j] << " ";
                    }
                    cout << endl;
               }
          }
     }
}
//Find a vertex in the graph given its label
struct Vertex* lookUp(vector<Vertex*> graph, char* name){
     for(int i = 0; i < 20; i++){
          if(graph.at(i) != NULL){
           //Check if the name of the vetex is equal to the name entered
           if(strcmp(name, graph.at(i)->label) == 0){
               return graph.at(i);
           }    
          }
     }
     //If it isn't in the graph
     return NULL;
}
int path(vector<Vertex*> graph, int x[20][20], struct Vertex* start, struct Vertex* end){
     //Make a queue that I can use to store the queue
     vector<Vertex*> q;
     //Loop through the vector and set all of the indexes to -1 to represent infinity
     for(int i = 0; i < 20; i++){
          if(graph.at(i) != NULL && strcmp(start->label, graph.at(i)->label) != 0){
               graph.at(i)->solved = 99999;
          }
          q.push_back(graph.at(i));
     }
     
     while(q.size() != 0){
          //Find v with the minimum distance from the source
          Vertex* v;
          int min = 9999999;
          int minInd;
          for(int i = 0; i < 20; i++){
               if(q.at(i) == NULL){
                    break;
               }
               else if(q.at(i) == q.back()){
                    break;
               }
               else if(min > q.at(i)->solved){
                    min = q.at(i)->solved;
                    v = q.at(i);
                    minInd = i;
               }
          }
          q.erase(q.begin() + minInd);
          //Find all of the adjacent nodes and see if there is a shorter path
          for(int i = 0; i < 20; i++){
               if(q.at(i) == NULL){
                    break;
               }
               else if(q.at(i) == q.back()){
                    break;
               }
               else if(x[v->index][q.at(i)->index]){
                    int distance = v->solved + x[v->index][q.at(i)->index];
                    if(distance < q.at(i)->solved){
                         q.at(i)->solved = distance;
                    }
               }
          }
     }
     return end->solved;
}
