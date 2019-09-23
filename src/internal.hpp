#ifndef SENTRY_INTERNAL_HPP_INCLUDED
#define SENTRY_INTERNAL_HPP_INCLUDED

// this marker changes the behavior of the header so that some internals
// can be defined differently
#define _SENTRY_INTERNAL

#include <errno.h>
#include <sentry.h>
#include <stdio.h>

#define SENTRY_SDK_NAME "sentry-native"
#define SENTRY_SDK_VERSION "0.0.0"
#define SENTRY_SDK_USER_AGENT (SENTRY_SDK_NAME "/" SENTRY_SDK_VERSION)

#if defined(__APPLE__)
#define OS_MACOS 1
#elif defined(__ANDROID__)
#define OS_ANDROID 1
#elif defined(__linux__)
#define OS_LINUX 1
#elif defined(_WIN32)
#define OS_WIN 1
#else
#error Platform not supported by Sentry
#endif

#define SENTRY_LOGF(message, ...)                                   \
    do {                                                            \
        const sentry_options_t *_options = sentry_get_options();    \
        if (_options && sentry_options_get_debug(_options)) {       \
            fprintf(stderr, "[sentry] " message "\n", __VA_ARGS__); \
        }                                                           \
    } while (0)

#define SENTRY_LOG(Message) SENTRY_LOGF("%s", Message "")

#ifdef _WIN32
#define EINTR_RETRY(X, Y)     \
    do {                      \
        int _tmp = (X);       \
        if (Y) {              \
            *(int *)Y = _tmp; \
        }                     \
    } while (false)
#else
#define EINTR_RETRY(X, Y)                       \
    do {                                        \
        int _tmp;                               \
        do {                                    \
            _tmp = (X);                         \
        } while (_tmp == -1 && errno == EINTR); \
        if (Y) {                                \
            *(int *)Y = _tmp;                   \
        }                                       \
    } while (false)
#endif

#define SENTRY_BREADCRUMBS_MAX 100
static const char *SENTRY_RUNS_FOLDER = "sentry-runs";
static const char *SENTRY_PENDING_FOLDER = "sentry-pending";
static const char *SENTRY_EVENT_FILE = "__sentry-event";
static const char *SENTRY_BREADCRUMB1_FILE = "__sentry-breadcrumb1";
static const char *SENTRY_BREADCRUMB2_FILE = "__sentry-breadcrumb2";

#include "value.hpp"

#endif
