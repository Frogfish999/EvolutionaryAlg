#include "MutableFunctionSubject.h"
#include "EvaluateToDouble.h"
#include "SimpleDouble.h"
#include "ValueSupplier.h"
#include "MutationOptions.h"

#include <cmath>

static double BREVITY_WEIGHT = 0.1;

MutableFunctionSubject::MutableFunctionSubject(): options(nullptr), generator(nullptr), mutableFuncObject(nullptr) {}

MutableFunctionSubject::MutableFunctionSubject(MutableFunctionSubject&& other): options(other.options), generator(other.generator), 
                                                            mutableFuncObject(std::move(other.mutableFuncObject)) { }

MutableFunctionSubject::MutableFunctionSubject(MutableFuncs::MutationOptions *options_in, ValueSupplier *generator_in): options(options_in), generator(generator_in)
{
    mutableFuncObject = std::move(std::unique_ptr<MutableFuncs::EvaluateToDouble>(new MutableFuncs::SimpleDouble(0)));
	options->validInputMutations.clear();
	
	for(auto it = generator->PeakVariables().cbegin(); it !=  generator->PeakVariables().cend(); ++it)
	{
		options->validInputMutations.push_back(*it);
	}
}

void MutableFunctionSubject::Mutate()
{
	MutableFuncs::EvaluateToDouble::MutatePointer(mutableFuncObject, *options);
}

double MutableFunctionSubject::Evaluate()
{
	const std::unordered_map<char, double>* variables = generator->GetValue().first;
	double correctResult = generator->GetValue().second;
	double result = mutableFuncObject->GetDouble(*variables);
	return 1.0 / (abs(correctResult - result) * BREVITY_WEIGHT * mutableFuncObject->GetHeight());
}

void MutableFunctionSubject::Print(std::ostream& out) const
{
    out << mutableFuncObject->Print();
}

std::unique_ptr<EvoAlg::Subject> MutableFunctionSubject::Clone()
{
	MutableFunctionSubject* toReturn(new MutableFunctionSubject(options, generator));
	toReturn->mutableFuncObject = move(mutableFuncObject->Clone());
	return std::unique_ptr<EvoAlg::Subject>(toReturn);
}