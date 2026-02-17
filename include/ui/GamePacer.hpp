#ifndef UI_GAME_PACER_HPP
#define UI_GAME_PACER_HPP

namespace ui {

enum class PaceMode {
    Instant,
    Smooth,
    Cinematic
};

class GamePacer {
  public:
    void setMode(PaceMode mode);
    [[nodiscard]] PaceMode mode() const;

    // Short pause for small UI transitions.
    void pauseShort() const;
    // Medium pause for phase changes.
    void pauseMedium() const;
    // Longer pause for reveal moments.
    void pauseLong() const;

  private:
    PaceMode mode_ = PaceMode::Smooth;
};

} // namespace ui

#endif
