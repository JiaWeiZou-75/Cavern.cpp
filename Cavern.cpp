/*
Name: JiaWei Zou
Date: 3/7/23
Cavern.cpp defines the constructors and private and public function implementation of the Cavern class
*/

#include "Cavern.hpp"
#include <cmath>

/*
  Default constructor.
  Default-initializes all private members. 
*/
Cavern::Cavern() {
    level_sum_ = 0;
    tame_count_ = 0;
}

/*
    @param   :   A reference to a Creature entering the Cavern
    @post    :   If the given Creature is not already in the Cavern, add Creature to the Cavern and updates the level sum and the tame Creature count if the creature is tame.
    @return  :   returns true if a Creature was successfully added to the Cavern, false otherwise
             :   Hint: Use the above definition of equality will help determine if a Creature is already in the Cavern

*/

bool Cavern::enterCavern(const Creature& aCreature){
    if (contains(aCreature)){
        return false; 
    } else {
        if (add(aCreature)){
            level_sum_ += aCreature.getLevel();
        if (aCreature.isTame()){
            tame_count_ += 1;
        }
            return true;
        } else{
            return false;
        }
    }
}

/*
    @param   :  A  reference to a Creature leaving the Cavern
    @return  :  returns true if a creature was successfully removed from the Cavern (i.e. items_), false otherwise
    @post    :  removes the creature from the Cavern and updates the level sum. 
                If the Creature is tame it also updates the tame count.
*/
bool Cavern::exitCavern(const Creature& aCreature){
    int level = aCreature.getLevel();
    bool is_Tame = aCreature.isTame();

    if (remove(aCreature)){
        level_sum_ = level_sum_ - level;
        if (is_Tame){
        tame_count_ = tame_count_ - 1;
        }
        return true;
    } else {
        return false;
    }
}

/*
    @return   :  The integer level count of all the creatures currently in the Cavern
*/
int Cavern::getLevelSum() const{
    return level_sum_;
}

/*
    @return   :  The average level (int) of all the creatures in the Cavern 
    @post     :  Computes the average level (double) of the Cavern rounded to the NEAREST integer.
*/
int Cavern::calculateAvgLevel() const{
    if (isEmpty()){
        return 0;
    } else{
        float total_levels = this->getLevelSum();
        float size = this->getCurrentSize();
        int ans = round(total_levels / size);
        return ans;
    }
}

/*
    @return   :  The integer count of tame Creatures in the Cavern
*/
int Cavern::getTameCount() const{
    return tame_count_;
}

/*
    @return   :   The percentage (double) of all the tame creatures in the Cavern
    @post     :   Computes the percentage of tame creatures in the Cavern rounded up to 2 decimal places.
*/
double Cavern::calculateTamePercentage() const{
    if (isEmpty()){
        return 0.0;
    } else{
        int total_Creatures = getCurrentSize();
        int total_tame = getTameCount();
        double percentage =  round((10000* total_tame)/ total_Creatures + 0.5) / 100;
        return percentage;
  }
}

/*
    @param   :   A reference to a string representing a creature Category with value in ["UNKNOWN", "UNDEAD", "MYSTICAL", "ALIEN"]
    @return  :  An integer tally of the number of creatures in the Cavern of the given category. 
                If the argument string does not match one of the expected category values, the tally is zero. 
    NOTE: no pre-processing of the input string necessary, only uppercase input will match.
*/
int Cavern::tallyCategory(const std::string& category) const{
    int count = 0;
    for (int i = 0; i < getCurrentSize(); i++){
        if (items_[i].getCategory() == category){
            count++;
        }
    }
    return count;
}

/*
    @param  :   An integer representing the level threshold of the creatures to be removed from the Cavern, with default value 0
    @post   :   Removes all creatures from the Cavern whose level is less than the given level. If no level is given, removes all creatures from the Cavern. Ignore negative input.
    @return :   The number of creatures removed from the Cavern
*/
int Cavern::releaseCreaturesBelowLevel(const int level){
    int removed = 0;
    int size = getCurrentSize();
    if (level < 0){
        return 0;
    } else if (level == 0){
        for (int i = 0; i< size; i++){
            if (exitCavern(items_[i])){
            removed += 1;
            };
        }
        return removed;
    } else{
        for (int i = 0; i < size; i++){
            if (level > items_[i].getLevel()){
                if (exitCavern(items_[i])){
                removed += 1;
                };
            }
        }
    }
    return removed;
}

/*
    @param  : A reference to a string representing a creature Category with a value in ["UNKNOWN", "UNDEAD", "MYSTICAL", "ALIEN"], or default value "ALL" if no category is given
    @post   : Removes all creatures from the Cavern whose category matches the given category. If no category is given, removes all creatures from the Cavern.
    @return : The number of creatures removed from the Cavern
    NOTE: no pre-processing of the input string necessary, only uppercase input will match. If the input string does not match one of the expected category values, do not remove any creatures.
*/
int Cavern::releaseCreaturesOfCategory(const std::string& category){
    int removed = 0;
    int size = getCurrentSize();
    for (int i = 0; i < size; i++){
        if (category == "ALL"){
            exitCavern(items_[i]);
        } else if (items_[i].getCategory() == category){
            exitCavern(items_[i]);
        }
        removed++;
    }
    return removed;
}

/*
    @post   : Outputs a report of the creatures currently in the Cavern in the form:
              "UNKNOWN: [x]\nUNDEAD: [x]\nMYSTICAL: [x]\nALIEN: [x]\n\nAVERAGE LEVEL: [x]\nTAME:[x]%\n"
              Note that the average level should be rounded to the NEAREST integer, and the percentage of tame creatures in the Cavern should be rounded to 2 decimal places.

              Example output: 
              UNKNOWN: 1
              UNDEAD: 3
              MYSTICAL: 2
              ALIEN: 1

              AVERAGE LEVEL: 5
              TAME: 85.72%
*/

void Cavern::cavernReport() const{
    std::cout << "UNKNOWN: " << tallyCategory("UNKNOWN") << std::endl;
    std::cout << "UNDEAD: " << tallyCategory("UNDEAD") << std::endl;
    std::cout << "MYSTICAL: " << tallyCategory("MYSTICAL") << std::endl;
    std::cout << "ALIEN: " << tallyCategory("ALIEN") << std::endl << std::endl;
    std::cout << std::endl;
    std::cout << "AVERAGE LEVEL: " << calculateAvgLevel() << std::endl;
    std::cout << "TAME: " << calculateTamePercentage() << "%" << std::endl;
}
