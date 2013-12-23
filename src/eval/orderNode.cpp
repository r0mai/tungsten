
#include "orderNode.hpp"

#include <algorithm>
#include <map>
#include <cctype>

#include <boost/algorithm/string/predicate.hpp>

#include "Identifiers.hpp"

namespace tungsten { namespace eval {

template<class T> struct NodeTypeToInt;

template<> struct NodeTypeToInt<math::Rational> {
	static const int value = 1;
};
template<> struct NodeTypeToInt<math::Real> {
	static const int value = 2;
};
template<> struct NodeTypeToInt<ast::String> {
	static const int value = 3;
};
template<> struct NodeTypeToInt<ast::Identifier> {
	static const int value = 4;
};
template<> struct NodeTypeToInt<ast::FunctionCall> {
	static const int value = 5;
};

//TODO COEFFsd ../../

//<base, exponent>
typedef std::map<ast::Node, ast::Node, NodeComparatorLess> BaseExponentMap;

BaseExponentMap toBaseExponentMap_powerOperands(const ast::Operands& powerOperands) {

	BaseExponentMap result;

	if ( powerOperands.size() != 2 ) {
		//We can't really allow ourselves to do the job of Power[] here
		result[ast::Node::make<ast::FunctionCall>(ids::Power, powerOperands)] = ast::Node::make<math::Rational>(1);
	} else {
		result[powerOperands[0]] = powerOperands[1];
	}

	return result;
}

BaseExponentMap toBaseExponentMap_timesOperands(const ast::Operands& timesOperands) {

	BaseExponentMap result;

	for ( const ast::Node& node : timesOperands ) {
		if ( node.isFunctionCall(ids::Power) ) {

			const ast::Operands& powerOperands = node.get<ast::FunctionCall>().getOperands();

			//FIXME Same code as above
			if ( powerOperands.size() != 2 ) {
				result[ast::Node::make<ast::FunctionCall>(ids::Power, powerOperands)] = ast::Node::make<math::Rational>(1);
			} else {
				result[powerOperands[0]] = powerOperands[1];
			}
		} else {
			result[node] = ast::Node::make<math::Rational>(1);
		}
	}

	return result;
}

template<class T>
BaseExponentMap toBaseExponentMap_other(const T& other) {
	BaseExponentMap result;
	result[ast::Node::make<T>(other)] = ast::Node::make<math::Rational>(1);
	return result;
}

std::ostream& operator<<(std::ostream& os, const BaseExponentMap& map) {
	for ( const auto& x : map ) {
		os << x.first << "^" << x.second << "\n";
	}
	return os;
}

void insertDummyCoefficient(BaseExponentMap& baseExponentMap) {
	//Find a coefficient, if there are none, insert a dummy one (1^0) (TODO maybe 1^1?)
	if (
		std::find_if( baseExponentMap.begin(), baseExponentMap.end(),
			[](const BaseExponentMap::value_type& v) {
				return v.first.isNumeric();
			}
		) == baseExponentMap.end() )
	{
		baseExponentMap[ast::Node::make<math::Rational>(1)] = ast::Node::make<math::Rational>(0);
	}
}

//acts as operator<
bool compareBaseExponentMaps(BaseExponentMap lhs, BaseExponentMap rhs) {
	assert( !lhs.empty() && !rhs.empty() );

	insertDummyCoefficient(lhs);
	insertDummyCoefficient(rhs);

	BaseExponentMap::const_reverse_iterator lhsIt = lhs.rbegin();
	BaseExponentMap::const_reverse_iterator rhsIt = rhs.rbegin();

	while (true) {

		if ( lhsIt == lhs.rend() && rhsIt == rhs.rend() ) {
			break;
		}

		if ( lhsIt == lhs.rend() ) {
			return true;
		}

		if ( rhsIt == rhs.rend() ) {
			return false;
		}

		if ( lhsIt->first != rhsIt->first ) {
			return nodeLess(lhsIt->first, rhsIt->first);
		}
		if ( lhsIt->second != rhsIt->second ) {
			return nodeLess(lhsIt->second, rhsIt->second);
		}
		++lhsIt;
		++rhsIt;
	}

	return false;
}

struct NodeLessVisitor : boost::static_visitor<bool> {

	//(String, Identifier), (Identifier, String)
	//(String, Rational), (Rational, String)
	//(String, Real), (Real, String)
	//(Identifier, Rational), (Rational, Identifier)
	//(Identifier, Real), (Real, Identifier)
	//(FunctionCall, Rational), (Rational, FunctionCall)
	//(FunctionCall, Real), (Real, FunctionCall)
	template<class T, class U>
	bool operator()(const T& /*lhs*/, const U& /*rhs*/) const {
		return NodeTypeToInt<T>::value < NodeTypeToInt<U>::value;
	}

	bool operator()(const ast::FunctionCall& lhs, const ast::FunctionCall& rhs) const {
		const ast::Node& lhsFunction = lhs.getFunction();
		const ast::Node& rhsFunction = rhs.getFunction();
		const ast::Operands& lhsOperands = lhs.getOperands();
		const ast::Operands& rhsOperands = rhs.getOperands();

		if (
				lhsFunction.is<ast::Identifier>(ids::Times) ||
				rhsFunction.is<ast::Identifier>(ids::Times) ||
				lhsFunction.is<ast::Identifier>(ids::Power) ||
				rhsFunction.is<ast::Identifier>(ids::Power)
				)
		{
			BaseExponentMap lhsBaseExponentMap;
			BaseExponentMap rhsBaseExponentMap;

			if ( lhsFunction.is<ast::Identifier>(ids::Times) ) {
				lhsBaseExponentMap = toBaseExponentMap_timesOperands( lhsOperands );
			} else if ( lhsFunction.is<ast::Identifier>(ids::Power) ) {
				lhsBaseExponentMap = toBaseExponentMap_powerOperands( lhsOperands );
			} else {
				lhsBaseExponentMap = toBaseExponentMap_other( lhs );
			}

			if ( rhsFunction.is<ast::Identifier>(ids::Times) ) {
				rhsBaseExponentMap = toBaseExponentMap_timesOperands( rhsOperands );
			} else if ( rhsFunction.is<ast::Identifier>(ids::Power) ) {
				rhsBaseExponentMap = toBaseExponentMap_powerOperands( rhsOperands );
			} else {
				rhsBaseExponentMap = toBaseExponentMap_other( rhs );
			}

			return compareBaseExponentMaps( lhsBaseExponentMap, rhsBaseExponentMap );
		} else {
			//default case
			if ( lhsFunction != rhsFunction ) {
				return nodeLess(lhsFunction, rhsFunction);
			}

			if ( lhsOperands.size() != rhsOperands.size() ) {
				return lhsOperands.size() < rhsOperands.size();
			}

			return std::lexicographical_compare( lhsOperands.begin(), lhsOperands.end(), rhsOperands.begin(), rhsOperands.end() );
		}
	}

	bool operator()(const ast::FunctionCall& lhs, const ast::Identifier& rhs) const {
		const ast::Node& lhsFunction = lhs.getFunction();
		const ast::Operands& lhsOperands = lhs.getOperands();

		if ( lhsFunction.is<ast::Identifier>(ids::Times) || lhsFunction.is<ast::Identifier>(ids::Power) ) {

			BaseExponentMap lhsBaseExponentMap;
			BaseExponentMap rhsBaseExponentMap;

			if ( lhsFunction.is<ast::Identifier>(ids::Times) ) {
				lhsBaseExponentMap = toBaseExponentMap_timesOperands( lhsOperands );
			} else {
				assert( lhsFunction.is<ast::Identifier>(ids::Power) );
				lhsBaseExponentMap = toBaseExponentMap_powerOperands( lhsOperands );
			}

			rhsBaseExponentMap = toBaseExponentMap_other( rhs );

			return compareBaseExponentMaps( lhsBaseExponentMap, rhsBaseExponentMap );

		} else {
			return operator()<>(lhs, rhs);
		}
	}

	bool operator()(const ast::Identifier& lhs, const ast::FunctionCall& rhs) const {
		const ast::Node& rhsFunction = rhs.getFunction();
		const ast::Operands& rhsOperands = rhs.getOperands();

		if ( rhsFunction.is<ast::Identifier>(ids::Times) || rhsFunction.is<ast::Identifier>(ids::Power) ) {

			BaseExponentMap lhsBaseExponentMap;
			BaseExponentMap rhsBaseExponentMap;

			lhsBaseExponentMap = toBaseExponentMap_other( lhs );

			if ( rhsFunction.is<ast::Identifier>(ids::Times) ) {
				rhsBaseExponentMap = toBaseExponentMap_timesOperands( rhsOperands );
			} else {
				assert( rhsFunction.is<ast::Identifier>(ids::Power) );
				rhsBaseExponentMap = toBaseExponentMap_powerOperands( rhsOperands );
			}

			return compareBaseExponentMaps( lhsBaseExponentMap, rhsBaseExponentMap );

		} else {
			return operator()<>(lhs, rhs);
		}
	}

	bool operator()(const ast::FunctionCall& lhs, const ast::String& rhs) const {
		const ast::Node& lhsFunction = lhs.getFunction();
		const ast::Operands& lhsOperands = lhs.getOperands();

		if ( lhsFunction.is<ast::Identifier>(ids::Times) || lhsFunction.is<ast::Identifier>(ids::Power) ) {

			BaseExponentMap lhsBaseExponentMap;
			BaseExponentMap rhsBaseExponentMap;

			if ( lhsFunction.is<ast::Identifier>(ids::Times) ) {
				lhsBaseExponentMap = toBaseExponentMap_timesOperands( lhsOperands );
			} else {
				assert( lhsFunction.is<ast::Identifier>(ids::Power) );
				lhsBaseExponentMap = toBaseExponentMap_powerOperands( lhsOperands );
			}

			rhsBaseExponentMap = toBaseExponentMap_other( rhs );

			return compareBaseExponentMaps( lhsBaseExponentMap, rhsBaseExponentMap );

		} else {
			return operator()<>(lhs, rhs);
		}
	}

	bool operator()(const ast::String& lhs, const ast::FunctionCall& rhs) const {
		const ast::Node& rhsFunction = rhs.getFunction();
		const ast::Operands& rhsOperands = rhs.getOperands();

		if ( rhsFunction.is<ast::Identifier>(ids::Times) || rhsFunction.is<ast::Identifier>(ids::Power) ) {

			BaseExponentMap lhsBaseExponentMap;
			BaseExponentMap rhsBaseExponentMap;

			lhsBaseExponentMap = toBaseExponentMap_other( lhs );

			if ( rhsFunction.is<ast::Identifier>(ids::Times) ) {
				rhsBaseExponentMap = toBaseExponentMap_timesOperands( rhsOperands );
			} else {
				assert( rhsFunction.is<ast::Identifier>(ids::Power) );
				lhsBaseExponentMap = toBaseExponentMap_powerOperands( rhsOperands );
			}

			return compareBaseExponentMaps( lhsBaseExponentMap, rhsBaseExponentMap );

		} else {
			return operator()<>(lhs, rhs);
		}
	}

	bool operator()(const ast::String& lhs, const ast::String& rhs) const {
		return dictionaryStringLess(lhs.toString(), rhs.toString());
	}

	bool operator()(const ast::Identifier& lhs, const ast::Identifier& rhs) const {
		return dictionaryStringLess(lhs.toString(), rhs.toString());
	}

	bool operator()(const math::Rational& lhs, const math::Rational& rhs) const {
		return lhs < rhs;
	}

	bool operator()(const math::Real& lhs, const math::Real& rhs) const {
		return lhs < rhs;
	}

	bool operator()(const math::Rational& lhs, const math::Real& rhs) const {
		if ( lhs < rhs ) {
			return true;
		} else if ( lhs > rhs ) {
			return false;
		}
		return operator()<>(lhs, rhs);
	}

	bool operator()(const math::Real& lhs, const math::Rational& rhs) const {
		if ( lhs < rhs ) {
			return true;
		} else if ( lhs > rhs ) {
			return false;
		}
		return operator()<>(lhs, rhs);
	}

};

bool nodeLess(const ast::Node& lhs, const ast::Node& rhs) {
	return ast::applyVisitor(lhs, rhs, NodeLessVisitor{});
}


bool dictionaryStringLess(const std::string& lhs, const std::string& rhs) {
	//Can't use std::lexicographical_compare, since there are no possible implementation for the individual characters,
	//because wm treats upper-lower case letters equally (sort-of)
	//x -> X -> xx

	if ( !boost::iequals(lhs, rhs) ) {
		return boost::ilexicographical_compare(lhs, rhs);
	}

	std::string::const_iterator first1 = lhs.begin();
	std::string::const_iterator first2 = rhs.begin();
	std::string::const_iterator last1 = lhs.end();

	for ( ; (first1 != last1); first1++, first2++ ) {
		if ( std::isupper(*first1) != std::isupper(*first2) ) {
			return std::isupper(*first2);
		}
	}

	return false;

}

}} //namespace tungsten::eval
