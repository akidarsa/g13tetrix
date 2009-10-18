1)  The piece is moved based on the key pressed event by calling the corresponding
function based on the key that was pressed.  The event function stores the key
value that was pressed and so this value is simply compared to the keys of the
current controls and the appropriate function call is used.

2)  The current implementation of the code uses five classes piecegenerator, 
tetrixboard, tetrixkey, tetrixpiece, and tetrixwindow.  The piecegenerator is 
the class that reads from the input file to create each of the pieces.  It has
functions openInput and getNextPiece which open the input file and send the 
next piece to the board.
  The tetrixboard class is what provides the basic tetris functionality.  It 
has many functions as well as multiple signals and slots for the connections 
between the buttons.  The first function is called setNextPieceLabel which 
displays the next piece in the next piece area.  The shapeAt function returns
 where the piece is on the board.  The squareWidth and squareHeight functions 
keep all of the bricks for each piece the proper size for the size of the board.  The clearBoard function clears the playing area, and the oneLineDown function
moves the piece one line down on the board while the dropDown function hard
drops the piece to the bottom of the playing space.  the pieceDropped function
checks if the dropped piece created a full line and changes the level with the
number of pieces that have been dropped.  The removeFullLines function removes
a full line from the play area, and the newPiece function calls the
 showNextPiece function which trys to display a new piece to the play area and 
if the piece cannot be added then a message pops up indicating a loss.  The 
tryMove function checks to see if a rotation or movement is possible given the
place of the current piece.  There are also signals that get called whenever
the scoring and counting displays need to be updated.  The slots are start,
pause, keyConfig, and demoMode.  The start slot sets up the displays and sets
all of the variables to the default.  The pause slot pauses the game, and the
keyConfig causes a key configuration window to pop up.  The demoMode slot is 
used for the demo mode of the game so the player cannot perform any operations
when demo mode is set.  There are event based functions as well named paintEvent
keyPressEvent, and timerEvent.  The paintEvent function is used to paint the 
pieces onto the board.  The keyPressEvent function is used to check the controls
input from the user to see what operations to perform on the piece.  Finally, 
the timerEvent causes the piece to drop one line every half second.
  The tetrixkey class has one function and one slot getKey and makepopup.  The 
getKey function returns the key that was pressed when the popup window was open.
The makepopup slot creates the window with buttons for each control allowing
the user to change the key configurations.
  The tetrixpiece class uses the setRandomShape function to read the piece 
from the file and then creates the piece.  The class also includes functions to
rotate the piece to the left and right and update the piece accordingly in the
play area.
  The tetrixwindow class sets up the window for the tetris game.  This is where the layout of the window is set as well as the connections for all of the 
buttons and displays.  This class only contains one function called creatLabel
which creates a QLabel.

3)  The code is prepared for the next stage in that the basic functionality of 
the tetris game is working for a single gameplay area.  The code can then be 
extended to work with another playarea with the same abilities and have two sets
 of configure keys operations.  The scoring displays as well as the button
operations can also be reused in the next stage of development.
