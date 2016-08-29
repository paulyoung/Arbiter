#include "dependencies.h"

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// not portable
#include <unistd.h>

static void print_usage (const char *executable)
{
  printf("Usage: %s path\n", executable);
  printf("\n");
  printf("Resolves a Dependencies file in the given path.\n");
}

static void die (const char *error)
{
  if (!error) {
    error = "An unknown error occurred";
  }

  fputs(error, stderr);
  exit(EXIT_FAILURE);
}

int main (int argc, const char **argv)
{
  assert(argc >= 1);

  if (argc < 2) {
    print_usage(argv[0]);
    return EXIT_FAILURE;
  }

  const char *path = argv[1];
  if (chdir(path) != 0) {
    perror("chdir()");
    return EXIT_FAILURE;
  }

  char *error = NULL;
  ArbiterDependencyList *dependencyList = create_dependency_list_from_path("Dependencies", &error);
  if (!dependencyList) {
    die(error);
  }

  ArbiterResolverBehaviors behaviors = {
    .createDependencyList = &create_dependency_list,
    .createAvailableVersionsList = &create_available_versions_list,
  };

  ArbiterResolver *resolver = ArbiterCreateResolver(behaviors, dependencyList, NULL);
  ArbiterFreeDependencyList(dependencyList);

  ArbiterResolvedDependencyList *resolvedList = ArbiterResolverCreateResolvedDependencyList(resolver, &error);
  ArbiterFreeResolver(resolver);
  if (!resolvedList) {
    die(error);
  }

  size_t count = ArbiterResolvedDependencyListCount(resolvedList);

  const ArbiterResolvedDependency *resolved[count];
  ArbiterResolvedDependencyListGetAll(resolvedList, resolved); 

  for (size_t i = 0; i < count; i++) {
    const ArbiterProjectIdentifier *project = ArbiterResolvedDependencyProject(resolved[i]);
    const ArbiterSelectedVersion *version = ArbiterResolvedDependencyVersion(resolved[i]);

    printf("%s @ %s\n", ArbiterProjectIdentifierValue(project), ArbiterSelectedVersionMetadata(version));
  }

  ArbiterFreeResolvedDependencyList(resolvedList);

  return EXIT_SUCCESS;
}