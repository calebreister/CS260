///@file main.cc
///@author Caleb Reister
#include <iostream>
#include <string>
#include "BinTree.hh"
using namespace std;

void printMember(const string& name, uint32_t treeLevel);

int main() {
    BinTree<string> crewMembers {"Kirk", "Checkov", "Sisko", "Chapel",
                                 "Janeway", "Sulu", "Bones", "Q", "Scotty",
                                 "Uhuru", "Picard", "Spock", "Worf"};
    cout << "Original tree\n";
    crewMembers.traverse(IN_ORDER, printMember);
    cout << "\n\n";
    BinTree<string> crewCopy(crewMembers);
    
    string remove[] = {"Bones", "Sisko", "Sulu", "Kirk"};
    for (int i = 0; i < 4; i++)
    {
        crewMembers.remove(remove[i]);
        cout << remove[i] << " Deleted\n";
        crewMembers.traverse(IN_ORDER, printMember);
        cout << endl;
    }

    cout << "Copy in PRE_ORDER\n";
    crewCopy.traverse(PRE_ORDER, printMember);
    cout << endl << "Copy in POST_ORDER\n";
    crewCopy.traverse(POST_ORDER, printMember);
}

void printMember(const string& name, uint32_t treeLevel) {
    cout << name << '(' << treeLevel << ")\n";
}
