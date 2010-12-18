#include "compire.hpp"
#include <iostream>
#include <string>
#include <boost/lexical_cast.hpp>
#include <boost/spirit/include/qi.hpp>
#include <boost/spirit/include/phoenix.hpp>
#include "identifier_map.hpp"

using namespace boost::spirit;
using namespace boost::phoenix;

namespace yappy {

namespace {
qi::rule<parse_iterator, int(), comment> assign;
qi::rule<parse_iterator, std::string(), comment> identifier;
qi::rule<parse_iterator, int(), comment> add;
qi::rule<parse_iterator, int(), comment> mul;
qi::rule<parse_iterator, int(), comment> unary;
qi::rule<parse_iterator, int(), comment> group;
}

compiler::compiler() : compiler::base_type(line_), line_(+((assign[_val = _1] > ';') | (add[_val = _1] > ';') | ';')) {
  group = identifier[try_[_val = boost::phoenix::bind(&get_val, _1)].catch_all[_pass = false]] | int_[_val = _1] | '(' > add[_val = _1] > ')';
  unary = group[_val = _1] | '-' > group[_val = -_1];
  mul = unary[_val = _1] > *(('*' > unary[_val *= _1]) | ('/' > unary[_val /= _1]));
  add = mul[_val = _1] > *(('+' > mul[_val += _1]) | ('-' > mul[_val -= _1]));
  identifier = lexeme[ascii::alpha > *(ascii::alnum | '_')];
  assign = lexeme["int" > +ascii::space] > (identifier > ":=" > add)[boost::phoenix::bind(&set_val, _1, _2)];
  qi::on_error<qi::fail>(group, std::cout << val("行目：)がありません。") << std::endl);
  qi::on_error<qi::fail>(unary, std::cout << val("行目：構文エラー") << std::endl);
  qi::on_error<qi::fail>(mul, std::cout << val("行目：構文エラー") << std::endl);
  qi::on_error<qi::fail>(add, std::cout << val("行目：構文エラー") << std::endl);
  qi::on_error<qi::fail>(assign, std::cout << val("行目：変数宣言の方式に誤りがあります。") << std::endl);
  qi::on_error<qi::fail>(line_, std::cout << val("行目：;がありません。") << std::endl);
}

bool compiler::compile(parse_iterator begin, parse_iterator end, int &result) const {
  return qi::phrase_parse(begin, end, *this, comment(), result);
}
}