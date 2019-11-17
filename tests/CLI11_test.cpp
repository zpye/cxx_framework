#include "CLI/CLI.hpp"

int main(int argc, char* argv[]) {
  CLI::App app("CLI11_simple");

  std::string str;
  CLI::Option* sopt =
      app.add_option("-s,-S,--str,--string,string", str, "string");

  int integer;
  CLI::Option* iopt =
      app.add_option("-i,--int", integer, "integer")->default_val("1234");

  int flag;
  CLI::Option* fopt = app.add_flag("-f,--flag", flag, "flag");

  double d;
  CLI::Option* dopt = app.add_option("-d,--double", d, "double value");
  // ->default_str("1.234");

  CLI11_PARSE(app, argc, argv);

  std::cout << "string: " << str << ", direct count: " << app.count("--str")
            << ", opt count: " << sopt->count() << std::endl;

  std::cout << "integer: " << integer << ", direct count: " << app.count("-i")
            << ", opt count: " << iopt->count() << std::endl;

  std::cout << "flag: " << flag << " (" << fopt->count() << ") times"
            << std::endl;

  std::cout << "double value: " << d << ", " << dopt->as<double>() << std::endl;

  return 0;
}