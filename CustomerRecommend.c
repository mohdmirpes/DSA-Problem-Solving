#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_USERS 100
#define MAX_PRODUCTS 100

// History structure
typedef struct history {
    int id;
    struct history *next;
} hist;

// User structure
typedef struct {
    int userID;
    char name[100];
    hist *browsehist;
    hist *purhist;
} User;

// Product structure
typedef struct {
    int productID;
    char productName[100];
    float price;
} Product;

// Add a new user
void addUser(User users[], int *userCount, char *name) {
    if (*userCount < MAX_USERS) {
        users[*userCount].userID = (*userCount + 1);
        strcpy(users[*userCount].name, name);
        users[*userCount].purhist = NULL;
        users[*userCount].browsehist = NULL;
        (*userCount)++;
    } else {
        printf("User limit reached!\n");
    }
}

// Add a new product
void addProduct(Product products[], int *productCount, char *productName, float price) {
    if (*productCount < MAX_PRODUCTS) {
        products[*productCount].productID = (*productCount + 1);
        strcpy(products[*productCount].productName, productName);
        products[*productCount].price = price;
        (*productCount)++;
    } else {
        printf("Product limit reached!\n");
    }
}

// Track browsing history
void trackBrowsingHistory(User *user, int productID) {
    hist *nn = (hist *)malloc(sizeof(hist));
    nn->id = productID;
    nn->next = NULL;

    if (user->browsehist == NULL) {
        user->browsehist = nn;
    } else {
        hist *temp = user->browsehist;
        while (temp->next != NULL) {
            temp = temp->next;
        }
        temp->next = nn;
    }
}

// Track purchase history
void trackPurchaseHistory(User *user, int productID) {
    hist *nn = (hist *)malloc(sizeof(hist));
    nn->id = productID;
    nn->next = NULL;

    if (user->purhist == NULL) {
        user->purhist = nn;
    } else {
        hist *temp = user->purhist;
        while (temp->next != NULL) {
            temp = temp->next;
        }
        temp->next = nn;
    }
}

// Find max index in array and reset that value to 0
int max(int arr[]) {
    int pos = -1;
    int maximum = -1;
    for (int i = 0; i < MAX_PRODUCTS; i++) {
        if (arr[i] > maximum) {
            pos = i;
            maximum = arr[i];
        }
    }
    if (pos != -1)
        arr[pos] = 0;
    return pos;
}

// Check if all elements are zero
int isEmpty(int arr[]) {
    for (int i = 0; i < MAX_PRODUCTS; i++) {
        if (arr[i] != 0) {
            return 0;
        }
    }
    return 1;
}

// Generate recommendations
void generateRecommendations(User *user, Product products[], int productCount) {
    printf("Recommendations for %s:\n", user->name);
    int rec[MAX_PRODUCTS] = {0};

    hist *temp = user->browsehist;
    while (temp != NULL) {
        int pid = temp->id;
        for (int j = 0; j < productCount; j++) {
            if (products[j].productID == pid) {
                rec[j]++;
                break;
            }
        }
        temp = temp->next;
    }

    temp = user->purhist;
    while (temp != NULL) {
        int pid = temp->id;
        for (int j = 0; j < productCount; j++) {
            if (products[j].productID == pid) {
                rec[j]++;
                break;
            }
        }
        temp = temp->next;
    }

    int count = 0;
    while (count < 3 && !isEmpty(rec)) {
        int index = max(rec);
        if (index != -1 && index < productCount) {
            printf("%d, %s\n", products[index].productID, products[index].productName);
            count++;
        }
    }
}

// Display user data
void displayUserData(User *user) {
    printf("User ID: %d\n", user->userID);
    printf("Name: %s\n", user->name);

    printf("Purchase History: ");
    hist *temp = user->purhist;
    if (temp == NULL)
        printf("No purchases yet.");
    else {
        while (temp != NULL) {
            printf("%d ", temp->id);
            temp = temp->next;
        }
    }
    printf("\n");

    printf("Browse History: ");
    temp = user->browsehist;
    if (temp == NULL)
        printf("No browsing history yet.");
    else {
        while (temp != NULL) {
            printf("%d ", temp->id);
            temp = temp->next;
        }
    }
    printf("\n");
}

// Main function
int main() {
    User users[MAX_USERS];
    Product products[MAX_PRODUCTS];
    int userCount = 0, productCount = 0;
    int m;
    char name[100];
    int userID;
    int productID;
    float price;

    while (1) {
        printf("\nMenu:\n");
        printf("1. Add user\n2. Add product\n3. Browse product\n4. Purchase product\n5. Display user details\n6. Generate recommendations\n7. Exit\n");
        printf("Enter choice: ");
        scanf("%d", &m);

        switch (m) {
            case 1:
                printf("Enter username: ");
                scanf("%s", name);
                addUser(users, &userCount, name);
                break;

            case 2:
                printf("Enter product name: ");
                scanf("%s", name);
                printf("Enter price: ");
                scanf("%f", &price);
                addProduct(products, &productCount, name, price);
                break;

            case 3:
                printf("Enter userID: ");
                scanf("%d", &userID);
                printf("Enter productID: ");
                scanf("%d", &productID);
                if (userID > 0 && userID <= userCount)
                    trackBrowsingHistory(&users[userID - 1], productID);
                else
                    printf("Invalid userID!\n");
                break;

            case 4:
                printf("Enter userID: ");
                scanf("%d", &userID);
                printf("Enter productID: ");
                scanf("%d", &productID);
                if (userID > 0 && userID <= userCount)
                    trackPurchaseHistory(&users[userID - 1], productID);
                else
                    printf("Invalid userID!\n");
                break;

            case 5:
                printf("Enter userID: ");
                scanf("%d", &userID);
                if (userID > 0 && userID <= userCount)
                    displayUserData(&users[userID - 1]);
                else
                    printf("Invalid userID!\n");
                break;

            case 6:
                printf("Enter userID: ");
                scanf("%d", &userID);
                if (userID > 0 && userID <= userCount)
                    generateRecommendations(&users[userID - 1], products, productCount);
                else
                    printf("Invalid userID!\n");
                break;

            case 7:
                exit(0);
                break;

            default:
                printf("Invalid input!\n");
                break;
        }
    }

    return 0;
}
