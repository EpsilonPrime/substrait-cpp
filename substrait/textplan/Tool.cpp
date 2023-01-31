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
  while (true) {
    int option_index = 0;
    static struct option long_options[] = {{nullptr, 0, nullptr, 0}};

    int c = getopt_long(argc, argv, "", long_options, &option_index);
    if (c == -1)
      break;
  }

  if (optind >= argc) {
    printf("Usage:  planconverter <file1> <file2> ...\n");
    return EXIT_FAILURE;
  }

  int curr_arg = optind;
  for (; curr_arg < argc; curr_arg++) {
    printf("===== %s =====\n", argv[curr_arg]);
    io::substrait::convertJSONToText(argv[curr_arg]);
  }

  return EXIT_SUCCESS;
}
