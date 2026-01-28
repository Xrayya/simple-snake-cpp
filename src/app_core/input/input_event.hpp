#pragma once

#include "app_core/event.hpp"
#include <cstdint>

enum class InputType : std::uint8_t {
  Key,
  Mouse,
  None,
};

enum class KeyCode : std::uint8_t {
  Unknown,

  // Letters
  A,
  B,
  C,
  D,
  E,
  F,
  G,
  H,
  I,
  J,
  K,
  L,
  M,
  N,
  O,
  P,
  Q,
  R,
  S,
  T,
  U,
  V,
  W,
  X,
  Y,
  Z,

  // Numbers
  Num0,
  Num1,
  Num2,
  Num3,
  Num4,
  Num5,
  Num6,
  Num7,
  Num8,
  Num9,

  // Symbols
  Exclamation,
  DoubleQuotes,
  Hash,
  Dollar,
  Percent,
  Ampersand,
  SingleQuote,
  LeftParenthesis,
  RightParenthesis,
  Asterisk,
  Plus,
  Comma,
  Minus,
  Dot,
  Slash,
  Colon,
  Semicolon,
  LessThan,
  Equal,
  GreaterThan,
  Question,
  At,
  LeftBracket,
  Backslash,
  RightBracket,
  Caret,
  Underscore,
  Backtick,
  LeftBrace,
  VerticalBar,
  RightBrace,
  Tilde,

  // Special keys
  Escape,
  Enter,
  Backspace,
  Tab,
  Space,

  // Arrow keys
  ArrowUp,
  ArrowDown,
  ArrowLeft,
  ArrowRight,
};

struct KeyModifiers {
  bool shift = false;
  bool ctrl = false;
  bool alt = false;
};

namespace event {
struct Input : Event {
  Input(const InputType &);

  InputType type_;
};

struct KeyInput : Input {
  KeyInput(const KeyCode &key, const KeyModifiers &modifiers,
           const bool &pressed);

  KeyCode key_code_;
  KeyModifiers modifiers_;
  bool pressed_;
};

struct MouseInput : Input {
  float x_;
  float y_;
  bool pressed_;
};
} // namespace event
