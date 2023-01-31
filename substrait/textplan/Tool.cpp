#include <getopt.h>
#include "PlanConverter.h"

namespace io::substrait {
namespace {

void convertJSONToText(const char* filename) {
  PlanConverter converter;
  std::string json = readFromFile(filename);
  converter.loadFromJSON(json);

  std::cout << converter.toString();
}

} // namespace
} // namespace io::substrait

int main(int argc, char* argv[]) {
  int c;
  int digit_optind = 0;

  while (true) {
    int this_option_optind = optind ? optind : 1;
    int option_index = 0;
    static struct option long_options[] = {{0, 0, 0, 0}};

    c = getopt_long(argc, argv, "abc:d:012", long_options, &option_index);
    if (c == -1)
      break;
  }

  if (optind >= argc) {
    printf("Usage:  planconverter <file1> <file2> ...\n");
    return EXIT_FAILURE;
  }

  while (optind < argc) {
    const char* filename = argv[optind++];
    printf("===== %s =====\n", filename);
    io::substrait::convertJSONToText(filename);
  }

  return EXIT_SUCCESS;
}
