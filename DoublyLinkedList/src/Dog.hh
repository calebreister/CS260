#ifndef ARRAY_HH
#define ARRAY_HH
#include <iostream>
#include <string>

enum MentalCapacity {
    COMPLETE_IDIOT, IDIOT,
    BELOW_AVG, AVG, ABOVE_AVG,
    SNOOPY, MR_PEABODY
};
enum Sound {
    BARK, MOO, YELP, HOWL, YAP
};

struct Dog {
    std::string name = "Cache";
    bool alive = true;
    MentalCapacity noodle = COMPLETE_IDIOT;
    unsigned int weightLbs = 5000;
    Sound snd = MOO;

    friend Dog operator+(const Dog& a, const Dog& b);
    friend bool operator==(const Dog& a, const Dog& b);
    friend bool operator!=(const Dog& a, const Dog& b);
    friend bool operator>(const Dog& a, const Dog& b);
    friend bool operator<(const Dog& a, const Dog& b);
    friend bool operator>=(const Dog& a, const Dog& b);
    friend bool operator<=(const Dog& a, const Dog& b);
    friend std::ostream& operator<<(std::ostream& stream, const Dog& data);
};

#endif
