/** @file timer.c
 *  @brief Global timer implementation.
 *
 *  @author Alexander Patel <acpatel@andrew.cmu.edu>
 *  @bug No known bugs.
 */

#include <SDL.h>
#include <assert.h>
#include <stdbool.h>
#include <stdint.h>
#include <timer.h>

/** @brief flag determining if timer has been started */
static bool started = false;

/** @brief flag determining if timer is paused */
static bool paused = false;

/** @brief total number of timer ticks since start */
static uint32_t start_ticks = 0;

/** @brief total number of timer ticks since last pause */
static uint32_t pause_ticks = 0;

/** @brief Starts the timer
 *
 *  Requires the timer to not yet be started.
 */
void timer_start(void) {
  assert(!started);

  started = true;
  paused = false;
  start_ticks = SDL_GetTicks();
  pause_ticks = 0;
}

/** @brief Stops the timer
 *
 *  Requires the timer to be started. The timer cannot be used after being
 *  stopped until it is later re-started.
 */
void timer_stop(void) {
  assert(started);

  started = false;
  paused = false;
  start_ticks = 0;
  pause_ticks = 0;
}

/** @brief Resets the timer
 *
 *  Requires the timer to be started.
 */
void timer_reset(void) {
  assert(started);

  paused = false;
  start_ticks = SDL_GetTicks();
  pause_ticks = 0;
}

/** @brief Pauses the timer
 *
 *  Requires the timer to be started and not paused.
 */
void timer_pause() {
  assert(started);
  assert(!paused);

  paused = true;
  pause_ticks = SDL_GetTicks() - start_ticks;
  start_ticks = 0;
}

/** @brief Resumes the timer
 *
 *  Requires the timer to be started and paused.
 */
void timer_resume(void) {
  assert(started);
  assert(paused);

  paused = false;
  start_ticks = SDL_GetTicks() - pause_ticks;
  pause_ticks = 0;
}

/** @brief Returns the current number of timer ticks
 *
 *  Requires that the timer is started.
 *
 *  @return The number of timer ticks. If the timer is currently paused, returns
 *          the number of ticks when the timer was paused. Otherwise, returns
 *          the total number of timer ticks since the timer was started.
 */
uint32_t timer_ticks(void) {
  assert(started);

  return paused ? pause_ticks : SDL_GetTicks() - start_ticks;
}