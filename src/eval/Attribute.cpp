
#include "Attribute.hpp"
#include "Identifiers.hpp"

#include <boost/assign/list_of.hpp>

namespace tungsten { namespace eval {

AttributeMap AttributeMap::makeDefault() {
	AttributeStorage attributeStorage = boost::assign::map_list_of
				(ids::Abs, AttributeSet({ids::Listable, ids::NumericFunction, ids::Protected}) )
				(ids::Plus, AttributeSet({ids::Flat, ids::Listable, ids::NumericFunction, ids::OneIdentity, ids::Orderless, ids::Protected}) )
				(ids::Times, AttributeSet({ids::Flat, ids::Listable, ids::NumericFunction, ids::OneIdentity, ids::Orderless, ids::Protected}) )
				(ids::Power, AttributeSet({ids::Listable, ids::NumericFunction, ids::OneIdentity, ids::Protected}) )
				(ids::Numerator, AttributeSet({ids::Listable, ids::Protected}) )
				(ids::Denominator, AttributeSet({ids::Listable, ids::Protected}) )
				(ids::Replace, AttributeSet({ids::Protected}) );

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


