// RATIONAL
// only deals with nonnegative rationals
class Rational {
private:
  long long n, d;
  
  void reduce()
  {
    // be a bit conservative here
    if (n > INT_MAX/10 || d > INT_MAX/10) {
      cout << "Overflow detected" << endl;
      exit(1);
    }

    long long a, b, r;

    a = n;
    b = d;
    while (b != 0) {
      r = a % b;
      a = b;
      b = r;
    }
    n /= a;
    d /= a;
  }
  
public:
  Rational(long long numer = 0, long long denom = 1)
    : n(numer), d(denom)
  {
    reduce();
  }

  Rational &operator+=(const Rational &r)
  {
    long long nn = n*r.d + r.n*d;
    long long dd = d*r.d;
    
    n = nn;
    d = dd;
    reduce();
    return *this;
  }

  Rational inverse() const
  {
    return Rational(d,n);
  }
  
  friend istream &operator>>(istream &is, Rational &r);
  friend ostream &operator<<(ostream &is, const Rational &r);
};

istream &operator>>(istream &is, Rational &r)
{
  long long n, d;

  if (!(is >> n)) {
    return is;
  }
  char c;
  is >> c;

  assert(c == '/');
  is >> d;
  r.n = n;
  r.d = d;
  r.reduce();
  return is;
}

ostream &operator<<(ostream &os, const Rational &r)
{
  return os << r.n << '/' << r.d;
}

// DATE
struct Date
{
  int m, d, y;

  Date(int mm = 1, int dd = 1, int yy = 2000)
    : m(mm), d(dd), y(yy) { }

  bool operator<(const Date &date) const
  {
    if (y != date.y) return y < date.y;
    if (m != date.m) return m < date.m;
    return d < date.d;
  }

  bool operator==(const Date &date) const
  {
    return y == date.y && m == date.m && d == date.d;
  }
  
  void inc()
  {
    if (d++ == daysInMonth[isLeap(y)][m]) {
      d = 1;
      if (m++ == 12) {
	m = 1;
	y++;
      }
    }
  }

  void dec()
  {
    if (d-- == 1) {
      if (m-- == 1) {
	m = 12;
	y--;
      }
      d = daysInMonth[isLeap(y)][m];
    }
  }
};

istream &operator>>(istream &is, Date &date)
{
  char c;
  return is >> date.m >> c >> date.d >> c >> date.y;
}

ostream &operator<<(ostream &os, const Date &date)
{
  return os << date.m << '/' << date.d << '/' << date.y;
}

// OTHER
cout << fixed << setprecision(2) << covered*100 << endl;

it = remove(s.begin(), s.end(), '\'');
it = remove(s.begin(), it, '-');
s.resize(it - s.begin());

class Expression {
private:
  enum Type { LT, PLUS, MINUS, AND, OR, XOR, VAR, NUM };
  Expression *left, *right;
  Type type;
  Variable *var;
  int value;

  void parse(string expr)
  {
    
  }
  
public:
  Expression(const string &line)
  {
    parse(line);
  }

  int evaluate() const 
  {

	}
}
