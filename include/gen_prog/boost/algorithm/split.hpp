#ifndef boost__algorithm__split_hpp
#define boost__algorithm__split_hpp


#include <boost/tokenizer.hpp>


namespace boost {
namespace algorithm {

std::vector< std::string > split(std::string string, boost::char_separator<char> separator)
{
  std::vector< std::string > array;
  boost::tokenizer< boost::char_separator<char> > tokens(str, separator);

  for (const auto & line : tokens)
  {
    array.push_back(t);
  }
  
  return array;
}
  
} // namespace algorithm
} // namespace boost

#endif // ** boost__algorithm__split_hpp ** //
