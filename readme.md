# Wordle Bot V2.0

## How to use Solver
1. Ask for initial guess (ex: Query>guess)
    1. The solver will give you a guess (ex: Best next guess: worst)
    2. Put this into Wordle (<span style="color:#6aaa64">W</span><span style="color:#6aaa64">O</span><span style="color:#6aaa64">R</span><span style="color:#c9b458">S</span><span style="color:#86888a">T</span>)
2. Submit result of guess (ex: Query>WOR##|S or-- Query>WORs#)
3. Repeat

### Commands
- \<green letters\>|\<yellow letters\> : input wordle feedback
    - Enter known green letters based on position placing '#' for unknown letters
    - Enter pipe '|'
    - Enter all yellow letters or nothing if none
- G#y##
    - Enter green letters with upper case letters.
    - Enter yellow letters with lower case letters.
    - Enter '#' for the rest
- guess: request a potential word and adds it as an attempted word
- attempt \<word\>: add an attempted word 
- attempts: list all attempted words
- pool: list all possible words based on current state
- reset: reset all solver state
- help: prints commands
- quit: Ends process

### TODO
* Write Solver
    1. ~~Write initial solver~~
    2. ~~Write tests for solver~~
    3. ~~Refactor with more 'functional' methods~~
    4. ~~Enhance solver to store/track/use yellow letter position~~
* Make it a bot

