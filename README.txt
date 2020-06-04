


Things missing:

 * Animations - after an entire day of work trying to implement Animations that got me nowhere I decided
 		to let go of them and focus on all other things that I still had to implement;

 * Combos - As it is the player does not get extra points for getting the 'cascading' destruction that happens
	    after a group is destroyed and the destruction of that group led to another group being destroyed;

 * Random Pieces spawning from time to time - the game does not have a lot of challenge, the player does not
	need to adapt to any unforseen circumstances, spawning a line of random piece from time to time
	would be a good way to	make the game more interesting in that regard;

 * Sounds - for group destruction, pair spawned, pair placed, level completed and game lost;

 * Particle Systems - for example when a group is destroyed or a level was completed;

 * Menu - with play and quit buttons. When the player lost the game, the game should return to this menu instead of
	starting right away again;
 
HIGHLIGHTS:
 * The event system and how easy it is to use is something that I am very proud of. I only started using it halfway
	through the development and it was a great way to make sure there was no unnecessary coupling for a lot of classes.
	This event system uses the SDL_Events as a basis;

 * I strongly believe that there are no memory leaks and the way I used smart pointers shows clearly when a 
	the ownership is being passed on from one object to another;

 * I was able to encapsulate a lot of data related implementation so that classes that used them didn't had lower level
	implementation details (p.e. 'MatrixGrid' using 'GridDataStructure');

 * The SDL references are condensed in a few files that are supposed to make the bridge between SDL and my project, even
though a very small amount of them are still present in files they should not be;

 * In general classes are small and only have one purpose;

 * I tried to make complex functions readable, p.e. 'Game::Update()'; 

 * Enumerations used abundantly to show the intent behind the code;

 * I used the Law of Demeter as much as I could (it is likely that I forgot some calls though);

 * A lot of information is being displayed to the player, like the current position of the pairOfPieces, the background
 helps the player understand where the pieces will fall and the limits of the grid, the bars shows roughly how much
 time the player still has to complete the level as well as how close he is to doing so and the level he is currently on;

 * Dependency Inversion was used in some parts of the code (p.e. 'IGridRepresentation' use in 'Game', if we wanted to test a different
representation for the Grid, or 'IEventData' used in various files that have callback functions where if we changed the underlying event
provider from SDL_Event to something else, not a lot of code needed to change);


Known bugs:

* Sometimes rotating a pair to close to the top of a column will cause the pair to stay still above the column
displaying a hole between the top of that column and one of the pieces of the pair. The player as to rotate 
the pair one more time for the game to work normally;

* When a column (this is most easily reproduced in the column where the pairs are spawned) is almost 
at full capacity and the player tries to rotate the pair, one of the pieces may stick to the column and the 
other falls through the grid and off the screen. This does disables input and only when the time runs out the 
game will be normal again.

* After losing a game because one of the columns got too high the first piece being spawned sometimes
is not registering the 'a' key being pressed, this does not happen with the 'd' key.