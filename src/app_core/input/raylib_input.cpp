#include "app_core/input/raylib_input.hpp"
#include "raylib.h"
#include <memory>

auto RaylibInputHandler::poll() const -> std::unique_ptr<event::Input> {
  // Arrow keys
  if (IsKeyPressed(KEY_UP)) {
    return std::make_unique<event::KeyInput>(KeyCode::ArrowUp, KeyModifiers{},
                                             false);
  }
  if (IsKeyPressed(KEY_DOWN)) {
    return std::make_unique<event::KeyInput>(KeyCode::ArrowDown, KeyModifiers{},
                                             false);
  }
  if (IsKeyPressed(KEY_LEFT)) {
    return std::make_unique<event::KeyInput>(KeyCode::ArrowLeft, KeyModifiers{},
                                             false);
  }
  if (IsKeyPressed(KEY_RIGHT)) {
    {
      return std::make_unique<event::KeyInput>(KeyCode::ArrowRight,
                                               KeyModifiers{}, false);
    }
  }

  int chr = GetCharPressed();

  if (chr != 0) {
    KeyModifiers modifiers{};

    if (chr >= 'A' && chr <= 'Z') {
      modifiers.shift = true;
      chr = chr - 'A' + 'a'; // convert to lowercase
    }

    switch (chr) {

    // Letters
    case 'a':
      return std::make_unique<event::KeyInput>(KeyCode::A, modifiers, false);
    case 'b':
      return std::make_unique<event::KeyInput>(KeyCode::B, modifiers, false);
    case 'c':
      return std::make_unique<event::KeyInput>(KeyCode::C, modifiers, false);
    case 'd':
      return std::make_unique<event::KeyInput>(KeyCode::D, modifiers, false);
    case 'e':
      return std::make_unique<event::KeyInput>(KeyCode::E, modifiers, false);
    case 'f':
      return std::make_unique<event::KeyInput>(KeyCode::F, modifiers, false);
    case 'g':
      return std::make_unique<event::KeyInput>(KeyCode::G, modifiers, false);
    case 'h':
      return std::make_unique<event::KeyInput>(KeyCode::H, modifiers, false);
    case 'i':
      return std::make_unique<event::KeyInput>(KeyCode::I, modifiers, false);
    case 'j':
      return std::make_unique<event::KeyInput>(KeyCode::J, modifiers, false);
    case 'k':
      return std::make_unique<event::KeyInput>(KeyCode::K, modifiers, false);
    case 'l':
      return std::make_unique<event::KeyInput>(KeyCode::L, modifiers, false);
    case 'm':
      return std::make_unique<event::KeyInput>(KeyCode::M, modifiers, false);
    case 'n':
      return std::make_unique<event::KeyInput>(KeyCode::N, modifiers, false);
    case 'o':
      return std::make_unique<event::KeyInput>(KeyCode::O, modifiers, false);
    case 'p':
      return std::make_unique<event::KeyInput>(KeyCode::P, modifiers, false);
    case 'q':
      return std::make_unique<event::KeyInput>(KeyCode::Q, modifiers, false);
    case 'r':
      return std::make_unique<event::KeyInput>(KeyCode::R, modifiers, false);
    case 's':
      return std::make_unique<event::KeyInput>(KeyCode::S, modifiers, false);
    case 't':
      return std::make_unique<event::KeyInput>(KeyCode::T, modifiers, false);
    case 'u':
      return std::make_unique<event::KeyInput>(KeyCode::U, modifiers, false);
    case 'v':
      return std::make_unique<event::KeyInput>(KeyCode::V, modifiers, false);
    case 'w':
      return std::make_unique<event::KeyInput>(KeyCode::W, modifiers, false);
    case 'x':
      return std::make_unique<event::KeyInput>(KeyCode::X, modifiers, false);
    case 'y':
      return std::make_unique<event::KeyInput>(KeyCode::Y, modifiers, false);
    case 'z':
      return std::make_unique<event::KeyInput>(KeyCode::Z, modifiers, false);

    // Numbers
    case '0':
      return std::make_unique<event::KeyInput>(KeyCode::Num0, modifiers, false);
    case '1':
      return std::make_unique<event::KeyInput>(KeyCode::Num1, modifiers, false);
    case '2':
      return std::make_unique<event::KeyInput>(KeyCode::Num2, modifiers, false);
    case '3':
      return std::make_unique<event::KeyInput>(KeyCode::Num3, modifiers, false);
    case '4':
      return std::make_unique<event::KeyInput>(KeyCode::Num4, modifiers, false);
    case '5':
      return std::make_unique<event::KeyInput>(KeyCode::Num5, modifiers, false);
    case '6':
      return std::make_unique<event::KeyInput>(KeyCode::Num6, modifiers, false);
    case '7':
      return std::make_unique<event::KeyInput>(KeyCode::Num7, modifiers, false);
    case '8':
      return std::make_unique<event::KeyInput>(KeyCode::Num8, modifiers, false);
    case '9':
      return std::make_unique<event::KeyInput>(KeyCode::Num9, modifiers, false);

    // Symbols
    case '!':
      modifiers.shift = true;
      return std::make_unique<event::KeyInput>(KeyCode::Exclamation, modifiers,
                                               false);
    case '"':
      modifiers.shift = true;
      return std::make_unique<event::KeyInput>(KeyCode::DoubleQuotes, modifiers,
                                               false);
    case '#':
      modifiers.shift = true;
      return std::make_unique<event::KeyInput>(KeyCode::Hash, modifiers, false);
    case '$':
      modifiers.shift = true;
      return std::make_unique<event::KeyInput>(KeyCode::Dollar, modifiers,
                                               false);
    case '%':
      modifiers.shift = true;
      return std::make_unique<event::KeyInput>(KeyCode::Percent, modifiers,
                                               false);
    case '&':
      modifiers.shift = true;
      return std::make_unique<event::KeyInput>(KeyCode::Ampersand, modifiers,
                                               false);
    case '\'':
      return std::make_unique<event::KeyInput>(KeyCode::SingleQuote, modifiers,
                                               false);
    case '(':
      modifiers.shift = true;
      return std::make_unique<event::KeyInput>(KeyCode::LeftParenthesis,
                                               modifiers, false);
    case ')':
      modifiers.shift = true;
      return std::make_unique<event::KeyInput>(KeyCode::RightParenthesis,
                                               modifiers, false);
    case '*':
      modifiers.shift = true;
      return std::make_unique<event::KeyInput>(KeyCode::Asterisk, modifiers,
                                               false);
    case '+':
      modifiers.shift = true;
      return std::make_unique<event::KeyInput>(KeyCode::Plus, modifiers, false);
    case ',':
      return std::make_unique<event::KeyInput>(KeyCode::Comma, modifiers,
                                               false);
    case '-':
      return std::make_unique<event::KeyInput>(KeyCode::Minus, modifiers,
                                               false);
    case '.':
      return std::make_unique<event::KeyInput>(KeyCode::Dot, modifiers, false);
    case '/':
      return std::make_unique<event::KeyInput>(KeyCode::Slash, modifiers,
                                               false);
    case ':':
      modifiers.shift = true;
      return std::make_unique<event::KeyInput>(KeyCode::Colon, modifiers,
                                               false);
    case ';':
      return std::make_unique<event::KeyInput>(KeyCode::Semicolon, modifiers,
                                               false);
    case '<':
      modifiers.shift = true;
      return std::make_unique<event::KeyInput>(KeyCode::LessThan, modifiers,
                                               false);
    case '=':
      return std::make_unique<event::KeyInput>(KeyCode::Equal, modifiers,
                                               false);
    case '>':
      modifiers.shift = true;
      return std::make_unique<event::KeyInput>(KeyCode::GreaterThan, modifiers,
                                               false);
    case '?':
      modifiers.shift = true;
      return std::make_unique<event::KeyInput>(KeyCode::Question, modifiers,
                                               false);
    case '@':
      modifiers.shift = true;
      return std::make_unique<event::KeyInput>(KeyCode::At, modifiers, false);
    case '[':
      return std::make_unique<event::KeyInput>(KeyCode::LeftBracket, modifiers,
                                               false);
    case '\\':
      return std::make_unique<event::KeyInput>(KeyCode::Backslash, modifiers,
                                               false);
    case ']':
      return std::make_unique<event::KeyInput>(KeyCode::RightBracket, modifiers,
                                               false);
    case '^':
      modifiers.shift = true;
      return std::make_unique<event::KeyInput>(KeyCode::Caret, modifiers,
                                               false);
    case '_':
      modifiers.shift = true;
      return std::make_unique<event::KeyInput>(KeyCode::Underscore, modifiers,
                                               false);
    case '`':
      return std::make_unique<event::KeyInput>(KeyCode::Backtick, modifiers,
                                               false);
    case '{':
      modifiers.shift = true;
      return std::make_unique<event::KeyInput>(KeyCode::LeftBrace, modifiers,
                                               false);
    case '|':
      modifiers.shift = true;
      return std::make_unique<event::KeyInput>(KeyCode::VerticalBar, modifiers,
                                               false);
    case '}':
      modifiers.shift = true;
      return std::make_unique<event::KeyInput>(KeyCode::RightBrace, modifiers,
                                               false);
    case '~':
      modifiers.shift = true;
      return std::make_unique<event::KeyInput>(KeyCode::Tilde, modifiers,
                                               false);
    default:
      break;
    }
  }
  return std::make_unique<event::Input>(InputType::None);
}
