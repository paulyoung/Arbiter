# Arbiter [![Build Status](https://travis-ci.org/jspahrsummers/Arbiter.svg?branch=master)](https://travis-ci.org/jspahrsummers/Arbiter)

Arbiter is a cross-platform C library<sup>1</sup> which implements the basic behaviors needed by any decentralized dependency manager or package manager, without being coupled to any particular use case, so that many more specific tools can be built on top.

In other words, **Arbiter does not prescribe any one user experience**—it just tries to solve those backend concerns which are common to all dependency managers.

_<sup>1</sup> Note that Arbiter is actually implemented in C++14, but currently only exposes a plain C API to minimize surface area and maximize interoperability._

## Functionality

Some major features of Arbiter include:

### Compliance with Semantic Versioning

[Semantic Versioning](http://semver.org), or SemVer, is a specification for what software version numbers _mean_, and how they should be used to convey compatibility (and the lack thereof).

Arbiter implements SemVer and incorporates it into its [dependency resolution algorithm](#lazy-decentralized-dependency-resolution), so that complex versioning and compatibility logic does not have to be reinvented from scratch for each new tool.

### Lazy, decentralized dependency resolution

Most package managers require a centralized server which has knowledge of all packages and versions in the system.

However, Arbiter resolves individual dependencies _on demand_, allowing them to be loaded from anywhere—even different places for different versions! This doesn’t preclude using a centralized server, but means that it is not a requirement.

### … and more to come

For a full list of planned features, check out our [backlog](https://github.com/jspahrsummers/Arbiter/issues?q=is%3Aopen+is%3Aissue+label%3Aenhancement+sort%3Acreated-desc). If you’d be interested in making any of these a reality, please consider [contributing](CONTRIBUTING.md)!

## Documentation

The Arbiter API is extensively documented in header comments, from which we periodically generate [Doxygen pages](http://jspahrsummers.com/Arbiter/). For the public C API, look at headers under [`include/arbiter/`](include/arbiter/) in the [file list of the documentation](http://jspahrsummers.com/Arbiter/files.html).

## Examples

This repository contains not-production-strength [examples](examples/) for demonstrating how the Arbiter API can be used to build different functionality.

To compile all included examples, run `make examples`.

For more information about individual examples, see the README in each folder. Of course, there are almost certainly other possible uses that we assuredly haven’t thought of or implemented, so this shouldn’t be taken as an exhaustive showcase!

## Bindings

Because the functionality of Arbiter is exposed in a C interface, it’s easy to build bindings into other languages. Currently, Arbiter already has [Swift bindings](bindings/swift/), with more planned!

To compile all included bindings, run `make bindings`.

If you’d like to implement your own bindings, please let us know about them [in a GitHub issue](https://github.com/jspahrsummers/Arbiter/issues/new), and we can include a link here in the README.

## License

Arbiter is released under the [MIT license](LICENSE.md).

I am providing code in this repository to you under an open source license. Because this is my personal repository, the license you receive to my code is from me and not from my employer (Facebook).
