#include "path.h"
#include <iostream>
using namespace depo::core;

Path::Path(const std::string_view&& path) : m_path{path} { std::cout << "explicit ctor" << std::endl; }
Path::Path(const Path& other) : m_path{other.m_path} { std::cout << "copy constructor" << std::endl; }

Path& Path::operator=(const Path& other) {
    m_path = other.m_path;
    std::cout << "copy assignment operator" << std::endl;
    return *this;
}
Path::Path(Path&& other) noexcept : m_path{std::move(other.m_path)} { std::cout << "move ctor" << std::endl; }
Path& Path::operator=(Path&& other) noexcept {
    std::cout << "move assignment operator" << std::endl;
    m_path = std::move(other.m_path);
    return *this;
}
Path::~Path() = default;
std::string Path::evalAsString() const { return m_path; }
