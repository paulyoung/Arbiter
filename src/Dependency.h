#pragma once

#ifndef __cplusplus
#error "This file must be compiled as C++."
#endif

#include <arbiter/Dependency.h>

#include "Types.h"
#include "Value.h"
#include "Version.h"

#include <functional>
#include <memory>
#include <ostream>
#include <unordered_set>
#include <vector>

struct ArbiterRequirement;

struct ArbiterProjectIdentifier final : public Arbiter::Base
{
  public:
    using Value = Arbiter::SharedUserValue<ArbiterProjectIdentifier>;

    Value _value;

    ArbiterProjectIdentifier ()
    {}

    explicit ArbiterProjectIdentifier (Value value)
      : _value(std::move(value))
    {}

    std::unique_ptr<Arbiter::Base> clone () const override;
    std::ostream &describe (std::ostream &os) const override;
    bool operator== (const Arbiter::Base &other) const override;

    bool operator< (const ArbiterProjectIdentifier &other) const
    {
      return _value < other._value;
    }
};

struct ArbiterDependency final : public Arbiter::Base
{
  public:
    ArbiterProjectIdentifier _projectIdentifier;

    ArbiterDependency (ArbiterProjectIdentifier projectIdentifier, const ArbiterRequirement &requirement);

    ArbiterDependency (const ArbiterDependency &other)
      : ArbiterDependency(other._projectIdentifier, other.requirement())
    {}

    ArbiterDependency &operator= (const ArbiterDependency &other);

    const ArbiterRequirement &requirement() const noexcept
    {
      return *_requirement;
    }

    std::unique_ptr<Arbiter::Base> clone () const override;
    std::ostream &describe (std::ostream &os) const override;
    bool operator== (const Arbiter::Base &other) const override;

    bool operator< (const ArbiterDependency &other) const
    {
      return _projectIdentifier < other._projectIdentifier;
    }

  private:
    std::unique_ptr<ArbiterRequirement> _requirement;
};

struct ArbiterDependencyList final : public Arbiter::Base
{
  public:
    std::vector<ArbiterDependency> _dependencies;

    ArbiterDependencyList () = default;

    explicit ArbiterDependencyList (std::vector<ArbiterDependency> dependencies)
      : _dependencies(std::move(dependencies))
    {}

    ArbiterDependencyList (const ArbiterDependencyList &) = default;
    ArbiterDependencyList &operator= (const ArbiterDependencyList &) = default;

    ArbiterDependencyList (ArbiterDependencyList &&) = default;
    ArbiterDependencyList &operator= (ArbiterDependencyList &&) = default;

    std::unique_ptr<Arbiter::Base> clone () const override;
    std::ostream &describe (std::ostream &os) const override;
    bool operator== (const Arbiter::Base &other) const override;
};

struct ArbiterResolvedDependency final : public Arbiter::Base
{
  public:
    ArbiterProjectIdentifier _project;
    ArbiterSelectedVersion _version;

    ArbiterResolvedDependency (ArbiterProjectIdentifier project, ArbiterSelectedVersion version)
      : _project(std::move(project))
      , _version(std::move(version))
    {}

    std::unique_ptr<Arbiter::Base> clone () const override;
    std::ostream &describe (std::ostream &os) const override;
    bool operator== (const Arbiter::Base &other) const override;
};

struct ArbiterResolvedDependencyGraph final : public Arbiter::Base
{
  public:
    // TODO: Should this be ordered?
    using DepthSet = std::unordered_set<ArbiterResolvedDependency>;

    std::vector<DepthSet> _depths;

    ArbiterResolvedDependencyGraph () = default;

    size_t count () const;

    size_t depth () const noexcept;
    size_t countAtDepth (size_t depthIndex) const;

    bool contains (const ArbiterResolvedDependency &node) const;

    std::unique_ptr<Arbiter::Base> clone () const override;
    std::ostream &describe (std::ostream &os) const override;
    bool operator== (const Arbiter::Base &other) const override;
};

namespace std {

template<>
struct hash<ArbiterProjectIdentifier> final
{
  public:
    size_t operator() (const ArbiterProjectIdentifier &project) const;
};

template<>
struct hash<ArbiterDependency> final
{
  public:
    size_t operator() (const ArbiterDependency &dependency) const;
};

template<>
struct hash<ArbiterResolvedDependency> final
{
  public:
    size_t operator() (const ArbiterResolvedDependency &dependency) const;
};

} // namespace std
