# Game-of-Life
Conway's Game of Life in C++ and SFML with mouse input option.


# Features

-   The code displays the game of life grid once per generation. All the updated cell positions are displayed using a single display command. As the display function usually takes the most processing time, this feature makes the code fast.

-   The code speed does not decrease noticeably with the increase of grid size. This is due to the fact that the number of times the display command, window.display(), is used is independent of grid size.

-   Can simulate very large gird sizes.

-   The simulation can be paused and cell status can be updated using mouse input. Then the simulation can be restarted with the modified cell status.


# Use

Run the make file from the terminal. An output file (game_of_life_output) will be created on the same folder. Run the output file from the terminal using \`\`\`.\\game_of_life_output \`\`\` command.

 
## Sample Output
<img src="https://github.com/zaman13/Game-of-Life/blob/master/Game-of-life_output_screen.gif" alt="alt text" width="440">
