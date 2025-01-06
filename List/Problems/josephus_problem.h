#include <stdexcept>
#include "../Circular Linked List/List.hpp"

class InvalidInput : public std::invalid_argument {
  public:
    InvalidInput(const char* message = "") : std::invalid_argument(message) {}
};

inline int getSurvivorForJosephusProblem(int numOfPlayers, int eliminatingPlayerPosition) {

  if (numOfPlayers < 1 || eliminatingPlayerPosition < 1) {
    throw InvalidInput("Invalid input given! Number of players, or eliminating player can never be less than 1!");
  }

  List players;
  
  for (int i = 1 ; i <= numOfPlayers; i++) {
    players.add(i);
  }

  // Move to start
  players.start();

  while (players.length() != 1) {
    // i = 1, because current player is also counted
    for (int i = 1; i < eliminatingPlayerPosition; i++) {
      players.next();
    }
    players.remove();
  }

  // Return the last player
  return players.get();
}