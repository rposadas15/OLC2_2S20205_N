#include "errors.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

static int   G_ERR_COUNT = 0;
static char  G_FILE[512] = {0};

void err_init(const char* filename) {
    G_ERR_COUNT = 0;
    if (filename) {
        strncpy(G_FILE, filename, sizeof(G_FILE)-1);
        G_FILE[sizeof(G_FILE)-1] = '\0';
    } else {
        G_FILE[0] = '\0';
    }
}

void err_set_filename(const char* filename) {
    if (!filename) return;
    strncpy(G_FILE, filename, sizeof(G_FILE)-1);
    G_FILE[sizeof(G_FILE)-1] = '\0';
}

static const char* kind_str(ErrKind k) {
    switch(k) {
        case ERR_LEX: return "lexical error";
        case ERR_SYN: return "syntax error";
        case ERR_SEM: return "semantic error";
        default:      return "error";
    }
}

static void vreport_prefix(ErrKind kind, int line, int col) {
    if (G_FILE[0]) fprintf(stderr, "%s:%d:%d: %s: ", G_FILE, line, col, kind_str(kind));
    else           fprintf(stderr, "%d:%d: %s: ", line, col, kind_str(kind));
}

void err_report(ErrKind kind, int line, int col, const char* fmt, ...) {
    ++G_ERR_COUNT;
    vreport_prefix(kind, line, col);
    va_list ap;
    va_start(ap, fmt);
    vfprintf(stderr, fmt, ap);
    va_end(ap);
    fprintf(stderr, "\n");
}

void err_report_range(ErrKind kind, int fl, int fc, int ll, int lc, const char* fmt, ...) {
    ++G_ERR_COUNT;
    if (G_FILE[0]) fprintf(stderr, "%s:%d:%d-%d:%d: %s: ", G_FILE, fl, fc, ll, lc, kind_str(kind));
    else           fprintf(stderr, "%d:%d-%d:%d: %s: ", fl, fc, ll, lc, kind_str(kind));
    va_list ap;
    va_start(ap, fmt);
    vfprintf(stderr, fmt, ap);
    va_end(ap);
    fprintf(stderr, "\n");
}

int err_count(void) { return G_ERR_COUNT; }

void err_summary_to_stderr(void) {
    if (G_ERR_COUNT == 0) {
        fprintf(stderr, "No se encontraron errores.\n");
    } else {
        fprintf(stderr, "Total de errores: %d\n", G_ERR_COUNT);
    }
}
