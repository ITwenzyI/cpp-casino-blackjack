# Blackjack Console Game (C++)

Konsolenbasiertes Blackjack-Projekt in C++ mit klar getrennten Schichten für Domain, Game-Logik und UI.

## Features

- 1 Spieler gegen Dealer im Terminal
- Kartenwerte 2-10, Bildkarten als 10, Ass als 1 oder 11
- Dealer zieht bis mindestens 17
- ASCII-Kartenanzeige inkl. verdeckter Karten
- BigText-Titel für Menues

## Architektur

Das Projekt ist in vier Verantwortungsbereiche aufgeteilt:

- `domain`: Kartenmodell, Deck, Hand (keine `cin/cout`)
- `game`: Spielregeln und Rundenablauf (keine direkte Konsoleingabe)
- `ui`: Konsolen-Ein-/Ausgabe (`ConsoleInput`, `ConsoleRenderer`)
- `util`: Hilfsfunktionen wie BigText

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
    ConsoleRenderer.hpp
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
    ConsoleRenderer.cpp
  util/
    BigText.cpp
```

## Hinweise

- Fokus liegt auf Refactoring und sauberer Trennung von Verantwortlichkeiten.
- Keine Echtgeld-/Gambling-Funktionalität.

## Author

Kilian
