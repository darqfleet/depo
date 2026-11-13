#include "path.h"
#include <filesystem>
#include <utility>
using namespace depo::core;
Path::~Path() = default;


Path::Path(std::string_view path) : m_path{path} {}


Path::Path(const Path& other) : m_path{other.m_path} {}


Path& Path::operator=(const Path& other) {
    if (this != &other)
    {
        m_path = other.m_path;
    }
    return *this;
}


Path::Path(Path&& other) noexcept : m_path{std::exchange(other.m_path, "")} {}


Path& Path::operator=(Path&& other) noexcept {
    if (this != &other)
    {
        m_path = std::exchange(other.m_path, "");
    }
    return *this;
}


Path& Path::operator+=(const Path& other) {
    m_path += other.m_path;
    return *this;
}

Path& Path::operator/=(const Path& other) {
    m_path += '/' + other.m_path;
    return *this;
}

Path Path::operator+(const Path& other) const {
    Path temp{*this};
    temp += other;
    return temp;
}


Path& Path::operator+=(std::string_view string) {
    m_path += string;
    return *this;
}

Path& Path::operator/=(std::string_view string) {
    m_path += '/';
    m_path += string;
    return *this;
}

Path Path::operator+(std::string_view string) const {
    Path temp{*this};
    temp += string;
    return temp;
}
Path Path::operator/(std::string_view string) const {
    Path temp{*this};
    temp /= string;
    return temp;
}

Path Path::operator/(const Path& other) const {
    Path temp{*this};
    temp /= other;
    return temp;
}

void Path::clear() { m_path.clear(); }

bool Path::operator==(const Path& other) const noexcept { return m_path == other.m_path; }

Path::operator bool() const noexcept { return !m_path.empty(); }

bool Path::exists() const { return std::filesystem::exists(m_path); }
std::string Path::unexpandedString() const { return m_path; }

const std::string& Path::getString() const noexcept { return m_path; }

bool depo::core::operator==(const Path& path, std::string_view string) { return string == path.getString(); }
