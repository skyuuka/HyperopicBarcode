#include <stdio.h>

#include "gnuplot.h"
#include "scanlines.h"


void save_data(Simulator *sim, const char *outfilename)
{
	char datafilename[1000];
	sprintf(datafilename, "%s.dat", outfilename);
	FILE *datafile = fopen(datafilename, "w");
	int start = sim->start - 20;
	int stop = sim->stop + 20;
	for (int x = start; x < stop; x++) {
		fprintf(datafile,
				"% 5d % 10.6f % 10.6f % 10.6f % 10.6f % 10.6f % 10.6f\n",
				x,
				sim->input[x] == UNKNOWN ? NAN : sim->input[x],
				sim->threshold[x] == UNKNOWN ? NAN : sim->threshold[x],
				sim->black[x] == UNKNOWN ? NAN : sim->black[x],
				sim->white[x] == UNKNOWN ? NAN : sim->white[x],
				sim->guess[x] == UNKNOWN ? NAN : sim->guess[x],
				sim->blur[x] == UNKNOWN ? NAN : sim->blur[x]);
	}
	fclose(datafile);
}


void plot_sections(Simulator *sim, FILE *plotfile)
{
	fprintf(plotfile, "set style rect fc lt -1 fs solid 0.3 noborder\n");
	for (int i = 0; i <= 96; i++) {
		if (i > 3 && i < 45 && (i - 3) % 7)
			continue;
		if (i > 50 && i < 92 && (i - 50) % 7)
			continue;
		float l = (float) sim->sections[i] - 0.5;
		float r = (float) sim->sections[i] + 0.5;
		fprintf(plotfile,
				"set obj rect from %.3f, graph 0 to %.3f, graph 1\n", l,
				r);
	}
}


void plot_digits(Simulator *sim, float y, FILE *plotfile)
{
	for (int d = 1; d < 13; d++) {
		int section = 7 * d - 1;
		if (d > 6)
			section += 5;
		fprintf(plotfile,
				"set label %d '%d' at %d, %.3f front nopoint\n",
				d, sim->digits[d], sim->sections[section], y);
	}
	int digit_width = sim->sections[7] - sim->sections[0];
	int x = sim->sections[3] - digit_width;
	fprintf(plotfile,
			"set label %d '%d' at %d, %.3f front nopoint\n",
			13, sim->digits[0], x, y);
	digit_width = sim->sections[95] - sim->sections[88];
	x = sim->sections[91] + digit_width;
	char extra[40] = { 0 };
	if (sim->checksum != sim->digits[12])
		strcpy(extra, " tc rgb 'red'");
	fprintf(plotfile,
			"set label %d '%d' at %d, %.3f front nopoint%s\n",
			14, sim->checksum, x, y, extra);
}


void plot_simulator(Simulator *sim, const char *select,
					const char *outfilename)
{
	// Save all curves to one data file.
	save_data(sim, outfilename);

	float bright = 0.0;
	float dark = 1.0;
	median(sim->width, sim->white, sim->start, sim->stop,
		   NULL, &bright, NULL, NULL, NULL);
	median(sim->width, sim->black, sim->start, sim->stop,
		   NULL, NULL, NULL, &dark, NULL);
	float range = dark - bright;
	dark += range / 10;
	bright -= range / 10;
	float digits = bright + range / 20;

	char plotfilename[1000];
	sprintf(plotfilename, "%s.plt", outfilename);
	FILE *plotfile = fopen(plotfilename, "w");
	fprintf(plotfile, "set terminal pdf size 4, 1.5\n");
	fprintf(plotfile, "set output '%s.pdf'\n", outfilename);
	fprintf(plotfile, "set lmargin 3\n");
	fprintf(plotfile, "set rmargin 2\n");
	if (strstr(select, "key"))
		fprintf(plotfile, "set key top left\n");
	else
		fprintf(plotfile, "set key off\n");
	fprintf(plotfile, "set size ratio 0.33333333\n", outfilename);
	fprintf(plotfile, "set yrange [%.4f:%.4f]\n", bright, dark);
	fprintf(plotfile, "set style line 1 lt rgb 'red' lw 3\n", outfilename);
	fprintf(plotfile, "set style line 2 lt rgb 'blue' lw 3\n",
			outfilename);
	if (strstr(select, "sections"))
		plot_sections(sim, plotfile);
	if (strstr(select, "digits"))
		plot_digits(sim, digits, plotfile);
	fprintf(plotfile, "plot \\\n", outfilename);
	if (strstr(select, "input"))
		fprintf(plotfile,
				"'%s.dat' using 1:2 with lines ls 1 title 'input', \\\n",
				outfilename);
	if (strstr(select, "threshold"))
		fprintf(plotfile,
				"'%s.dat' using 1:3 with lines ls 3 title 'threshold', \\\n",
				outfilename);
	if (strstr(select, "black"))
		fprintf(plotfile,
				"'%s.dat' using 1:4 with lines ls 2 title 'black', \\\n",
				outfilename);
	if (strstr(select, "white"))
		fprintf(plotfile,
				"'%s.dat' using 1:5 with lines ls 2 title 'white', \\\n",
				outfilename);
	if (strstr(select, "guess"))
		fprintf(plotfile,
				"'%s.dat' using 1:6 with lines ls 2 title 'guess', \\\n",
				outfilename);
	if (strstr(select, "simulated"))
		fprintf(plotfile,
				"'%s.dat' using 1:7 with lines ls 2 title 'simulated', \\\n",
				outfilename);
	fprintf(plotfile, "NaN notitle\n");
	fclose(plotfile);
}
