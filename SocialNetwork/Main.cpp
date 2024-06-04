#include "SocialNetwork.h"
#include <iostream>

int main() {
    // Create a SocialNetwork object
    SocialNetwork network;

    int choice;
    int user_id1, user_id2;
    for (int i = 1; i < 11; i++) {
        network.addUser(i);
    }
    network.addConnection(1, 2);
    network.addConnection(1, 3);
    network.addConnection(1, 4);
    network.addConnection(2, 5);
    network.addConnection(3, 6);
    network.addConnection(4, 7);
    network.addConnection(4, 8);
    network.addConnection(5, 9);
    network.addConnection(6, 10);
    /*
    Here is an example graph you can start with:

    GRAPH (starting node is 1):

         2--5--9
         |
         1--3--6--10
         |
      8--4--7


    CODE:
    
     */

    do {
        // Display menu options
        std::cout << "Social Network Menu" << std::endl;
        std::cout << "1. Add User" << std::endl;
        std::cout << "2. Remove User" << std::endl;
        std::cout << "3. Add Connection" << std::endl;
        std::cout << "4. Remove Connection" << std::endl;
        std::cout << "5. Find Shortest Path" << std::endl;
        std::cout << "6. BFS Traversal" << std::endl;
        std::cout << "7. DFS Traversal" << std::endl;
        std::cout << "8. Print Network" << std::endl;
        std::cout << "9. Check if Network Empty" << std::endl;
        std::cout << "10. Number of Users" << std::endl;
        std::cout << "11. Number of Connections" << std::endl;
        std::cout << "12. Check if Users Connected" << std::endl;
        std::cout << "13. Clear Network" << std::endl;
        std::cout << "14. See Network Details" << std::endl;
        std::cout << "15. Exit" << std::endl;
        std::cout << "Enter your choice: ";
        std::cin >> choice;

        switch (choice) {
        case 1: {
            std::cout << "Enter user ID to add: ";
            std::cin >> user_id1;
            network.addUser(user_id1);
            break;
        }
        case 2: {
            if (!network.isEmpty()) {
                std::cout << "Enter user ID to remove: ";
                std::cin >> user_id1;
                network.removeUser(user_id1);
            }
            else {
                std::cout << "Network is empty." << std::endl;
            }
            break;
        }
        case 3: {
            std::cout << "Enter First's user ID: ";
            std::cin >> user_id1;
            std::cout << "Enter Second's user ID: ";
            std::cin >> user_id2;
            network.addConnection(user_id1, user_id2);
            break;
        }
        case 4: {
            if (!network.isEmpty()) {
                std::cout << "Enter First's user ID: ";
                std::cin >> user_id1;
                std::cout << "Enter Second's user ID: ";
                std::cin >> user_id2;
                network.removeConnection(user_id1, user_id2);
            }
            else {
                std::cout << "Network is empty." << std::endl;
            }
            break;
        }
        case 5: {
            if (!network.isEmpty()) {
                std::cout << "Enter First's user ID: ";
                std::cin >> user_id1;
                std::cout << "Enter Second's user ID: ";
                std::cin >> user_id2;
                int shortestPath = network.findShortestPath(user_id1, user_id2);
                if (shortestPath != -1) {
                    std::cout << "Shortest path length: " << shortestPath << std::endl;
                }
            }
            else {
                std::cout << "Network is empty." << std::endl;
            }
            break;
        }
        case 6: {
            if (!network.isEmpty()) {
                std::cout << "Enter user ID to start BFS traversal: ";
                std::cin >> user_id1;
                network.BFS(user_id1);
            }
            else {
                std::cout << "Network is empty." << std::endl;
            }
            break;
        }
        case 7: {
            if (!network.isEmpty()) {
                std::cout << "Enter user ID to start DFS traversal: ";
                std::cin >> user_id1;
                network.DFS(user_id1);
            }
            else {
                std::cout << "Network is empty." << std::endl;
            }
            break;
        }
        case 8: {
            if (network.isEmpty()) {
                std::cout << "Network is empty." << std::endl;
            }
            else {
                network.printNetwork();
            }
            break;
        }
        case 9: {
            if (network.isEmpty()) {
                std::cout << "Network is empty." << std::endl;
            }
            else {
                std::cout << "Network is not empty." << std::endl;
            }
            break;
        }
        case 10: {
            if (!network.isEmpty()) {
                std::cout << "Number of users: " << network.numberOfUsers() << std::endl;
            }
            else {
                std::cout << "Network is empty." << std::endl;
            }
            break;
        }
        case 11: {
            if (!network.isEmpty()) {
                std::cout << "Number of connections: " << network.numberOfConnections() << std::endl;
            }
            else {
                std::cout << "Network is empty." << std::endl;
            }
            break;
        }
        case 12: {
            if (!network.isEmpty()) {
                std::cout << "Enter First's user ID: ";
                std::cin >> user_id1;
                std::cout << "Enter Second's user ID: ";
                std::cin >> user_id2;

                if (network.isConnected(user_id1, user_id2)) {
                    std::cout << "Users " << user_id1 << " and " << user_id2 << " are connected." << std::endl;
                }
                else {
                    std::cout << "Users " << user_id1 << " and " << user_id2 << " are not connected." << std::endl;
                }
            }
            else {
                std::cout << "Network is empty." << std::endl;
            }

            break;
        }
        case 13: {
            if (!network.isEmpty()) {
                std::cout << "Are you sure you want to clear the network? (y/n): ";
                char confirm;
                std::cin >> confirm;
                if (confirm == 'y' || confirm == 'Y') {
                    network.clearNetwork();
                }
                else {
                    std::cout << "Network was not cleared." << std::endl;
                }

            }
            else {
                std::cout << "Network is already empty." << std::endl;
            }
            break;
        }
        case 14: {
            if (!network.isEmpty()) {
                std::cout << "Number of users: " << network.numberOfUsers() << std::endl;
                std::cout << "Number of connections: " << network.numberOfConnections() << std::endl;
            }
            else {
                std::cout << "Network is empty." << std::endl;
            }
            break;
        }
        case 15: {
            std::cout << "Exiting..." << std::endl;
            break;
        }
        default: {
            std::cout << "Invalid choice. Please try again." << std::endl;
            break;
        }
        }
        std::cout << "--------------------------\n" << std::endl;
    } while (choice != 15);

    return 0;
}