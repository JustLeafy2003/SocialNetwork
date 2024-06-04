#ifndef SOCIALNETWORK_H
#define SOCIALNETWORK_H

#include <iostream>
#include <vector>


/**
 * @class SocialNetwork
 * @brief A class to represent a social network.
 *
 * This class provides the necessary functions to manage a social network, including user and connection management,
 * graph traversal and pathfinding, utility functions, and network insights.
 */
class SocialNetwork {
public:
    /**
     * @brief Construct a new Social Network object
     */
    SocialNetwork();

    /**
     * @brief Destroy the Social Network object
     */
    ~SocialNetwork();

    /**
     * @brief Add a user to the social network.
     * @param user_id The ID of the user to be added.
     */
    void addUser(int user_id);

    /**
     * @brief Remove a user from the social network.
     * @param user_id The ID of the user to be removed.
     */
    void removeUser(int user_id);

    /**
     * @brief Add a connection between two users.
     * @param user_id1 The ID of the first user.
     * @param user_id2 The ID of the second user.
     */
    void addConnection(int user_id1, int user_id2);

    /**
     * @brief Remove a connection between two users.
     * @param user_id1 The ID of the first user.
     * @param user_id2 The ID of the second user.
     */
    void removeConnection(int user_id1, int user_id2);

    /**
     * @brief Find the shortest path between two users.
     * @param user_id1 The ID of the first user.
     * @param user_id2 The ID of the second user.
     * @return The shortest path between the two users.
     */
    int findShortestPath(int user_id1, int user_id2);

    /**
     * @brief Perform a breadth-first search from a given user.
     * @param user_id The ID of the user to start the search from.
     */
    void BFS(int user_id);

    /**
     * @brief Perform a depth-first search from a given user.
     * @param user_id The ID of the user to start the search from.
     */
    void DFS(int user_id);

    /**
     * @brief Print the current state of the network.
     */
    void printNetwork() const;

    /**
     * @brief Check if the network is empty.
     * @return true if the network is empty, false otherwise.
     */
    bool isEmpty() const;

    /**
     * @brief Get the number of users in the network.
     * @return The number of users in the network.
     */
    int numberOfUsers() const;

    /**
     * @brief Get the number of connections in the network.
     * @return The number of connections in the network.
     */
    int numberOfConnections() const;

    /**
     * @brief Check if two users are connected.
     * @param user_id1 The ID of the first user.
     * @param user_id2 The ID of the second user.
     * @return true if the two users are connected, false otherwise.
     */
    bool isConnected(int user_id1, int user_id2) const;

    /**
     * @brief Clear the network of all users and connections.
     */
    void clearNetwork();

private:
    /**
     * @class UserNode
     * @brief A class to represent a user in the social network.
     *
     * This class holds the user's ID and pointers to the next user in the adjacency list and the user's connections.
     */
    struct UserNode {
    public:
        int user_id;  // The user's ID.
        UserNode* next;  // Pointer to the next user in the adjacency list.
        UserNode* connections;  // Pointer to the user's connections.

        /**
         * @brief Construct a new User Node object.
         * @param id The ID of the user.
         */
        UserNode(int id) : user_id(id), next(nullptr), connections(nullptr) {}
    };

    typedef UserNode* UserNodePtr;  // Typedef for a pointer to a UserNode.
    UserNodePtr adjacency_list;  // Pointer to the adjacency list of the network.
    int num_of_users;  // The number of users in the network.

    /**
     * @brief Find a user in the network.
     * @param user_id The ID of the user to find.
     * @return A pointer to the user if found, nullptr otherwise.
     */

    UserNodePtr findUser(int user_id) const;

};

#endif // SOCIALNETWORK_H