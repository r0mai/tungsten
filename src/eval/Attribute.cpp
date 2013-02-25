
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
				(ids::Replace, AttributeSet({ids::Protected}) )
				(ids::Set, AttributeSet({ids::HoldFirst, ids::Protected, ids::SequenceHold}) )
				(ids::SetDelayed, AttributeSet({ids::HoldAll, ids::Protected, ids::SequenceHold}) )
				(ids::RandomReal, AttributeSet({ids::Protected}) )
				(ids::Divide, AttributeSet({ids::Listable, ids::NumericFunction, ids::Protected}) )
				(ids::Head, AttributeSet({ids::Protected}) )
				(ids::Table, AttributeSet({ids::HoldAll, ids::Protected}) )
				(ids::Table, AttributeSet({ids::HoldAll, ids::Protected, ids::ReadProtected}) )
				(ids::Minus, AttributeSet({ids::Listable, ids::NumericFunction, ids::Protected}) )
				(ids::Subtract, AttributeSet({ids::Listable, ids::NumericFunction, ids::Protected}) )
				(ids::Apply, AttributeSet({ids::Protected}) )
				(ids::Sin, AttributeSet({ids::Listable, ids::NumericFunction, ids::Protected}) )
				(ids::Cos, AttributeSet({ids::Listable, ids::NumericFunction, ids::Protected}) )
				(ids::Tan, AttributeSet({ids::Listable, ids::NumericFunction, ids::Protected}) )
				(ids::Cot, AttributeSet({ids::Listable, ids::NumericFunction, ids::Protected}) )
				(ids::Sec, AttributeSet({ids::Listable, ids::NumericFunction, ids::Protected}) )
				(ids::Csc, AttributeSet({ids::Listable, ids::NumericFunction, ids::Protected}) );

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


