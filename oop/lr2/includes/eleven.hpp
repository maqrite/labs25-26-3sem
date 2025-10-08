#ifndef ELEVEN_HPP
#define ELEVEN_HPP

#include <iostream>
#include <string>
#include <vector>

class Eleven {
private:
  std::vector<unsigned char> digits;

  void trim();

public:
  Eleven();
  Eleven(const std::string &s);
  Eleven(const Eleven &other);
  ~Eleven();

  Eleven add(const Eleven &other) const;
  Eleven subtract(const Eleven &other) const;
  Eleven copy() const;

  bool is_greater_than(const Eleven &other) const;
  bool is_less_than(const Eleven &other) const;
  bool is_equal_to(const Eleven &other) const;

  std::string to_string() const;
};

#endif
