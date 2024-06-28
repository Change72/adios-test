#include <iostream>
#include <memory>  // Include the memory header for std::unique_ptr

class Remote {
public:
    Remote() {
        std::cout << "Remote created" << std::endl;
    }

    ~Remote() {
        std::cout << "Remote destroyed" << std::endl;
    }

    void doSomething() {
        std::cout << "Remote is doing something" << std::endl;
    }
};

class MyClass {
public:
    MyClass(bool dataIsRemote) : m_dataIsRemote(dataIsRemote) {}

    void initializeRemote() {
        if (m_dataIsRemote && !m_Remote) {
            m_Remote = std::unique_ptr<Remote>(new Remote());
            std::cout << "Remote initialized" << std::endl;
        }
    }

    void useRemote() {
        if (m_Remote) {
            m_Remote->doSomething();
        } else {
            std::cout << "Remote is not initialized" << std::endl;
        }
    }

    void releaseRemote() {
        m_Remote.reset();  // This will delete the managed object
        std::cout << "Remote released" << std::endl;
    }

private:
    bool m_dataIsRemote;
    std::unique_ptr<Remote> m_Remote; // Unique pointer to Remote
};

int main() {
    MyClass myClass(true);

    myClass.initializeRemote(); // This will initialize m_Remote and execute the block
    myClass.useRemote();        // This will use the Remote object

    myClass.releaseRemote();    // Manually release the Remote object
    myClass.useRemote();        // This will show that Remote is not initialized

    // When myClass goes out of scope, if m_Remote is not reset, it will be destroyed automatically

    return 0;
}
