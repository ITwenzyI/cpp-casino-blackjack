# Blackjack Console Game (C++)

A console-based Blackjack implementation in modern C++, designed with a clear separation of concerns between domain logic, game rules, and user interface.

This project focuses on clean architecture, modular design, and maintainable code structure rather than feature complexity.

## Features

- Single-player mode against a dealer (terminal-based)
  Standard Blackjack rules:
- Card values 2-10
- Face cards count as 10
- Ace counts as 1 or 11 (dynamic evaluation)
- Dealer draws until reaching at least 17
- ASCII card rendering including hidden dealer card
- BigText ASCII title rendering for menus
- Cleanly separated layers (no UI logic inside domain)

## Architecture

The project is structured into four clearly defined responsibility layers:

- `domain`: Pure domain model. Contains no console input/output and no knowledge about the UI.
- `game`: Encapsulates Blackjack rules and round flow. Coordinates player and dealer logic without directly interacting with the console.
- `ui`: Responsible for all console interaction. (`ConsoleInput`, `ConsoleOutput`, `ConsoleRenderer`, `GamePacer`)
- `util`: Utility functionality independent of the game rules. (`BigText` - ASCII title generation for menus)

### Struktur

```text
include/
  domain/
    Card.hpp
    Deck.hpp
    Hand.hpp
  game/
    BlackjackGame.hpp
    BlackjackRound.hpp
  ui/
    ConsoleInput.hpp
    ConsoleOutput.hpp
    ConsoleRenderer.hpp
    GamePacer.hpp
  util/
    BigText.hpp

src/
  main.cpp
  domain/
    Card.cpp
    Deck.cpp
    Hand.cpp
  game/
    BlackjackGame.cpp
    BlackjackRound.cpp
  ui/
    ConsoleInput.cpp
    ConsoleOutput.cpp
    ConsoleRenderer.cpp
    GamePacer.cpp
  util/
    BigText.cpp
```

## Design Principles

- Clear separation of responsibilities
- No std::cin / std::cout inside domain logic
- Game logic independent from rendering
- Modular file organization
- Focus on readability and maintainability
- Suitable as a learning and refactoring project

## Future Improvements

Potential extensions include:

- Betting system (without real money)
- Split / Double Down support
- Unit testing for domain and game logic
- Logging system

## Disclaimer

- This project does not involve real gambling or financial transactions.
- It is a software design and learning exercise only.

## Author

`Kilian`

As part of independent study in Medical Informatics. The software was fully developed in C++ using modern programming techniques.
