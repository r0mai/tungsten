
#ifndef AST_NODEFWD_HPP_
#define AST_NODEFWD_HPP_

#include <memory>

namespace tungsten { namespace ast {

class Node;

typedef std::unique_ptr<Node> NodePtr;

}} //namespace tungsten::ast


#endif /* NODEFWD_HPP_ */
