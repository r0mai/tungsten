
#ifndef ASTNODEVISITOR_HPP_
#define ASTNODEVISITOR_HPP_

namespace tungsten {

template<class RT = void>
struct AstNodeVisitor {
	typedef RT ReturnType;
};

} //namespace tungsten

#endif /* ASTNODEVISITOR_HPP_ */
