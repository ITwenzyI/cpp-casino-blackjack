# 🃏 Blackjack Console Game (C++)

This is a console-based implementation of the classic card game **Blackjack** written in C++.  
It features a simplified casino-style rule set, full game loop, card drawing visuals, and realistic Blackjack mechanics like Ace handling and hidden dealer cards.

---

## 🎮 Gameplay Features

- Fully interactive terminal game
- Randomized card drawing with realistic values (2–10, J, Q, K, A)
- **Ace counts as 1 or 11** dynamically depending on hand
- Dealer follows standard rules:
    - Draws until 17 or more
    - Only one card is shown until the end unless Blackjack
- **Blackjack check at the start**:
    - If dealer has 21, game ends immediately
    - Player gets two cards at the same time
- Graphical card representation using terminal symbols (♠ ♥ ♦ ♣)

---

## ⚙️ Technical Details

- Written in modern **C++**
- Uses:
    - `<vector>`, `<string>`, `<random>`, `<chrono>`, `<thread>`, `<limits>`
- Structure:
    - `BlackJack.cpp` → Game logic
    - `KartenPrintAusgabe.h/cpp` → Card display
    - `BigText.h` → ASCII title visuals (Not completed)

---

## 🧠 Game Rules Summary

- Cards 2–10: Count at face value
- J, Q, K: Count as 10
- Ace: Counts as 1 or 11 (whichever is more favorable)
- Goal: Get as close to **21** as possible without going over
- Blackjack: Ace + 10 on first two cards
- If player and dealer both go over 21 → draw
- If both have 21 → draw

---

## 💡 Notes
- The game currently supports only one player vs dealer.
- It's designed for learning purposes, not for gambling.
- Future features could include:
  - Multiple players
  - Money System
  - Split / double down mechanics

---

## 👤 Author
This project was created by **Kilian** as part of independent study in Medical Informatics.
The software was fully developed in C++ using modern programming techniques.
