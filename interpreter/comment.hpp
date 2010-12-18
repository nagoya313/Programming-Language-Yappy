#pragma once
#include "yappy_fwd.hpp"
#include <boost/spirit/include/qi_grammar.hpp>

namespace yappy {
class comment : public boost::spirit::qi::grammar<parse_iterator> {
 public:
  comment();

 private:
  boost::spirit::qi::rule<parse_iterator> comment_;
};
}