#ifndef ELEVEN_HPP
#define ELEVEN_HPP

#include <exception>
#include <initializer_list>
#include <iostream>
#include <stdexcept>
#include <string>
#include <utility>
#include <vector>

class Eleven {
private:
  std::vector<unsigned char> digits;

  void trim();

public:
  Eleven();

  Eleven(size_t n, unsigned char t);

  Eleven(const std::initializer_list<unsigned char> &t);

  Eleven(const std::string &s);

  Eleven(const Eleven &other);

  virtual ~Eleven();

  Eleven add(const Eleven &other) const;
  Eleven subtract(const Eleven &other) const;
  Eleven copy() const;

  bool is_greater_than(const Eleven &other) const;
  bool is_less_than(const Eleven &other) const;
  bool is_equal_to(const Eleven &other) const;

  std::string to_string() const;
};

#endif
