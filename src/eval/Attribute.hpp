
#ifndef EVAL_ATTRIBUTE_HPP_
#define EVAL_ATTRIBUTE_HPP_

#include <map>
#include <set>
#include <vector>

#include "ast/Identifier.hpp"

namespace tungsten { namespace eval {

typedef ast::Identifier Attribute;
//typedef std::map<ast::Identifier, AttributeVector> AttributeMap;

//TODO typedef nameing is a little bit inconsistent here
class AttributeMap {
public:
	typedef std::set<Attribute> AttributeSet;
	typedef std::map<ast::Identifier, AttributeSet> AttributeStorage;

	AttributeMap();
	AttributeMap(const AttributeStorage& attributeStorage);


	static AttributeMap makeDefault();

	bool hasAttribute(const ast::Identifier& identifier, const Attribute& attribute) const;
	void addAttribute(const ast::Identifier& identifier, const Attribute& attribute);

private:
	AttributeStorage attributeStorage;
};

}} //namespace tungsten::eval

#endif /* EVAL_ATTRIBUTE_HPP_ */
