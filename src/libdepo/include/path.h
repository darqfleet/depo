#pragma once
#include <string>

namespace depo::core {
    class Path {
    public:
        ~Path();
        explicit Path(std::string_view path = "");
        Path(const Path& other);
        Path& operator=(const Path& other);
        Path(Path&& other) noexcept;
        Path& operator=(Path&& other) noexcept;

        Path& operator+=(const Path& other);
        Path& operator+=(std::string_view string);

        Path& operator/=(const Path& other);
        Path& operator/=(std::string_view string);

        Path operator+(const Path& other) const;
        Path operator+(std::string_view string) const;

        Path operator/(const Path& other) const;
        Path operator/(std::string_view string) const;

        bool operator==(const Path& other) const noexcept;
        explicit operator bool() const noexcept;

        [[nodiscard]] bool exists() const;
        [[nodiscard]] const std::string& unexpandedString() const;
        void clear();
        friend bool operator==(const Path& path, std::string_view string);

    private:
        [[nodiscard]] const std::string& eval() const noexcept;
        std::string m_path;
    };
    bool operator==(const Path& path, std::string_view string);
} // namespace depo::core
