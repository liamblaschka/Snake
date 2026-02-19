# Snake

## Description
Snake with BFS and DFS search algorithms in C++ using SFML.
The game can be played by BFS or DFS search algorithms, or can be played by the user.
The BFS and DFS search algorithms play the game by searching for and traversing a path to the fruit; BFS is able to find the shortest path to the fruit, while DFS does not.
The user can play the game using the arrow keys.

## Instructions
- Make a build directory and within it run `cmake ..` , then when it is finished, run `make`.
- Navigate to the bin directory within build.
### To play as user
- Run `snake` executable.
### To play with search algorithm
- Run `snake <algorithm>` in terminal; `snake BFS` or `snake DFS`.

## Preview
Video preview of BFS playing Snake: https://www.youtube.com/watch?v=eUCAugH0eGM
<div align="center">
  <img src="https://github.com/liamblaschka/image-repo/blob/main/Snake/gameplay.png" width="355" height="400">
  <p>
    The snake in green has the goal of eating the white square fruit.<br>
    The score and high score are displayed at the top of the game, and in the terminal when the game is over.
  </p>
</div>
