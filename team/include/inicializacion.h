#ifndef INICIALIZACION_H
#define INICIALIZACION_H

#include<commons/collections/list.h>
#include<commons/string.h>
#include "common_utils.h"
#include "suscripcion.h"
#include <semaphore.h>

typedef enum{
	NEW = 0,
	READY,
	EXEC,
	BLOCKED,
    BLOCKED_BY_BROKER,
	E_P_EXIT
} enum_process_state;
/* Estructura de posición */
typedef struct{
    uint32_t posix;
    uint32_t posiy;   
} t_position_to_map;

typedef struct{
    char *pokemon; 
    t_position position;
} t_pokemon;

/* Estructura basica de un entrenador*/
typedef struct{
    uint32_t id_trainer;
    t_position position;
    t_list* pokemonOwned; ///Pokemons that i captured 
    t_list* pokemonNeeded; //Pokemons that i must capture to accomplish the objetive
} t_trainer;

//hilos de entrenador / metricas de algoritmos
typedef struct {
    uint32_t idTrainer;
    enum_process_state state;
    pthread_t threadTrainer;
    pthread_mutex_t mutexAction;
    time_t incomingTime;
    double valueEstimator; //Needed for SJF 
    uint32_t contextSwitchCount;
    uint32_t cpuCycleCount;
    t_position positionTo;
    bool destinyIsTrainer;
    uint32_t interchangeCycleCount;
    uint32_t idMessageCatch;
} t_threadTrainer;

/* Estructura con los datos del archivo de configuración */
typedef struct{
       char *ip_team;
       char *puerto_team;
       uint32_t tiempo_reconexion; 
       uint32_t  retardo_ciclo_cpu; 
       char *algoritmo_planificacion;
       uint32_t quantum;
       double alpha;
       uint32_t estimacion_inicial;
       char *ip_broker;
       char *puerto_broker;       
} t_configuration;

t_list* trainers; //List of type t_trainer
t_configuration config_values; //Values readed from tema.config
t_list* threadsTrainers;
t_list* globalObjetive;
uint32_t deadlockCount;
sem_t plannerSemaphore;
char* pokemonCompareGlobalObjetive; //Variable used ONLY to calculate global objetive

void* planTrainers();
void initialize_team();
void validateEndTeam();
void read_config();
void create_optional_logger();
void create_obligatory_logger();
void load_values_config();
void assign_data_trainer();
void* trainerDo(void* ptrIdTrainer);
void release_resources();
void destroy_pointer(void*);
void destroy_lists_and_loaded_elements();

void calculate_global_objetives();
bool analyzePokemonInGlobal(void* );

#endif



