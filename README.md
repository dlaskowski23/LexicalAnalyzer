# CS280-Lexcia-Analyzer-Parser-and-Interpreter 

## The first part was creating a lexical analyzer that is used to read a text file and determine what the next token is. With the
knowledge of the next and previous token, the analyzer determines if an error has occurred and what the error is. The language
being analyzed is an untyped language that can recognize strings, ints, and real numbers. The language also supports single-line
comments and single-line if-else statements. <br>
 <br>The second part is a decent recursive parser. This uses simple Grammar to determine syntactical errors by comparing Tokes and
the Grammar's structure. The Recursive Decent Parser uses a Lexical Analyzer as a front to determine what type of Token a string
of text is within a file. The Tokens are used in the Parser to find syntax errors by comparing them to a basic language grammar
that defines how the language works. <br>
<br>The third part combines the previous parts creating an Interpreter. The Interpreter will now not only check for syntax errors but
also run the assigned statements. The Language Interpreter uses value checking along with the previous format of the Recursive
