#include "../includes/eleven.hpp"
#include <cstddef>
#include <stdexcept>
#include <string>

void Eleven::trim() {
  while (this->digits.size() > 1 && this->digits.back() == 0) {
    this->digits.pop_back();
  }
}

Eleven::Eleven() { this->digits.push_back(0); }

Eleven::Eleven(const std::string &s) {
  if (s.empty()) {
    throw std::invalid_argument("Input string can't be empty");
  }

  for (int i = s.length() - 1; i >= 0; --i) {
    char c = s[i];
    if (c >= '0' && c <= '9') {
      this->digits.push_back(c - '0');
    } else if (c == 'A' || c == 'a') {
      this->digits.push_back(10);
    } else {
      throw std::invalid_argument("Invalid character");
    }
  }
  this->trim();
}

Eleven::Eleven(const Eleven &other) { this->digits = other.digits; }

Eleven::~Eleven() {}

Eleven Eleven::add(const Eleven &other) const {
  Eleven result;
  result.digits.clear();

  int carry = 0;
  size_t max_len = std::max(this->digits.size(), other.digits.size());

  for (size_t i = 0; i < max_len; ++i) {
    int d1 = (i < this->digits.size()) ? this->digits[i] : 0;
    int d2 = (i < other.digits.size()) ? other.digits[i] : 0;

    int sum = d1 + d2 + carry;
    result.digits.push_back(sum % 11);
    carry = sum / 11;
  }

  if (carry > 0) {
    result.digits.push_back(carry);
  }

  return result;
}

Eleven Eleven::subtract(const Eleven &other) const {
  if (this->is_less_than(other)) {
    throw std::logic_error("substract would result in a negative number");
  }

  Eleven result;
  result.digits.clear();

  int borrow = 0;

  for (size_t i = 0; i < this->digits.size(); ++i) {
    int d1 = this->digits[i];
    int d2 = (i < other.digits.size()) ? other.digits[i] : 0;

    int diff = d1 - d2 - borrow;
    if (diff < 0) {
      diff += 11;
      borrow = 1;
    } else {
      borrow = 0;
    }
    result.digits.push_back(diff);
  }

  result.trim();
  return result;
}

Eleven Eleven::copy() const { return Eleven(*this); }

bool Eleven::is_equal_to(const Eleven &other) const {
  return this->digits == other.digits;
}

bool Eleven::is_less_than(const Eleven &other) const {
  if (this->digits.size() < other.digits.size()) {
    return true;
  }

  if (this->digits.size() > other.digits.size()) {
    return false;
  }

  for (int i = this->digits.size() - 1; i >= 0; --i) {
    if (this->digits[i] < other.digits[i]) {
      return true;
    }

    if (this->digits[i] > other.digits[i]) {
      return false;
    }
  }

  return false;
}

bool Eleven::is_greater_than(const Eleven &other) const {
  if (this->digits.size() > other.digits.size()) {
    return true;
  }

  if (this->digits.size() < other.digits.size()) {
    return false;
  }

  for (int i = this->digits.size() - 1; i >= 0; --i) {
    if (this->digits[i] > other.digits[i]) {
      return true;
    }

    if (this->digits[i] < other.digits[i]) {
      return false;
    }
  }

  return false;
}

std::string Eleven::to_string() const {
  std::string s = "";
  if (this->digits.empty()) {
    return "0";
  }

  for (int i = this->digits.size() - 1; i >= 0; --i) {
    int digit = this->digits[i];
    if (digit < 10) {
      s += std::to_string(digit);
    } else {
      s += 'A';
    }
  }
  return s;
}
