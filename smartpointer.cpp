
#include <iostream>
#include <memory>
using namespace std;

class Resource
{
    string name;
public:
    Resource(string n) : name(n) {
        cout << "Resource [" << name << "] acquired" << endl;
    }
    ~Resource() {
        cout << "Resource [" << name << "] released" << endl;
    }
    void use() {
        cout << "Using resource [" << name << "]" << endl;
    }
};

int main() {
    cout << "--- Modified Smart Pointer Demo ---" << endl;

    // 1. Using unique_ptr with move semantics
    {
        unique_ptr<Resource> p1 = make_unique<Resource>("Alpha");
        p1->use();
        
        // Transfer ownership
        unique_ptr<Resource> p2 = move(p1);
        if (!p1) cout << "p1 is now null after move" << endl;
        p2->use();
    } // p2 goes out of scope here, releasing "Alpha"

    cout << "\n--- Shared Pointer Reference Count Tracking ---" << endl;
    {
        shared_ptr<Resource> sp1 = make_shared<Resource>("Beta");
        cout << "Initial count: " << sp1.use_count() << endl;

        {
            shared_ptr<Resource> sp2 = sp1;
            cout << "Count after sp2 copy: " << sp1.use_count() << endl;
            sp2->use();
        } // sp2 goes out of scope here

        cout << "Count after sp2 goes out of scope: " << sp1.use_count() << endl;
    } // sp1 goes out of scope here, releasing "Beta"

    cout << "Program completed successfully." << endl;
    return 0;
}
