#pragma once
#include <stdint.h>
#include <stdbool.h>

typedef int Time;

typedef uint8_t byte;

typedef enum State {
  SLEEPING,
  AWAKENING,
  AWAKE
} State;

