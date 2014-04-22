#include "Dog.hh"
using namespace std;

Dog operator+(const Dog& a, const Dog& b) {
    Dog result = a;
    result.weightLbs = a.weightLbs + b.weightLbs;
    return result;
}

bool operator==(const Dog& a, const Dog& b) {
    if (a.alive == b.alive &&
        a.noodle == b.noodle &&
        a.snd == b.snd &&
        a.weightLbs == b.weightLbs)
        return true;
    else
        return false;
}

bool operator!=(const Dog& a, const Dog& b) {
    if (a == b)
        return false;
    else
        return true;
}

bool operator>(const Dog& a, const Dog& b) {
    if (a.noodle > b.noodle &&
        a.weightLbs > b.weightLbs)
        return true;
    else
        return false;
}

bool operator<(const Dog& a, const Dog& b) {
    if (a.noodle < b.noodle &&
        a.weightLbs < b.weightLbs)
        return true;
    else
        return false;
}

bool operator>=(const Dog& a, const Dog& b) {
    if (a > b || a == b)
        return true;
    else
        return false;
}

bool operator<=(const Dog& a, const Dog& b) {
    if (a > b || a == b)
        return true;
    else
        return false;
}
