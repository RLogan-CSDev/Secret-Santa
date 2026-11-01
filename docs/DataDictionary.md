# Data Dictionary: Secret Santa Application
This document serves as the single source of truth for all core data structures, entities,
and their attributes within the Secret Santa application. Clearly defining the data types,
relationships, assignments, constraints, and more allows this document to ensure structural
consistency across the C++ codebase and guide for future maintenance/expansion.

## Object : Player()

| **Variable ID** | **Field Name** | **Date Type** | **Technical Description** | **Constraints** | **Syntax Pattern** |
| :---: | :---: | :---: | :---: | :---: | :---: |
| 1 | name | QString | The name of the player added | *none* | "*data*"
| 2 | gift | QString | The gift of the player added | *none* | "*data*"
| 3 | partner | QString | String used to track partner of player added | defaulted to name of player to ensure variable holds a value | "*data*"

## Object : SantaBag()
| **Variable ID** | **Field Name** | **Date Type** | **Technical Description** | **Constraints** | **Syntax Pattern** |
| :---: | :---: | :---: | :---: | :---: | :---: |
| 1 | players | std::vector(Player) | Vector that holds Player() objects | vector is static and will not be changed during runtime | *players.push_back(playerObject)* |
| 2 | playerCount | int | Accumulator for total additions in vector, used for live feedback during runtime | cannot be negative number | *data* |
| 3 | MAX_ATTEMPTS | const int | Constant used for limiting looping repetitions for assignment attempts; avoids using magic numbers | unchanging value, set in header file | *= 100* |
| 4 | hasDrawnFlags | std::vector(bool) | Parallel vector that maintains valid assignments | defaulted to false | *true/false* |
| 5 | assignmentIndices | std::vector(int) | Parallel vector that gets shuffled to generate valid assignments | defaulted to -1; uses std::shuffle and std::mt19937 to randomize vector | *0-playerCount* |
| 6 | giverPlayer | Player* | Pointer to player in players vector for who is giving | defaulted to a null pointer used in valid draws that pull selected player from front-end | *= &players(index)* |
| 7 | assignedPlayer | Player* | Pointer to player in players vector for who is assigned | defaulted to a null pointer | *= &players(index)* |
| 8 | assignedName | QString | String used to pull name from assignedPlayer pointer | must be pulled from Player object | *->getName()* |
| 9 | assignedGift | QString | String used to pull gift from assignedPlayer pointer | must be pulled from Player object | *->getGift()* |