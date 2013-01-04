

#ifndef UT_EVAL_UNITTESTSESSIONENVIRONMENT_HPP_
#define UT_EVAL_UNITTESTSESSIONENVIRONMENT_HPP_

#include "eval/SessionEnvironment.hpp"

class UnitTestEnvironment : public tungsten::eval::SessionEnvironment {
public:
	//Expose this for unit testing purposes
	void addAttribute(const tungsten::ast::Identifier& identifier, const tungsten::eval::Attribute& attribute) {
		attributeMap.addAttribute(identifier, attribute);
	}
};

#endif /* UT_EVAL_UNITTESTSESSIONENVIRONMENT_HPP_ */
