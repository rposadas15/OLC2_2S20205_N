#ifndef ERRORS_H
#define ERRORS_H

#include <stdarg.h>

/* Nivel de error */
typedef enum {
    ERR_LEX = 1,
    ERR_SYN = 2,
    ERR_SEM = 3
} ErrKind;

/* Inicializa el módulo (útil para incluir nombre de archivo) */
void err_init(const char* filename);

/* Setea el nombre de archivo si cambia durante la ejecución */
void err_set_filename(const char* filename);

/* Reporte genérico con (linea,columna) */
void err_report(ErrKind kind, int line, int col, const char* fmt, ...);

/* Reporte con rango (línea/columna inicial y final) */
void err_report_range(ErrKind kind, int fl, int fc, int ll, int lc, const char* fmt, ...);

/* Accesores y resumen */
int  err_count(void);
void err_summary_to_stderr(void);

#endif
