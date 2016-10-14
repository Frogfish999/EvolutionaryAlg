#ifndef EVALUATETODOUBLE_H
#define EVALUATETODOUBLE_H

/*
 * A generic class to define anything that can evaluate to a double
 * By Danny Reilman <reilman@umich.edu>
 */

class EvaluateToDouble
{
public:
    virtual double GetDouble() const = 0;
};

#endif