/**@file Dog.hh
 * @author Caleb Reister <calebreister@gmail.com>
 * @brief Implements the dog operators, mainly for comparison
 */
#include "Dog.hh"
using namespace std;

///@brief combines the weights of two dogs
Dog operator+(const Dog& a, const Dog& b) {
    Dog result = a;
    result.weightLbs = a.weightLbs + b.weightLbs;
    return result;
}

///@brief Compares the mortality, intelligence, sound, and weight of two dogs
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

///@brief Compares intelligence and weight of two dogs
bool operator>(const Dog& a, const Dog& b) {
    if (a.noodle > b.noodle &&
        a.weightLbs > b.weightLbs)
        return true;
    else
        return false;
}

///@brief Compares intelligence and weight of two dogs
bool operator<(const Dog& a, const Dog& b) {
    if (a.noodle < b.noodle &&
        a.weightLbs < b.weightLbs)
        return true;
    else
        return false;
}

///@brief A boolean or || of the appropriate previously defined operators
bool operator>=(const Dog& a, const Dog& b) {
    if (a > b || a == b)
        return true;
    else
        return false;
}

///@brief A boolean or || of the appropriate previously defined operators
bool operator<=(const Dog& a, const Dog& b) {
    if (a < b || a == b)
        return true;
    else
        return false;
}

///@brief Prints all of the dog data, with keys, on one line
ostream& operator<<(ostream& stream, const Dog& data) {
    stream << "Name:" << data.name << " Alive:" << data.alive
           << " Intel:" << data.noodle << " Weight:" << data.weightLbs
           << " Sound:" << data.snd << endl;
    return stream;
}
