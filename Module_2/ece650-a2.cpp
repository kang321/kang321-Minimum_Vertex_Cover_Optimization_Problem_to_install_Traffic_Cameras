
#include <iostream>
#include <sstream>

#include <vector>
#include <string.h>

#include<list>
#include<algorithm>
#define MAX 100000
using namespace std;


bool BFS(vector<int> adj_vec[], int source, int destination, int vertex,
         int previous_value[])
{
    
    list <int> queue;
 
    //creating an array of bool values to check if a vertex is visited or not
    bool visited[vertex];
 
    //all visited are false during initial run
    //all previous value are set to -1
    for (int i = 0; i < vertex; i++) {
        visited[i] = false;
        
        previous_value[i] = -1;
    }
 
    // now source is first to be visited
    visited[source] = true;
    
    queue.push_back(source);
 
    //BFS algorithm
    while (!queue.empty()) {
        int a = queue.front();
        queue.pop_front();
        for (long unsigned int i = 0; i < adj_vec[a].size(); i++) {
            if (visited[adj_vec[a][i]] == false) {
                visited[adj_vec[a][i]] = true;
                
                previous_value[adj_vec[a][i]] = a;
                queue.push_back(adj_vec[a][i]);
 
                // We stop BFS when we find
                // destination.
                if (adj_vec[a][i] == destination)
                    return true;
            }
        }
    }
 
    return false;
}


void shortest_distance_is(vector <int> adj_vec[], int vertex,int source,int destination){
    int previous_value[vertex];
    if (BFS(adj_vec, source, destination, vertex, previous_value) == false) {
        cout << "Error: No path found"<<endl;
        return;
    }
 
    // vector path stores the shortest path in reverse order
    vector<int> path;
    int b = destination;
    path.push_back(b);
    while (previous_value[b] != -1) {
        path.push_back(previous_value[b]);
        b = previous_value[b];
    }
 
    // printing path from source to destination in reverse order
   
    for (int i = path.size() - 1; i >= 0; i--)
        if (path[i] == path[0]){
            cout<<path[0]<<endl;
        }
        else{
        cout << path[i]<<"-";}
}




int main(int argc, char** argv) {
    int vertex=0;
	// read the line from input untill end of line 
	while (!::cin.eof()) {
        
        string arr;
        vector<int> E_vec;		    
        
	    
		//getline(cin, line);

		//istringstream input(line);

		while (getline(cin, arr)) {
            //creating array of type char of max=100000 length 
            // creating vertex of int type
			//char arr[MAX];
			
            
            //copying all the line contents which contain V and E values in array arr
			//strcpy(arr, line.c_str());
            //sssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssss
            //if first element of arr is s
            if (arr[0] == 's') {
                if(E_vec.size() == 0 || vertex ==0){
                    cout<<"Error: E_vec and Vertex are empty"<<endl;
                }
                else{
                vector <int> s_vec;				
				vector<char> new_vec;
				char new_arr[MAX]={0};

				for (int a = 0; arr[a] != '\0'; a++) {
					new_vec.push_back(arr[a]);
				}

				new_vec.push_back('.');

				/*for (int i = 0; i < new_vec.size(); i++) {
					cout << new_vec[i] ;
				}*/
				for (long unsigned int i = 0; i < new_vec.size(); i++) {
					new_arr[i] = new_vec[i];
				}
				int num = 0;

				for (int i = 0; new_arr[i] != '\0'; i++) {

					if (new_arr[i] > '0' && new_arr[i] <= '9') {
						/*cout << arr[i] << "\n";*/
						num = num * 10 + new_arr[i] - '0';
					}
					else {
						if (new_arr[i] == '0' && num == 0) {
							s_vec.push_back(0);
						}
						if (new_arr[i] == '0' && (num != 0)) {
							num = num * 10 + new_arr[i] - '0';
							s_vec.push_back(num);
							num = 0;
						}
						if (new_arr[i] != '0' && (num != 0)) {
							s_vec.push_back(num);
							num = 0;
						}

					}
                }
                int destination = s_vec[1];
                int source = s_vec[0];
                vector<int> adj_vec[vertex];
                //cout<<"source= "<<source<<"destination= "<<destination<<endl;
                for(long unsigned int i = 0; i<(E_vec.size()/2);i++){
					int even_edge = E_vec[2*i];
					int odd_edge = E_vec[2*i + 1];
					//cout<< "src"<<even_edge<<endl;
					//cout <<"dest"<<odd_edge<<endl;

					adj_vec[even_edge].push_back(odd_edge);
    				adj_vec[odd_edge].push_back(even_edge);

				} 
                shortest_distance_is(adj_vec,vertex,source,destination);
            }}
            //VVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVV
            //if first element of arr is V
			else if (arr[0] == 'V') {
				//cout << "vertex\n";
				//cout << line << endl; //a3: edit it to print the graph that it has read before accepting an s command.

				int num = 0;
                //converting character into integer. \0 is null
				for (int i = 0; arr[i] != '\0'; ++i) {
                    //here ascii value of chars is compared
					if (arr[i] >= '0' && arr[i] <= '9')                    
						num = num * 10 + arr[i] - '0';
				}

				
                //assigning num to vertex
                vertex = num+1;
                // cout<<"Vector V  is: "<<vertex<<endl;
				

				while (vertex == 0) {
					cout << "Error: NO vertex is entered." << endl;
					break;
				}
				break;
			}
            //checking if first element is E or not, if yes then extract the contents after special characters
			
            //EEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEE
            else if (arr[0] == 'E') {
				int num = 0;
				//cout << line << endl;//a3: edit it to print the graph that it has read before accepting an s command.
				
                for (int i = 0; arr[i] != '\0'; i++) {
					if (arr[i] > '0' && arr[i] <= '9') {
						//*cout << arr[i] << "\n";*//
						num = num * 10 + arr[i] - '0'; //edge<1,2>
					}
					else {
						if (arr[i] == '0' && num == 0) {
							E_vec.push_back(0); //edge <0,1>
						}
						if (arr[i] == '0' && (num != 0)) {
							num = num * 10 + arr[i] - '0';
							E_vec.push_back(num);  //edge<10,10>
							num = 0;
						}
						if (arr[i] != '0' && (num != 0)) {
							E_vec.push_back(num);   //edge<11,19>
							num = 0;
						}

					}
				}
                int maxi = *max_element(E_vec.begin(), E_vec.end());
                //cout<<"hello"<<maxi<<"vertex"<<vertex<<endl;
                if (maxi > (vertex-1)){
                    //cout<<"entering"<<endl;

                    vertex = 0;
                    E_vec.clear();
                    cout<<"Error: Invalid edge"<<endl;}

                
            }            
            //printing edges
            // for (int i:E_vec )
            //    std::cout << i << ' ';
            //printing s
            // for (int i:s_vec )
            //     std::cout << i << ' ';
            
        }   
        
    }
    

}