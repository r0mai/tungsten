
#ifndef EVAL_FUNCTIONOPTIONS_HPP_
#define EVAL_FUNCTIONOPTIONS_HPP_

#include <map>

#include "ast/Node.hpp"

namespace tungsten { namespace eval {

/*
 * Represents OptionsPattern[]
 * f[..., x->y, a->b]
 *
 * FunctionOptions map stores (Identifer, Node) pairs
 */

typedef std::map<ast::Identifier, ast::Node> IdentifierNodeMap;

class FunctionOptions {
public:
	FunctionOptions() = default;
	FunctionOptions(const IdentifierNodeMap& identifierNodeMap);

	/*
	 * Overwrites any existing options
	 * TODO look into exactly what should happen with duplicates and defaults
	 * Returns false if [begin, end) range cannot be matched by an OptionPattern[]
	 */
	bool addFromNodeRange(ast::Operands::const_iterator begin, ast::Operands::const_iterator end);
	/*
	 * Overwrites any existing options
	 * Note: node can be a List, in which case every List element is added to the FunctionOptions
	 */
	bool addFromNode(const ast::Node& node);

	bool hasOption(const ast::Identifier& key) const;
	const ast::Node& getOption(const ast::Identifier& key) const;
private:
	IdentifierNodeMap identifierNodeMap;
};

}} //namespace tungsten::eval

#endif /* EVAL_FUNCTIONOPTIONS_HPP_ */
