
#ifndef CAVERN_HPP
#define CAVERN_HPP
#include "ArrayBag.hpp"
#include "Creature.hpp"

template <class Creature>

class Cavern : public ArrayBag<Creature> {

    public:
/**
  Default constructor.
  Default-initializes all private members. 
*/

    Cavern();

/** 
  * @param   :   A reference to a Creature entering the Cavern
  * @post    :   If the given Creature is not already in the Cavern, add Creature to the Cavern and updates the level sum and the tame Creature count if the creature is tame.
  * @return  :   returns true if a Creature was successfully added to the Cavern, false otherwise
            :   Hint: Use the above definition of equality will help determine if a Creature is already in the Cavern
**/

    bool enterCavern(const Creature& enCav);

/** 
  * @param   :   A  reference to a Creature leaving the Cavern
  * @return  :  returns true if a creature was successfully removed from the Cavern (i.e. items_), false otherwise
  * @post    :    removes the creature from the Cavern and updates the level sum. 
                  If the Creature is tame it also updates the tame count.
**/

    bool exitCavern(const Creature& exCav);

 /** 
  * @return   :  The integer level count of all the creatures currently in the Cavern
  **/

    int getLevelSum() const;

/**
  * @return   :  The average level (int) of all the creatures in the Cavern
  * @post     :  Computes the average level (double) of the Cavern rounded to the NEAREST integer.
  **/

    int calculateAvgLevel() const;

/**
  * @return   :  The integer count of tame Creatures in the Cavern
  **/

    int getTameCount() const;

/**
  * @return   :  The percentage (double) of all the tame creatures in the Cavern
  * @post     :   Computes the percentage of tame creatures in the Cavern rounded up to 2 decimal places.
  **/
    double calculateTamePercentage() const;

    int tallyCategory(const std::string &Category) const;

    /**
      * @param  :   A reference to a string representing a creature Category with value in ["UNKNOWN", "UNDEAD", "MYSTICAL", "ALIEN"]
      * @return  :  An integer tally of the number of creatures in the Cavern of the given category.
                  If the argument string does not match one of the expected category values, the tally is zero.
                  NOTE: no pre-processing of the input string necessary, only uppercase input will match.
    **/

    int tallyCategory(const std::string& tallycategory);

/**
    @param  :   An integer representing the level threshold of the creatures to be removed from the Cavern, with default value 0
    @post   :   Removes all creatures from the Cavern whose level is less than the given level. If no level is given, removes all creatures from the Cavern. Ignore negative input.
    @return :   The number of creatures removed from the Cavern
*/

    int releaseCreaturesBelowLevel(const int level = 0);

/**
    @param  : A reference to a string representing a creature Category with a value in ["UNKNOWN", "UNDEAD", "MYSTICAL", "ALIEN"], or default value "ALL" if no category is given
    @post   : Removes all creatures from the Cavern whose category matches the given category. If no category is given, removes all creatures from the Cavern.
    @return : The number of creatures removed from the Cavern
              NOTE: no pre-processing of the input string necessary, only uppercase input will match. If the input string does not match one of the expected category values, do not remove any creatures.
*/

    int releaseCreaturesOfCategory(const std::string& category = "ALL");

/**
  * @post    : Outputs a report of the creatures currently in the Cavern in the form:
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

    void cavernReport() const;

/**
- An integer sum of the levels of all the creatures currently in the Cavern
- An integer count of all the creatures currently in the Cavern that are tame
*/

private:
    int level_Sum_;
    int tame_Count_;
};
#include "Cavern.cpp"
#endif
