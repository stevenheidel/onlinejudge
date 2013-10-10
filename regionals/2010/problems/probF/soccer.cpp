#include <iostream>
#include <algorithm>
#include <string>
#include <cassert>
#include <vector>

using namespace std;

const int MAX_TEAMS = 20;

struct Team {
  string name;
  int index;

  int points;
  int highest, lowest; // highest rank = lowest numeric value!
  
  Team()
    : points(0), highest(MAX_TEAMS+100), lowest(0) { };
    

  void update(int my_goals, int opp_goals)
  {
    if (my_goals > opp_goals) {
      points += 3;
    } else if (my_goals == opp_goals) {
      points += 1;
    }
  }

  bool operator<(const Team &t) const
  {
    return points > t.points;
  }

  bool operator==(const Team &t) const
  {
    return points == t.points;
  }

  void update_rank(int rank)
  {
    highest = min(highest, rank);
    lowest = max(lowest, rank);
  }

  void print_rank(int rank) const
  {
    cout << rank;
    if (rank == 1) {
      cout << "st";
    } else if (rank == 2) {
      cout << "nd";
    } else if (rank == 3) {
      cout << "rd";
    } else {
      cout << "th";
    }
    cout << " place";
  }
  
  void print() const
  {
    //    cout << name << ": " << points << endl;
    cout << "Team " << name << " can finish as high as ";
    print_rank(highest);
    cout << " and as low as ";
    print_rank(lowest);
    cout << "." << endl;
  }
};

bool indexcmp(const Team &t1, const Team &t2) 
{
  return t1.index < t2.index;
}


typedef pair<int, int> Game;

static int index(const Team team[], int n, const string &name)
{
  for (int i = 0; i < n; i++) {
    if (team[i].name == name) {
      return i;
    }
  }
  assert(false);
}

void search(Team team[], int n, const vector<Game> &game, unsigned int gi)
{
  if (gi >= game.size()) {
    Team team2[MAX_TEAMS];
    for (int i = 0; i < n; i++) {
      team2[i].points = team[i].points;
      team2[i].index = team[i].index;
    }
    sort(team2, team2+n);
    int i, j;
    for (i = 0; i < n; i = j) {
      team[team2[i].index].update_rank(i+1);
      for (j = i+1; j < n && team2[i] == team2[j]; j++) {
	team[team2[j].index].update_rank(i+1);
      }
    }
    return;
  }

  // try each possible result

  // save old teams
  int index1 = game[gi].first, index2 = game[gi].second;
  int pts1 = team[index1].points, pts2 = team[index2].points;

  // team 1 wins
  team[index1].update(1, 0);
  team[index2].update(0, 1);
  search(team, n, game, gi+1);
  team[index1].points = pts1;
  team[index2].points = pts2;

  // team 2 wins
  team[index1].update(0, 1);
  team[index2].update(1, 0);
  search(team, n, game, gi+1);
  team[index1].points = pts1;
  team[index2].points = pts2;

  // tie
  team[index1].update(0, 0);
  team[index2].update(0, 0);
  search(team, n, game, gi+1);
  team[index1].points = pts1;
  team[index2].points = pts2;
}

bool do_case(bool first)
{
  int n, m;
  cin >> n >> m;
  if (n == 0 && m == 0) {
    return false;
  }
  
  if (!first) {
    cout << endl;
  }

  Team team[MAX_TEAMS];
  for (int i = 0; i < n; i++) {
    cin >> team[i].name;
    team[i].index = i;
  }

  vector<Game> game;
  for (int i = 0; i < m; i++) {
    string team1, team2, vs;
    int g1, g2;
    cin >> team1 >> vs >> team2 >> g1 >> g2;
    
    team2.erase(team2.length()-1, 1);   // get rid of ":"
    int index1 = index(team, n, team1);
    int index2 = index(team, n, team2);
    if (g1 >= 0 && g2 >= 0) {
      team[index1].update(g1, g2);
      team[index2].update(g2, g1);
    } else {
      assert(g1 == -1 && g2 == -1);
      game.push_back(make_pair(index1, index2));
    }
  }

  search(team, n, game, 0);
  sort(team, team+n, indexcmp);
  
  for (int i = 0; i < n; i++) {
    team[i].print();
  }

  return true;
}

int main(void)
{
  bool first = true;
  while (do_case(first)) {
    first = false;
  }
  return 0;
}
