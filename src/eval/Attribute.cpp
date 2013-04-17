
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
				(ids::Factorial, AttributeSet({ids::Listable, ids::NumericFunction, ids::Protected}) )
				(ids::Factorial2, AttributeSet({ids::Listable, ids::NumericFunction, ids::Protected}) )
				(ids::Sin, AttributeSet({ids::Listable, ids::NumericFunction, ids::Protected}) )
				(ids::Cos, AttributeSet({ids::Listable, ids::NumericFunction, ids::Protected}) )
				(ids::Tan, AttributeSet({ids::Listable, ids::NumericFunction, ids::Protected}) )
				(ids::Cot, AttributeSet({ids::Listable, ids::NumericFunction, ids::Protected}) )
				(ids::Sec, AttributeSet({ids::Listable, ids::NumericFunction, ids::Protected}) )
				(ids::Csc, AttributeSet({ids::Listable, ids::NumericFunction, ids::Protected}) )
				(ids::Sqrt, AttributeSet({ids::Listable, ids::NumericFunction, ids::Protected}) )
				(ids::Rule, AttributeSet({ids::SequenceHold, ids::Protected}) )
				(ids::RuleDelayed, AttributeSet({ids::HoldRest, ids::SequenceHold, ids::Protected}) )
				(ids::Sort, AttributeSet({ids::Protected}) )
				(ids::Plot, AttributeSet({ids::HoldAll, ids::Protected}) )
				(ids::Evaluate, AttributeSet({ids::Protected}) )
				(ids::N, AttributeSet({ids::Protected}) )
				(ids::NumericQ, AttributeSet({ids::Protected}) )
				(ids::OrderedQ, AttributeSet({ids::Protected}) )
				(ids::Function, AttributeSet({ids::HoldAll, ids::Protected}) )
				(ids::Less, AttributeSet({ids::Protected}) )
				(ids::Greater, AttributeSet({ids::Protected}) )
				(ids::LessEqual, AttributeSet({ids::Protected}) )
				(ids::GreaterEqual, AttributeSet({ids::Protected}) )
				(ids::Equal, AttributeSet({ids::Protected}) )
				(ids::Unequal, AttributeSet({ids::Protected}) )
				(ids::If, AttributeSet({ids::HoldRest, ids::Protected}) )
				(ids::Slot, AttributeSet({ids::NHoldAll, ids::Protected}) )
				(ids::TrueQ, AttributeSet({ids::Protected}) )
				(ids::Not, AttributeSet({ids::Protected}) )
				(ids::And, AttributeSet({ids::Flat, ids::HoldAll, ids::OneIdentity, ids::Protected}) )
				(ids::Or, AttributeSet({ids::Flat, ids::HoldAll, ids::OneIdentity, ids::Protected}) )
				(ids::Boole, AttributeSet({ids::Listable, ids::Protected}) )
				(ids::While, AttributeSet({ids::HoldAll, ids::Protected}) )
				(ids::Attributes, AttributeSet({ids::HoldAll, ids::Listable, ids::Protected}) )
				(ids::CompoundExpression, AttributeSet({ids::HoldAll, ids::Protected, ids::ReadProtected}) )
				(ids::Flatten, AttributeSet({ids::Protected}) )
				(ids::ArcSin, AttributeSet({ids::Listable, ids::NumericFunction, ids::Protected, ids::ReadProtected}) )
				(ids::ArcCos, AttributeSet({ids::Listable, ids::NumericFunction, ids::Protected, ids::ReadProtected}) )
				(ids::ArcTan, AttributeSet({ids::Listable, ids::NumericFunction, ids::Protected, ids::ReadProtected}) )
				(ids::Print, AttributeSet({ids::Protected}) )
				(ids::Part, AttributeSet({ids::NHoldRest, ids::Protected, ids::ReadProtected}) )
				(ids::Floor, AttributeSet({ids::Listable, ids::NumericFunction, ids::Protected}) )
				(ids::Ceiling, AttributeSet({ids::Listable, ids::NumericFunction, ids::Protected}) )
				(ids::Round, AttributeSet({ids::Listable, ids::NumericFunction, ids::Protected}) )
				(ids::IntegerPart, AttributeSet({ids::Listable, ids::NumericFunction, ids::Protected}) )
				(ids::FractionalPart, AttributeSet({ids::Listable, ids::NumericFunction, ids::Protected}) )
				(ids::Hold, AttributeSet({ids::HoldAll, ids::Protected}) );

	return AttributeMap(attributeStorage);
}

AttributeMap::AttributeMap() {}

AttributeMap::AttributeMap(const AttributeStorage& attributeStorage) :
		attributeStorage(attributeStorage) {}

AttributeSet AttributeMap::getAttributeSet(const ast::Identifier& identifier) const {
	AttributeStorage::const_iterator it = attributeStorage.find( identifier );

	if ( it == attributeStorage.end() ) {
		return AttributeSet{};
	}

	return it->second;
}

bool AttributeMap::hasAttribute(const ast::Identifier& identifier, const Attribute& attribute) const {
	AttributeStorage::const_iterator it = attributeStorage.find( identifier );

	return it != attributeStorage.end() && it->second.count( attribute ) > 0;
}

void AttributeMap::addAttribute(const ast::Identifier& identifier, const Attribute& attribute) {
	attributeStorage[identifier].insert( attribute );
}

}} //namespace tungsten::eval


