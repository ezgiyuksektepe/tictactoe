 The state of the game is represented by a 9 digit base 3 number.
 Each digit represents one position on the board, labeled as follows:
 0 | 1 | 2
 --+--+--
 3 | 4 | 5
 --+--+--
 6 | 7 | 8
 
 Each digit can have values 0: Empty, 1: X, or 2: O
 Every state can be represented as number between 0
 and 3**9 - 1.  By convention, 3**9: tie, 3**9+1: X win, 3**9+2: O win
 
 The program is designed to play with other tic-tac-toe players.  Therefore
 uses the following conventions...
 
 1. The first parameter to the program must be either "X" or "O" (the
 letter O... not the number) to represent whether this program should
 play "X" or "O".
 
 2. X always takes the first turn.
 
 3. When the program  makes a move, it writes the state out to standard
 output via a simple printf statement.  The program will not write anything
 else to standard output.  (However, it can write messages to standard
 error.)
 
 4. The program will determine what its opponent's move is by reading
 a single integer from standard input.  This number represents the
 position (0-8) which your opponent will take.  For instance, if the
 program is playing "O", and reads "2" from standard input, then
 the opponent is asking to put an "X" in the upper right hand
 corner of the board.  If the opponent specifies an incorrect input,
 either an invalid number, or a position that has already been taken,
 then the program can claim a win by default.
 