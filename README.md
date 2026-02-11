# Word Finder Game
## Description

Word Finder Game is a C++ console application that challenges players to form valid English words from a randomly generated set of letters within a limited time and number of attempts.

The game validates each word against a dictionary, calculates scores based on word length, and maintains a persistent high score list.

## Features

- Random generation of a 9-letter set
  
- Word validation against a dictionary file
 
- Prevention of duplicate word entries

- Letter frequency validation (no overuse of letters)

- Score calculation based on word length

- Time-limited gameplay (60 seconds)

- Attempt limit (25 attempts)

- Persistent high score system (top 5)

- Timestamped high score entries

- Clean console UI with screen refresh

## Requirements

- Windows OS

- Visual Studio 2022 or newer

- C++20 compatible compiler

## How to Run

Open the solution in Visual Studio

- Ensure C++20 is enabled

- Build the solution

- Run the WordFinderGame project
  
## How to Play

- Form words using only the displayed letters

- Words must:

  - Be at least 3 letters long

  - Exist in the dictionary

  - Not be previously used

  - Respect available letter counts

- Type /quit to exit the game

- Press Enter on an empty line to refresh the remaining time

- The game ends when:

  - The time limit expires, or

  - The maximum number of attempts is reached
    
## Technologies Used

- C++

- Microsoft Native Unit Testing Framework

- Visual Studio 2022

## Architecture Overview

The application follows a clean separation of concerns:

- GameController – Orchestrates game flow

- GameState – Manages state, attempts, and timing

- WordValidator – Handles word validation logic

- ScoreCalculator – Computes scoring rules

- Dictionary – Loads and stores valid words

- HighScoreManager – Manages persistence and ranking

- ConsoleUI – Handles console input and output

- GameConfig – Centralized configuration values

Core logic components are unit tested.
