#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_USERS 100  // Maximum number of users

// Structure for a message in a doubly linked list
typedef struct Message {
    char sender[50];
    char content[256];
    struct Message* prev;
    struct Message* next;
} Message;

// Structure for the chat history (Doubly linked list of messages)
typedef struct Chat {
    Message* head;
    Message* tail;
} Chat;

// Structure for a user
typedef struct User {
    char userId[50];
    char username[50];
    Chat chatHistory;
    struct User* next;  // Pointer to next user for collision handling
} User;

// HashMap for storing users (with collision handling via linked lists)
User* userDirectory[MAX_USERS];

// Hash function to calculate the index for user storage
int hashFunction(char* userId) {
    int hash = 0;
    for (int i = 0; i < strlen(userId); i++) {
        hash = (hash + userId[i]) % MAX_USERS;
    }
    return hash;
}

// Function to create a new user
void createUser(char* userId, char* username) {
    int index = hashFunction(userId);
    User* newUser = (User*)malloc(sizeof(User));
    strcpy(newUser->userId, userId);
    strcpy(newUser->username, username);
    newUser->chatHistory.head = NULL;
    newUser->chatHistory.tail = NULL;
    newUser->next = userDirectory[index];  // Link new user to the current list at index
    userDirectory[index] = newUser;  // Set new user as the head of the list
}

// Function to find a user by userId
User* findUser(char* userId) {
    int index = hashFunction(userId);
    User* current = userDirectory[index];
    while (current != NULL) {
        if (strcmp(current->userId, userId) == 0) {
            return current;
        }
        current = current->next;
    }
    return NULL;  // User not found
}

// Function to create a new message
Message* createMessage(char* content, char* senderId) {
    Message* newMessage = (Message*)malloc(sizeof(Message));
    strcpy(newMessage->content, content);
    strcpy(newMessage->sender, senderId);
    newMessage->prev = NULL;
    newMessage->next = NULL;
    return newMessage;
}

// Function to send a message (add to chat history)
void sendMessage(User* user, char* content, char* senderId) {
    Message* newMessage = createMessage(content, senderId);
    if (user->chatHistory.tail == NULL) {
        user->chatHistory.head = newMessage;
        user->chatHistory.tail = newMessage;
    } else {
        user->chatHistory.tail->next = newMessage;
        newMessage->prev = user->chatHistory.tail;
        user->chatHistory.tail = newMessage;
    }
}

// Function to list all messages in a chat
void listMessages(User* user) {
    Message* current = user->chatHistory.head;
    if (current == NULL) {
        printf("No messages in the chat.\n");
        return;
    }
   // printf("Chat History:\n");
    while (current != NULL) {
        printf("%s: %s\n", current->sender, current->content);
        current = current->next;
    }
}

int main() {
    // Initialize user directory
    for (int i = 0; i < MAX_USERS; i++) {
        userDirectory[i] = NULL;
    }

    int choice, numUsers, numMessages;
    char userId[50], username[50], senderId[50], content[256];

    // Create users
    //printf("Enter the number of users: ");
    scanf("%d", &numUsers);
    for (int i = 0; i < numUsers; i++) {
       // printf("Enter the user ID: ");
        scanf("%s", userId);
       // printf("Enter the username: ");
        scanf("%s", username);
        createUser(userId, username);
    }

    // Send messages
    //printf("Enter the number of messages to send: ");
    scanf("%d", &numMessages);
    for (int i = 0; i < numMessages; i++) {
        //printf("Enter the sender ID: ");
        scanf("%s", senderId);
        //printf("Enter the content: ");
        getchar();  // Clear newline left by previous scanf
        fgets(content, sizeof(content), stdin);
        content[strcspn(content, "\n")] = 0;  // Remove newline character

        User* sender = findUser(senderId);
        if (sender == NULL) {
            printf("User not found.\n");
            continue;
        }

        sendMessage(sender, content, senderId);
    }

    // List messages for a user
    //printf("Enter the user ID to display chat history: ");
    scanf("%s", userId);
    User* user = findUser(userId);
    if (user == NULL) {
        printf("User not found.\n");
    } else {
        listMessages(user);
    }

    return 0;
}
