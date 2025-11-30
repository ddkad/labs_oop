#include "../include/dungeon.h"

#include <iostream>
#include <limits>
#include <string>

void printMenu() {
  std::cout << "\n1. Add an NPC" << std::endl;
  std::cout << "2. Show all NPCs" << std::endl;
  std::cout << "3. Save to file" << std::endl;
  std::cout << "4. Download from file" << std::endl;
  std::cout << "5. Start the fight" << std::endl;
  std::cout << "6. Output" << std::endl;
  std::cout << "Select an action: ";
}

void addNPCInteractive(DungeonEditor &editor) {
  std::string type, name;
  int x, y;

  std::cout << "Available NPC types: Dragon, Bull, Frog" << std::endl;
  std::cout << "Enter the type: ";
  std::cin >> type;

  std::cout << "Enter the name: ";
  std::cin >> name;

  std::cout << "Enter the X coordinate (0-500): ";
  std::cin >> x;

  std::cout << "Enter the Y coordinate (0-500): ";
  std::cin >> y;

  editor.addNPC(type, name, x, y);
}

int main() {
  DungeonEditor editor;
  int choice;

  std::cout << "Welcome in Balagur Fate 3!" << std::endl;

  do {
    printMenu();
    std::cin >> choice;

    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    switch (choice) {
    case 1:
      addNPCInteractive(editor);
      break;

    case 2:
      editor.printNPCs();
      break;

    case 3:
      editor.saveToFile("save.txt");
      break;

    case 4:
      editor.loadFromFile("save.txt");
      break;

    case 5: {
      double range;
      std::cout << "Enter the combat range in meters: ";
      std::cin >> range;
      editor.startCombat(range);
    } break;

    case 6:
      std::cout << "See you soon" << std::endl;
      break;

    default:
      std::cout << "Wrong choice" << std::endl;
      break;
    }

  } while (choice != 6);

  return 0;
}