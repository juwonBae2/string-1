#include "string.hpp"
#include <spdlog/spdlog.h>
#include <memory>

// String::String() : data_(std::make_unique<char[]>(1)), size_(0)
// {
//     data_[0] = '\0';
// }

String::String() : data_(new char[1]{'\0'}), size_(0), capacity_(1) {}

String::String(const char *str)
{
    initializeFromString(str);
    size_ = strlen(data_);
}

String::String(const char *str, size_t length)
{
    if (str == nullptr)
    {
        data_ = nullptr;
        size_ = 0;
    }
    else
    {
        data_ = new char[length + 1];
        strncpy(data_, str, length);
        data_[length] = '\0';
        size_ = length;
    }
}

String::~String()
{
    if (data_ != nullptr)
    {
        delete[] this->data_;
    }
}

String::String(const String &str)
{
    initializeFromOther(str);
    capacity_ = str.capacity_;
}

// TODO: Add test code
String::String(String &&str) noexcept : data_(str.data_), size_(str.size_), capacity_(str.capacity_)
{
    str.data_ = nullptr;
    str.size_ = 0;
    str.capacity_ = 0;
}

String &String::operator=(const String &str)
{
    if (this != &str)
    {
        delete[] data_;
        initializeFromOther(str);
    }
    return *this;
}

String &String::operator=(String &&str) noexcept
{
    if (this != &str)
    {
        delete[] data_;

        data_ = str.data_;
        size_ = str.size_;

        str.data_ = nullptr;
        str.size_ = 0;
    }
    return *this;
}

bool String::operator==(const String &str) const
{
    return (strcmp(data_, str.data_) == 0);
}

bool String::operator!=(const String &str) const
{
    return !(*this == str);
}

bool String::operator<(const String &str) const
{
    return (strcmp(data_, str.data_) < 0);
}

bool String::operator<=(const String &str) const
{
    return (strcmp(data_, str.data_) <= 0);
}

bool String::operator>(const String &str) const
{
    return (strcmp(data_, str.data_) > 0);
}

bool String::operator>=(const String &str) const
{
    return (strcmp(data_, str.data_) >= 0);
}

String String::operator+(const String &str) const
{
    String result;
    result.size_ = size_ + str.size_;
    result.data_ = new char[result.size_ + 1];

    if (data_)
    {
        strcpy(result.data_, data_);
    }
    if (str.data_)
    {
        strcat(result.data_, str.data_);
    }
    return result;
}

String &String::operator+=(const String &str)
{
    size_t new_size = size_ + str.size_;
    char *new_data = new char[new_size + 1];

    if (data_)
    {
        strcpy(new_data, data_);
    }
    if (str.data_)
    {
        strcat(new_data, str.data_);
    }
    delete[] data_;
    data_ = new_data;
    size_ = new_size;

    return *this;
}

char &String::front() const
{
    return data_[0];
}

char &String::back() const
{
    return data_[size_ - 1];
}

String String::trim() const
{
    if (data_ == nullptr)
    {
        return String();
    }

    size_t length = strlen(data_);
    size_t newIndex = 0;
    char *trimmedData = new char[length + 1];

    for (size_t i = 0; i < length; ++i)
    {
        if (!isspace(data_[i]))
        {
            trimmedData[newIndex++] = data_[i];
        }
    }

    trimmedData[newIndex] = '\0';

    // TODO: trim을 할 게 없거나 빈 생성자가 들어올 경우 로그 추가
    // if (newIndex == 0)
    // {
    //     spdlog::warn("Trimmed string is empty.");
    // }

    String trimmedString(trimmedData);
    delete[] trimmedData;

    return trimmedString;
}

String String::erase(size_t start, size_t count) const
{
    if (data_ == nullptr)
    {
        spdlog::error("Null pointer in erase() function.");
        throw std::runtime_error("Null pointer in erase() function.");
    }

    size_t length = strlen(data_);

    if (start >= length || count == 0)
    {
        spdlog::error("Erase start index or count is out of bounds. Returning original string.");
        return *this;
    }

    if (start + count > length)
    {
        count = length - start;
        spdlog::warn("Erase count adjusted to fit within string length. String length: {}", count);
    }

    try
    {
        char *erasedData = new char[length - count + 1];

        strncpy(erasedData, data_, start);
        erasedData[start] = '\0';

        strcat(erasedData, data_ + start + count);

        String erasedString(erasedData);
        delete[] erasedData;

        return erasedString;
    }
    catch (const std::bad_alloc &)
    {
        spdlog::error("Memory allocation failed in erase.");
        throw std::runtime_error("Memory allocation failed in erase.");
    }
}

String String::find(const String &str) const
{
    if (str.data_ == nullptr || data_ == nullptr)
    {
        spdlog::error("Null pointer passed to find() function.");
        throw std::runtime_error("Null pointer passed to find() function.");
    }

    if (str.size() == 0)
    {
        spdlog::error("Empty string passed to find() function.");
    }

    char *found = strstr(data_, str.data_);
    if (found)
    {
        size_t foundIndex = found - data_;
        return String(data_ + foundIndex, str.size());
    }
    else if (str.size() != 0)
    {
        spdlog::info("Substring not found.");
    }

    return String();
}

String String::substr(size_t start) const
{
    if (data_ == nullptr)
    {
        spdlog::error("Null pointer in substr() function.");
        throw std::runtime_error("Null pointer in substr() function.");
    }

    size_t length = strlen(data_);
    if (start >= length)
    {
        spdlog::error("Invalid start index in substr() function.");
        throw std::runtime_error("Invalid start index in substr() function.");
    }

    size_t count = length - start;

    try
    {
        char *substrData = new char[count + 1];

        strncpy(substrData, data_ + start, count);
        substrData[count] = '\0';

        String subString(substrData);
        delete[] substrData;

        return subString;
    }
    catch (const std::bad_alloc &)
    {
        spdlog::error("Memory allocation failed in substr.");
        throw std::runtime_error("Memory allocation failed in substr.");
    }
}

String String::substr(size_t start, size_t count) const
{
    if (data_ == nullptr)
    {
        spdlog::error("Null pointer in substr() function.");
        throw std::runtime_error("Null pointer in substr() function.");
    }

    size_t length = strlen(data_);
    if (start >= length)
    {
        spdlog::error("Invalid start index in substr() function.");
        throw std::out_of_range("Invalid start index in substr() function.");
    }

    if (count == 0)
    {
        return String();
    }

    try
    {
        char *substrData = new char[count + 1];

        strncpy(substrData, data_ + start, count);
        substrData[count] = '\0';

        String subString(substrData);
        delete[] substrData;

        return subString;
    }
    catch (const std::bad_alloc &)
    {
        spdlog::error("Memory allocation failed in substr.");
        throw std::runtime_error("Memory allocation failed in substr.");
    }
}

bool String::empty() const
{
    return size_ == 0;
}

void String::pop_back()
{
    if (empty())
    {
        spdlog::info("String::pop_back(): string is already empty");
    }
    else
    {
        char *newChar = new char[size_];

        for (size_t i = 0; i < size_ - 1; ++i)
        {
            newChar[i] = data_[i];
        }

        delete[] data_;
        data_ = newChar;

        size_ = size_ - 1;
    }
}

void String::push_back(const String &str)
{
    size_t totalSize = size_ + str.size_;
    char *newData = new char[totalSize + 1];

    if (data_ != nullptr)
    {
        strcpy(newData, data_);
    }

    if (str.data_ != nullptr)
    {
        strcat(newData, str.data_);
    }

    delete[] data_;

    data_ = newData;
    size_ = totalSize;
}

char &String::at(size_t index) const
{
    return this->data_[index];
}

void String::clear() noexcept
{
    if (data_ != nullptr)
    {
        delete[] data_;
        data_ = nullptr;
    }

    size_ = 0;
}

void String::reserve(size_t new_cap) noexcept
{
    if (new_cap > capacity_)
    {
        char *new_data = new char[new_cap];
        if (data_)
        {
            std::copy(data_, data_ + size_, new_data);
            delete[] data_;
        }
        data_ = new_data;
        capacity_ = new_cap;
    }
}

// String String::resize();

std::ostream &operator<<(std::ostream &os, const String &str)
{
    if (str.data_ != nullptr)
    {
        os << str.data_;
    }
    return os;
}

size_t String::size() const noexcept
{
    // big -O(1)
    return size_;

    // big -O(n)
    // return data_ ? strlen(data_) : 0;
}

size_t String::length() const noexcept
{
    return size();
}

size_t String::capacity() const noexcept
{
    return capacity_;
}

void String::initializeFromString(const char *str)
{
    if (str != nullptr)
    {
        size_t str_length = strlen(str);
        data_ = new char[str_length + 1];
        strcpy(data_, str);
        size_ = str_length;
    }
    else
    {
        data_ = nullptr;
        size_ = 0;
        capacity_ = 1;
    }
}

void String::initializeFromOther(const String &other)
{
    if (other.data_ != nullptr)
    {
        size_ = other.size_;
        capacity_ = other.capacity_;
        data_ = new char[capacity_];
        strcpy(data_, other.data_);
    }
    else
    {
        data_ = nullptr;
        size_ = 0;
        capacity_ = 1;
    }
}

String::Iterator::Iterator(pointer ptr) : ptr_(ptr) {}

String::Iterator::reference String::Iterator::operator*() const
{
    return *ptr_;
}

String::Iterator::pointer String::Iterator::operator->()
{
    return ptr_;
}

String::Iterator &String::Iterator::operator++()
{
    ++ptr_;
    return *this;
}

String::Iterator String::Iterator::operator++(int)
{
    Iterator temp = *this;
    ++ptr_;
    return temp;
}

bool String::Iterator::operator==(const Iterator &other) const
{
    return ptr_ == other.ptr_;
}

bool String::Iterator::operator!=(const Iterator &other) const
{
    return ptr_ != other.ptr_;
}

bool String::Iterator::operator<(const Iterator &other) const
{
    return ptr_ < other.ptr_;
}

bool String::Iterator::operator<=(const Iterator &other) const
{
    return ptr_ <= other.ptr_;
}

bool String::Iterator::operator>(const Iterator &other) const
{
    return ptr_ > other.ptr_;
}

bool String::Iterator::operator>=(const Iterator &other) const
{
    return ptr_ >= other.ptr_;
}

String::Iterator String::begin()
{
    return String::Iterator(data_);
}

String::Iterator String::end()
{
    return String::Iterator(data_ + size_);
}
