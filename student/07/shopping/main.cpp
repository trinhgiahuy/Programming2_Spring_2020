/*
Task description:
This program stores all the information about the
products in different store from input file
It provides some command such as listing the chains, the
store belong to those chains. their products and prices or
out of stock and find all the stores selling cheapest product.


Student1 name : Trinh Gia Huy
Student1 number: 290290
Student1 user id: bdgitr
Student1 email: giahuy.trinh@tuni.fi

Student2 name: Huynh Khuong Van
Student2 number: 290270
Student2 user : bqvahu
Student2 email: van.huynh@tuni.fi


*/



#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <map>
#include <algorithm>
#include <cstring>
#include <iomanip>


// Declare struct Product for storing product name and price
struct Product
{
    std::string product_name;
    double product_price;
};


/* Function for splitting a string
@param: a string
@return: a vector containing strings
*/
std::vector<std::string> split(const std::string& s, const char delimiter, bool ignore_empty = false) {
    std::vector<std::string> result;
    std::string tmp = s;

    while (tmp.find(delimiter) != std::string::npos)
    {
        std::string new_part = tmp.substr(0, tmp.find(delimiter));
        tmp = tmp.substr(tmp.find(delimiter) + 1, tmp.size());
        if (not (ignore_empty and new_part.empty()))
        {
            result.push_back(new_part);
        }
    }
    if (not (ignore_empty and tmp.empty()))
    {
        result.push_back(tmp);
    }
    return result;
}


/* This function compares product_name of two Products, it is used as a
a third parameter in the sort function in the "selection" command
@param: two Product to compare
@return a boolean algebra of comparison between two product_name
*/
bool compare(const Product &a, const Product &b)
{
    return a.product_name < b.product_name;
}

/* Function for handling Product vector input
@param: a vector contains Product struct and Struct products
*/

void update_product(std::vector<Product>& list, Product sp) {

    std::vector<Product>::iterator iter_vector;
    bool in_product = false;

    // Check whether product is already in vector, change product_price if true
    for (iter_vector = list.begin(); iter_vector != list.end(); iter_vector++) {
        if (iter_vector->product_name == sp.product_name) {
            iter_vector->product_price = sp.product_price;
            in_product = true;
        }
    }

    // If false push_back new product into vector
    if (!in_product) {
        list.push_back(sp);
    }
}


/* Function used in "selection" command
@param: vector containing all products information
@return: print out information of the product
*/

void selection(std::vector<Product> &list) {

    sort(list.begin(), list.end(), compare);
    for (auto it : list) {
        if (it.product_price == -1) {
            std::cout << it.product_name << " out of stock" << std::endl;
        }
        else {
            std::cout << it.product_name << " " << std::fixed << std::setprecision(2)<< it.product_price << std::endl;
        }
    }
}


/* Funtion used in "cheapest" command
@param: A datastructure, name and location of store(string) and a vector contains all
@return: Print out the cheapest price of the products and their stores
*/

void find_cheapest_products(std::map<std::string, std::map < std::string,std::vector<Product>>>superMarketMap,
    std::string name, std::vector<std::string>all_products) {

    //an iterator that check a outer data stucture superMarketMap
    std::map<std::string, std::map<std::string, std::vector<Product>>>::iterator iter_map;

    //an iterator that check the local store
    std::map<std::string, std::vector<Product>>::iterator iter_chain;

    //an iterator that check the vector all_products
    std::vector<std::string>::iterator iter_all_product;

    iter_all_product = find(all_products.begin(), all_products.end(), name);
    if (iter_all_product == all_products.end()) {
        std::cout << "The product is not part of product selection" << std::endl;

    } else {

        double min_value = 0;
        std::vector <std::string> min_list;

        //Scan the data structure and find the cheapest value
        for (iter_map = superMarketMap.begin(); iter_map != superMarketMap.end(); ++iter_map) {
            for (iter_chain = iter_map->second.begin(); iter_chain != iter_map->second.end(); ++iter_chain) {
                for (auto element : iter_chain->second) {
                    if (element.product_name == name) {
                        std::string cheap_store = "";
                        cheap_store += iter_map->first + " " + iter_chain->first;
                        if (min_list.empty() && element.product_price >= 0) {
                            min_list.push_back(cheap_store);
                            min_value = element.product_price;
                        }
                        else if (element.product_price == min_value) {
                            min_list.push_back(cheap_store);
                        }
                        else if (element.product_price < min_value && element.product_price>0) {
                            min_list.clear();
                            min_list.push_back(cheap_store);
                            min_value = element.product_price;
                        }

                    }
                }
            }
        }

        //print out the exception the product is out of stockeverywhere
        if (min_list.empty()) {
            std::cout << "The product is temporarily out of stock everywhere" << std::endl;
        }
        else {
            std::cout << std::fixed << std::setprecision(2) << min_value << " euros" << std::endl;
            std::sort(min_list.begin(), min_list.end());
        }

        //print all the store that contain cheapest product
        for (auto locate : min_list) {
            std::cout << locate << std::endl;
        }

    }
}


int main()
{
    std::string filename = "";

    // Vector containing name of all products
    std::vector<std::string> all_products;

    // Data structure for storing inputs
    std::map < std::string, std::map < std::string, std::vector<Product> > > superMarketMap;

    /* Asks for input file name, stores
     the information and deals with input errors
     */
    std::cout << "Input file: ";
    std::getline(std::cin, filename);
    std::ifstream file_object(filename);

    if (not file_object) {
        std::cout << "Error: the input file cannot be opened" << std::endl;
        return EXIT_FAILURE;
    }
    else {
        std::string superMarket, city_name, food_name;
        double price;
        std::string line;
        std::string myString;

        while (getline(file_object, line)) {
            std::vector<std::string> parts = split(line, ';', true);

            // Prints out error if the file contains erroneous line
            if (parts.size() != 4) {
                std::cout << "Error: the input file has an erroneous line" << std::endl;
                return EXIT_FAILURE;
            }

            superMarket = parts.at(0);
            city_name = parts.at(1);
            food_name = parts.at(2);
            myString = parts.at(3);

            // Checks whether necessary input elements are given
            if (superMarket == "" || city_name == "" \
                    || food_name == "" || myString == "") {
                std::cout << "Error: the input file has an erroneous line" << std::endl;
                return EXIT_FAILURE;
            }

            // The price of the food counts as -1 if out-of-stock
            if (myString != "out-of-stock") {
                price = stod(myString);
            }
            else {
                price = -1;
            }

            // After reading each file line, stores data into the data structure
            update_product(superMarketMap[superMarket][city_name],
            { food_name, price });

            // Store data into vector all_product
            std::vector<std::string>::iterator product_iter
                    = find(all_products.begin(), all_products.end(), food_name);
            if (product_iter == all_products.end()) {
                all_products.push_back(food_name);
            }
        }
    }

            while (true) {

                   // Handle command input
                   std::string line;
                   std::cout << "> ";
                   getline(std::cin, line);
                   std::vector<std::string> parts = split(line, ' ', true);


                   std::string command = parts.at(0);

                   if (command == "quit") {
                       return EXIT_SUCCESS;
                   }

                   // Command "chains" lists all store chains in alphabetical order
                   else if (command == "chains") {
                       for (auto it = superMarketMap.cbegin(); it != superMarketMap.cend(); ++it)
                       {
                           std::cout << it->first << std::endl;
                       }
                   }

                   /* Command "stores" prints out the location of stores of a chain,
                   prints out Error if chain name is incorrect.
                    */
                   else if (command == "stores") {
                       std::string name = parts.at(1);

                       if ( superMarketMap.find(name) == superMarketMap.end()) {
                           std::cout << "Error: unknown chain name" << std::endl;
                       }
                       else {
                       for (auto it = superMarketMap[name].cbegin();
                            it != superMarketMap[name].cend(); ++it){
                           std::cout << it->first << std::endl;
                       }
                       }
                   }

                   /* Command "selection" prints out the information of all products
                    in selected store. The process is done above in "select_store"
                    function. Prints out errors if any.
                    */
                   else if (command == "selection") {
                       std::string name = parts.at(1);
                       std::string location = parts.at(2);
                       if ( superMarketMap.find(name) == superMarketMap.end()) {
                           std::cout << "Error: unknown chain name" << std::endl;
                       } else if ( superMarketMap[name].find(location) == superMarketMap[name].end()) {
                           std::cout << "Error: unknown store" << std::endl;
                       } else {
                           selection(superMarketMap[name][location]);
                       }

                   }

                   /* Command "products" prints out all the products 's names
                   in alphabetical order. Prints out errors if any.
                    */
                   else if (command == "products") {
                       if (parts.size() != 1) {
                           std::cout << "Error: error in command products" << std::endl;
                           continue;
                       }
                       std::sort(all_products.begin(), all_products.end());
                       for (std::string x : all_products) {
                           std::cout << x << "\n";
                       }
                   }

                   /* Command "cheapest" prints out the cheapest price can be found
                    of a product and also the stores where it is sold. Prints out errors
                    if any.
                    */
                   else if (command == "cheapest") {
                       std::string name = parts.at(1);
                       if (parts.size() != 2) {
                           std::cout << "Error: error in command cheapest" << std::endl;
                       }
                       else {
                           find_cheapest_products(superMarketMap, name, all_products);
                       }
                   }

                   else {
                       std::cout << "Error: unknown command: " << command << std::endl;
                   }

        }
    return 0;
}
