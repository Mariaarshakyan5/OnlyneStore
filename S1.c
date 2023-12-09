#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Product {
    char name[50];
    char category[20];
    float price;
    struct Product* left;
    struct Product* right;
};

// Function to read product data from a file
void readProductData(struct Product products[], int numProducts, const char *filename) {
    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        perror("Error opening file");
        exit(EXIT_FAILURE);
    }

    for (int i = 0; i < numProducts; ++i) {
        fscanf(file, "%s %s %f", products[i].name, products[i].category, &products[i].price);
        products[i].left = NULL;
        products[i].right = NULL;
    }

    fclose(file);
}

// Function to display product information
void displayProductInfo(struct Product products[], int numProducts) {
    printf("Product Information:\n");
    for (int i = 0; i < numProducts; ++i) {
        printf("Name: %s | Category: %s | Price: $%.2f\n", products[i].name, products[i].category, products[i].price);
    }
}

// Function for statistical analysis
void performStatisticalAnalysis(struct Product products[], int numProducts) {
    float totalPrice = 0.0;
    float averagePrice;
    float maxPrice = products[0].price;  
    char mostExpensiveProduct[50];

    for (int i = 0; i < numProducts; ++i) {
        totalPrice += products[i].price;

        if (products[i].price > maxPrice) {
            maxPrice = products[i].price;
            strcpy(mostExpensiveProduct, products[i].name);
        }
    }
    averagePrice = totalPrice / numProducts;
    printf("\nStatistical Analysis:\n");
    printf("Average Price: $%.2f\n", averagePrice);
    printf("Most Expensive Product: %s | Price: $%.2f\n", mostExpensiveProduct, maxPrice);
}

// Function for making predictions
void makePredictions(struct Product products[], int numProducts) {
    printf("\nPredictions:\n");
    for (int i = 0; i < numProducts; ++i) {
        float discounted_price = 0.9 * products[i].price;
        printf("Product: %s | Original Price: $%.2f | Predicted Discounted Price: $%.2f\n",
               products[i].name, products[i].price, discounted_price);
    }
}

// Function to create a new product node
struct Product* createProductNode(struct Product* product) {
    struct Product* newNode = (struct Product*)malloc(sizeof(struct Product));
    if (newNode == NULL) {
        perror("Error creating product node");
        exit(EXIT_FAILURE);
    }

    strcpy(newNode->name, product->name);
    strcpy(newNode->category, product->category);
    newNode->price = product->price;
    newNode->left = NULL;
    newNode->right = NULL;

    return newNode;
}

// Function to insert a product into the BST
struct Product* insertBST(struct Product* root, struct Product* product) {
    if (root == NULL) {
        return createProductNode(product);
    }

    int compareResult = strcmp(product->name, root->name);

    if (compareResult < 0) {
        root->left = insertBST(root->left, product);
    } else if (compareResult > 0) {
        root->right = insertBST(root->right, product);
    }

    return root;
}

// Function to search for a product in the BST
struct Product* searchBST(struct Product* root, const char* productName) {
    if (root == NULL || strcmp(productName, root->name) == 0) {
        return root;
    }

    if (strcmp(productName, root->name) < 0) {
        return searchBST(root->left, productName);
    } else {
        return searchBST(root->right, productName);
    }
}

int main() {
    const int numProducts = 30;
    struct Product products[numProducts];

    readProductData(products, numProducts, "products.txt");
    displayProductInfo(products, numProducts);
    performStatisticalAnalysis(products, numProducts);
    makePredictions(products, numProducts);
    struct Product* bstRoot = NULL;
    for (int i = 0; i < numProducts; ++i) {
        // Insert products into the BST
        bstRoot = insertBST(bstRoot, &products[i]);
    }
    const char* productNameToSearch = "Slim_Fit_Chinos";
    struct Product* searchedProduct = searchBST(bstRoot, productNameToSearch);

    if (searchedProduct != NULL) {
        printf("\nProduct Found in BST:\n");
        printf("Name: %s | Category: %s | Price: $%.2f\n", searchedProduct->name, searchedProduct->category, searchedProduct->price);
    } else {
        printf("\nProduct not found in BST.\n");
    }

    return 0;
}
