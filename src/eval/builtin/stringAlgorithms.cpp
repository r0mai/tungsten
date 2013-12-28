
#include <vector>

#include "functions.hpp"

#include "eval/SessionEnvironment.hpp"
#include "math/Integer.hpp"

namespace tungsten { namespace eval { namespace builtin {

typedef std::vector<ast::String> StringVector;

boost::optional<StringVector> parseStringOrStringList(const ast::Node& node) {
	if ( node.is<ast::String>() ) {
		return StringVector{ node.get<ast::String>() };
	}

	if ( !node.isFunctionCall(ids::List) ) {
		return boost::none_t{};
	}

	const ast::Operands& operands = node.get<ast::FunctionCall>().getOperands();

	StringVector result;
	result.reserve(operands.size());

	for ( const ast::Node& operand : operands ) {
		if ( !operand.is<ast::String>() ) {
			return boost::none_t{};
		}
		result.push_back(operand.get<ast::String>());
	}

	return result;
}

//represents n
struct SingleSequence {
	SingleSequence() = default;
	SingleSequence(int index) : index(index) {}
	int index;
};

//represents {n}, {m, n}, {m, n, s}
struct ThroughSequence {
	ThroughSequence() = default;
	ThroughSequence(int min, int max, int step) : min(min), max(max), step(step) {}
	int min, max, step;
};

typedef boost::variant<SingleSequence, ThroughSequence> SequenceSpecificationVariant;

boost::optional<SequenceSpecificationVariant> parseSequenceSpecification(const ast::Node& node) {
	if ( node.isInteger() ) {
		math::Integer index = node.getInteger();
		if ( !math::fits<int>(index) ) {
			return boost::none_t{};
		}
		return SequenceSpecificationVariant{SingleSequence(math::as<int>(index))};
	}

	if ( node.isFunctionCall(ids::List) ) {
		const ast::Operands& operands = node.get<ast::FunctionCall>().getOperands();
		if ( operands.size() < 1 || operands.size() > 3 ) {
			return boost::none_t{};
		}

		std::vector<int> intOperands;
		intOperands.reserve(operands.size());

		for ( const ast::Node& node : operands ) {
			if ( !node.isInteger() ) {
				return boost::none_t{};
			}
			math::Integer nodeInteger = node.getInteger();
			if ( !math::fits<int>(nodeInteger) ) {
				return boost::none_t{};
			}
			intOperands.push_back(math::as<int>(nodeInteger));
		}

		switch (intOperands.size()) {
		default:
			assert(false);
		case 1:
			return SequenceSpecificationVariant{ThroughSequence{intOperands[0], intOperands[0], 1}};
		case 2:
			return SequenceSpecificationVariant{ThroughSequence{intOperands[0], intOperands[1], 1}};
		case 3:
			return SequenceSpecificationVariant{ThroughSequence{intOperands[0], intOperands[1], intOperands[2]}};
		}
	}

	return boost::none_t{};
}

OptionalNode StringLength(const ast::Operands& operands, eval::SessionEnvironment& sessionEnvironment) {
	if ( operands.size() != 1 ) {
		sessionEnvironment.raiseMessage( Message(ids::StringLength, ids::argx, {
				ast::Node::make<ast::Identifier>( ids::StringLength ),
				ast::Node::make<math::Rational>( operands.size() )
		} ));
		return EvaluationFailure();
	}
	const ast::Node& operand = operands.front();

	if ( !operand.is<ast::String>() ) {
		sessionEnvironment.raiseMessage( Message(ids::StringLength, ids::string, {
				ast::Node::make<math::Rational>( 1 ),
				ast::Node::make<ast::FunctionCall>( ids::StringLength, operands )
		} ));
		return EvaluationFailure();
	}

	const ast::String& string = operand.get<ast::String>();
	return ast::Node::make<math::Rational>(string.length());
}

OptionalNode Characters(const ast::Operands& operands, eval::SessionEnvironment& sessionEnvironment) {
	if ( operands.size() != 1 ) {
		sessionEnvironment.raiseMessage( Message(ids::Characters, ids::argx, {
				ast::Node::make<ast::Identifier>( ids::Characters ),
				ast::Node::make<math::Rational>( operands.size() )
		} ));
		return EvaluationFailure();
	}
	const ast::Node& operand = operands.front();

	if ( !operand.is<ast::String>() ) {
		return ast::Node::make<ast::FunctionCall>(ids::Characters, operands);
	}

	const ast::String& string = operand.get<ast::String>();
	ast::Operands resultOperands;
	resultOperands.reserve(string.size());

	for ( char ch : string ) {
		resultOperands.push_back( ast::Node::make<ast::String>(1, ch) );
	}

	return ast::Node::make<ast::FunctionCall>(ids::List, std::move(resultOperands));
}

OptionalNode StringJoin(const ast::Operands& operands, eval::SessionEnvironment& sessionEnvironment) {
	//TODO this actually should do some joining even if some operands are not Strings
	bool failed = false;
	std::size_t i = 1;
	for ( const ast::Node& operand : operands ) {
		if ( !operand.is<ast::String>() ) {
			sessionEnvironment.raiseMessage( Message(ids::StringReverse, ids::string, {
					ast::Node::make<math::Rational>( i ),
					ast::Node::make<ast::FunctionCall>( ids::StringReverse, operands )
			} ));
			failed = true;
		}
		++i;
	}

	if ( failed ) {
		return EvaluationFailure();
	}

	ast::String result;

	for ( const ast::Node& operand : operands ) {
		result += operand.get<ast::String>();
	}
	return ast::Node::make<ast::String>(result);
}

OptionalNode StringInsert(const ast::Operands& operands, eval::SessionEnvironment& sessionEnvironment) {
	return EvaluationFailure();
}

OptionalNode StringDrop(const ast::Operands& operands, eval::SessionEnvironment& sessionEnvironment) {
	return EvaluationFailure();
}

OptionalNode StringTake(const ast::Operands& operands, eval::SessionEnvironment& sessionEnvironment) {
	return EvaluationFailure();
}

OptionalNode StringReverse(const ast::Operands& operands, eval::SessionEnvironment& sessionEnvironment) {
	if ( operands.size() != 1 ) {
		sessionEnvironment.raiseMessage( Message(ids::StringReverse, ids::argx, {
				ast::Node::make<ast::Identifier>( ids::StringReverse ),
				ast::Node::make<math::Rational>( operands.size() )
		} ));
		return EvaluationFailure();
	}
	const ast::Node& operand = operands.front();

	if ( !operand.is<ast::String>() ) {
		sessionEnvironment.raiseMessage( Message(ids::StringReverse, ids::string, {
				ast::Node::make<math::Rational>( 1 ),
				ast::Node::make<ast::FunctionCall>( ids::StringReverse, operands )
		} ));
		return EvaluationFailure();
	}

	ast::String string = operand.get<ast::String>();
	std::reverse(string.begin(), string.end());
	return ast::Node::make<ast::String>(string);
}

}}} //namespace tungsten::eval::builtin

