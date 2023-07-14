#include <iostream>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <chrono>

class Spoon;

class Diner {
private:
    std::string name;
    bool isHungry;
    std::condition_variable cv;

public:
    Diner(const std::string& n) : name(n), isHungry(true) {}

    std::string getName() const { return name; }
    bool getIsHungry() const { return isHungry; }
    void setIsHungry(bool hungry) { isHungry = hungry; }

    void eatWith(Spoon& spoon, Diner& spouse);
};

class Spoon {
private:
    Diner* owner;
    std::mutex spoonMutex;

public:
    Spoon(Diner& d) : owner(&d) {}

    Diner* getOwner() { return owner; }
    void setOwner(Diner& d) { owner = &d; }

    void use() {
        std::lock_guard<std::mutex> lock(spoonMutex);
        std::cout << owner->getName() << " has eaten!" << std::endl;
    }
};

void Diner::eatWith(Spoon& spoon, Diner& spouse) {
    while (getIsHungry()) {
        std::unique_lock<std::mutex> spoonLock(spoon.spoonMutex);
        std::unique_lock<std::mutex> spouseLock(spouse.spoonMutex);

        if (spoon.getOwner() != this) {
            cv.wait(spoonLock, [&]() { return spoon.getOwner() == this; });
            continue;
        }

        if (spouse.getIsHungry()) {
            std::cout << name << ": You eat first my darling " << spouse.getName() << "!" << std::endl;
            spoon.setOwner(spouse);
            continue;
        }

        spoon.use();
        setIsHungry(false);

        std::cout << name << ": I am stuffed, my darling " << spouse.getName() << "!" << std::endl;
        spoon.setOwner(spouse);
        cv.notify_one();
    }
}

void threadFunc1(Diner& husband, Spoon& s, Diner& wife) {
    husband.eatWith(s, wife);
}

void threadFunc2(Diner& wife, Spoon& s, Diner& husband) {
    wife.eatWith(s, husband);
}

int main() {
    Diner husband("Bob");
    Diner wife("Alice");

    Spoon s(husband);

    std::thread thread1(threadFunc1, std::ref(husband), std::ref(s), std::ref(wife));
    std::thread thread2(threadFunc2, std::ref(wife), std::ref(s), std::ref(husband));

    thread1.join();
    thread2.join();

    return 0;
}
