#include "Requirement-inl.h"

namespace Arbiter {
namespace Requirement {

bool AtLeast::operator== (const ArbiterRequirement &other) const noexcept
{
  if (auto *ptr = dynamic_cast<const AtLeast *>(&other)) {
    return _minimumVersion == ptr->_minimumVersion;
  } else {
    return false;
  }
}

bool CompatibleWith::satisfiedBy (const ArbiterSemanticVersion &version) const noexcept
{
  if (version._major != _baseVersion._major) {
    return false;
  }

  if (version._major > 0) {
    // According to SemVer, any 0.y.z release can break compatibility.
    // Therefore, minor versions need to match exactly.
    if (version._minor != _baseVersion._minor) {
      return false;
    }

    // Patch versions also technically need to match exactly, but we permit
    // choosing looser behavior.
    switch (_strictness) {
      case STRICT:
        if (version._patch != _baseVersion._patch) {
          return false;
        }

        break;

      case ALLOW_VERSION_ZERO_PATCHES:
        break;
    }
  }

  // Always permit prerelease strings and build metadata to vary (even on major
  // version 0), as long as the candidate version has higher precedence.
  return version >= _baseVersion;
}

bool CompatibleWith::operator== (const ArbiterRequirement &other) const noexcept
{
  if (auto *ptr = dynamic_cast<const CompatibleWith *>(&other)) {
    return _baseVersion == ptr->_baseVersion;
  } else {
    return false;
  }
}

bool Exactly::operator== (const ArbiterRequirement &other) const noexcept
{
  if (auto *ptr = dynamic_cast<const Exactly *>(&other)) {
    return _version == ptr->_version;
  } else {
    return false;
  }
}

}
}
