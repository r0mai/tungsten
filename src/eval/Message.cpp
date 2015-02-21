
#include "Message.hpp"
#include "io/NodeToInputForm.hpp"
#include "Identifiers.hpp"

#include <boost/assign/list_of.hpp>

namespace tungsten { namespace eval {

Message::Message(const ast::Identifier& symbol, const ast::String& tag, const ast::Operands& arguments) :
		symbol(symbol), tag(tag), arguments(arguments) {}

Message::Message(const ast::Identifier& symbol, const ast::String& tag, std::initializer_list<ast::Node> arguments) :
		Message(symbol, tag, ast::Operands(arguments)) {}

const ast::Identifier& Message::getSymbol() const {
	return symbol;
}

const ast::String& Message::getTag() const {
	return tag;
}

const ast::Operands& Message::getArguments() const {
	return arguments;
}

ErrorMessageStringMap createErrorMessageStringMap() {
	return boost::assign::map_list_of
		(ids::argm, "%1% called with %2% arguments; %3% or more arguments are expected.")
		(ids::argx, "%1% called with %2% arguments; 1 argument is expected")
		(ids::argrx, "%1% called with %2% arguments; %3% arguments are expected.")
		(ids::argt, "%1% called with %2% arguments; %3% or %4% arguments are expected.")
		(ids::argb, "%1% called with %2% arguments; between %3% and %4% arguments are expected.")
		(ids::argbu, "%1% called with 1 argument; between %2% and %3% arguments are expected.")
		(ids::infy, "Infinite expression %1% encountered.")
		(ids::indet, "Indeterminate expression %1% encountered.")
		(ids::ovfl, "Overflow occurred in computation.")
		(ids::tdlen, "Objects of unequal length in %1% cannot be combined.")
		(ids::itform, "Argument %1% at position %2% does not have the correct form for an iterator.")
		(ids::iterb, "Iterator %1% does not have appropriate bounds.")
		(ids::normal, "Nonatomic expression expected at position %1% in %2%.")
		(ids::flev, "The level argument %1% in position %2% of %3% should be a non-negative integer or Infinity giving the levels to flatten through or a list of lists of levels to flatten together.")
		(ids::slot, "%1% (in %2%) should contain a non-negative integer.")
		(ids::fdargs, "The argument %1% in %2% is not supported.")
		(ids::ssle, "Symbol, string, or HoldPattern[symbol] expected at position %2% in %1%.")
		(ids::pspec, "Part specification %1% is neither an integer nor a list of integers.")
		(ids::partd, "Part specification %1% is longer than depth of object.")
		(ids::partw, "Part %1% of %2% does not exist.")
		(ids::lvlist, "Local variable specification %1% is not a List.")
		(ids::lvsym, "Local variable specification %1% contains %2%, which is not a symbol or an assignment to a symbol.")
		(ids::lvset, "Local variable specification %1% contains %2%, which is an assignment to %3%; only assignments to symbols are allowed.")
		(ids::patvar, "First element in pattern %1% is not a valid pattern name.")
		(ids::rmix, "Elements of %1% are a mixture of lists and nonlists.")
		(ids::reps, "%1% is neither a list of replacement rules nor a valid dispatch table, and so cannot be used for replacing.")
		(ids::string, "String expected at position %1% in %2%.")
		(ids::mseqs, "Sequence specification (+n, -n, {+n}, {-n}, {m, n}, or {m, n, s}) or a list of sequence specifications expected at position %2% in %1%.")
		(ids::strse, "String or list of strings expected at position %1% in %2%.")
		(ids::drop, "Cannot drop positions %1% through %2% in \"%3%\".")
		(ids::take, "Cannot take positions %1% through %2% in \"%3%\".");
}

}} //namespace tungsten::eval




