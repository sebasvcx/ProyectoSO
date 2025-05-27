#!/usr/bin/perl
use strict;
use warnings;
use Time::HiRes qw(gettimeofday tv_interval);

my $results_dir = "./results";
my @executables = ("pdispersa", "hdispersa");
my $runs = 100;
my $csv_file = "$results_dir/results.csv";

# Lista fija de matrices
my @matrices = qw(
    matriz1000.txt
);

# Crea el directorio de resultados si no existe
mkdir $results_dir unless -d $results_dir;

# Abre el archivo CSV para escribir resultados
open(my $csv, ">", $csv_file) or die "No se puede abrir $csv_file: $!";
print $csv "Ejecucion;Tiempo\n";

foreach my $exe (@executables) {
    foreach my $matrix (@matrices) {
        for my $i (1..$runs) {
            my $matrix_path = "./$matrix";
            my $start = [gettimeofday];
            # Ajusta los parámetros -f, -c, -n, -p según corresponda a tus matrices
            system("./$exe -f 10 -c 10 -a $matrix_path -n 4 -p 50 > /dev/null 2>&1");
            my $elapsed = tv_interval($start) * 1_000_000; # microsegundos
            print $csv "$i;$elapsed\n";
            print "$exe $matrix $i $elapsed\n";
        }
    }
}

close($csv);
print "Resultados guardados en $csv_file\n";