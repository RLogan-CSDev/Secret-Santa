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
| 4 | assignedName | QString | Player's name assignment | cannot be self or partner name | "*data*"
| 5 | assignedGift | QString | Player's gift assignment from name assigned | cannot be self or partner gift | "*data*"

## Object : SantaBag()
| **Variable ID** | **Field Name** | **Date Type** | **Technical Description** | **Constraints** | **Syntax Pattern** |
| :---: | :---: | :---: | :---: | :---: | :---: |
| 1 | players | std::vector(Player) | Vector that holds Player() objects | vector is static and will not be changed during runtime | players.push_back(playerObject);
| 2 | selectionPool | std::vector(Player) | Dynamic vector for assignment | *none* | selectionPool = players;
| 3 | playerCount | int | Accumulator for total additions in vector, used for live feedback during runtime | cannot be negative number | 
| 4 | MAX_REDRAW | const int | Constant used for limiting assignment when certain conditions are met; avoids using magic numbers | unchanging value, set in header file | 
| 5 | 
| 6 | 
