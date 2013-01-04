
#include "Attribute.hpp"

#include <boost/assign/list_of.hpp>

namespace tungsten { namespace eval {

AttributeMap AttributeMap::makeDefault() {
	AttributeStorage attributeStorage = boost::assign::map_list_of
				("Plus", AttributeSet({"Flat", "Listable", "NumericFunction", "OneIdentity", "OrderLess", "Protected"}) )
				("Times", AttributeSet({"Flat", "Listable", "NumericFunction", "OneIdentity", "OrderLess", "Protected"}) );

	return AttributeMap(attributeStorage);
}

AttributeMap::AttributeMap() {}

AttributeMap::AttributeMap(const AttributeStorage& attributeStorage) :
		attributeStorage(attributeStorage) {}

bool AttributeMap::hasAttribute(const ast::Identifier& identifier, const Attribute& attribute) const {
	AttributeStorage::const_iterator it = attributeStorage.find( identifier );

	return it != attributeStorage.end() && it->second.count( attribute ) > 0;
}

void AttributeMap::addAttribute(const ast::Identifier& identifier, const Attribute& attribute) {
	attributeStorage[identifier].insert( attribute );
}

}} //namespace tungsten::eval


