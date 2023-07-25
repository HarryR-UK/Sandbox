# Conways's Game of Life
Conway's Game of Life is a cellular automata which simulates the population of life following 4 rules

This program uses C++ and the SFML library for graphics to visually represent these rules. This produces some interesting results!


## 4 Rules
1.  Any live cell with fewer than two live neighbours dies, as if by underpopulation.
2.  Any live cell with two or three live neighbours lives on to the next generation.
3.  Any live cell with more than three live neighbours dies, as if by overpopulation.
4.  Any dead cell with exactly three live neighbours becomes a live cell, as if by reproduction.

# Controls

> **SPACE** is used to start and stop the simulation
>
> **LEFT CLICK** is used to turn cells alive when the game is paused
>
> **RIGHT CLICK** is used to kill cells when the game is paused
>
> **R** will reset the randomised cells when the game is paused
> 
> **C** will clear the cells entirely when the game is paused
>
> **F** will turn changing cycling colors on / off
> 
> **O** will make the alive cells look more pixelated / less pixelated
>
> **SCROLL WHEEL** will zoom in and out
>
> **LEFT ARROW KEY** will cycle left through the colors when cycle color is false
>
> **RIGHT ARROW KEY** will cycle right through the colors when cycle color is false
>
> **UP ARROW KEY** increases the simulation delay
>
> **DOWN ARROW KEY** decreases the simulation delay
>
> **W A S D** will pan around the map

# IMAGES

![STILL IMAGE](img/GOL.png)

![STILL IMAGE](img/GOL2.png)

![DRAW](img/DRAW.png)

# GIFS
![GIF](img/gifs/GOLGIF.gif)
