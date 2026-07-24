
module;

#include <fmt/core.h>
#include <fmt/color.h>
#include <fmt/chrono.h>
#include <chrono>

export module tmes;


namespace tmes
{

template <typename... Args>
auto log_impl(const char *level, fmt::text_style style, fmt::format_string<Args...> fmt_str, Args&&... args) -> void
{
    fmt::basic_memory_buffer<char, 512> buf;

    fmt::format_to(std::back_inserter(buf), 
            "[{:%Y-%m-%d - %H:%M:%S}][{}] -> ", 
            std::chrono::time_point_cast<std::chrono::milliseconds>(std::chrono::system_clock::now()),
            fmt::styled(fmt::format("{:^7}", level), style));

    fmt::format_to(std::back_inserter(buf), fmt_str, std::forward<Args>(args)...);
    buf.push_back('\n');

    fmt::print("{}", fmt::string_view(buf.data(), buf.size()));
}


export template <typename... Args>
auto info(fmt::format_string<Args...> fmt_str, Args&&... args) -> void 
{
    log_impl("info", fmt::fg(fmt::color::cyan) | fmt::emphasis::bold, fmt_str, std::forward<Args>(args)...);
}

export template <typename... Args>
auto success(fmt::format_string<Args...> fmt_str, Args&&... args) -> void 
{
    log_impl("success", fmt::fg(fmt::color::green) | fmt::emphasis::bold, fmt_str, std::forward<Args>(args)...);
}

export template <typename... Args>
auto warn(fmt::format_string<Args...> fmt_str, Args&&... args) -> void 
{
    log_impl("warning", fmt::fg(fmt::color::yellow) | fmt::emphasis::bold, fmt_str, std::forward<Args>(args)...);
}

export template <typename... Args>
auto error(fmt::format_string<Args...> fmt_str, Args&&... args) -> void 
{
    log_impl("error", fmt::fg(fmt::color::red) | fmt::emphasis::bold, fmt_str, std::forward<Args>(args)...);
}

export template <typename... Args>
auto crit(fmt::format_string<Args...> fmt_str, Args&&... args) -> void 
{
    log_impl("crit", fmt::bg(fmt::color::red) | fmt::fg(fmt::color::black) | fmt::emphasis::bold, fmt_str, std::forward<Args>(args)...);
}

} // namespace tmes
