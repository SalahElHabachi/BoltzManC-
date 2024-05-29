#include <cstdlib>
#include <string>
#include <iostream>

#include "lbm/LBMSolver.h" 

#include <chrono>

int main(int argc, char* argv[])
{


  // read parameter file and initialize parameter
  // parse parameters from input file
  std::string input_file = argc>1 ? std::string(argv[1]) : "flowAroundCylinder.ini";

  // TODO : uncomment the last two lines when activating OpenACC
  // print OpenACC version / info
  // print_openacc_version();
  //init_openacc();

  ConfigMap configMap(input_file);

  // test: create a LBMParams object
  LBMParams params = LBMParams();
  params.setup(configMap);

  // print parameters on screen
  params.print();

      // Début du chronomètre
  auto start = std::chrono::high_resolution_clock::now(); // l'heure du début de calcul 

  LBMSolver* solver = new LBMSolver(params);

  solver->run();

  auto end = std::chrono::high_resolution_clock::now(); // L'heure de la fin d'exécution


    // Calcul de la durée écoulée en secondes et en nanosecondes
  auto duration_seconds = std::chrono::duration_cast<std::chrono::seconds>(end - start);
  auto duration_nanoseconds = std::chrono::duration_cast<std::chrono::nanoseconds>(end - start);

  auto duration_millisecond = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);

  std::cout << "Temps d'execution : ============================================================\n" 
            << "secondes     : "<<duration_seconds.count() << "    |    " 
            << "milliseconds : " <<duration_millisecond.count() << "    |    " 
            << "nanosecondes : " <<duration_nanoseconds.count() << std::endl;
  std::cout << "================================================================================\n";
  delete solver;


  return EXIT_SUCCESS;
}
