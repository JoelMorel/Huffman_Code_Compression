//
//  main.cpp
//  CSC323 Project 2 (Huffman)
//
//  Created by Joel Morel on 2/20/18.
//  Copyright © 2018 Joel Morel. All rights reserved.
//

#include <fstream>
#include <iostream>
using namespace std;

ifstream inFile;
ofstream output1, output2, output3, output4;

class listBinTreeNode
{
private:
protected:
public:
    int prob;
    string chStr;
    string code;
    listBinTreeNode* next;
    listBinTreeNode* left;
    listBinTreeNode* right;
    
    listBinTreeNode()
    {
        this->chStr = " ";
        this->prob = 0;
        this->next = NULL;
        this->left = NULL;
        this->right = NULL;
    }
    
    listBinTreeNode(string chStr, int prob, listBinTreeNode* left, listBinTreeNode* right)
    {
        this->chStr = chStr;
        this->prob = prob;
        this->next = NULL;
        this->left = left;
        this->right = right;
    }
    
    void printNode(listBinTreeNode* T, ofstream& outFile)
    {
        outFile << T->chStr << "," << T->prob << "," << T->code << "," << T->next->chStr << endl;// << T->code << T->next->chStr << T->left->chStr << T->right->chStr << endl;
    }

};

class HuffmanLinkedList
{
private:
protected:
public:
    
    listBinTreeNode* listhead;
    listBinTreeNode* oldlisthead;
    listBinTreeNode*  spot;
    listBinTreeNode* root;
    
    HuffmanLinkedList()
    {
        listhead = new listBinTreeNode("dummy", 0, NULL, NULL);
        this->oldlisthead = NULL;
    }
    
    void ConstructLinkedList()
    {
        string charIn;
        int prob;
        
        if (!inFile)
        {
            cerr << "Unable to open file datafile.txt" << endl;
            exit(1);
        }
    
        while (inFile >> charIn >> prob)
        {
            spot = findSpot(prob);
            listBinTreeNode* newNode = new listBinTreeNode(charIn, prob, NULL, NULL);
            listInsert(spot, newNode);
            printList(this->listhead, output1);
        }

    }
    
    void ConstructBinTree()
    {
       oldlisthead = listhead->next;
        
        while(listhead->next->next != NULL)
        {
            string newChStr = listhead->next->chStr + listhead->next->next->chStr;
            int newProb = listhead->next->prob + listhead->next->next->prob;
            
            listBinTreeNode* newNode = new listBinTreeNode();
            newNode->chStr = newChStr;
            newNode->prob = newProb;
            newNode->left = listhead->next;
            newNode->right = listhead->next->next;
            
            listhead = listhead->next->next;
            spot = findSpot(newNode->prob);
            listInsert(spot, newNode);
            printList(oldlisthead, output2);
        }
        
        root = oldlisthead->next;
        
        while(root->next != NULL)
        {
            cout << root->chStr << endl;
            root = root->next;
        }
        ConstructCode(root, "" "");
    }
    
    void ConstructCode(listBinTreeNode* T, string str)
    {
        if(T == NULL)
        {
            return;
        }
        else if(isLeaf(T))
        {
            T->code = str;
            output3 << T->chStr << " " << T->code << endl;
        }
        else
        {
            ConstructCode(T->left, str + "0");
            ConstructCode(T->right, str + "1");
        }
    }
    
    
    listBinTreeNode* findSpot(int newNodeProb)
    {
        spot = this->listhead;
        
        while(spot->next != NULL)
        {
            if(spot->next != NULL && spot->next->prob < newNodeProb)
            {
                spot = spot->next;
            }
            return spot;
        }
        return spot;
        
    }
    
    void listInsert(listBinTreeNode* spot, listBinTreeNode* newNode)
    {
        if(spot != NULL)
        {
            newNode->next = spot->next;
            spot->next = newNode;
        }
    }
    
    void preOrderTraversal(listBinTreeNode* T)
    {
        if(T == NULL)
        {
            return;
        }
        
        output4 << "(" << T->chStr<<"," << " " << T->prob<< ")-->";
        preOrderTraversal(T->left);
        preOrderTraversal(T->right);
    }
    
    void inOrderTraversal(listBinTreeNode* T)
    {
        if(T == NULL)
        {
            return;
        }
        
        inOrderTraversal(T->left);
        output4 << "(" << T->chStr<<"," << " " << T->prob << ")-->";
        inOrderTraversal(T->right);
    }
    
    void postOrderTraversal(listBinTreeNode* T)
    {
        if(T == NULL)
        {
            return;
        }
        postOrderTraversal(T->left);
        postOrderTraversal(T->right);
        output4 << "(" << T->chStr<<"," << " " << T->prob << ")-->";
    }
    
    bool isLeaf(listBinTreeNode* T)
    {
        if(T->left == NULL && T->right == NULL)
        {
            return true;
        }
        else
        {
            return false;
        }
    }
    
    void printList(listBinTreeNode* T, ofstream& outFile)
    {
        listBinTreeNode* current = this->listhead;
        outFile << "listHead -->";
        while(current->next != NULL)
        {
            outFile << "(" << current->chStr<<"," << " " << current->prob<<"," << " " << current->next->chStr << ")-->";
            current = current->next;
        }
        outFile << "(" << current->chStr << " " << current->prob << " NULL)" << endl;
    }
    
    bool isEmpty()
    {
        if (this->listhead->next == NULL)
        {
            return true;
        }
        else
        {
            return false;
        }
    }
    
};

int main(int argc, const char * argv[])
{
    HuffmanLinkedList huffList;
    
    inFile.open(argv[1]);
    output1.open(argv[2]);
    output2.open(argv[3]);
    output3.open(argv[4]);
    output4.open(argv[5]);
    
    huffList.ConstructLinkedList();
    huffList.ConstructBinTree();
    huffList.ConstructCode(huffList.root, " ");
    
    output4 << "Pre-Order Traversal: " << endl;
    huffList.preOrderTraversal(huffList.root);
    output4 << endl;
    output4 << "In-Order Traversal: " << endl;
    huffList.inOrderTraversal(huffList.root);
    output4 << endl;
    output4 << "Post-Order Traversal: " << endl;
    huffList.postOrderTraversal(huffList.root);
    
    inFile.close();
    output1.close();
    output2.close();
    output3.close();
    output4.close();
    
    return 0;
}
