#include <cstring>
#include "cppstring.h"

const size_t kInitialSize = 256;
const int kIncreaseCoefficient = 2;

// private methods

std::size_t String::Strlen(const char *c_string) {
    std::size_t size = 0;
    while (c_string[size] != '\0') {
        ++size;
    }
    return size;
}


void String::Clear() {
    m_length_ = 0;
}

void String::PushBack(char c) {
    if (m_length_ >= m_capacity_) {
        IncreaseData();
    }
    m_data_[m_length_] = c;
    ++m_length_;
}

void String::IncreaseData() {
    std::size_t new_cap = kIncreaseCoefficient * m_capacity_;
    auto *new_data = new char[new_cap];
    for (std::size_t i = 0; i < m_length_; ++i) {
        new_data[i] = m_data_[i];
    }
    delete[] m_data_;
    m_data_ = new_data;
    m_capacity_ = new_cap;
}

// public methods

String::String() : m_data_(new char[kInitialSize]), m_length_(0), m_capacity_(kInitialSize) {
}

String::String(char c) : String() {
    m_data_[0] = c;
    m_length_ = 1;
}

String::String(const char *c_string) {
    std::size_t real_size = Strlen(c_string);
    std::size_t size = std::max(kInitialSize, real_size);
    m_data_ = new char[size];
    m_length_ = real_size;
    m_capacity_ = size;
    for (std::size_t i = 0; i < m_length_; ++i) {
        m_data_[i] = c_string[i];
    }
}

String::String(const String &other) :
m_data_(new char[other.m_capacity_]), m_length_(other.m_length_), m_capacity_(other.m_capacity_) {
    for (std::size_t i = 0; i < m_length_; ++i) {
        m_data_[i] = other.m_data_[i];
    }
}

String::String(String &&other) :
m_data_(other.m_data_), m_length_(other.m_length_), m_capacity_(other.m_capacity_) {
    other.m_data_ = nullptr;
    m_length_ = 0;
    m_capacity_ = 256;
}

String::~String() {
    delete[] m_data_;
}

void String::Swap(String &other) {
    std::swap(m_data_, other.m_data_);
    std::swap(m_length_, other.m_length_);
    std::swap(m_capacity_, other.m_capacity_);
}

std::size_t String::Length() const {
    return m_length_;
}

std::int64_t String::Index(char c) const {
    for (std::size_t i = 0; i < m_length_; ++i) {
        if (m_data_[i] == c) {
            return static_cast<int64_t>(i);
        }
    }
    return -1;
}

char String::operator[](std::size_t index) const {
    return m_data_[index];
}

char &String::operator[](std::size_t index) {
    return m_data_[index];
}

void String::ToUpper(std::size_t first, std::size_t last) {
    for (std::size_t i = first; i < last; ++i) {
        if (std::islower(m_data_[i])) {
            m_data_[i] = static_cast<char>(std::toupper(m_data_[i]));
        }
    }
}

void String::ToLower(std::size_t first, std::size_t last) {
    for (std::size_t i = first; i < last; ++i) {
        if (std::isupper(m_data_[i])) {
            m_data_[i] = static_cast<char>(std::tolower(m_data_[i]));
        }
    }
}

std::ostream &operator<<(std::ostream &stream, const String &string) {
    for (size_t i = 0; i < string.Length(); ++i) {
        stream << string[i];
    }
    return stream;
}

std::istream &operator>>(std::istream &stream, String &string) {
    string.Clear();
    char upcoming_char;
    if (!(stream >> upcoming_char)) {
        return stream;
    }
    do {
        string.PushBack(upcoming_char);
        upcoming_char = std::char_traits<char>::eof();
        stream.get(upcoming_char);
        if (isspace(upcoming_char)) {
            stream.putback(upcoming_char);
            break;
        }
    } while (upcoming_char != std::char_traits<char>::eof());
    return stream;;
}

String &String::operator=(const String &other) {
    if (&other == this) {
        return *this;
    }
    String(other).swap(*this);
    return *this;
}

String &String::operator=(String &&other) {
    delete[] m_data_;
    m_data_ = other.m_data_;
    m_length_ = other.m_length_;
    m_capacity_ = other.m_capacity_;
    other.m_data_ = nullptr;
    return *this;
}

String &String::operator+=(const String &other) {
    for (std::size_t i = 0; i < other.Length(); ++i) {
        PushBack(other[i]);
    }
    return *this;
}

String operator+(const String &lhs, const String &rhs) {
    String ans = lhs;
    ans += rhs;
    return ans;
}

bool operator==(const String &lhs, const String &rhs) {
    if (lhs.Length() != rhs.Length()) {
        return false;
    }
    for (std::size_t i = 0; i < lhs.Length(); ++i) {
        if (lhs[i] != rhs[i]) {
            return false;
        }
    }
    return true;
}

bool operator==(const String &lhs, char rhs) {
    return lhs == String(rhs);
}

bool operator==(const String &lhs, const char *rhs) {
    return lhs == String(rhs);
}

bool operator==(char lhs, const String &rhs) {
    return String(lhs) == rhs;
}

bool operator==(const char *lhs, const String &rhs) {
    return String(lhs) == rhs;
}

bool operator>(const String &lhs, const String &rhs) {
    std::size_t min_size= std::min(lhs.Length(), rhs.Length());
    for (std::size_t i = 0; i < min_size; ++i) {
        if (lhs[i] > rhs[i]) {
            return true;
        } 
        if (lhs[i] < rhs[i]) {
            return false;
        }
    }
    return lhs.Length() > rhs.Length();
}

bool operator>(const String &lhs, char rhs) {
    return lhs > String(rhs);
}

bool operator>(const String &lhs, const char *rhs) {
    return lhs > String(rhs);
}

bool operator>(char lhs, const String &rhs) {
    return String(lhs) > rhs;
}

bool operator>(const char *lhs, const String &rhs) {
    return String(lhs) > rhs;
}

bool operator!=(const String &lhs, const String &rhs) {
    return !(lhs == rhs);
}

bool operator!=(const String &lhs, char rhs) {
    return lhs != String(rhs);
}

bool operator!=(const String &lhs, const char *rhs) {
    return lhs != String(rhs);
}

bool operator!=(char lhs, const String &rhs) {
    return String(lhs) != rhs;
}

bool operator!=(const char *lhs, const String &rhs) {
    return String(lhs) != rhs;
}

bool operator<(const String &lhs, const String &rhs) {
    return rhs > lhs;
}

bool operator<(const String &lhs, char rhs) {
    return lhs < String(rhs) ;
}

bool operator<(const String &lhs, const char *rhs) {
    return lhs < String(rhs);
}

bool operator<(char lhs, const String &rhs) {
    return String(lhs) < rhs;
}

bool operator<(const char *lhs, const String &rhs) {
    return String(lhs) < rhs;
}

bool operator<=(const String &lhs, const String &rhs) {
    return !(lhs > rhs);
}

bool operator<=(const String &lhs, char rhs) {
    return lhs <= String(rhs);
}

bool operator<=(const String &lhs, const char *rhs) {
    return lhs <= String(rhs);
}

bool operator<=(char lhs, const String &rhs) {
    return String(lhs) <= rhs;
}

bool operator<=(const char *lhs, const String &rhs) {
    return String(lhs) <= rhs;
}

bool operator>=(const String &lhs, const String &rhs) {
    return !(lhs < rhs);
}

bool operator>=(const String &lhs, char rhs) {
    return lhs >= String(rhs);
}

bool operator>=(const String &lhs, const char *rhs) {
    return lhs >= String(rhs);
}

bool operator>=(char lhs, const String &rhs) {
    return String(lhs) >= rhs;
}

bool operator>=(const char *lhs, const String &rhs) {
    return String(lhs) >= rhs;
}
