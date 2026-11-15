#include <filesystem>
#include <utility>

#include "enums.h"
#include "path.h"
#include "trimString.h"

using namespace depo::core;
Path::~Path() = default;


Path::Path(std::string_view path) {
    std::string_view trimPath{TrimString::trim(path, " /", TrimDir::RIGHT)};
    if (trimPath.empty() && !path.empty() && path.find('/') != std::string_view::npos)
    {
        m_path = "/";
    }
    else
    {
        m_path = trimPath;
    }
}


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


Path& Path::operator+=(const Path& other) { return *this += other.m_path; }
Path& Path::operator+=(std::string_view string) {
    std::string_view trimPath{TrimString::trim(string, " /", TrimDir::RIGHT)};
    if (m_path.empty() && trimPath.empty() && !string.empty() && string.find('/') != std::string_view::npos)
    {
        m_path = "/";
    }
    else
    {
        m_path += trimPath;
    }
    return *this;
}

Path& Path::operator/=(const Path& other) { return *this /= other.m_path; }

Path& Path::operator/=(std::string_view string) {
    std::string_view trimmed{TrimString::trim(string, " /", TrimDir::BOTH)};
    if (trimmed.empty())
    {
        return *this;
    }
    if (!m_path.empty() && m_path.back() != '/')
    {
        m_path += '/';
    }
    m_path += trimmed;
    return *this;
}

Path Path::operator+(const Path& other) const {
    Path temp{*this};
    temp += other;
    return temp;
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

bool Path::exists() const { return std::filesystem::exists(eval()); }
const std::string& Path::unexpandedString() const { return m_path; }
const std::string& Path::eval() const noexcept { return m_path; }
bool depo::core::operator==(const Path& path, std::string_view string) { return string == path.unexpandedString(); }
