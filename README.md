# Chess Game

#### By _Nikolay Georgiev_
<br>

## Usage:
- Create `/build` directory
- From the `/build` directory run `cmake ..` command in terminal
- After `CMake` is done run `make`
- New target `Chess` is created
- Run
- Enjoy

<br>

## Note:
At the momement this project runs only on Linux 

<br>

## Implemented:
- Game logic:
  - Pawn promotion
  - All figures movement behaviour
  - En Passant
  - Check
  - Checkmate(can stil be improved to cover more cases)
  - Player turn timer cap
  
- Start game panel with navigation buttons for `Start`, `Continue`, `Exit` and `Quit` Game
- Timer that gives each player one minute for turn is drawn in game
- Movement Log that is visualised in game
- Game and it's current state can be saved then loaded

<br>

## Known issues and things to improve:
- Castle feauture not implememnted
- Dead position not implemented
- Checkmate feauture can be improved to cover more cases
- Start Panel not showing when game has ended in Checkmate


