# TileMatchingGame
Tile Matching Game inspired by [Puyo Puyo](https://www.youtube.com/watch?v=YJjRJ_4gcUw)

### 0th iteration: 1 estimated day (last day: 20th of May)
* [x] schedule and task list
* [x] gitHub
* [x] project settings
* [x] precompiled header
* [ ] cap framerate
* [ ] time count
* [ ] event system

### 1st iteration: 1 estimated day (last day: 21st of May)
* [ ] grid 8 * 16 is created
* [ ] pieces/grid are being drawn
* [ ] pairs are being spawned when another pair is placed
* [ ] pairs go down the screen and they stop when they reach the bottom
* [ ] pieces are visually in the right grid position
* [ ] player can move pairs with keyboard (lessons 4 and 18)
* [ ] movement of pair is restricted by board boundaries
* [ ] pieces stack, pairs can split

### 2nd iteration: 3 estimated days (last day: 24th of May)
* [ ] 4 different pieces
* [ ] check for matching groups and delete them
* [ ] when a group is deleted update the positions of the remaining pieces
* [ ] rotate pair using mouse
* [ ] increase pair speed with keyboard

### 3rd iteration: estimated 4 days (last day: 28th of May)
* [ ] change sprite of pieces that have neighbours of the same color (lessons 10 and 13)
* [ ] make a group flash from full color to high transparency before deleting it (or fade it out) (lessons 10 and 13)
* [ ] attribute points for deleted groups (#pieces * 10)
* [ ] win condition (check if current points are higher than needed points)
* [ ] bar that shows the progress of the player towards the completion of the level
* [ ] restart game
* [ ] if the player won, the game should restart with higher needed points for win
* [ ] lose condition (if pair placed would be outside of the grid)
* [ ] combos affect points (new formula for points should be #pieces * 10 * combo)

### 4th iteration: estimated 4 days (last day: 1st of June)
* [ ] show what the next pair will be
* [ ] display victory and lose text (lessons 16)
* [ ] use particles when a group is destroyed (lesson 38)
* [ ] sounds for group, pair spawned, pair placed
* [ ] make menu with start game and exit buttons
* [ ] if the player loses, send him to the menu
* [ ] display combo counter
