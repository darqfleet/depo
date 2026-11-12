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
        bool operator==(const Path& other) const noexcept;
        [[nodiscard]] std::string unexpandedString() const;

        friend bool operator==(const Path& path, std::string_view string);

    private:
        [[nodiscard]] const std::string& getString() const noexcept;
        std::string m_path;
    };
    bool operator==(const Path& path, std::string_view string);
} // namespace depo::core
