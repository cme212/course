
#include "Name.hpp"

/// The class Name contains family and given names.

Name::Name(const std::string givenName, const std::string familyName)
  : givenName_(givenName),
    familyName_(familyName)
{
}

Name::~Name()
{
}

std::string Name::getName() const
{
  return (givenName_ + " " + familyName_);
}
