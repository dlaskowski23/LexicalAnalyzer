#include "parserInt.h"
#include "lex.h"

map<string, bool> defVar;
map<string, Token> SymTable;
map<string, Value> TempsResults; 
queue <Value>* ValQue; 

namespace Parser {
	bool pushed_back = false;
	LexItem	pushed_token;

	static LexItem GetNextToken(istream& in, int& line) {
		if (pushed_back) {
			pushed_back = false;
			return pushed_token;
		}
		return getNextToken(in, line);
	}

	static void PushBackToken(LexItem& t) {
		if (pushed_back) {
			abort();
		}
		pushed_back = true;
		pushed_token = t;
	}

}

static int error_count = 0;

int ErrCount()
{
	return error_count;
}

void ParseError(int line, string msg)
{
	++error_count;
	cout << error_count << ". Line # " << line << ": " << msg << endl;
}

//-------------------------------------------------------------------------------------------------------

//Prog ::= StmtList
bool Prog(istream& in, int& line) {
	bool stmtListStatus = StmtList(in, line);

	if (!stmtListStatus) {
		ParseError(line, "Error in Program");
		return false;
	}
	
	cout << endl << "(DONE)" << endl;
	return true;
}

//-------------------------------------------------------------------------------------------------------

//StmtList ::= Stmt ;{ Stmt; }

bool StmtList(istream& in, int& line)
{
	bool status;
	LexItem t;

	status = Stmt(in, line);
	if (!status) {
		ParseError(line, "Syntatic Error in program body");
		return false;
	}
	t = Parser::GetNextToken(in, line);
	if (t != SEMICOL)
	{
		ParseError(line, "Missing Semi-colon after statement");
		return false;
	}
	t = Parser::GetNextToken(in, line);
	if (t == RBRACES) {
		Parser::PushBackToken(t);
		return true;
	}
	if (t != DONE) {
		Parser::PushBackToken(t);
		return StmtList(in, line);
	}

	return true;
}

//-------------------------------------------------------------------------------------------------------

//Stmt :: = AssignStmt | WriteLnStmt | IfStmt
bool Stmt(istream& in, int& line) {
	bool status = false;
	LexItem t = Parser::GetNextToken(in, line);

	if (t == WRITELN) {
		status = WritelnStmt(in, line);
		if (!status) {
			ParseError(line, "Incorrect Writeln Statement");
			return false;
		}
	}

	else if (t == IF) {
		status = IfStmt(in, line);
		if (!status) {
			ParseError(line, "Incorrect If Statement");
			return false;
		}
	}

	else {
		Parser::PushBackToken(t);
		status = AssignStmt(in, line);
		if (!status) {
			ParseError(line, "Incorrect Assignment Statement");
			return false;
		}
	}

	return true;
}

//-------------------------------------------------------------------------------------------------------

//WritelnStmt:= WRITELN (ExpreList) 
bool WritelnStmt(istream& in, int& line) {
	LexItem t;
	ValQue = new queue<Value>;

	t = Parser::GetNextToken(in, line);
	if (t != LPAREN) {

		ParseError(line, "Missing Left Parenthesis of Writeln Statement");
		return false;
	}

	bool ex = ExprList(in, line);

	if (!ex) {
		ParseError(line, "Missing expression list after Print");
		while (!(*ValQue).empty())
		{
			ValQue->pop();
		}
		delete ValQue;
		return false;
	}

	while (!(*ValQue).empty())
	{
		Value nextVal = (*ValQue).front();
		cout << nextVal;
		ValQue->pop();
	}
	cout << endl;

	t = Parser::GetNextToken(in, line);
	if (t != RPAREN) {

		ParseError(line, "Missing Right Parenthesis of Writeln Statement");
		return false;
	}
	return true;
}

//-------------------------------------------------------------------------------------------------------

//IfStmt ::= if (Expr) ‘{‘ StmtList ‘}’ [ else ‘{‘ StmtList ‘}’ ]
bool IfStmt(istream& in, int& line) {
	bool ex = false, status;
	LexItem t;
	Value retVal;

	t = Parser::GetNextToken(in, line);
	if (t != LPAREN) {
		ParseError(line, "Missing Left Parenthesis of If condition");
		return false;
	}
	ex = Expr(in, line, retVal);
	if (!ex) {
		ParseError(line, "Missing if statement Logic Expression");
		return false;
	}
	t = Parser::GetNextToken(in, line);
	if (t != RPAREN) {
		ParseError(line, "Missing Right Parenthesis of If condition");
		return false;
	}
	if (!retVal.IsBool()) {
		ParseError(line, "error");
		return false;
	}
	
	t = Parser::GetNextToken(in, line);
	if (t != LBRACES) {
		ParseError(line, "If Statement Syntax Error: Missing left brace");
		return false;
	}
	
	if (retVal.GetBool()) {
		status = StmtList(in, line);
		if (!status) {
			ParseError(line, "Missing Statement for If-Stmt Clause");
			return false;
		}
		t = Parser::GetNextToken(in, line);
		if (t != RBRACES) {
			ParseError(line, "If Statement Syntax Error: Missing right brace.");
			return false;
		}
		t = Parser::GetNextToken(in, line); 
		if (t == ELSE) {
			t = Parser::GetNextToken(in, line);
			if (t != LBRACES) {
				ParseError(line, "If Statement Syntax Error: Missing left brace");
				return false;
			}
			t = Parser::GetNextToken(in, line);
			while (t != RBRACES) {
				if (t == DONE) {
					ParseError(line, "If Statement Syntax Error: Missing right brace.");
					return false;
				}
				t = Parser::GetNextToken(in, line);
			}
		}
		else { 
			Parser::PushBackToken(t); 
		} 
	}
	else {
		while (t != RBRACES) {
			if (t == DONE || t == ELSE) {
				ParseError(line, "If Statement Syntax Error: Missing right brace.");
				return false;
			}
			t = Parser::GetNextToken(in, line);
		}

		t = Parser::GetNextToken(in, line);
		if (t == ELSE) {
			t = Parser::GetNextToken(in, line);
			if (t != LBRACES) {
				ParseError(line, "If Statement Syntax Error: Missing left brace");
				return false;
			}
			status = StmtList(in, line);
			if (!status) {
				ParseError(line, "Missing Statement for Else-Clause");
				return false;
			}
			t = Parser::GetNextToken(in, line);
			if (t != RBRACES) {
				ParseError(line, "If Statement Syntax Error: Missing right brace.");
				return false;
			}
		}
		else {
			Parser::PushBackToken(t);
		}
	}

	return true;
}

//-------------------------------------------------------------------------------------------------------

//AssignStmt ::= Var = Expr 
bool AssignStmt(istream& in, int& line) {
	bool status = false;
	LexItem idtok;
	idtok = Parser::GetNextToken(in, line);
	Value retVal;

	status = Var(in, line, idtok);
	if (!status) {
		return false;
	}

	string lexeme = idtok.GetLexeme();
	LexItem t;
	t = Parser::GetNextToken(in, line);
	if (t != ASSOP) {
		defVar[lexeme] = false;
		Parser::PushBackToken(t);
		return true;
	}

	status = Expr(in, line, retVal);
	if (!status) {
		ParseError(line, "Missing Expression in Assign Statement");
		return false;
	}
	
	if (idtok == NIDENT && !retVal.IsInt() && !retVal.IsReal() ) {
		ParseError(line, "error");
		return false;
	}
	if (idtok == SIDENT && !retVal.IsInt() && !retVal.IsReal() && !retVal.IsString()) {
		ParseError(line, "error");
		return false;
	}
	TempsResults[lexeme] = retVal;

	defVar[lexeme] = true;
	return true;
}

//-------------------------------------------------------------------------------------------------------

//Var :: = NIDENT | SIDENT
bool Var(istream& in, int& line, LexItem& idtok) {
	if (idtok != NIDENT && idtok != SIDENT) {
		return false;
	}

	return true;
}

//-------------------------------------------------------------------------------------------------------

//ExprList ::= Expr { , Expr }
bool ExprList(istream& in, int& line) {
	bool status = false;
	Value retVal;

	status = Expr(in, line,retVal);
	if (!status) {
		ParseError(line, "Error in exprlist()1");
		return false;
	}
	ValQue->push(retVal);
	LexItem tok = Parser::GetNextToken(in, line);

	if (tok == COMMA) {
		status = ExprList(in, line);
	}
	else if (tok.GetToken() == ERR) {
		ParseError(line, "Error in exprlist()2");
		cout << "(" << tok.GetLexeme() << ")" << endl;
		return false;
	}
	else {
		Parser::PushBackToken(tok);
		return true;
	}
	return status;
}


//-------------------------------------------------------------------------------------------------------

//Expr :: = RelExpr[(-eq | == ) RelExpr]
bool Expr(istream& in, int& line, Value& retVal) {
	bool relExprStatus = false;
	LexItem t;


	relExprStatus = RelExpr(in, line, retVal);
	if (!relExprStatus) {
		return false;
	}

	Value val = retVal;
	t = Parser::GetNextToken(in, line);

	if (t == SEQ || t == NEQ) {
		relExprStatus = RelExpr(in, line, retVal);
		if (!relExprStatus) {
			ParseError(line, "Missing opperand after operator");
			return false;
		}
		if (t == SEQ) {
			retVal = val.SEqual(retVal);
		}
		else if (t == NEQ) {
			retVal = val == retVal;
		}
		if (retVal.IsErr()) {
			ParseError(line, "error LOL1");
			return false;
		}
	}
	else {
		Parser::PushBackToken(t);
	}

	return true;
}

//-------------------------------------------------------------------------------------------------------

//RelExpr ::= AddExpr [ ( -lt | -gt | < | > ) AddExpr ]
bool RelExpr(istream& in, int& line, Value& retVal) {
	bool addExprStatus = false;
	LexItem t;
	

	addExprStatus = AddExpr(in, line, retVal);
	if (!addExprStatus) {
		return false;
	}

	Value val = retVal;
	t = Parser::GetNextToken(in, line);

	if (t == SLTHAN || t == SGTHAN || t == NLTHAN || t == NGTHAN) {

		addExprStatus = AddExpr(in, line, retVal);
		if (!addExprStatus) {
			ParseError(line, "Missing opperand after operator");
			return false;
		}
		if (t == SLTHAN) {
			retVal = val.SLthan(retVal);
		}
		else if (t == SGTHAN) {
			retVal = val.SGthan(retVal);
		}
		else if (t == NLTHAN) {
			retVal = val < retVal;
		}
		else if (t == NGTHAN) {
			retVal = val > retVal;
		}
		if (retVal.IsErr()) {
			ParseError(line, "error LOL2");
			return false;
		}
	}
	else {
		Parser::PushBackToken(t);
	}

	return true;
}


//-------------------------------------------------------------------------------------------------------

//AddExpr :: MultExpr { ( + | - | .) MultExpr }
bool AddExpr(istream& in, int& line, Value& retVal) {
	bool multExprStatus = false;
	LexItem t;
	

	multExprStatus = MultExpr(in, line, retVal);
	if (!multExprStatus) {
		return false;
	}

	t = Parser::GetNextToken(in, line);

	while (t == PLUS || t == MINUS || t == CAT) {
		Value val = retVal;
		multExprStatus = MultExpr(in, line, retVal);
		if (!multExprStatus) {
			ParseError(line, "Missing opperand after operator");
			return false;
		}
		
		if(t == PLUS) {
			retVal = val + retVal;
		}
		else if (t == MINUS) {
			retVal = val - retVal;
		}
		else if (t == CAT) {
			retVal = val.Catenate(retVal);
		}
		if (retVal.IsErr()) {
			ParseError(line, "error LOL3");
			return false;
		}
		t = Parser::GetNextToken(in, line);
	}

	Parser::PushBackToken(t);
	return true;
}

//-------------------------------------------------------------------------------------------------------

//MultExpr ::= ExponExpr { ( * | / | **) ExponExpr }
bool MultExpr(istream& in, int& line, Value& retVal) {
	bool ExponExprStatus = false;
	LexItem t;
	

	ExponExprStatus = ExponExpr(in, line, retVal);
	if (!ExponExprStatus) {
		return false;
	}

	t = Parser::GetNextToken(in, line);

	while (t == MULT || t == DIV || t == SREPEAT) {
		Value val = retVal;
		ExponExprStatus = ExponExpr(in, line, retVal);
		if (!ExponExprStatus) {
			ParseError(line, "Missing opperand after operator");
			return false;
		}

		if (t == MULT) {
			retVal = val * retVal;
		}
		else if (t == DIV) {
			retVal = val / retVal;
		}
		else if (t == SREPEAT) {
			retVal = val.Repeat(retVal);
		}
		if (retVal.IsErr()) {
			ParseError(line, "error LOL4");
			return false;
		}
		t = Parser::GetNextToken(in, line);
	}

	Parser::PushBackToken(t);
	return true;
}

//-------------------------------------------------------------------------------------------------------

//ExponExpr ::= UnaryExpr { ^ UnaryExpr }
bool ExponExpr(istream& in, int& line, Value& retVal) {
	bool Status = false;
	LexItem t;
	

	Status = UnaryExpr(in, line, retVal);
	if (!Status) {
		return false;
	}

	Value val = retVal;
	t = Parser::GetNextToken(in, line);

	if (t == EXPONENT) {
		Status = ExponExpr(in, line, retVal);
		if (!Status) {
			ParseError(line, "Missing opperand after operator");
			return false;
		}
		retVal = val ^ retVal;
		
	}
	else {
		Parser::PushBackToken(t);
	}
	return true;
}

//-------------------------------------------------------------------------------------------------------

//UnaryExpr ::= [( - | + )] PrimaryExpr

bool UnaryExpr(istream& in, int& line, Value& retVal)
{
	LexItem t = Parser::GetNextToken(in, line);
	bool status;
	int sign = 0;

	if (t == MINUS)
	{
		sign = -1;
	}
	else if (t == PLUS)
	{
		sign = 1;
	}
	else {
		Parser::PushBackToken(t);
	}

	status = PrimaryExpr(in, line, sign, retVal);

	return status;
}

//-------------------------------------------------------------------------------------------------------

//PrimaryExpr ::= IDENT | SIDENT | NIDENT | ICONST | RCONST | SCONST | (Expr)

bool PrimaryExpr(istream& in, int& line, int sign, Value& retVal) {
	LexItem t = Parser::GetNextToken(in, line);
	string x = t.GetLexeme();
	if (t == IDENT || t == ICONST || t == RCONST || t == SCONST) {
		if (t == ICONST || t == RCONST) {
			
			if (x[x.size() - 1] == '.') {
				int y = stoi(x);
				retVal = Value(y);
			}
			else {
				double y = stod(x);
				retVal = Value(y);
			}
		}
		else if (t == SCONST) {
			if (sign != 0) {
				ParseError(line, "not possible, sign error");
				return false;
			}
			retVal = Value(x);
		}
		return true;
	}

	else if (t == SIDENT || t == NIDENT) {
		if (defVar[t.GetLexeme()] != true) {
			ParseError(line, "Undefined Variable");
			return false;
		}

		if (sign == -1) {
			retVal = TempsResults[x] * -1;
		}
		else {
			retVal = TempsResults[x];
		}
		
		return true;
	}

	else if (t == LPAREN) {
		bool status = Expr(in, line, retVal);
		if (!status) {
			ParseError(line, "Missing expression after Left Parenthesis");
			return false;
		}
		if (Parser::GetNextToken(in, line) == RPAREN)
			return status;
		else
		{

			ParseError(line, "Missing right Parenthesis after expression");
			return false;
		}
	}

	else {
		return false;
	}
}

//-------------------------------------------------------------------------------------------------------