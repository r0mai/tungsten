
#ifndef EVAL_ITERATIONSPECIFIER_HPP_
#define EVAL_ITERATIONSPECIFIER_HPP_

#include <vector>

#include <boost/variant.hpp>
#include <boost/optional.hpp>

#include "ast/Node.hpp"
#include "eval/SessionEnvironment.hpp"

namespace tungsten { namespace eval {

namespace detail {

struct MinMaxIteration {
	MinMaxIteration();
	MinMaxIteration(const ast::Node& min, const ast::Node& max, const ast::Node& step);

	ast::Node min, max, step;
};

struct ListIteration {
	ListIteration();
	ListIteration(const std::vector<ast::Node>& iterationValues);

	std::vector<ast::Node> iterationValues;
};

} //namespace detail

class IterationSpecifier {
public:
	class Iterator {
	public:
		Iterator();
		Iterator(const std::vector<ast::Node>& iterationValues);

		ast::Node current() const;
		bool isEnd() const;
		void advance();

	private:
		unsigned currentIndex;
		std::vector<ast::Node> iterationValues;
	};

	static boost::optional<IterationSpecifier> fromNode(const ast::Node& node, SessionEnvironment& sessionEnvironment);

	bool hasVariable() const;
	ast::Identifier getVariable() const;

	bool isFinite() const;
	//Can be expensive, precondition: isFinite()
	Iterator makeIterator() const;

private:
	IterationSpecifier();

	typedef boost::variant<detail::MinMaxIteration, detail::ListIteration> IterationStorage;
	typedef boost::optional<ast::Identifier> OptionalVariable;

	OptionalVariable optionalVariable;
	IterationStorage iteration;
};

}} //namespace tungsten::eval

#endif /* EVAL_ITERATIONSPECIFIER_HPP_ */
