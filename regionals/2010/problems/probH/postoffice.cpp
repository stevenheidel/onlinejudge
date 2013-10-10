#include <iostream>
#include <algorithm>

using namespace std;

bool between(double x, double low, double hi)
{
  return low <= x && x <= hi;
}

bool isLetter(double dim[3])
{
  return between(dim[0], 0.25, 7) &&
    between(dim[1], 90, 155) && between(dim[2], 125, 290);
}

bool isPacket(double dim[3])
{
  return dim[2] >= 125 && dim[1] >= 90 && dim[0] >= 0.25 &&
    (dim[2] > 290 || dim[1] > 155 || dim[0] > 7) &&
    dim[2] <= 380 && dim[1] <= 300 && dim[0] <= 50;
}

bool isParcel(double dim[3])
{
  return dim[2] >= 125 && dim[1] >= 90 && dim[0] >= 0.25 &&
    (dim[2] > 380 || dim[1] > 300 || dim[0] > 50) &&
    dim[2] + 2*(dim[1] + dim[0]) <= 2100;
}

int main(void)
{
  double dim[3];
  while (cin >> dim[0] >> dim[1] >> dim[2] &&
	 !(dim[0] == 0 && dim[1] == 0 && dim[2] == 0)) {
    sort(dim, dim+3);
    if (isLetter(dim)) {
      cout << "letter";
    } else if (isPacket(dim)) {
      cout << "packet";
    } else if (isParcel(dim)) {
      cout << "parcel";
    } else {
      cout << "not mailable";
    }
    cout << endl;
  }
  return 0;
}

  
