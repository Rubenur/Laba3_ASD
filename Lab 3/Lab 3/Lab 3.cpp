#include <iostream>
#include <iomanip>
#include <sstream>
#include "tree.h"

using namespace std;

void menu() // menu
{
    std::cout << std::endl;
    std::cout << "Function menu:" << std::endl;
    std::cout << "1) Search for an element in the tree by key." << std::endl;
    std::cout << "2) Adding an element to the tree by key." << std::endl;
    std::cout << "3) Remove the tree element by key." << std::endl;
    std::cout << "4) Creating an iterator that implements one of the depth-first traversal methods." << std::endl;
    std::cout << "5) Creating an iterator that implements breadth-first traversal methods." << std::endl;
    std::cout << "6) Create a tree of 10 random keys." << std::endl;
    std::cout << "7) Print all keys in ascending order." << std::endl;
    std::cout << "8) Exit." << std::endl;
}

int input() // input function
{
    int output_value;
    bool nonDig = true;

    do
    {
        std::string str;
        std::cin >> str;
        if (str.find_first_not_of("0123456789", 0) != std::string::npos)
        {
            nonDig = false;
            std::cout << std::endl;
            std::cout << "Input error!" << std::endl;
            std::cout << "Repeat the input:";
        }
        else
        {
            std::istringstream sstream(str);
            sstream >> output_value;
            nonDig = true;
        }
    } while (nonDig == false);

    return output_value;
}

int main()
{
    Tree<int> intTree;           // creating a new binary tree with a key of type int
    int numChoice, data;
    bool end_indicator = false;
    srand(time(0));

    do
    {
        menu();
        std::cout << std::endl;
        std::cout << "Enter the element number:";

        numChoice = input();

        switch (numChoice)
        {
        case 1:
            std::cout << std::endl;
            std::cout << "Enter the key of the item you want to search for:";
            data = input();
            if (intTree.contains(data) == true)
            {
                std::cout << std::endl;
                std::cout << "--> This item was found.";
                std::cout << std::endl;
            }
            else
            {
                std::cout << std::endl;
                std::cout << "--> This element does not exist.";
                std::cout << std::endl;
            }
            break;
        case 2:
            std::cout << std::endl;
            std::cout << "Enter the key of the item you want to create:";
            data = input();
            intTree.insert(data);
            break;
        case 3:
            std::cout << std::endl;
            std::cout << "Enter the key of the item you want to delete:";
            data = input();
            intTree.remove(data);
            break;
        case 4:
        {
//           intTree.dft_walk(intTree.get_root());
//            Tree<int>::iterator_deep dft(intTree);
            Tree<int>::iterator_deep dft = intTree.create_dtf_iterator();
            for (int i = 1 ; dft.get() != 0 ; ++dft, i++)
            {
                std::cout << i << "-->" << dft.get()->get_data() << std::endl;
            }
        }
            break;
        case 5:
        {
            Tree<int>::iterator_width bft = intTree.create_bft_iterator();
            for (int i = 1; bft.get() != 0; ++bft, i++)
            {
                std::cout << i << "-->" << bft.get()->get_data() << std::endl;
            }
            /*
            std::cout << std::endl;
            intTree.bft_walk(intTree.get_root());
            for (size_t i = 0; i < intTree.bft_matrix.size(); i++)
            {
                std::vector< TreeNode<int>* > stroka = intTree.bft_matrix[i];
                if (!stroka.empty())
                {
                    std::cout << "LEVEL:" << i + 1 << std::endl;
                    for (size_t j = 0; j < stroka.size(); j++)
                    {
                        std::cout << j + 1 << "-->" << stroka[j]->get_data() << std::endl;
                    }
                }
                */
            }
            break;
        case 6:
            std::cout << std::endl;
            for (int i = 0; i < 10; i++)        // fill it out
            {
                intTree.insert(rand() % 100);
            }
            break;
        case 7:
            std::cout << std::endl;
            intTree.inorder_walk(intTree.get_root());
            std::cout << std::endl;
            break;
        case 8:
            end_indicator = true;
            break;
        default:
            std::cout << std::endl;
            std::cout << "Input error!" << std::endl;
            std::cout << std::endl;
            break;
        }
    } while (end_indicator != true);

    /*
    for (int i = 0; i < 10; i++)        // fill it out
    {
        cin >> a;
        intTree.insert_node(a);
    }
    
    cout << endl << "inorder_walk:" << endl;             
    intTree.inorder_walk(intTree.get_root());       // вот для этого понадобился метод get_root() :-) 
    //cout << endl << "Minimum is: " << (intTree.find_min(intTree.get_root()))->get_data() << endl;
    //cout << endl << "Maximum is: " << (intTree.find_max(intTree.get_root()))->get_data() << endl;
    cout << "Enter node value U want to delete:";     // попробуем удалить узел с ключем a 
    cin >> a;
    intTree.delete_node(intTree.find_node(intTree.get_root(), a));    // если их несколько, то удалится первй найденный 
    cout << endl << "Now inorder_walk:" << endl;
    intTree.inorder_walk(intTree.get_root());       // посмотрим на результат 
    */
    return 0;
}