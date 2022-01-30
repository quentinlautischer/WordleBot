# Wordle Bot V2.0

## How to use Solver
1. Ask for initial guess (ex: Query>guess)
2. Submit result of guess (ex: Query>WOR##|DS)
3. Repeat

### Commands
- \<green letters\>|\<yellow letters\> : input wordle feedback
    - Enter known green letters based on position placing '#' for unknown letters
    - Enter pipe '|'
    - Enter all yellow letters or nothing if none
- guess: request a potential word
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

