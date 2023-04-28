#!/usr/bin/awk -f

BEGIN {
    FS=","; #separador de columnas
    
    meses[1]="ene" ;#arreglo de meses
    meses[2]="feb";
    meses[3]="mar";
    meses[4]="abr";
    for (i=1; i<=4; i++) {
        total_sismos[i] = 0 ;
        sum_magnitudes[i] = 0;
        sum_profundidades[i] = 0;
        sum_latitudes[i] = 0;
        sum_longitudes[i] = 0;
        count[i] = 0 ;
        
    }

    # Lee el archivo con funcion getline, recorre linea a linea
    while (getline < "sismos.csv") {
        # recorre la fecha
        split($2, fecha, "/") #columna meses
        mes = fecha[2];
        

        # incrementa contador de sismos y sumar valores por mes
        for (i=1; i<=4; i++) {
            if (mes == meses[i]) {
                total_sismos[i]++;
                sum_magnitudes[i] += $10;
                sum_profundidades[i] += $9;
                sum_latitudes[i] += $7;
                sum_longitudes[i] += $8;
                count[i]++;
            }
        }
    

        # verificar si leer el archivo : lo lee.
        #print $0
        
    }

    
    for (i=1; i<=4; i++) { #verifica si esta recorriendo el archivo y calculando lo anterior, recorre pero no calcular
        print "Mes:", meses[i];
        print "total_sismos:", total_sismos[i];
        print "sum_magnitudes:", sum_magnitudes[i];
        print "sum_profundidades:", sum_profundidades[i];
        print "sum_latitudes:", sum_latitudes[i];
        print "sum_longitudes:", sum_longitudes[i];
        print "count:", count[i];
    }

    # Cerrar el archivo
    close("sismos.csv")

    # calcula promedios y desviaciones estándar:
    
    for (i=1; i<=4; i++) {

        if (count[i] != 0) { #verifica que existan sismos para que no haya division por cero 
            prom_magnitudes[i] = sum_magnitudes[i] / count[i];
            prom_profundidades[i] = sum_profundidades[i] / count[i]; #divide cada uno en la cantidad total de sismo de cada mes
            prom_latitudes[i] = sum_latitudes[i] / count[i];
            prom_longitudes[i] = sum_longitudes[i] / count[i];

            for (j=1; j<=count[i]; j++) { 
                sum_var_magnitudes[i] += (prom_magnitudes[i] - $10) ** 2;#cuadrados de la suma de las diferencias entre cada valor
                sum_var_profundidades[i] += (prom_profundidades[i] - $9) ** 2;
                sum_var_latitudes[i] += (prom_latitudes[i] - $7) ** 2;
                sum_var_longitudes[i] += (prom_longitudes[i] - $8) ** 2;         
                desv_magnitudes[i] = sqrt(sum_var_magnitudes[i] / count[i]);
                desv_profundidades[i] = sqrt(sum_var_profundidades[i] / count[i]);
                desv_latitudes[i] = sqrt(sum_var_latitudes[i] / count[i]);
                desv_longitudes[i] = sqrt(sum_var_longitudes[i] / count[i]);
            } 
        }    
    }

    

}           
        
END {

    for (i=1; i<=4; i++) {
        printf("Mes: %s\n", meses[i])
        printf("Numero total de sismos: %d\n", total_sismos[i])
        printf("Promedio de magnitud: %.2f\n", prom_magnitudes[i])
        printf("Desviacion estandar de magnitud: %.2f\n", desv_magnitudes[i])
        printf("Promedio de profundidad: %.2f\n", prom_profundidades)
        printf("Desviacion estandar de profundidad: %.2f\n", desv_profundidades[i])
        printf("Promedio de latitud: %.2f\n", prom_latitudes[i])
        printf("Promedio de longitud: %.2f\n", prom_longitudes[i])
        printf("Desviacion estandar de latitud: %.2f\n", desv_latitudes[i])
        printf("Desviacion estandar de longitud: %.2f\n", desv_longitudes[i])
        printf("\n")
    }
}    
       
    




