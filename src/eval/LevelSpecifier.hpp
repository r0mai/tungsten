
#ifndef EVAL_LEVELSPECIFIER_HPP_
#define EVAL_LEVELSPECIFIER_HPP_

#include <utility>
#include <boost/optional.hpp>

#include "ast/Node.hpp"

namespace tungsten { namespace eval {

typedef long Depth;

class LevelSpecifier {
public:
	LevelSpecifier();
	LevelSpecifier(const Depth& min, const Depth& max);

	static boost::optional<LevelSpecifier> fromNode(const ast::Node& node);


	//In case of Infinities, std::numeric_limits<Depth>::{min,max} is used
	Depth min;
	Depth max;
};

}} //namespace tungsten::eval

#endif /* EVAL_LEVELSPECIFIER_HPP_ */
