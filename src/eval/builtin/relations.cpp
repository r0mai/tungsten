
#include "functions.hpp"

namespace tungsten { namespace eval { namespace builtin {

OptionalNode Less(const ast::Operands& operands, eval::SessionEnvironment& /*sessionEnvironment*/) {

	for ( unsigned i = 1; i < operands.size(); ++i ) {
		 if ( !operands[i-1].isNumeric() || !operands[i].isNumeric() ) {
			 return ast::Node::make<ast::FunctionCall>(ids::Less, operands);
		 }
		 if ( operands[i-1].getNumeric() >= operands[i].getNumeric() ) {
			 return ast::Node::make<ast::Identifier>(ids::False);
		 }
	}

	return ast::Node::make<ast::Identifier>(ids::True);
}

OptionalNode LessEqual(const ast::Operands& operands, eval::SessionEnvironment& /*sessionEnvironment*/) {

	for ( unsigned i = 1; i < operands.size(); ++i ) {
		 if ( !operands[i-1].isNumeric() || !operands[i].isNumeric() ) {
			 return ast::Node::make<ast::FunctionCall>(ids::Less, operands);
		 }
		 if ( operands[i-1].getNumeric() > operands[i].getNumeric() ) {
			 return ast::Node::make<ast::Identifier>(ids::False);
		 }
	}

	return ast::Node::make<ast::Identifier>(ids::True);
}


OptionalNode Greater(const ast::Operands& operands, eval::SessionEnvironment& /*sessionEnvironment*/) {

	for ( unsigned i = 1; i < operands.size(); ++i ) {
		 if ( !operands[i-1].isNumeric() || !operands[i].isNumeric() ) {
			 return ast::Node::make<ast::FunctionCall>(ids::Less, operands);
		 }
		 if ( operands[i-1].getNumeric() <= operands[i].getNumeric() ) {
			 return ast::Node::make<ast::Identifier>(ids::False);
		 }
	}

	return ast::Node::make<ast::Identifier>(ids::True);
}


OptionalNode GreaterEqual(const ast::Operands& operands, eval::SessionEnvironment& /*sessionEnvironment*/) {

	for ( unsigned i = 1; i < operands.size(); ++i ) {
		 if ( !operands[i-1].isNumeric() || !operands[i].isNumeric() ) {
			 return ast::Node::make<ast::FunctionCall>(ids::Less, operands);
		 }
		 if ( operands[i-1].getNumeric() > operands[i].getNumeric() ) {
			 return ast::Node::make<ast::Identifier>(ids::False);
		 }
	}

	return ast::Node::make<ast::Identifier>(ids::True);
}


}}}; // tungsten::eval::builtin;
