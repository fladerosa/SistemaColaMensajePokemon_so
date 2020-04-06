#include "gameboy.h"

int main(int argc, char ** argv){

    t_log* obligatory_logger;
    t_log* optional_logger; 

    t_config* config;

    //Inicializando la config
    config = config_create("./cfg/gameboy.config");

    int showConsole = config_get_int_value(config,"LOG_SHOW");

    //Inicializando el logger
    obligatory_logger = log_create("./cfg/obligatory.log", "obligatory", showConsole, LOG_LEVEL_INFO); 
    optional_logger = log_create("./cfg/optional.log", "optional", showConsole, LOG_LEVEL_INFO);

    char* ip; 
    char* port;

    char* server = argv[1];
    //Busco el ip y el puerto
    if(strcmp(server,"BROKER")){
        ip = config_get_string_value(config, "IP_BROKER");
        port = config_get_string_value(config, "PUERTO_BROKER");
    }else if(strcmp(server,"TEAM")){
        ip = config_get_string_value(config, "IP_TEAM");
        port = config_get_string_value(config, "PUERTO_TEAM");
    }else if(strcmp(server,"GAMECARD")){
        ip = config_get_string_value(config, "IP_GAMECARD");
        port = config_get_string_value(config, "PUERTO_GAMECARD");
    }else{
        log_error(optional_logger,"No se pudo conectar");
        exit(4);
    }

    //Creo la conexion
    int connection = create_connection(ip, port);

    //Mando el mensaje
    send_message(argv,connection);

    //Cierro y elimino todo
    closeAll(optional_logger, obligatory_logger,config,connection);
    return 0;
}

void send_message(char** message, int socket_cliente)
{
	t_paquete* paquete = malloc(sizeof(t_paquete));
	
    //El nombre de la funcion esta en el parametro 2 del argv que le paso como parametro
    char* message_function = message[2]; 
    op_code operation_code = stringToEnum(message_function);

    switch(operation_code){
        case 1:
             
        case 2: 
        case 3: 
        case 4: 
        case 5: 
    }
    
    
    int size = strlen(message) + 1;

	//paquete->codigo_operacion = MENSAJE;
	paquete->buffer = malloc(sizeof(t_buffer));
	paquete->buffer->size = size;
	paquete->buffer->stream = malloc(paquete->buffer->size);
	memcpy(paquete->buffer->stream, message, paquete->buffer->size);

	int bytes = paquete->buffer->size + 2*sizeof(int);

	void* a_enviar = serializar_paquete(paquete, bytes);

	send(socket_cliente, a_enviar, bytes, 0);

	free(a_enviar);
	free(paquete->buffer->stream);
	free(paquete->buffer);
	free(paquete);
}

op_code stringToEnum(char* message_function){

    for(int i = 0; i < sizeof(op_code); i++){
        if(strcmp(message_string[i].name, message_function)){
            return message_string[i].operation;
        }
    }
    return 1; //Revisar cuando sale con error
}

closeAll(t_log* optional_logger,t_log* obligatory_logger, t_config* config, int connection){
    log_destroy(optional_logger);
    log_destroy(obligatory_logger);
    config_destroy(config);
    close(connection);
}