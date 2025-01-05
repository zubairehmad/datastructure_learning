#include <stdexcept>
#include "../Circular Linked List/List.hpp"

class InvalidInput : public std::invalid_argument {
  public:
    InvalidInput(const char* message = "") : std::invalid_argument(message) {}
};

inline int getSurvivorForJosephusProblem(int numOfPlayers, int eliminatingPlayer) {

  if (numOfPlayers < 1 || eliminatingPlayer < 1) {
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
    for (int i = 1; i < eliminatingPlayer; i++) {
      players.next();
    }
    List newList = players;
    newList.end();
    bool condition = players.get() == newList.get();

    players.remove();
  }

  // Return the last player
  return players.get();
}