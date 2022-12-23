#include <iostream>
#include <iomanip>
#include <string>
#include <stack>
#include <exception>

using namespace std::literals::string_literals;

auto constexpr DEBUG { true };

/*
 *  MARK: main()
 */
int main(int argc, char const * argv[]) {
  std::cout << "MatchBrace++\n"s;

  try {
    auto delims = std::stack<char>();
    auto ch { '\0' };
    while (std::cin.get(ch)) {
      switch (ch) {
        case '{' /* } */:
        case '(' /* ) */:
        case '[' /* ] */:
          if (DEBUG) {
            std::cout << "push('"s
                      << ch
                      << "')\n"s;
          }
          delims.push(ch);
          break;

        case /* { */ '}':
          {
            if (delims.size() == 0) {
              throw std::underflow_error("GRONK! unexpected, empty stack"s);
            }

            auto pc { delims.top() };
            delims.pop();
            if (DEBUG) {
              std::cout << "top() = '"s << pc
                        << "' ch = '"s << ch
                        << "'\n"s;
            }
            if (pc != '{' /* } */) {
              throw std::runtime_error(/* { */ "GRONK! mismatched '}'"s);
            }
          }
          break;

        case /* ( */ ')':
          {
            if (delims.size() == 0) {
              throw std::underflow_error("GRONK! unexpected, empty stack"s);
            }

            auto pc { delims.top() };
            delims.pop();
            if (DEBUG) {
              std::cout << "top() = '"s << pc
                        << "' ch = '"s << ch
                        << "'\n";
            }
            if (pc != '(' /* ) */) {
              throw std::runtime_error(/* ( */ "GRONK! mismatched ')'"s);
            }
          }
          break;

        case /* [ */ ']':
          {
            if (delims.size() == 0) {
              throw std::underflow_error("GRONK! unexpected, empty stack"s);
            }

            auto pc { delims.top() };
            delims.pop();
            if (DEBUG) {
              std::cout << "top() = '"s << pc
                        << "' ch = '"s << ch
                        << "'\n";
            }
            if (pc != '[' /* ] */) {
              throw std::runtime_error(/* [ */ "GRONK! mismatched ']'"s);
            }
          }
          break;

        default:
          break;
      }
    }

    if (delims.size() != 0) {
      throw std::runtime_error("GRONK! Delimiters don't match"s);
    }

    std::cout << "OK. Delimiters match\n"s;
  }
  catch (std::exception const & ex) {
    std::cout << ex.what() << std::endl;
  }
  catch (...) {
    std::cout << "GRONK! Unexpected exception\n"s;
  }

  std::cout << std::endl;

  return 0;
}
