#include <cstdio>
#include <algorithm>
#include <cstdlib>
#include <iostream>
#include <sstream>
#include <string>
#include <strings.h>
#include <vector>

using namespace std;

typedef struct team_t {
	string name;
	int wins;
	int losses;
	int ties;
	int goals_scored;
	int goals_against;
} team;

int find_team(vector<team> teams, int size, string name) {
	for (int i = 0; i < size; i++)
		if (teams[i].name.compare(name) == 0)
			return i;
	
	return -1;
}

bool ranker(team a, team b) {
	int points_a = a.wins*3 + a.ties;
	int points_b = b.wins*3 + b.ties;

	if (points_a != points_b)
		return (points_a > points_b);

	if (a.wins != b.wins)
		return (a.wins > b.wins);

	int gd_a = a.goals_scored-a.goals_against;
	int gd_b = b.goals_scored-b.goals_against;

	if (gd_a != gd_b)
		return (gd_a > gd_b);

	if (a.goals_scored != b.goals_scored)
		return (a.goals_scored > b.goals_scored);

	int gp_a = a.wins + a.ties + a.losses;
	int gp_b = b.wins + b.ties + b.losses;

	if (gp_a != gp_b)
		return (gp_a > gp_b);

	return (strcasecmp(a.name.c_str(), b.name.c_str()) == 1);
}

int main() {
	int N, _;
	_ = scanf("%i\n", &N);

	for (int n = 0; n < N; n++) {
		if (n > 0)
			printf("\n");

		string line;
		getline(cin, line);
		cout << line << endl;

		int T;
		_ = scanf("%i\n", &T);

		vector<team> teams;

		for (int t = 0; t < T; t++) {
			team temp_team;

			getline(cin, line);
			temp_team.name = line;
			temp_team.wins = 0;
			temp_team.losses = 0;
			temp_team.ties = 0;
			temp_team.goals_scored = 0;
			temp_team.goals_against = 0;

			teams.push_back(temp_team);
		}

		int G;
		_ = scanf("%i\n", &G);

		string team1, team2;
		int goals1, goals2;
		int idx1, idx2;
		
		for (int g = 0; g < G; g++) {
			getline(cin, line);

			team1 = line.substr(0, line.find("#"));
			team2 = line.substr(line.rfind("#")+1, line.size());
			
			sscanf(line.substr(line.find("#")+1, line.rfind("#")-line.find("#")-1).c_str(), "%i@%i", &goals1, &goals2);

			idx1 = find_team(teams, T, team1);
			idx2 = find_team(teams, T, team2);

			teams[idx1].goals_scored += goals1;
			teams[idx1].goals_against += goals2;
			teams[idx2].goals_scored += goals2;
			teams[idx2].goals_against += goals1;

			if (goals1 > goals2) {
				teams[idx1].wins += 1;
				teams[idx2].losses += 1;
			}
			else if (goals2 > goals1) {
				teams[idx2].wins += 1;
				teams[idx1].losses += 1;
			}
			else {
				teams[idx1].ties += 1;
				teams[idx2].ties += 1;
			}
		}
		
		sort(teams.begin(), teams.end(), ranker);

		for (int t = 0; t < T; t++) {
			printf("%i) %s %ip, %ig (%i-%i-%i), %igd (%i-%i)\n", t+1, teams[t].name.c_str(), 3*teams[t].wins+teams[t].ties, teams[t].wins+teams[t].ties+teams[t].losses, teams[t].wins, teams[t].ties, teams[t].losses, teams[t].goals_scored-teams[t].goals_against, teams[t].goals_scored, teams[t].goals_against);
		}
	}

	return EXIT_SUCCESS;
}
