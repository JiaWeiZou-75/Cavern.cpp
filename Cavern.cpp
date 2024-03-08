#include "Cavern.hpp"
#include "Creature.hpp"
#include <iostream>
#include <string>
#include <cmath>
#include "ArrayBag.hpp"

/**
  Default constructor.
  Default-initializes all private members. 
*/

template <class Creature>
Cavern<Creature>::Cavern() {
    level_Sum_ = 0;
    tame_Count_ = 0;
}

bool Cavern<Creature>::enterCavern(const Creature& enCav) {
    if (!contains(enCav)) {
    if (add(enCav)) {
        level_sum_ += enCav.getLevel();
        if (enCav.isTame()) {
            tame_count_++;
        }
        return true;
    }
    }
    return false;
}

template <class Creature>
bool Cavern<Creature>::exitCavern(const Creature& exCav) {
    if (contains(exCav)) {
        remove(exCav);
        level_Sum_ -= exCav.getLevel();

        if (exCav.isTame()) {
            tame_Count_--;
        }

        return true;
    }
    return false;
}

template <class Creature>
double Cavern<Creature>::calculateTamePercentage() const {
    if (tame_Count_ > 0) {
        double percentage = static_cast<double>(getTameCount()) / getCurrentSize() * 100.0;
        return std::round(percentage * 100.0) / 100.0;
    } else {
        return 0.0;
    }
}

template <class Creature>
int Cavern<Creature>::tallyCategory(const std::string& Category) const {
    int categoryCount = 0;

    for (int i = 0; i < getCurrentSize(); i++) {
        Creature creature = items_[i];
        if (creature.getCategory() == Category) {
            categoryCount++;
        }
    }

    return categoryCount;
}

template <class Creature>
int Cavern<Creature>::releaseCreaturesBelowLevel(const int level) {
    // keeping count of creatures removed
    int remove_count = 0;
    if (level < 0) {
        clear();
        level_Sum_ = 0;
        tame_Count_ = 0;

        return remove_count;
    } else {
        for (int i = 0; i < getCurrentSize(); i++) {
            if (items_[i].getLevel() < level) {
                level_Sum_ -= items_[i].getLevel();
                tame_Count_--;
                remove(items_[i]);
                remove_count++;
            }
        }
    }
    return remove_count;
}

template <class Creature>
void Cavern<Creature>::cavernReport() const {
    std::cout << "UNKNOWN: " << tallyCategory("UNKNOWN") << "\n";
    std::cout << "UNDEAD: " << tallyCategory("UNDEAD") << "\n";
    std::cout << "MYSTICAL: " << tallyCategory("MYSTICAL") << "\n";
    std::cout << "ALIEN: " << tallyCategory("ALIEN") << "\n\n";
    std::cout << "AVERAGE LEVEL: " << calculateAvgLevel() << "\n";
    std::cout << "TAME: " << calculateTamePercentage() << "%" << "\n";
}
