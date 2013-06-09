
#include "Attribute.hpp"
#include "Identifiers.hpp"

#include <boost/assign/list_of.hpp>

namespace tungsten { namespace eval {

AttributeMap AttributeMap::makeDefault() {
	AttributeStorage attributeStorage = boost::assign::map_list_of
		(ids::List, AttributeSet({ids::Locked, ids::Protected}))
		(ids::Plus, AttributeSet({ids::Flat, ids::Listable, ids::NumericFunction, ids::OneIdentity, ids::Orderless, ids::Protected}))
		(ids::Times, AttributeSet({ids::Flat, ids::Listable, ids::NumericFunction, ids::OneIdentity, ids::Orderless, ids::Protected}))
		(ids::Power, AttributeSet({ids::Listable, ids::NumericFunction, ids::OneIdentity, ids::Protected}))
		(ids::Abs, AttributeSet({ids::Listable, ids::NumericFunction, ids::Protected}))
		(ids::Divide, AttributeSet({ids::Listable, ids::NumericFunction, ids::Protected}))
		(ids::Numerator, AttributeSet({ids::Listable, ids::Protected}))
		(ids::Denominator, AttributeSet({ids::Listable, ids::Protected}))
		(ids::Replace, AttributeSet({ids::Protected}))
		(ids::Set, AttributeSet({ids::HoldFirst, ids::Protected, ids::SequenceHold}))
		(ids::SetDelayed, AttributeSet({ids::HoldAll, ids::Protected, ids::SequenceHold}))
		(ids::RandomReal, AttributeSet({ids::Protected}))
		(ids::DirectedInfinity, AttributeSet({ids::Listable, ids::Protected, ids::ReadProtected}))
		(ids::Overflow, AttributeSet({ids::Protected}))
		(ids::Thread, AttributeSet({ids::Protected}))
		(ids::Pattern, AttributeSet({ids::HoldFirst, ids::Protected}))
		(ids::Blank, AttributeSet({ids::Protected}))
		(ids::Integer, AttributeSet({ids::Protected}))
		(ids::Rational, AttributeSet({ids::Protected}))
		(ids::Real, AttributeSet({ids::Protected}))
		(ids::String, AttributeSet({ids::Protected}))
		(ids::Symbol, AttributeSet({ids::Locked, ids::Protected}))
		(ids::Head, AttributeSet({ids::Protected}))
		(ids::Table, AttributeSet({ids::HoldAll, ids::Protected}))
		(ids::CompoundExpression, AttributeSet({ids::HoldAll, ids::Protected, ids::ReadProtected}))
		(ids::Minus, AttributeSet({ids::Listable, ids::NumericFunction, ids::Protected}))
		(ids::Subtract, AttributeSet({ids::Listable, ids::NumericFunction, ids::Protected}))
		(ids::Apply, AttributeSet({ids::Protected}))
		(ids::Sin, AttributeSet({ids::Listable, ids::NumericFunction, ids::Protected}))
		(ids::Cos, AttributeSet({ids::Listable, ids::NumericFunction, ids::Protected}))
		(ids::Tan, AttributeSet({ids::Listable, ids::NumericFunction, ids::Protected}))
		(ids::Cot, AttributeSet({ids::Listable, ids::NumericFunction, ids::Protected}))
		(ids::Csc, AttributeSet({ids::Listable, ids::NumericFunction, ids::Protected}))
		(ids::Sec, AttributeSet({ids::Listable, ids::NumericFunction, ids::Protected}))
		(ids::ArcSin, AttributeSet({ids::Listable, ids::NumericFunction, ids::Protected, ids::ReadProtected}))
		(ids::ArcCos, AttributeSet({ids::Listable, ids::NumericFunction, ids::Protected, ids::ReadProtected}))
		(ids::ArcTan, AttributeSet({ids::Listable, ids::NumericFunction, ids::Protected, ids::ReadProtected}))
		(ids::ArcCot, AttributeSet({ids::Listable, ids::NumericFunction, ids::Protected, ids::ReadProtected}))
		(ids::ArcCsc, AttributeSet({ids::Listable, ids::NumericFunction, ids::Protected, ids::ReadProtected}))
		(ids::ArcSec, AttributeSet({ids::Listable, ids::NumericFunction, ids::Protected, ids::ReadProtected}))
		(ids::Factorial, AttributeSet({ids::Listable, ids::NumericFunction, ids::Protected}))
		(ids::Factorial2, AttributeSet({ids::Listable, ids::NumericFunction, ids::Protected}))
		(ids::Sqrt, AttributeSet({ids::Listable, ids::NumericFunction, ids::Protected}))
		(ids::Rule, AttributeSet({ids::Protected, ids::SequenceHold}))
		(ids::RuleDelayed, AttributeSet({ids::HoldRest, ids::Protected, ids::SequenceHold}))
		(ids::Flatten, AttributeSet({ids::Protected}))
		(ids::Sort, AttributeSet({ids::Protected}))
		(ids::Normal, AttributeSet({ids::Protected}))
		(ids::Sequence, AttributeSet({ids::Protected}))
		(ids::Evaluate, AttributeSet({ids::Protected}))
		(ids::N, AttributeSet({ids::Protected}))
		(ids::NumericQ, AttributeSet({ids::Protected}))
		(ids::Complex, AttributeSet({ids::Protected}))
		(ids::OrderedQ, AttributeSet({ids::Protected}))
		(ids::Function, AttributeSet({ids::HoldAll, ids::Protected}))
		(ids::Slot, AttributeSet({ids::NHoldAll, ids::Protected}))
		(ids::SlotSequence, AttributeSet({ids::NHoldAll, ids::Protected}))
		(ids::Equal, AttributeSet({ids::Protected}))
		(ids::Unequal, AttributeSet({ids::Protected}))
		(ids::Less, AttributeSet({ids::Protected}))
		(ids::LessEqual, AttributeSet({ids::Protected}))
		(ids::Greater, AttributeSet({ids::Protected}))
		(ids::GreaterEqual, AttributeSet({ids::Protected}))
		(ids::If, AttributeSet({ids::HoldRest, ids::Protected}))
		(ids::TrueQ, AttributeSet({ids::Protected}))
		(ids::And, AttributeSet({ids::Flat, ids::HoldAll, ids::OneIdentity, ids::Protected}))
		(ids::Or, AttributeSet({ids::Flat, ids::HoldAll, ids::OneIdentity, ids::Protected}))
		(ids::Not, AttributeSet({ids::Protected}))
		(ids::Boole, AttributeSet({ids::Listable, ids::Protected}))
		(ids::While, AttributeSet({ids::HoldAll, ids::Protected}))
		(ids::Attributes, AttributeSet({ids::HoldAll, ids::Listable, ids::Protected}))
		(ids::Print, AttributeSet({ids::Protected}))
		(ids::Part, AttributeSet({ids::NHoldRest, ids::Protected, ids::ReadProtected}))
		(ids::Span, AttributeSet({ids::Protected}))
		(ids::Floor, AttributeSet({ids::Listable, ids::NumericFunction, ids::Protected}))
		(ids::Ceiling, AttributeSet({ids::Listable, ids::NumericFunction, ids::Protected}))
		(ids::Round, AttributeSet({ids::Listable, ids::NumericFunction, ids::Protected}))
		(ids::IntegerPart, AttributeSet({ids::Listable, ids::NumericFunction, ids::Protected}))
		(ids::FractionalPart, AttributeSet({ids::Listable, ids::NumericFunction, ids::Protected}))
		(ids::Hold, AttributeSet({ids::HoldAll, ids::Protected}))
		(ids::Append, AttributeSet({ids::Protected}))
		(ids::AppendTo, AttributeSet({ids::HoldFirst, ids::Protected}))
		(ids::Prepend, AttributeSet({ids::Protected}))
		(ids::PrependTo, AttributeSet({ids::HoldFirst, ids::Protected}))
		(ids::Length, AttributeSet({ids::Protected}))
		(ids::HoldComplete, AttributeSet({ids::HoldAllComplete, ids::Protected}))
		(ids::Plot, AttributeSet({ids::HoldAll, ids::Protected}))
		(ids::Graphics, AttributeSet({ids::Protected, ids::ReadProtected}))
		(ids::Export, AttributeSet({ids::Protected, ids::ReadProtected}))
		(ids::Circle, AttributeSet({ids::Protected, ids::ReadProtected}))
		(ids::Rectangle, AttributeSet({ids::Protected, ids::ReadProtected}))
		(ids::Red, AttributeSet({ids::Protected}))
		(ids::Hue, AttributeSet({ids::Protected, ids::ReadProtected}))
		(ids::Blue, AttributeSet({ids::Protected}))
		(ids::Green, AttributeSet({ids::Protected}))
		(ids::Black, AttributeSet({ids::Protected}))
		(ids::White, AttributeSet({ids::Protected}))
		(ids::None, AttributeSet({ids::Protected}))
		(ids::RGBColor, AttributeSet({ids::Protected, ids::ReadProtected}))
		(ids::Gray, AttributeSet({ids::Protected}))
		(ids::Magenta, AttributeSet({ids::Protected}))
		(ids::Yellow, AttributeSet({ids::Protected}))
		(ids::Cyan, AttributeSet({ids::Protected}))
		(ids::Brown, AttributeSet({ids::Protected}))
		(ids::Orange, AttributeSet({ids::Protected}))
		(ids::Pink, AttributeSet({ids::Protected}))
		(ids::Purple, AttributeSet({ids::Protected}))
		(ids::Thick, AttributeSet({ids::Protected, ids::ReadProtected}))
		(ids::Thin, AttributeSet({ids::Protected, ids::ReadProtected}))
		(ids::Thickness, AttributeSet({ids::Protected, ids::ReadProtected}))
		(ids::Disk, AttributeSet({ids::Protected, ids::ReadProtected}))
		(ids::Line, AttributeSet({ids::Protected, ids::ReadProtected}))
		(ids::Point, AttributeSet({ids::Protected, ids::ReadProtected}))
		(ids::BezierCurve, AttributeSet({ids::Protected, ids::ReadProtected}))
		(ids::Arrow, AttributeSet({ids::Protected, ids::ReadProtected}))
		(ids::Polygon, AttributeSet({ids::Protected, ids::ReadProtected}))
		(ids::E, AttributeSet({ids::Constant, ids::Protected, ids::ReadProtected}))
		(ids::Pi, AttributeSet({ids::Constant, ids::Protected, ids::ReadProtected}))
		(ids::Degree, AttributeSet({ids::Constant, ids::Protected, ids::ReadProtected}))
		(ids::GoldenRatio, AttributeSet({ids::Constant, ids::Protected}))
		(ids::EulerGamma, AttributeSet({ids::Constant, ids::Protected}))
		(ids::Catalan, AttributeSet({ids::Constant, ids::Protected}))
		(ids::Khinchin, AttributeSet({ids::Constant, ids::Protected}))
		(ids::I, AttributeSet({ids::Locked, ids::Protected, ids::ReadProtected}))
		(ids::Glaisher, AttributeSet({ids::Constant, ids::Protected}))
		(ids::Null, AttributeSet({ids::Protected}))
		(ids::Infinity, AttributeSet({ids::Protected, ids::ReadProtected}))
		(ids::Indeterminate, AttributeSet({ids::Protected}))
		(ids::True, AttributeSet({ids::Locked, ids::Protected}))
		(ids::False, AttributeSet({ids::Locked, ids::Protected}))
		(ids::Flat, AttributeSet({ids::Protected}))
		(ids::Listable, AttributeSet({ids::Protected}))
		(ids::NumericFunction, AttributeSet({ids::Protected}))
		(ids::OneIdentity, AttributeSet({ids::Protected}))
		(ids::Orderless, AttributeSet({ids::Protected}))
		(ids::Protected, AttributeSet({ids::Protected}))
		(ids::ReadProtected, AttributeSet({ids::Protected}))
		(ids::SequenceHold, AttributeSet({ids::Protected}))
		(ids::HoldFirst, AttributeSet({ids::Protected}))
		(ids::HoldRest, AttributeSet({ids::Protected}))
		(ids::HoldAll, AttributeSet({ids::Protected}))
		(ids::NHoldAll, AttributeSet({ids::Protected}))
		(ids::NHoldFirst, AttributeSet({ids::Protected}))
		(ids::NHoldRest, AttributeSet({ids::Protected}))
		(ids::HoldAllComplete, AttributeSet({ids::Protected}))
		(ids::General, AttributeSet({ids::Protected}))
		(ids::Syntax, AttributeSet({ids::Protected}))
		(ids::Range, AttributeSet({ids::Listable, ids::Protected}))
		(ids::Block, AttributeSet({ids::HoldAll, ids::Protected}))
		(ids::Map, AttributeSet({ids::Protected}))
		(ids::Sum, AttributeSet({ids::HoldAll, ids::Protected}))
		(ids::MatchQ, AttributeSet({ids::Protected}))
		(ids::PatternTest, AttributeSet({ids::HoldRest, ids::Protected}))
		(ids::HoldPattern, AttributeSet({ids::HoldAll, ids::Protected}))
		(ids::ReplaceAll, AttributeSet({ids::Protected}));

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


