#pragma once
#include <string>

namespace depo::core {
    class resolver;
    class Path {
    public:
        explicit Path(const std::string_view&& path = "");
        Path(const Path& other);
        Path& operator=(const Path& other);
        Path(Path&& other) noexcept;
        Path& operator=(Path&& other) noexcept;
        ~Path();
        [[nodiscard]] std::string evalAsString() const;

    private:
        std::string m_path;
    };
} // namespace depo::core
