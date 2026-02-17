#include "ui/GamePacer.hpp"

#include <chrono>
#include <thread>

namespace ui {

namespace {
    void sleepMs(const int milliseconds) {
        if (milliseconds <= 0) {
            return;
        }
        std::this_thread::sleep_for(std::chrono::milliseconds(milliseconds));
    }
} // namespace

void GamePacer::setMode(const PaceMode mode) {
    mode_ = mode;
}

PaceMode GamePacer::mode() const {
    return mode_;
}

void GamePacer::pauseShort() const {
    switch (mode_) {
        case PaceMode::Instant:
            return;
        case PaceMode::Smooth:
            sleepMs(300);
            return;
        case PaceMode::Cinematic:
            sleepMs(450);
            return;
    }
}

void GamePacer::pauseMedium() const {
    switch (mode_) {
        case PaceMode::Instant:
            return;
        case PaceMode::Smooth:
            sleepMs(900);
            return;
        case PaceMode::Cinematic:
            sleepMs(1300);
            return;
    }
}

void GamePacer::pauseLong() const {
    switch (mode_) {
        case PaceMode::Instant:
            return;
        case PaceMode::Smooth:
            sleepMs(1600);
            return;
        case PaceMode::Cinematic:
            sleepMs(2200);
            return;
    }
}

} // namespace ui
