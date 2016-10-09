/*
 * General function form, for defining valid moves
 * By Danny Reilman <reilman@umich.edu>
 */
#include <vector>
#include "EvaluateToDouble.h"

class Function {
public:
	/*
	 * Returns the number of arguments that should be sent into evaluate
	 */
	virtual int GetNumArgs() = 0;

	/*
	 * Requires: arguments.length == getNumArgs();
	 *  Returns the function evaluated over the arguments.
	 */
	virtual int Eval(const vector<EvaluateToDouble*>) = 0;
};
