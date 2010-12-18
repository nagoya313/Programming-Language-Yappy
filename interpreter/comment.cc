#include "comment.hpp"
#include <boost/spirit/include/qi_char_.hpp>
#include <boost/spirit/include/qi.hpp>

namespace yappy {
comment::comment() : comment::base_type(comment_) {
  comment_ = ("//" >> *(boost::spirit::qi::char_ - '\n') >> '\n') | 
             ("/*" >> *(boost::spirit::qi::char_ - "*/") >> "*/") | 
             boost::spirit::qi::ascii::space;
}
}