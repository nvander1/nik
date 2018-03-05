#ifndef NIK_STRING_HPP
#define NIK_STRING_HPP

#include <cctype>
#include <string>

namespace nik {

class string : public std::string {
public:
  using std::string::string;
  string capitalize() {
    auto copied = *this;
    auto& front_char = copied.front();
    front_char = std::toupper(front_char);
    return copied;
  }

  // https://github.com/python/cpython/blob/master/Objects/stringlib/transmogrify.h#L156-L174
  string center(int width, char fillchar = ' ') {
    if (size() >= width)
      return *this;

    auto marg = width - size();
    auto left = marg / 2 + (marg & width & 1);

    return pad(left, marg - left, fillchar);
  }

  size_t count(std::string sub, size_t start = 0, size_t end = 0) {
    if (end == 0)
      end += size();
    auto searched_portion = substr(start, end - start);
    size_t seen = 0;
    size_t pos = searched_portion.find(sub);
    while (pos != std::string::npos) {
      seen++;
      pos = searched_portion.find(sub, pos + 1);
    }
    return seen;
  }

private:
  // https://github.com/python/cpython/blob/master/Objects/stringlib/transmogrify.h#L93-L120
  string pad(size_t left, size_t right, char fill) {
    if (left < 0)
      left = 0;
    if (right < 0)
      right = 0;

    if (left == 0 && right == 0)
      return *this;

    auto padded = nik::string(left + size() + right, fill);
    padded.replace(left, size(), *this);

    return padded;
  }
};

} // namespace nik

#endif // NIK_STRING_HPP