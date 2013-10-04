#include <vector>
#include <iostream>
#include <stdlib.h>
#include <string>
#include <map>
#include <algorithm>

using namespace std;

// Changed to struct, assuming error with conversion to C++ from Java
struct TestResult {
	int studentId;
	string testDate;
	int testScore;
};

bool resulter(TestResult a, TestResult b) {
	if (a.studentId != b.studentId)
		return a.studentId < b.studentId;

	return a.testScore > b.testScore;
}

map<int, double> calculateFinalScores(vector<TestResult> results) {
	map<int, double> ret;

	sort(results.begin(), results.end(), resulter);

	int current_student = results[0].studentId;
	int count = 0;
	int sum = 0;

	for (vector<TestResult>::const_iterator i = results.begin(); i != results.end(); ++i) {
		if (i->studentId != current_student) {
			ret.insert(pair<int, double>(current_student, sum / count));
	
			current_student = i->studentId;
			count = 0;
			sum = 0;
		}

		if (count < 5) {
			sum += i->testScore;
			count += 1;
		}
	}
	ret.insert(pair<int, double>(current_student, sum / count));

	return ret;
}

int main() {
	vector<TestResult> r;

	TestResult s[10];
	for (int i = 0; i < 10; i++) {
		if (i < 3)
			s[i].studentId = 1;
		else
			s[i].studentId = 2;

		s[i].testScore = i * 10;
		
		r.push_back(s[i]);
	}

	map<int, double> ans = calculateFinalScores(r);

	cout << ans[1] << ';' << ans[2] << endl;

	return EXIT_SUCCESS;
}
