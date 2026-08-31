/* 
Eric McIlrath & Abraham Rashdan
emcilrat
arashdan
lib_info.cpp

Inputs songs and sorts them. Then outputs them, sorted.

Learned a lot about iterators and pointers.
*/
#include <iostream>
#include <string>
#include <map>
#include <iomanip>
#include <fstream>
#include <sstream>
#include <cstdio>
#include <algorithm>
using namespace std;



class Song { 
  public:
    string title;
    int time;
    int track;
};

class Album {
  public:
    map <int, Song *> songs;
    string name;
    int time;
	int nsongs;
};

class Artist {
  public:
    map <string, Album *> albums;
    string name;
    int time;
    int nsongs;
};

// mm:ss -> seconds
int time_to_seconds(string str) {
	stringstream ss(str);
	int seconds = 0;
	string temp;

	getline(ss, temp,':');
	seconds += stoi(temp) * 60;
	getline(ss, temp);
	seconds += stoi(temp);
	return seconds;
}

int main(int argc, char *argv[]) {
if (argc < 2) { // Check right amount of args
  cerr << "usage: " << argv[0] << " <file>" << "\n";
  return 1;
}

string file = argv[1];
map <string, Artist *> Artists; // Main map
string line, title, time ,artist, album, genre;
int track;
map <string, Artist *>::iterator itr1;
map <string, Album *>::iterator itr2;
map <int, Song *>::iterator itr3;

ifstream fin(file.c_str()); // Open file

if (!fin.is_open()) { 
  cerr << "The file did not open." << "\n";
  return 1;
}

while (getline(fin, line)) { // processing line by line
	stringstream ss(line);
	ss >> title >> time >> artist >> album >> genre >> track;

	replace(artist.begin(), artist.end(), '_', ' '); // replace '_' "Coltrane,_John" -> "Coltrane, John"
	replace(album.begin(), album.end(), '_', ' ');
	replace(title.begin(), title.end(), '_', ' ');

	if (Artists.find(artist) == Artists.end()) { // create artist if not found
		
		//push artist into artists map
		Artists.insert(make_pair(artist, new Artist));
		itr1 = Artists.find(artist);

		itr1->second->name = artist;
		itr1->second->time = 0;
		itr1->second->nsongs = 0;
	}
	else itr1 = Artists.find(artist);

	if (itr1->second->albums.find(album) == itr1->second->albums.end()) { // create album if not found

		itr1->second->albums[album] = new Album;
		itr2 = itr1->second->albums.find(album);

		itr2->second->name = album;
		itr2->second->time = 0;
		itr2->second->nsongs = 0;
	} 
	else itr2 = itr1->second->albums.find(album);

	if (itr2->second->songs.find(track) == itr2->second->songs.end()) { // create song if not found

		itr2->second->songs[track] = new Song; 
		itr3 = itr2->second->songs.find(track);

		itr3->second->title = title;
		itr3->second->time = time_to_seconds(time);
		itr1->second->time += itr3->second->time; // add song time to artist time
		itr2->second->time += itr3->second->time; // add song time to album time
		itr3->second->track = track;
		itr1->second->nsongs += 1; // number of songs artist has
		itr2->second->nsongs += 1; // number of songs album has
	}
}

for (itr1 = Artists.begin(); itr1 != Artists.end(); ++itr1) {
	//printf("%s: %d, %s", itr1->second->name, itr1->second->nsongs, time_to_string(itr1->second->time));
	cout << itr1->second->name << ": " << itr1->second->nsongs << ", " << itr1->second->time / 60 << ":" << setw(2) << setfill('0') << itr1->second->time % 60 << endl;
	for (itr2 = itr1->second->albums.begin(); itr2 != itr1->second->albums.end(); ++itr2) {
		//printf("%8s: %d, %s", itr2->second->name, itr2->second->nsongs, time_to_string(itr2->second->time));
		cout << "        " << itr2->second->name << ": " << itr2->second->nsongs << ", " << itr2->second->time / 60 << ":" << setw(2) <<setfill('0') << itr2->second->time % 60 << endl;
		for (itr3 = itr2->second->songs.begin(); itr3 != itr2->second->songs.end(); ++itr3) {
			//printf("%16d. %s: %s", itr3->second->track, itr3->second->title.replace(title.begin(), title.end(), '_', ' '), time_to_string(itr3->second->time));
			cout << "                " << itr3->second->track << ". " << itr3->second->title << ": " << itr3->second->time / 60 << ":" << setw(2) << setfill('0') << itr3->second->time % 60 << endl;
		}
	}
} 

fin.close();

return 0;
}

