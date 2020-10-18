//NODE TYPES:
//junction (emtpy)
//sigedit (random) - modify a connection with a random number and send a signal down it
//source node (fixed) - grab a set word
//source node (random) - grab a random word
//wipe node - wipe a node and replace it with a new one, then send a signal to it
//output node - outputs
//TODO - S2 CONVERTED TO 4D, S5 TOO, CHANGE NODE FLOW SYSTEM TOO
#include <iostream>
#include <vector>
#include <ctime>
#include <fstream>
#include <algorithm>
using namespace std;
int netlength;
int netwidth;
string island;
string islandII;
long int countI;
long int countII;
long int countIII;
long int countIV;
vector<string> input;
int initnodex;
int initnodey;
fstream tempscript;
fstream dictionaryfile;
vector<string> dictionary;
int newconnection;
int targetnodex;
int targetnodey;
vector<int>output;
vector<int>possiblesx;
vector<int>possiblesy;
int nodex;
int nodey;
int newnode;
int main() {
	srand(unsigned(time(0)));
	cout << "Loading language." << endl;
	dictionaryfile.open("dictionary.txt");
	while (!dictionaryfile.eof()) {
		getline(dictionaryfile, island);
		dictionary.push_back(island);
	}
	dictionaryfile.close();
	cout << "Enter net length: ";
	cin >> netlength;
	cout << "Enter net width: ";
	cin >> netwidth;
	cout << "Generating net";
	vector<vector<int>>nodetable(netlength, vector<int>(netwidth));
	int nodedata[netlength][netwidth];
	cout << ".";
	for (countI = 0; countI < netwidth; countI++) {
		for (countII = 0; countII < netlength; countII++) {
			nodetable[countI][countII] = (rand () % 6 ) + 1;
			switch (nodetable[countI][countII]) {
				case 3:
					nodedata[countI][countII] = (rand () % dictionary.size()) + 0;
			}
		}
	}
	cout << ".";
	vector<vector<vector<vector<int>>>> connectiontable(netwidth, vector<vector<vector<int>>> (netlength, vector<vector<int>> (netwidth, vector<int>(netlength))));
	for (countI = 0; countI < netwidth; countI++) {
		for (countII = 0; countII < netlength; countII++) {
			for (countIII = 0; countIII < netwidth; countIII++) {
				for (countIV = 0; countIV < netlength; countIV++) {
					connectiontable[countI][countII][countIII][countIV] = (rand () % dictionary.size()) + 0;
				}
			}
		}
	}
	cout << "." << endl;
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
	while (island != ".") {
		cin >> island;
		if (island == ":q") {
			dictionaryfile.open("dictionary.txt");
			for (countI = 0; countI < dictionary.size(); countI++) {
				dictionaryfile << dictionary[countI] << endl;
			}
			cout << "Goodbye." << endl;
			return 0;
		}
		else {
			if (count(dictionary.begin(), dictionary.end(), island)) {
				input.push_back(island);
			}
			else {
				dictionary.push_back(island);
			}
		}
	}
	input.erase(input.begin() + input.size());
	initnodex = (rand () % (netwidth)) + 0;
	initnodey = (rand () % (netlength)) + 0;
	nodex = initnodex;
	nodey = initnodey;
	//SWITCH CASE FOR S FUNCTIONS, MAIN AI LOOP
	while (1 < 2)  {
		switch (nodetable[nodex][nodey]) {
			case 2:
				targetnodex = (rand () % netwidth) + 0;
				targetnodey - (rand () % netlength) + 0;
				connectiontable[nodex][nodey][targetnodex][targetnodey] = (rand () % dictionary.size()) + 0;
				break;
			case 3:
				output.push_back(nodedata[nodex][nodey]);
				break;
			case 4:
				output.push_back((rand () % dictionary.size()) + 0);
				break;
			case 5:
				targetnodex = (rand () % netwidth) + 0;
				targetnodey = (rand () % netlength) + 0;
				nodetable[targetnodex][targetnodey] = (rand () % 6) + 1;
				for (countI = 0; countI < netwidth; countI++) {
					for (countII = 0; countII < netlength; countII++) {
						connectiontable[targetnodex][targetnodey][countI][countII] = (rand () % dictionary.size()) + 0;
					}
				}
				if (nodetable[targetnodex][targetnodey] == 3) {
					nodedata[targetnodex][targetnodey] = (rand () % dictionary.size()) + 0;
				}
				break;
			case 6:
				cout << "Hermes says: ";
				for (countI = 0; countI < output.size(); countI++) {
					cout << dictionary[output[countI]] << " ";
				}
				cout << endl;
				output.clear();
				island = " ";
				while (island != ".") {
					cin >> island;
					if (island == ":q") {
						dictionaryfile.open("dictionary.txt");
						for (countI = 0; countI < dictionary.size(); countI++) {
							dictionaryfile << dictionary[countI] << endl;
						}
						cout << "Goodbye." << endl;
						return 0;
					}
					else {
						if (count(dictionary.begin(), dictionary.end(), island)) {
							input.push_back(island);
						}
						else {
							dictionary.push_back(island);
						}
					}
				}
				input.erase(input.begin() + input.size());
				break;
			default:
				break;
		}
		for (countI = 0; countI < netwidth; countI++) {
			for (countII = 0; countII < netlength; countII++) {
				for (countIII = 0; countIII < output.size(); countIII++) {
					if (connectiontable[nodex][nodey][countI][countII] == output[countIII]) {
						possiblesx.push_back(countI);
						possiblesy.push_back(countII);
					}
				}
			}
		}
		if (possiblesx.size() != 0) {
			 newnode = (rand () % possiblesx.size()) + 0;
			 nodex = possiblesx[newnode];
			 nodey = possiblesy[newnode];
		}
		else {
			nodex = (rand () % netwidth) + 0;
			nodey = (rand () % netlength) + 0;
		}
	}
	return 0;
}
