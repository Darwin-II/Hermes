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
ofstream outfile;
vector <string> dictionary;
string island;
int main() {
	srand(unsigned(time(0)));
	file.open("dictionary.txt");
	while (!file.eof()) {
		getline(file, island);
		dictionary.push_back(island);
	}
	remove("netx.txt");
	remove("nety.txt");
	remove("nodedata.txt");
	remove("synapses.txt");
	remove("nodes.txt");
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
			nodetable[countI][countII] = (rand () % 7 ) + 1;
			switch (nodetable[countI][countII]) {
				case 3:
					nodedata[countI][countII] = (rand () % dictionary.size()) + 0;
					break;
				case 7:
					nodedata[countI][countII] = (rand () % 2) + 1;
					break;
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
	outfile.open("netx.txt");
	outfile << netwidth;
	outfile.close();
	outfile.open("nety.txt");
	outfile << netlength;
	outfile.close();
	cout << "Unloading net." << endl;
	outfile.open("nodes.txt");
	for (countI = 0; countI < netwidth; countI++) {
		for (countII = 0; countII < netlength; countII++) {
			outfile << nodetable[countI][countII] << endl;
		}
	}
	outfile.close();
	outfile.open("synapses.txt");
	for (countI = 0; countI < netwidth; countI++) {
		for (countII = 0; countII < netlength; countII++) {
			for (countIII = 0; countIII < netwidth; countIII++) {
				for (countIV = 0; countIV < netlength; countIV++) {
					outfile << connectiontable[countI][countII][countIII][countIV] << endl;
				}
			}
		}
	}
	outfile.close();
	cout << "Unloading node data." << endl;
	outfile.open("nodedata.txt");
	for (countI = 0; countI < netwidth; countI++) {
		for (countII = 0; countII < netlength; countII++) {
			outfile << nodedata[countI][countII] << endl;
		}
	}
	cout << "Finished." << endl;
	return 0;
}
