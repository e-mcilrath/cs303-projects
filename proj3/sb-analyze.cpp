/*
Eric McIlrath
emcilrat
sb-analyze.cpp 

Reads a Superball board on stdin and prints every scoreable component.

TODO: rewrite header

*/

#include <cstdio>
#include <cstring>
#include <iostream>
#include <vector>

#include "disjoint.h"

using namespace std;

class Superball {
  public:
    Superball(int argc, char **argv);
    void analyze_superball();
    int r;
    int c;
    int mss;
    int empty;
    vector <int> board;
    vector <int> goals;
    vector <int> colors;
};

void usage(const char *s) 
{
  fprintf(stderr, "usage: sb-analyze rows cols min-score-size colors\n");
  if (s != NULL) fprintf(stderr, "%s\n", s);
  exit(1);
}

Superball::Superball(int argc, char **argv)
{
  int i, j;
  string s;

  if (argc != 5) usage(NULL);

  if (sscanf(argv[1], "%d", &r) == 0 || r <= 0) usage("Bad rows");
  if (sscanf(argv[2], "%d", &c) == 0 || c <= 0) usage("Bad cols");
  if (sscanf(argv[3], "%d", &mss) == 0 || mss <= 0) usage("Bad min-score-size");

  colors.resize(256, 0);

  for (i = 0; i < (int) strlen(argv[4]); i++) {
    if (!isalpha(argv[4][i])) usage("Colors must be distinct letters");
    if (!islower(argv[4][i])) usage("Colors must be lowercase letters");
    if (colors[argv[4][i]] != 0) usage("Duplicate color");
    colors[argv[4][i]] = 2+i;
    colors[toupper(argv[4][i])] = 2+i;
  }

  board.resize(r*c);
  goals.resize(r*c, 0);

  empty = 0;

  for (i = 0; i < r; i++) {
    if (!(cin >> s)) {
      fprintf(stderr, "Bad board: not enough rows on standard input\n");
      exit(1);
    }
    if ((int) s.size() != c) {
      fprintf(stderr, "Bad board on row %d - wrong number of characters.\n", i);
      exit(1);
    }
    for (j = 0; j < c; j++) {
      if (s[j] != '*' && s[j] != '.' && colors[s[j]] == 0) {
        fprintf(stderr, "Bad board row %d - bad character %c.\n", i, s[j]);
        exit(1);
      }
      board[i*c+j] = s[j];
      if (board[i*c+j] == '.') empty++;
      if (board[i*c+j] == '*') empty++;
      if (isupper(board[i*c+j]) || board[i*c+j] == '*') {
        goals[i*c+j] = 1;
        board[i*c+j] = tolower(board[i*c+j]);
      }
    }
  }
}

void Superball::analyze_superball() {
  DisjointSetByRankWPC ds(r*c);

  for(int i = 0; i < r; i++) {
    for (int j = 0; j < c; j++) {
      int cell = i*c + j;
      if (board[cell] == '.' || board[cell] == '*') continue;  // skip empty
      if (j+1 < c) {
        if (board[cell] == board[cell+1]) { //if colors are the same 
          int root_a = ds.Find(cell);       // root a
          int root_b = ds.Find(cell+1);     // root b
          if (root_a != root_b) {           // if roots are different, union
            ds.Union(root_a, root_b);
          }
        }
      }
      if (i+1 < r) {
        if (board[cell] == board[cell+c]) {  // if colors are the same
          int root_a = ds.Find(cell);   // root a
          int root_b = ds.Find(cell+c); // root b
          if (root_a != root_b) {       // if the roots are different, union
            ds.Union(root_a, root_b);
          }
        }
      }
    }
  }
  
  vector<int> size(r*c, 0);   // vector of all cells
  for (int cell = 0; cell < r*c; cell++) {
    if (board[cell] == '.' || board[cell] == '*') continue;
    size[ds.Find(cell)]++;
  }

  printf("Scoring sets:\n");
  vector <bool> printed(r*c, false);
  for(int i = 0; i < r; i++) {
    for (int j = 0; j <c; j++) {
      int cell = i*c + j;
      if (board[cell] == '.' || board[cell] == '*') continue;
      if (goals[cell] != 1) continue;

      int root = ds.Find(cell); // find root
      if (size[root] >= mss && !printed[root]) {
        printf("  Size: %2d  Char: %c  Scoring Cell: %d,%d\n", size[root], board[cell], i, j);
        printed[root] = true;
      }
    }
  }


}


int main(int argc, char **argv)
{
  Superball *s;

  s = new Superball(argc, argv);

 s->analyze_superball();
 delete s;
}
