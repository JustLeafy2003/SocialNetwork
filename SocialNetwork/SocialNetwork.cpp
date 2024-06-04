#include "SocialNetwork.h"
#include <queue>
#include <stack>
#include <vector>

/**
 * @brief Default constructor for SocialNetwork class.
 * Initializes adjacency_list to nullptr and num_of_users to 0.
 */
SocialNetwork::SocialNetwork() : adjacency_list(nullptr), num_of_users(0) {}


/**
 * @brief Destructor for SocialNetwork class.
 * Calls the clearNetwork function to delete all users and connections.
 */
SocialNetwork::~SocialNetwork() {
    clearNetwork();
}


/**
 * @brief Adds a user to the social network.
 * @param user_id The ID of the user to be added.
 */
void SocialNetwork::addUser(int user_id) {
    // check if user already exists
    if (findUser(user_id)) {
        std::cout << "User with ID " << user_id << " already exists." << std::endl;
        return;
    }

    //Create new user node
    UserNodePtr newUser = new UserNode(user_id);

    //Check if list is empty
    if (adjacency_list == nullptr) {
        adjacency_list = newUser;

    }
    else {
        //Here, list is not empty, so traverse the list
        UserNodePtr currentNode = adjacency_list;
        while (currentNode->next != nullptr) {
            currentNode = currentNode->next;
        }
        //Append new user to the end of the list
        currentNode->next = newUser;
    }
    //Increment number of users
    num_of_users++;
    std::cout << "User " << user_id << " added successfully." << std::endl;
}


/**
 * @brief Removes a user from the social network.
 * @param user_id The ID of the user to be removed.
 */
void SocialNetwork::removeUser(int user_id) {
    // check if the network is empty
    if (isEmpty()) {
        std::cout << "Network is empty." << std::endl;
        return;
    }
    // check if a user exists
    UserNodePtr userToRemove = findUser(user_id);
    if (userToRemove == nullptr) {
        std::cout << "User with ID " << user_id << " not found." << std::endl;
        return;
    }

    if (userToRemove == adjacency_list) {
        adjacency_list = userToRemove->next;
    }
    else {
        // Find the previous node of the user to remove
        UserNodePtr prevNode = adjacency_list;
        while (prevNode != nullptr && prevNode->next != userToRemove) {
            prevNode = prevNode->next;
        }

        // check if previous node is found
        if (prevNode != nullptr) {
            // Bypass the user to remove
            prevNode->next = userToRemove->next;
        }
        else {
            std::cout << "User with ID " << user_id << " not found." << std::endl;
            return;
        }
    }
    // Remove connections of the user from other users
    UserNodePtr currentNode = adjacency_list;
    while (currentNode != nullptr) {
        UserNodePtr prevConnection = nullptr;
        UserNodePtr currentConnection = currentNode->connections;

        while (currentConnection != nullptr) {
            // Check if connection points to the user to remove
            if (currentConnection->user_id == user_id) {
                // If it's the first connection, update the head
                if (prevConnection == nullptr) {
                    currentNode->connections = currentConnection->next;
                }
                else {
                    // Otherwise, bypass the connection to remove
                    prevConnection->next = currentConnection->next;
                }
                // Delete the connection node
                delete currentConnection;
                // Update the current connection to point to the next connection
                if (prevConnection != nullptr) {
                    currentConnection = prevConnection->next;
                }
                else {
                    // If prevConnection is null, it means the first connection was removed,
                    // so we need to update currentConnection to the new head.
                    currentConnection = currentNode->connections;
                }
            }
            else {
                // Move to the next connection
                prevConnection = currentConnection;
                currentConnection = currentConnection->next;
            }
        }
        // Move to the next user in the adjacency list
        currentNode = currentNode->next;
    }
    delete userToRemove;
    num_of_users--;
    std::cout << "User " << user_id << " removed successfully." << std::endl;
}


/**
 * @brief Adds a connection between two users in the social network.
 * @param user_id1 The ID of the first user.
 * @param user_id2 The ID of the second user.
 */
void SocialNetwork::addConnection(int user_id1, int user_id2) {
    if (user_id1 == user_id2) {
        std::cout << "A user cannot connect to itself." << std::endl;
        return;
    }
    // check for an existing connection
    if (isConnected(user_id1, user_id2)) {
        std::cout << "Connection between User " << user_id1 << " and User " << user_id2 << " already exists." << std::endl;
        return;
    }

    // find user nodes
    UserNodePtr user1 = findUser(user_id1);
    UserNodePtr user2 = findUser(user_id2);

    // check if user nodes exist
    if (user1 == nullptr || user2 == nullptr) {
        if (user1 == nullptr) {
            std::cout << "User with ID " << user_id1 << " not found." << std::endl;
        }
        if (user2 == nullptr) {
            std::cout << "User with ID " << user_id2 << " not found." << std::endl;
        }
        return;
    }

    // create new connection nodes
    UserNodePtr newUser1Connection = new UserNode(user_id2);
    UserNodePtr newUser2Connection = new UserNode(user_id1);

    // Add Connection to user1
    newUser1Connection->next = user1->connections;
    user1->connections = newUser1Connection;

    // Add Connection to user2
    newUser2Connection->next = user2->connections;
    user2->connections = newUser2Connection;

    std::cout << "Connection added between " << user_id1 << " and " << user_id2 << "." << std::endl;

}

/**
 * @brief Removes a connection between two users in the social network.
 * @param user_id1 The ID of the first user.
 * @param user_id2 The ID of the second user.
 */
void SocialNetwork::removeConnection(int user_id1, int user_id2) {
    // check if the network is empty
    if (isEmpty()) {
        std::cout << "Network is empty." << std::endl;
        return;
    }
    // check if a user exists
    UserNodePtr user1 = findUser(user_id1);
    UserNodePtr user2 = findUser(user_id2);

    if (user1 == nullptr || user2 == nullptr) {
        if (user1 == nullptr) {
            std::cout << "User with ID " << user_id1 << " not found." << std::endl;
        }
        if (user2 == nullptr) {
            std::cout << "User with ID " << user_id2 << " not found." << std::endl;
        }
        return;
    }

    // check if user is trying to disconnect themselves
    if (user_id1 == user_id2) {
        std::cout << "A user cannot disconnect to itself." << std::endl;
        return;
    }

    // check for an existing connection
    if (!(isConnected(user_id1, user_id2))) {
        std::cout << "Connection between User " << user_id1 << " and User " << user_id2 << " does not exist." << std::endl;
        return;
    }

    // Remove connection from user1
    // Track previous connection in user1's list
    UserNodePtr prevConnection1 = nullptr;
    UserNodePtr currentConnection1 = user1->connections;

    while (currentConnection1 != nullptr) {
        if (currentConnection1->user_id == user_id2) {
            // If it's the first connection, update the head
            if (prevConnection1 == nullptr) {
                user1->connections = currentConnection1->next;
            }
            else {
                // Otherwise, bypass the connection to remove
                prevConnection1->next = currentConnection1->next;
            }
            // Delete the connection node
            delete currentConnection1;
            break;
        }
        else {
            // Move to the next connection
            prevConnection1 = currentConnection1;
            currentConnection1 = currentConnection1->next;
        }
    }
    // Remove connection from user2's connections list
    UserNodePtr prevConnection2 = nullptr;
    UserNodePtr currentConnection2 = user2->connections;

    while (currentConnection2 != nullptr) {
        if (currentConnection2->user_id == user_id1) {
            // If it's the first connection, update the head
            if (prevConnection2 == nullptr) {
                user2->connections = currentConnection2->next;
            }
            else {
                // Otherwise, bypass the connection to remove
                prevConnection2->next = currentConnection2->next;
            }
            // Delete the connection node
            delete currentConnection2;
            break;
        }
        else {
            // Move to the next connection
            prevConnection2 = currentConnection2;
            currentConnection2 = currentConnection2->next;
        }

    }
    std::cout << "Connection removed between " << user_id1 << " and " << user_id2 << "." << std::endl;

}

/**
 * @brief Find the shortest path between two users in the social network.
 * @param user_id1 The ID of the first user.
 * @param user_id2 The ID of the second user.
 * @return The length of the shortest path between the two users, or -1 if no path exists.
 */
int SocialNetwork::findShortestPath(int user_id1, int user_id2) {
    int max_user_id_encountered = std::max(user_id1, user_id2);  // Update the maximum user ID encountered

    std::vector<int> distance(max_user_id_encountered + 1, INT_MAX);
    std::vector<int> parent(max_user_id_encountered + 1, -1);
    std::queue<UserNodePtr> q;

    UserNodePtr startNode = findUser(user_id1);
    if (startNode == nullptr) {
        std::cout << "User with ID " << user_id1 << " does not exist." << std::endl;
        return -1;
    }

    q.push(startNode);
    distance[startNode->user_id] = 0;

    while (!q.empty()) {
        UserNodePtr currentUser = q.front();
        q.pop();

        if (currentUser->user_id == user_id2) {
            break;
        }

        UserNodePtr neighbor = currentUser->connections;

        while (neighbor != nullptr) {
            int neighborId = neighbor->user_id;

            if (distance[neighborId] == INT_MAX) {
                distance[neighborId] = distance[currentUser->user_id] + 1;
                parent[neighborId] = currentUser->user_id;
                q.push(findUser(neighborId));
            }

            neighbor = neighbor->next;
        }
    }

    if (parent[user_id2] == -1) {
        std::cout << "There is no path from user " << user_id1 << " to user " << user_id2 << "." << std::endl;
        return -1;
    }

    // Retrieve the shortest path
    std::vector<int> shortestPath;
    int currentNode = user_id2;
    while (currentNode != -1) {
        shortestPath.push_back(currentNode);
        currentNode = parent[currentNode];
    }

    // Reverse the path to obtain the correct order
    reverse(shortestPath.begin(), shortestPath.end());

    std::cout << "Shortest path from user " << user_id1 << " to user " << user_id2 << ": ";
    for (int node : shortestPath) {
        std::cout << node << " ";
    }
    std::cout << std::endl;

    return distance[user_id2];
}


/**
 * @brief Perform a breadth-first search (BFS) starting from a given user in the social network.
 * @param user_id The ID of the user to start the search from.
 */
void SocialNetwork::BFS(int user_id) {
    UserNodePtr startNode = findUser(user_id);
    if (startNode == nullptr) {
        std::cout << "User with ID " << user_id << " does not exist." << std::endl;
        return;
    }

    std::vector<bool> visited(numberOfUsers() + 1, false); // Initialize all users as not visited
    std::queue<UserNodePtr> bfsQueue;
    bfsQueue.push(startNode);
    visited[user_id] = true; // Mark the first user as visited
    std::cout << "BFS starting from vertex " << user_id << ": ";

    while (!bfsQueue.empty()) {
        UserNodePtr currentNode = bfsQueue.front();
        std::cout << currentNode->user_id;
        bfsQueue.pop();

        // Collect neighbors' IDs in a vector
        std::vector<int> neighbor_ids;
        UserNodePtr neighbor = currentNode->connections;
        while (neighbor != nullptr) {
            neighbor_ids.push_back(neighbor->user_id);
            neighbor = neighbor->next;
        }

        // Sort the neighbor IDs
        std::sort(neighbor_ids.begin(), neighbor_ids.end());

        // Enqueue neighbors in sorted order
        for (int id : neighbor_ids) {
            if (!visited[id]) {
                bfsQueue.push(findUser(id));
                visited[id] = true; // Mark the neighbor as visited
            }
        }

        if (!bfsQueue.empty()) {
            std::cout << ", ";
        }
    }

    std::cout << std::endl;
}

/**
 * @brief Perform a depth-first search (DFS) starting from a given user in the social network.
 * @param user_id The ID of the user to start the search from.
 */
void SocialNetwork::DFS(int userId) {
    std::vector<bool> visited(num_of_users + 1, false);
    std::stack<UserNodePtr> dfsStack;

    UserNodePtr startNode = findUser(userId);
    if (startNode == nullptr) {
        std::cout << "User with ID " << userId << " does not exist." << std::endl;
        return;
    }

    std::cout << "DFS starting from vertex " << userId << ": ";

    dfsStack.push(startNode);
    visited[startNode->user_id] = true;

    bool firstNode = true; // Flag to handle the first node

    while (!dfsStack.empty()) {
        UserNodePtr currentNode = dfsStack.top();
        dfsStack.pop();

        if (!firstNode) {
            std::cout << ", ";
        }
        else {
            firstNode = false;
        }

        std::cout << currentNode->user_id;

        UserNodePtr neighbor = currentNode->connections;
        while (neighbor != nullptr) {
            if (!visited[neighbor->user_id]) {
                dfsStack.push(findUser(neighbor->user_id));
                visited[neighbor->user_id] = true;
            }
            neighbor = neighbor->next;
        }
    }

    std::cout << std::endl;
}


/**
 * @brief Find a user in the network.
 * @param user_id The ID of the user to find.
 * @return A pointer to the user if found, nullptr otherwise.
 */
SocialNetwork::UserNodePtr SocialNetwork::findUser(int userId) const {
    auto findUser = [this](int userId) -> UserNodePtr {
        UserNodePtr current = adjacency_list;
        while (current != nullptr) {
            if (current->user_id == userId) {
                // Return the user node pointer if found
                return current;
            }
            current = current->next;
        }
        // Return nullptr if user not found
        return nullptr;
    };

    // Call the lambda function and return its result
    return findUser(userId);
}

/**
 * @brief Prints the network.
 */
void SocialNetwork::printNetwork() const {
    // Check if the network is empty
    if (isEmpty()) {
        std::cout << "Network is empty." << std::endl;
        return;
    }

    UserNodePtr currentNode = adjacency_list;
    while (currentNode != nullptr) {
        std::cout << "\n--------------------------" << std::endl;
        std::cout << "User ID: " << currentNode->user_id << std::endl;

        // Count the number of connections
        int numConnections = 0;
        UserNodePtr currentConnection = currentNode->connections;
        while (currentConnection != nullptr) {
            numConnections++;
            currentConnection = currentConnection->next;
        }

        std::cout << "Number of connections: " << numConnections << std::endl;

        std::cout << "Connected to: ";
        currentConnection = currentNode->connections;
        if (currentConnection == nullptr) {
            std::cout << "None";
        }
        else {
            while (currentConnection != nullptr) {
                std::cout << currentConnection->user_id;
                if (currentConnection->next != nullptr) {
                    std::cout << ", ";
                }
                currentConnection = currentConnection->next;
            }

        }

        std::cout << std::endl;
        // Move to the next user
        currentNode = currentNode->next;
    }
}
/**
 * @brief Check if the network is empty.
 * @return True if the network is empty, false otherwise.
 */
bool SocialNetwork::isEmpty() const {
    return adjacency_list == nullptr;
}


/**
 * @brief Get the number of users in the network.
 * @return The number of users in the network.
 */
int SocialNetwork::numberOfUsers() const {
    return num_of_users;
}


/**
 * @brief Get the number of connections in the network.
 * @return The number of connections in the network.
 */
int SocialNetwork::numberOfConnections() const {
    int totalConnections = 0;
    UserNodePtr currentNode = adjacency_list;

    while (currentNode != nullptr) {
        UserNodePtr currentConnection = currentNode->connections;
        while (currentConnection != nullptr) {
            // count each connection
            totalConnections++;
            currentConnection = currentConnection->next;
        }
        // Move to the next user
        currentNode = currentNode->next;
    }
    // Each connection is counted twice (in an undirected graph), so divide by 2
    return (totalConnections / 2);
}


/**
 * @brief Check if two users are connected.
 * @param user_id1 The ID of the first user.
 * @param user_id2 The ID of the second user.
 * @return True if the two users are connected, false otherwise.
 */
bool SocialNetwork::isConnected(int user_id1, int user_id2) const {
    // Check if the network is empty
    if (isEmpty()) {
        std::cout << "Network is empty." << std::endl;
        return false;
    }
    // A user is always connected to itself
    if (user_id1 == user_id2) {
        return true;
    }

    // Find the user nodes
    UserNodePtr user1 = findUser(user_id1);
    UserNodePtr user2 = findUser(user_id2);

    // find if at least one user is not in the network
    if (user1 == nullptr || user2 == nullptr) {
        std::cout << "One of the users does not exist." << std::endl;
        return false;
    }

    //if user nodes exist, traverse connections of user1 to find user2
    UserNodePtr currentUser = user1->connections;
    while (currentUser != nullptr) {
        if (currentUser->user_id == user_id2) {
            // connection found
            return true;
        }
        currentUser = currentUser->next;
    }
    // connection not found
    return false;
}


/**
 * @brief clear the network of all users and connections.
 */
void SocialNetwork::clearNetwork() {
    // Check if network is empty
    if (isEmpty()) {
        return;
    }
    // Iterate through the adjacency list and delete each user node
    UserNodePtr currentNode = adjacency_list;

    while (currentNode != nullptr) {
        // Store Next Node before deleting the current node
        UserNodePtr nextNode = currentNode->next;

        // Delete connection of the current user
        UserNodePtr currentConnection = currentNode->connections;
        while (currentConnection != nullptr) {
            // Store Next Connection before deleting the current connection
            UserNodePtr nextConnection = currentConnection->next;
            delete currentConnection;
            currentConnection = nextConnection;
        }
        // Delete the current user node
        delete currentNode;
        // Move to the next user node
        currentNode = nextNode;
    }
    // Reset the adjacency list and number of users
    adjacency_list = nullptr;
    num_of_users = 0;
    std::cout << "Network cleared." << std::endl;
};