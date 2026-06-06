# Architecture POC (Raylib-Friendly Layer System)

This proof-of-concept introduces a minimal layer architecture inspired by Cherno's pattern, adapted for this Raylib snake project.

## What was added

- `src/core/layer.hpp`
  - Base `Layer` abstraction with three lifecycle hooks:
    - `OnEvent(Event&)`
    - `OnUpdate(float deltaTime)`
    - `OnRender()`
- `src/core/event.hpp`
  - Type-safe event model (`Event`, `EventDispatcher`)
  - Minimal events used by the POC:
    - `KeyPressedEvent`
    - `WindowCloseEvent`
    - `GameOverEvent`
- `src/core/layer_stack.hpp`
  - Ordered container for layers + overlays
- `src/core/application.hpp`
  - Main loop manager
  - Per-frame update/render dispatch
  - Event routing through stack (topmost layer first)

## Example layers

- `src/layers/input_layer.hpp/.cpp`
  - Polls Raylib input via existing `RaylibInputHandler`
  - Emits `KeyPressedEvent`
  - Emits `WindowCloseEvent` when `WindowShouldClose()` is true
- `src/layers/game_layer.hpp/.cpp`
  - Wraps existing `Game` class
  - Converts `KeyPressedEvent` to existing `event::KeyInput`
  - Owns existing `RaylibRenderer`
  - Emits `GameOverEvent` when the snake dies
- `src/layers/debug_layer.hpp/.cpp`
  - Shows runtime debug info in window title (`Score`, `FPS`)

## Flow overview

1. `Application::Run()` updates all layers.
2. `InputLayer` emits events into application queue.
3. Application dispatches events from top layer to bottom layer.
4. `GameLayer` handles key events and updates game state.
5. `DebugLayer` updates debug information (window title).

## Incremental migration idea

You can migrate existing features by introducing new layers one-by-one:

- Menu/pause screen as overlays
- Settings or control remapping layer
- Runtime debug tooling layer

No need to replace everything at once. The old wiring is preserved as comments in `src/main.cpp` for comparison.
