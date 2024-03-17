#include "data_struct.hpp"
#include <fstream>
#include <iomanip>
#include <cmath>
#include "delimiter.hpp"

bool nikitov::DataStruct::operator<(const DataStruct& other) const
{
  double ownComplex = std::pow(2, key2.real()) + std::pow(2, key2.imag());
  double otherComplex = std::pow(2, other.key2.real()) + std::pow(2, other.key2.imag());
  if (key1 != other.key1)
  {
    return key1 < other.key1;
  }
  else
  {
    if (ownComplex != otherComplex)
    {
      return ownComplex < otherComplex;
    }
    else
    {
      return (key3.length() <= other.key3.length());
    }
  }
}

std::istream& nikitov::operator>>(std::istream& input, DataStruct& value)
{
  std::istream::sentry guard(input);
  if (guard)
  {
    using DelStr = DelimiterString;
    using DelChar = DelimiterChar;

    size_t keyNum = 0;
    input >> DelChar({'('});
    for (size_t i = 0; i != 3; ++i)
    {
      input >> DelStr({":key"}) >> keyNum;
      inputKey(value, keyNum, input);
    }
    input >> DelStr({":)"});
  }
  return input;
}

std::ostream& nikitov::operator<<(std::ostream& output, const DataStruct& value)
{
  std::ostream::sentry guard(output);
  if (guard)
  {
    output << std::setprecision(1) << std::fixed;
    output << "(:key1 " << '\'' << value.key1 << '\'';
    output << ":key2 " << "#c(" << value.key2.real() << ' ' << value.key2.imag() << ')';
    output << ":key3 " << '\"' << value.key3 << '\"' << ":)";
    output.flush();
  }
  return output;
}

std::istream& nikitov::operator>>(std::istream& input, std::string& line)
{
  std::istream::sentry guard(input);
  if (guard)
  {
    char symb = {};
    input >> std::noskipws >> std::fixed;
    while (input >> symb)
    {
      if (symb == '\"')
      {
        break;
      }
      line += symb;
    }
    input >> std::skipws >> std::fixed;
  }
  return input;
}

void nikitov::inputKey(DataStruct& value, size_t keyNum, std::istream& input)
{
  using DelStr = DelimiterString;
  using DelChar = DelimiterChar;
  if (keyNum == 1)
  {
    input >> DelChar({'\''}) >> value.key1 >> DelChar({'\''});
  }
  else if (keyNum == 2)
  {
    double real = 0.0;
    double imag = 0.0;
    input >> DelStr({"#c("}) >> real >> imag >> DelChar({')'});
    value.key2 = { real, imag };
  }
  else if (keyNum == 3)
  {
    input >> DelChar({'\"'});
    input >> value.key3;
  }
  else
  {
    input.setstate(std::ios::failbit);
  }
}
