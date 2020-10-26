#include <iostream>
#include <vector>
#include <ctime>
#include <fstream>
using namespace std;
int netlength;
int netwidth;
int countI;
int countII;
int countIII;
int countIV;
fstream file;
vector <string> dictionary;
string island;
int main() {
	srand(unsigned(time(0)));
	file.open("dictionary.txt");
	while (!file.eof()) {
		getline(file, island);
		dictionary.push_back(island);
	}
	file.close();
	cout << "Enter net length: ";
	cin >> netlength;
	cout << "Enter net width: ";
	cin >> netwidth;
	cout << "Generating net." << endl;
	int nodetable[netwidth][netlength];
	vector<vector<int>> nodedata (netwidth, vector<int>(netlength));
	vector<vector<vector<vector<int>>>> connectiontable (netwidth, vector<vector<vector<int>>> (netlength, vector<vector<int>> (netwidth, vector<int> (netlength))));
	for (countI = 0; countI < netwidth; countI++) {
		for (countII = 0; countII < netlength; countII++) {
			nodetable[countI][countII] = (rand () % 6 ) + 1;
			switch (nodetable[countI][countII]) {
				case 3:
					nodedata[countI][countII] = (rand () % dictionary.size()) + 0;
			}
		}
	}
	for (countI = 0; countI < netwidth; countI++) {
		for (countII = 0; countII < netlength; countII++) {
			for (countIII = 0; countIII < netwidth; countIII++) {
				for (countIV = 0; countIV < netlength; countIV++) {
					connectiontable[countI][countII][countIII][countIV] = (rand () % dictionary.size()) + 0;
				}
			}
		}
	}
	cout << "Done." << endl;
	cout << "Total nodes: " << (netwidth * netlength) << endl;
	cout << "Show net? [yes / no] ";
	cin >> island;
	if (island == "yes") {
		for (countI = 0; countI < netwidth; countI++) {
			for (countII = 0; countII < netlength; countII++) {
				cout << " " << nodetable[countI][countII] << " ";
			}	
			cout << endl;
		}
	}
	cout << "Unloading net dimensions." << endl;
	file.open("netx.txt");
	file << netwidth;
	file.close();
	file.open("nety.txt");
	file << netlength;
	file.close();
	cout << "Unloading net." << endl;
	file.open("nodes.txt");
	for (countI = 0; countI < netwidth; countI++) {
		for (countII = 0; countII < netlength; countII++) {
			file << nodetable[countI][countII] << endl;
		}
	}
	file.close();
	file.open("synapses.txt");
	for (countI = 0; countI < netwidth; countI++) {
		for (countII = 0; countII < netlength; countII++) {
			for (countIII = 0; countIII < netwidth; countIII++) {
				for (countIV = 0; countIV < netlength; countIV++) {
					file << connectiontable[countI][countII][countIII][countIV] << endl;
				}
			}
		}			
	}
	file.close();
	return 0;
}
