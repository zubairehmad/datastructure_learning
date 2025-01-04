#include <iostream>
#include "../Circular Linked List/List.hpp"

using namespace std;

int main() {

  List players;
  int numOfPlayers;
  int eliminatingPlayer;

  cout << "\nEnter total number of players : ";
  cin >> numOfPlayers;

  cout << "\nEvery which player will be eliminated : ";
  cin >> eliminatingPlayer;

  if (numOfPlayers < 1 || eliminatingPlayer < 1) {
    cout << "\nInvalid number of players, or eliminating player given! Please try again.\n";
    return 0;
  }

  // Add required amount of players
  for (int i = 0; i < numOfPlayers; i++) {
    players.add(i+1);
  }

  // Move to start
  players.start();

  while (players.length() != 1) {
    // i = 1, because current player is also counted
    for (int i = 1; i < eliminatingPlayer; i++) {
      players.next();
    }
    players.remove();
  }

  cout << "\nSurvivor : " << players.get() << endl;
  return 0;
}