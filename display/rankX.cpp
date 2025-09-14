#include "rankX.hpp"

void draw_score_progress(
        ox::sdl_instance& win,
        const std::span<const score_data> ranks,
        const std::span<const score_data> scores,
        int min,
        [[maybe_unused]] dimensions size
) {
    auto max_marker_iter = std::max_element(ranks.begin(), ranks.end());
    auto max_marker = max_marker_iter->score;
    int highmark = std::max(min, max_marker);
    int total_points = std::accumulate(scores.begin(), scores.end(), 0, [](int sum, const score_data& s){return sum + s.score;});
    draw_score_progress_bar(win, scores, highmark);
    draw_rank_markers_scores(win, ranks, total_points, highmark);
    draw_score_text(win, ranks);
}

int draw_score_progress_bar(
        ox::sdl_instance& win,
        const std::span<const score_data> scores,
        int highmark,
        dimensions size,
        bool clear_render
) {
    auto [fullwidth, fullheight] = win.get_window_size();
    int width = fullwidth - 2 * size.x_buffer;
    if (width <= 0)
        return size.start_x;
    double divisor = highmark / (width * size.scale);
    if (clear_render)
        size.clear_render(win);
    double currentX = size.left();

    SDL_Rect last_text_rect;
    const ox::sdl_instance::texture* last_text_texture = nullptr;

    for (auto& score : scores) {
        if (score.score == 0) {
            continue;
        }
        double score_ticks = score.score / divisor;
        double nextX = std::min(currentX + score_ticks, static_cast<double>(width));
        int currentI = static_cast<int>(lround(currentX));
        int nextI = static_cast<int>(lround(nextX));
        auto text = win.get_texture(score.name);

        win.set_renderer_color(score.foreground);
        SDL_Rect r{currentI, size.top(), nextI - currentI, size.height};
        if (text) {
            if(last_text_texture)
                last_text_texture->render(last_text_rect.x, last_text_rect.y);
            last_text_rect = r;
            last_text_rect.x = std::min(last_text_rect.x, nextI);
            last_text_texture = text;
        }
        SDL_RenderFillRect(win.screen_renderer(), &r);
        currentX = nextX;
    }
    if(last_text_texture)
        last_text_texture->render(last_text_rect.x, last_text_rect.y);

    return static_cast<int>(lround(currentX - size.x_buffer));
}

template<std::regular_invocable<int, int> CompareFunc>
void draw_rank_markers_scores(
    ox::sdl_instance& win,
    const std::span<const score_data> ranks,
    int total_points,
    int highmark,
    dimensions size,
    CompareFunc comp
){
    SDL_Rect rank_image{0, 0, size.height, size.height};
    auto [fullwidth, fullheight] = win.get_window_size();
    int width = fullwidth - 2 * size.left();
    if (width <= 0)
        return;
    double divisor = highmark / (width * size.scale);

    // int text_y = size.top() + size.height + 5;
    for (auto& rank : ranks) {
        int rank_ticks = static_cast<int>(rank.score / divisor);
        bool pass = comp(total_points, rank.score);
        auto image = win.get_texture(std::format("{}{}", rank.name, pass));

        if (image) {
            image->render(rank_ticks + size.left(), size.top(), &rank_image);
        } else {
            win.set_renderer_color(pass ? ox::named_colors::DarkGreen : ox::named_colors::DarkRed);
            SDL_Rect r{rank_ticks + size.left(), size.top(), 2, size.height};
            SDL_RenderFillRect(win.screen_renderer(), &r);
        }
    }
}

template void draw_rank_markers_scores<std::greater_equal<int>> (
    ox::sdl_instance&, const std::span<const score_data>,
    int, int, dimensions, std::greater_equal<int>
);

template void draw_rank_markers_scores<std::less_equal<int>> (
        ox::sdl_instance&, const std::span<const score_data>,
        int, int, dimensions, std::less_equal<int>
);

template void draw_rank_markers_scores<std::less<int>> (
        ox::sdl_instance&, const std::span<const score_data>,
        int, int, dimensions, std::less<int>
);

void draw_score_text(
        ox::sdl_instance& win,
        const std::span<const score_data> scores,
        dimensions size
) {
    SDL_Rect rank_image{0, 0, size.height, size.height};

    int& text_y = size.start_y;
    for (auto& score : scores) {
        auto image_pass = win.get_texture(std::format("{}true", score.name));
        auto text = win.get_texture(score.name + (image_pass ? "_text" : "_text_with_name"));
        size.clear_render(win);

        if (text) {
            int score_start = size.left();
            if (image_pass) {
                image_pass->render(score_start, size.top(), &rank_image);
                score_start += size.height + 5;
            }

            text->render(score_start, size.top());
        }
        text_y += (size.height);
    }
}

void draw_score_text_horizontal(
        ox::sdl_instance& win,
        const std::span<const score_data> scores,
        dimensions size
) {
    SDL_Rect rank_image{0, 0, size.height, size.height};

    // int width = size.width().value_or(win.get_window_size().first - 2 * size.x_buffer);
    int left = size.left();

    for (auto& score : scores) {
        auto image_pass = win.get_texture(std::format("{}true", score.name));
        auto text = win.get_texture(score.name + (image_pass ? "_text" : "_text_with_name"));
        if (text) {
            if (image_pass) {
                image_pass->render(left, size.top(), &rank_image);
                left += size.height + 5;
            }

            SDL_Point text_dim;
            SDL_QueryTexture(text->get(), nullptr, nullptr, &text_dim.x, &text_dim.y);
            text->render(left, size.top());
            left += text_dim.x + 30;
        }
    }
}
