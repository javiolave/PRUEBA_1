#include <stdio.h>
#include <math.h>

#define MAX_SISMOS 3180 // Número máximo de sismos a procesar

int main() {
    FILE* fp;
    char filename[] = "sismos.csv";
    char line[100];
    double magnitudes[MAX_SISMOS];
    double profundidades[MAX_SISMOS];
    double latitudes[MAX_SISMOS];
    double longitudes[MAX_SISMOS];
    int num_sismos = 0;
    double sum_magnitudes = 0;
    double sum_profundidades = 0;
    double sum_latitudes = 0;
    double sum_longitudes = 0;

    // Abrir archivo
    fp = fopen(filename, "r");
    if (fp == NULL) {
        printf("Error al abrir archivo\n");
        return 1;
    }

    // Leer archivo línea por línea
    while (fgets(line, sizeof(line), fp)) {
        // Parsear línea
        int ano, mes, dia, hora, min, sec;
        double lat, lon, prof, mag;
        sscanf(line, "%d,%d,%d,%d,%d,%d,%lf,%lf,%lf,%lf", &ano, &mes, &dia, &hora, &min, &sec, &lat, &lon, &prof, &mag);

        // Calcular estadísticas
        magnitudes[num_sismos] = mag;
        profundidades[num_sismos] = prof;
        latitudes[num_sismos] = lat;
        longitudes[num_sismos] = lon;
        sum_magnitudes += mag;
        sum_profundidades += prof;
        sum_latitudes += lat;
        sum_longitudes += lon;
        num_sismos++;
    }

    // Calcular promedios
    double prom_magnitudes = sum_magnitudes / num_sismos;
    double prom_profundidades = sum_profundidades / num_sismos;
    double prom_latitudes = sum_latitudes / num_sismos;
    double prom_longitudes = sum_longitudes / num_sismos;

    // Calcular desviaciones estándar
    double sum_var_magnitudes = 0;
    double sum_var_profundidades = 0;
    double sum_var_latitudes = 0;
    double sum_var_longitudes = 0;
    for (int i = 0; i < num_sismos; i++) {
        sum_var_magnitudes += pow(magnitudes[i] - prom_magnitudes, 2);
        sum_var_profundidades += pow(profundidades[i] - prom_profundidades, 2);
        sum_var_latitudes += pow(latitudes[i] - prom_latitudes, 2);
        sum_var_longitudes += pow(longitudes[i] - prom_longitudes, 2);
    }
    double desv_magnitudes = sqrt(sum_var_magnitudes / num_sismos);
    double desv_profundidades = sqrt(sum_var_profundidades / num_sismos);
    double desv_latitudes = sqrt(sum_var_latitudes / num_sismos);
    double desv_longitudes = sqrt(sum_var_longitudes / num_sismos);

    // Cerrar archivo
    fclose(fp);

    
    // Imprimir resultados
    printf("Número de sismos: %d\n", num_sismos);
    printf("Magnitud promedio: %lf\n", prom_magnitudes);
    printf("Profundidad promedio: %lf\n", prom_profundidades);
    printf("Latitud promedio: %lf\n", prom_latitudes);
    printf("Longitud promedio: %lf\n", prom_longitudes);
    printf("Desviación estándar de magnitudes: %lf\n", desv_magnitudes);
    printf("Desviación estándar de profundidades: %lf\n", desv_profundidades);
    printf("Desviación estándar de latitudes: %lf\n", desv_latitudes);
    printf("Desviación estándar de longitudes: %lf\n", desv_longitudes);

}


    
