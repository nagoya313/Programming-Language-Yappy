#pragma once
#include "yappy_fwd.hpp"
#include "comment.hpp"

namespace yappy {
class compiler : public boost::spirit::qi::grammar<parse_iterator, int(), comment> {
 public:
  compiler();

  bool compile(parse_iterator begin, parse_iterator end, int &result) const;

 private:
  boost::spirit::qi::rule<parse_iterator, int(), comment> line_;
};
}