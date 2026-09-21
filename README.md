# 🧩 Sudoku Game Records Manager

A command-driven C program that manages Sudoku puzzle records, registered players, and individual game results, loaded from plain-text data files. Built as a university systems programming assignment focused on manual memory management, file parsing, and dual data representations (dynamic arrays and linked lists) of the same dataset.

## What It Does

The program reads three semicolon-delimited text files and lets you query, edit, and export data through a small command interpreter read from stdin:

- **`Sudoku.txt`** — puzzle ID + solution grid pairs
- **`RegisterHracov.txt`** — registered players (ID, name, country, birth year)
- **`RegisterRieseni.txt`** — individual solve records (which player solved which puzzle, when, and how long it took)

Two parallel representations of the same data are maintained on purpose:
- **Dynamic arrays** (built with `realloc`), used for direct file-backed lookups and edits
- **Singly linked lists** (`HRACI_DATA`, `RIESENI_DATA`), built from the arrays, used for structured traversal, sorting, and record management

## Commands

| Input | Function | What it does |
|---|---|---|
| `v 1` | `print_players_with_sample_solutions` | Lists every player with up to 10 sample solve records, read directly from the raw files |
| `v 2` | `print_players_with_solutions_arrays` | Lists every player with their solve records, using the loaded arrays |
| `v 3` | `print_linked_players` | Prints all players and their solve records from the linked-list representation |
| `h <SID>` | `export_solutions_by_sid` | Finds all solve records for a given puzzle ID and writes them to `Vystup_H.txt` |
| `n` | `load_arrays_from_files` | (Re)loads all three files into dynamic arrays, freeing any previously loaded data |
| `q <pos>` | `insert_solution_record` | Inserts a new solve record at a given position in the array, with input format validation |
| `w <PID>` | `delete_solution_records_by_pid` | Deletes all solve records for a given player ID from the array |
| `e <SID> <n>` | `generate_puzzle_with_gaps` | Generates a puzzle with `n` random cells removed per row and writes it to `Vystup_E.txt` |
| `m` | `build_linked_lists_from_arrays` | Builds the `HRACI_DATA` / `RIESENI_DATA` linked lists from the loaded file data |
| `a <pos> <name> <country> <year>` | `add_player_to_list` | Adds a new player to the linked list at a given position, with duplicate checking |
| `s <GID>` | `delete_solution_by_gid` | Removes a solve record (by game ID) from both the linked list and each player's record array |
| `d` | `sort_players_solutions_by_duration` | Sorts each player's solve records by duration (bubble sort) |
| `k` | `cleanup_and_exit` | Frees all allocated memory, closes open files, and exits |

## Build & Run

```bash
gcc -Wall -o sudoku_manager sudoku_manager.c
./sudoku_manager
```

Run it from a directory containing `Sudoku.txt`, `RegisterHracov.txt`, and `RegisterRieseni.txt` (sample data files included). Enter commands one at a time, e.g.:

```
v 1
n
v 2
k
```

## Design Notes

- All dynamic memory (arrays and linked-list nodes) is manually managed with `malloc`/`realloc`/`free`; `cleanup_and_exit` frees everything on exit — the program was written and tested with careful attention to avoiding leaks, since nothing here is garbage-collected.
- File parsing uses `strtok` on a fixed delimiter (`#`) to split each record line into fields.
- Insert/delete operations on the array-backed records (`insert_solution_record`, `delete_solution_records_by_pid`) shift elements manually rather than relying on any higher-level container, since the assignment required raw array manipulation.
- Input validation (e.g. `insert_solution_record`'s ID format checks) rejects malformed IDs and reprompts rather than trusting stdin blindly.

## Tech Stack

- **C** (standard library only)
- Custom singly linked list implementations
- Manual dynamic array management via `realloc`

---
*Author: Vladyslav Chytynskyi*
