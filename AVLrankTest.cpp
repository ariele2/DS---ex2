#include "rankedAVL.h"

using namespace std; 

int main() {
    int n1 = 2, n2 = 2, n3 = 2;
    rankedAVL tree1;
    for (int i=0; i<n1; i++) {
        for (int j=0; j<n2; j++) {
            for (int k=0; k<n3; k++) {
                tree1.insert(trio(i,j,k));
            }
        }
    }
    cout << "Inorder: " << endl;
    tree1.printInorder();
    cout<< "Preorder: " << endl;
    tree1.printPreorder();
    tree1.remove(trio(1,0,1));
    cout << "Removed....." << endl;
    cout << "Inorder: " << endl;
    tree1.printInorder();
    cout<< "Preorder: " << endl;
    tree1.printPreorder();
    return 0;
}