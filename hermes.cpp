//NODE TYPES:
//junction (emtpy)
//sigedit (random) - modify a connection with a random number and send a signal down it
//source node (fixed) - grab a set word
//source node (random) - grab a random word
//wipe node - wipe a node and replace it with a new one, then send a signal to it
//output node - outputs
//switch - switches mode internal monologue (word matches in output) and comprehension synapses (word matches in input)
//TODO - 
//remove thinking net and all the stuff to do with the switch node
//Q-learning in netgen program
#include <iostream>
#include <vector>
#include <ctime>
#include <fstream>
#include <algorithm>
using namespace std;
int netlength;
int netwidth;
string island;
int countI;
int countII;
int countIII;
int countIV;
vector<int> input;
int initnodex;
int initnodey;
fstream dictionaryfile;
fstream file;
vector<string> dictionary;
vector<int> trainingdata;
int newstrength;
int totalstrengths;
int strengthdiff;
int strengthdiffavg;
int targetnodex;
int targetnodey;
vector<int>output;
vector<int>possiblesx;
vector<int>possiblesy;
int nodex;
int nodey;
int newnode;
int thinkingmode;
int previousstrength;
int draw;
int main() {
	srand(unsigned(time(0)));
	cout << "Loading language." << endl;
	dictionaryfile.open("dictionary.txt");
	while (!dictionaryfile.eof()) {
		getline(dictionaryfile, island);
		dictionary.push_back(island);
	}
	dictionaryfile.close();
	cout << "Gathering net dimensions." << endl;
	file.open("netx.txt");
	file >> island;
	netwidth = stoi(island);
	file.close();
	file.open("nety.txt");
	file >> island;
	netlength = stoi(island);
	file.close();
	int nodetable[netwidth][netlength];
	vector<vector<int>> nodedata (netwidth, vector<int>(netlength));
	vector<vector<vector<vector<int>>>> connectiontable (netwidth, vector<vector<vector<int>>> (netlength, vector<vector<int>> (netwidth, vector<int> (netlength))));
	cout << "Loading net." << endl;
	file.open("nodes.txt");
	for (countI = 0; countI < netwidth; countI++) {
		for (countII = 0; countII < netlength; countII++) {
			getline(file, island);
			nodetable[countI][countII] = stoi(island);
		}
	}
	file.close();
	cout << "Loading synapses." << endl;
	file.open("synapses.txt");
	for (countI = 0; countI < netwidth; countI++) {
		for (countII = 0; countII < netlength; countII++) {
			for (countIII = 0; countIII < netwidth; countIII++) {
				for (countIV = 0; countIV < netlength; countIV++) {
					getline(file, island);
					connectiontable[countI][countII][countIII][countIV] = stoi(island);
				}
			}
		}
	}
	file.close();
	cout << "Loading node data." << endl;
	file.open("nodedata.txt");
	for (countI = 0; countI < netwidth; countI++) {
		for (countII = 0; countII < netlength; countII++) {
			getline(file, island);
			nodedata[countI][countII] = stoi(island);
		}
	}
	file.close();
	cout << "Done." << endl;
	remove("netx.txt");
	remove("nety.txt");
	remove("nodedata.txt");
	remove("synapses.txt");
	remove("nodes.txt");
	while (island != ".") {
		cin >> island;
		if (island == ":q") {
			cout << "Unloading language." << endl;
			dictionaryfile.open("dictionary.txt");
			for (countI = 0; countI < dictionary.size(); countI++) {
				dictionaryfile << dictionary[countI] << endl;
			}
			dictionaryfile.close();
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
			cout << "Unloading node data." << endl;
			file.open("nodedata.txt");
			for (countI = 0; countI < netwidth; countI++) {
				for (countII = 0; countII < netlength; countII++) {
					file << nodedata[countI][countII] << endl;
				}
			}
			file.close();
			cout << "Goodbye." << endl;
			return 0;
		}
		else {
			if (count(dictionary.begin(), dictionary.end(), island)) {
				for (countI = 0; countI < dictionary.size(); countI++) {
					if (dictionary[countI] == island) {
						input.push_back(countI);
					}
				}
			}
			else {
				dictionary.push_back(island);
			}
		}
	}	
	initnodex = (rand () % (netwidth)) + 0;
	initnodey = (rand () % (netlength)) + 0;
	nodex = initnodex;
	nodey = initnodey;
	thinkingmode = (rand () % 2) + 1;
	output.push_back(1);
	//SWITCH CASE FOR S FUNCTIONS, MAIN AI LOOP
	while (1 < 2)  {
		switch (nodetable[nodex][nodey]) {
			case 2:
				targetnodex = (rand () % netwidth) + 0;
				targetnodey = (rand () % netlength) + 0;
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
				switch (nodetable[targetnodex][targetnodey]) {
					case 3:
						nodedata[targetnodex][targetnodey] = (rand () % dictionary.size()) + 0;
					case 7:
						nodedata[targetnodex][targetnodey] = (rand () % 2) + 1;
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
						cout << "Unloading language." << endl;
						dictionaryfile.open("dictionary.txt");
						for (countI = 0; countI < dictionary.size(); countI++) {
							dictionaryfile << dictionary[countI] << endl;
						}
						dictionaryfile.close();
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
						cout << "Unloading node data." << endl;
						file.open("nodedata.txt");
						for (countI = 0; countI < netwidth; countI++) {
							for (countII = 0; countII < netlength; countII++) {
								file << nodedata[countI][countII] << endl;
							}
						}
						file.close();
						file.open("trainingdata.txt");
						for (countI = 0; countI < trainingdata.size(); countI++) {
							file << trainingdata[countI] << endl;
						}
						file.close();
						cout << "Goodbye." << endl;
						return 0;
					}
					else {
						if (count(dictionary.begin(), dictionary.end(), island)) {
							for (countI = 0; countI < dictionary.size(); countI++) {
								if (dictionary[countI] == island) {
									input.push_back(countI);
									trainingdata.push_back(countI);
								}
							}
						}
						else {
							dictionary.push_back(island);
						}
					}
				}
				break;
			case 7:
				thinkingmode = nodedata[nodex][nodey];
			default:
				break;
		}
		switch (thinkingmode) {
			case 1:
				for (countI = 0; countI < netwidth; countI++) {
					for (countII = 0; countII < netlength; countII++) {
						for (countIII = 0; countIII < input.size(); countIII++) {
							if (connectiontable[nodex][nodey][countI][countII] == input[countIII]) {
								possiblesx.push_back(countI);
								possiblesy.push_back(countII);
							}
						}
					}
				}
				break;
			case 2:
				for (countI = 0; countI < netwidth; countI++) {
					for (countII = 0; countII < netlength; countII++) {
						for (countIII = 0; countIII < input.size(); countIII++) {
							if (connectiontable[nodex][nodey][countI][countII] == output[countIII]) {
								possiblesx.push_back(countI);
								possiblesy.push_back(countII);
							}
						}
					}
				}
				break;
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