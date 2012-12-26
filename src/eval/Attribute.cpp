
#include "Attribute.hpp"

#include <boost/assign/list_of.hpp>

namespace tungsten { namespace eval {

AttributeMap createDefaultAttributeMap() {

	return boost::assign::map_list_of
			("Plus", AttributeVector({"Flat", "Listable", "NumericFunction", "OneIdentity", "OrderLess", "Protected"}) )
			("Times", AttributeVector({"Flat", "Listable", "NumericFunction", "OneIdentity", "OrderLess", "Protected"}) );
}

}} //namespace tungsten::eval


