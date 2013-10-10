/*
 * Infix expressions evaluation
 *
 * Author: Howard Cheng
 *
 * The evaluate() routine takes a string containing an infix arithmetic
 * expression, and return the numeric result after evaluation.  The
 * parameter error indicates whether an error has occurred (syntax
 * error, illegal operation, etc.).  If there is an error the result
 * returned is meaningless.
 *
 * The routine assumes that the operands in the input are integers
 * with no leading signs.  It supports the standard +, -, *, / and
 * parentheses.  If you need to support more operators, operand types,
 * etc., you will need to modify the code.  See comments below.
 * 
 */

#include <iostream>
#include <string>
#include <stack>
#include <cctype>
#include <cstdlib>

using namespace std;

// What is a token?  Modify if needed (e.g. to support variables, extra
// operators, etc.)
struct Token
{
  enum Type {VARIABLE, PLUS, TIMES, LEFT_PAREN, RIGHT_PAREN};
  
  // priority of the operators: bigger number means higher priority
  // e.g. * has priority 2, + has priority 1, ( has priority 0
  int priority[5];
  
  // is the operator left associative?  It's assumed that all operators
  // of the same priority level has the same left/right associative property
  bool left_assoc[5];
  
  Type type;
  char var;

  Token()
  {
    priority[1] = 1;
    priority[2] = 2;
    priority[3] = 0;
    left_assoc[1] = left_assoc[2] = true;
    var = ' ';
  }

  int get_priority() {
    return priority[type];
  }
  
  bool is_left_assoc() {
    return left_assoc[type];
  }

  // returns true if there is a next token
  bool next_token(const string &expr, int &start, bool &error)
  {
    int len = expr.length();

    error = false;
    while (start < len && isspace(expr[start])) {
      start++;
    }
    if (start >= len) {
      return false;
    }
    
    switch (expr[start]) {
    case '(':
      type = LEFT_PAREN;
      break;
    case ')':
      type = RIGHT_PAREN;
      break;
    case '*':
      type = TIMES;
      break;
    case '+':
      type = PLUS;
      break;
    default:
      // check for variable
      if (!islower(expr[start])) {
	error = true;
	return false;
      }
      type = VARIABLE;
      var = expr[start];
    }
    start++;
    return true;
  }
};

struct ResultType {
  Token::Type main_type;
  string val;

  ResultType(char v = ' ', Token::Type type = Token::VARIABLE)
    : main_type(type)
  {
    val += v;
  }

  ResultType(const string &v, Token::Type type)
    : main_type(type), val(v) { }

};

// Modify this if you need to support more operators or change their
// meanings.
//
// returns true if operation is successful
bool apply_op(stack<ResultType> &operands, Token token)
{
  ResultType a, b;
  string result;
  if (operands.size() < 2) {
    return false;
  }
  if (token.type == Token::PLUS) {
    b = operands.top(); operands.pop();
    a = operands.top(); operands.pop();
    result = a.val + "+" + b.val;
  } else if (token.type == Token::TIMES) {
    b = operands.top(); operands.pop();
    a = operands.top(); operands.pop();
    if (a.main_type == Token::PLUS) {
      result += "(" + a.val + ")";
    } else {
      result += a.val;
    }
    if (b.main_type == Token::PLUS) {
      result += "(" + b.val + ")";
    } else {
      result += b.val;
    }
  } else {
    return false;
  }
  operands.push(ResultType(result, token.type));
  return true;
}

string evaluate(string expr, bool &error)
{
  for (string::size_type i = 0; i < expr.length(); i++) {
    if (expr[i] == ')' || islower(expr[i])) {
      if (i+1 < expr.length() && (expr[i+1] == '(' || islower(expr[i+1]))) {
	expr.insert(i+1, "*");
      }
    }
  }

  stack<Token> s;
  stack<ResultType> operands;
  int i;
  Token token;

  error = false;
  i = 0;
  while (token.next_token(expr, i, error) && !error) {
    switch (token.type) {
    case Token::VARIABLE:
      operands.push(token.var);
      break;
    case Token::LEFT_PAREN:
      s.push(token);
      break;
    case Token::RIGHT_PAREN:
      while (!(error = s.empty()) && s.top().type != Token::LEFT_PAREN) {
	if ((error = !apply_op(operands, s.top()))) {
	  break;
	}
	s.pop();
      }
      if (!error) {
	s.pop();
      }
      break;
    default:      // arithmetic operators
      while (!error && !s.empty() && 
	     (token.get_priority() < s.top().get_priority() ||
	      (token.get_priority() == s.top().get_priority() &&
	      token.is_left_assoc()))) {
	error = !apply_op(operands, s.top());
	s.pop();
      }
      if (!error) {
	s.push(token);
      }
    }
    if (error) {
      break;
    }
  }
  while (!error && !s.empty()) {
    error = !apply_op(operands, s.top());
    s.pop();
  }
  error |= (operands.size() != 1);
  if (error) {
    return "";
  }
  return operands.top().val;
}

int main(void)
{
  string result;
  string expr;
  bool error; 

  getline(cin, expr);
  while (!cin.eof()) {
    result = evaluate(expr, error);
    if (error) {
      cout << "Invalid expression" << endl;
    } else {
      cout << result << endl;
    }
    getline(cin, expr);
  }
  return 0;

}
