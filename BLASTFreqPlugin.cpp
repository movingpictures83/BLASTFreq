#include "PluginManager.h"
#include <stdio.h>
#include <stdlib.h>
#include "BLASTFreqPlugin.h"

void BLASTFreqPlugin::input(std::string file) {
 inputfile = file;
}

void BLASTFreqPlugin::run() {
   
}

void BLASTFreqPlugin::output(std::string file) {
 // alpha_diversity.py -i filtered_otu_table.biom -m observed_species,chao1,shannon,PD_whole_tree -t rep_set.tre -o alpha.txt
   //std::string command = "samtools sort " + inputfile + " > "+file;
	std::string command = "";


command = "awk '/Query=/{print; flag=1; next} flag && /^>/{print; next} flag && /No hits found/{print; flag=0}' "+inputfile+" > temp1.txt";
	std::cout << command << std::endl;
        system(command.c_str());

command = "sed 's/PREDICTED: //' temp1.txt > temp2.txt";
	std::cout << command << std::endl;
        system(command.c_str());

command = "awk '/Query=/{print; flag=1; next} flag && /^>/{print $1,$3; next} flag && /No hits found/{print; flag=0}' temp2.txt > temp3.txt";
	std::cout << command << std::endl;
        system(command.c_str());

command = "sed 's/\\*\\*\\*\\*\\* No hits found \\*\\*\\*\\*\\*/> No_hits_found/g' temp3.txt > temp4.txt";
	std::cout << command << std::endl;
        system(command.c_str());

command = "awk '/Query=/{query=$0; next} $0 ~ /^>/ {result[query][$0]++} END {for (q in result) {max_count=0; most_frequent=""; for (r in result[q]) {if (result[q][r] > max_count) {max_count=result[q][r]; most_frequent=r}} print q, most_frequent}}' temp4.txt > temp5.txt";
	std::cout << command << std::endl;
        system(command.c_str());

command = "awk '{print $2,$4}' temp5.txt > temp6.txt";
	std::cout << command << std::endl;
        system(command.c_str());
command = "sed -i 's/ /\t/' temp6.txt";
	std::cout << command << std::endl;
        system(command.c_str());

command = "echo -e \"contig\\tMostHits\" > "+file;//TopHitBLAST.txt
	std::cout << command << std::endl;
        system(command.c_str());

command = "sort -t_ -k2n temp3.txt >> "+file;//TopHitBLAST.txt
	std::cout << command << std::endl;
        system(command.c_str());


}

PluginProxy<BLASTFreqPlugin> BLASTFreqPluginProxy = PluginProxy<BLASTFreqPlugin>("BLASTFreq", PluginManager::getInstance());
