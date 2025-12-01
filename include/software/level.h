#include <types.h>
#include <filesystem.h>

#define MAX_ROOMS 32
#define MAX_LOADED_ROOMS 5
#define ROOM_SIZE 38
#define HEADER_SIZE 8

typedef enum LEVEL_LOAD_ERR {
    LOAD_OK,
    INVALID_HEADER,
    UNSUPPORTED_VERSION,
    WARN_ZERO_ROOMS,
} LEVEL_LOAD_ERR;

typedef struct room_meta{
    uint8_t name[32];
    bool loaded;
    uint16_t entity_count;
    uint32_t entity_first; // Offset into file to find first entity
    ent_generic **entities; // If loaded, pointer to entities. If unloaded, undefined (possibly NULL)
} room_meta;

typedef struct level_meta{    
    uint32_t room_count;
    room_meta *rooms;
} level_meta;


extern room_meta *loaded_rooms[];
extern room_meta room_metas[];
extern int total_rooms;
extern uint32_t currentFileLBA;




/// @brief Load a level from a FileStream
/// @param s Pointer to FileStream to load from
/// @param err Loading error enum
/// @return Pointer to the allocated level_meta
level_meta *level_load(FileStream *s, LEVEL_LOAD_ERR *err);
/// @brief Load the entities within a room
/// @param s Pointer to FileStream to load from
/// @param r Pointer to the room_meta to load into
void room_load(FileStream *s, room_meta *r);

