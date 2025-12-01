#include <cdrom.h>
#include <level.h>
#include <stdio.h>
#include <stdlib.h>


room_meta *loaded_rooms[MAX_LOADED_ROOMS];
room_meta room_metas[MAX_ROOMS];
int total_rooms = 0;
uint32_t currentFileLBA = 0;

level_meta *level_load(FileStream *s, LEVEL_LOAD_ERR *err){
    level_meta *level;
    
    // Header
    if(
        FileStream_read8(s) != 'M' ||
        FileStream_read8(s) != 'A' ||
        FileStream_read8(s) != 'P'
    ){
        *err = INVALID_HEADER;
        return NULL;
    }
    if(FileStream_read8(s) != 0x01){
        *err = UNSUPPORTED_VERSION;
        return NULL;
    }

    level = malloc(sizeof(level_meta));
    level->room_count = FileStream_read32(s);
    
    if(level->room_count == 0){
        *err = WARN_ZERO_ROOMS;
        return level;
    }

    level->rooms = malloc(sizeof(room_meta) * level->room_count);
    for(int room_i = 0; room_i < level->room_count; room_i ++){
        room_meta *r = &level->rooms[room_i];
        FileStream_readBytes(s, r->name, 32);
        r->entity_count = FileStream_read16(s);
        r->entity_first = FileStream_read32(s);
    }

    *err = LOAD_OK;
    return level;
}

void level_unload(level_meta *){
    // Destructor
    
}


void room_load(FileStream *s, room_meta *r){
    if(!s) return;
    if(!r) return;
    if(r->loaded) return;
    if(!r->entity_count) return;
    if(!r->entity_first) return;

    r->entities = malloc(sizeof(ent_generic*) * r->entity_count);

    FileStream_seek(s, r->entity_first);

    for(int ent_i = 0; ent_i < r->entity_count; ent_i++){
        ENT_TYPE type = FileStream_read16(s);
        switch(type){
            case ENT_FUNC_ROOM:
                ent_func_room *e = malloc(sizeof(ent_func_room));
                r->entities[ent_i] = (ent_generic*)e;
                e->base.type = type;
                

                e->bsp_offset = 0; // Unsupported for now.
                s->globalOffset+=4; // Skip 32-bits (reserved for bsp for now)
                
                // TODO: Turn this into a function to read brush_render or even entire brushes
                uint16_t tri_count = FileStream_read16(s);
                uint16_t quad_count = FileStream_read16(s);
                
                // Allocate all the extra arrays TODO: Redesign this to not need as many mallocs
                e->render->triCount = tri_count;
                e->render->quadCount = quad_count;
                e->render->tris = malloc(sizeof(uint32_t) * 9 * tri_count);
                e->render->triPrims = malloc(sizeof(uint32_t) * 9 * tri_count * 2);
                e->render->quads = malloc(sizeof(uint32_t) * 12 * quad_count);
                e->render->quadPrims = malloc(sizeof(uint32_t) * 11 * quad_count * 2);

                // Read the structs into their proper place.
                FileStream_readBytes(s, e->render->tris, sizeof(Tri3) * tri_count);
                FileStream_readBytes(s, e->render->triPrims, sizeof(uint32_t) * 9 * tri_count); // 2x for double-buffering
                s->globalOffset -= sizeof(uint32_t) * 9 * tri_count; // Rewind
                FileStream_readBytes(s, &e->render->triPrims[9 * tri_count], sizeof(uint32_t) * 9 * tri_count);
                FileStream_readBytes(s, e->render->quads, sizeof(Quad3) * quad_count);
                FileStream_readBytes(s, e->render->quadPrims, sizeof(uint32_t) * 11 * quad_count); // 2x for double-buffering
                s->globalOffset -= sizeof(uint32_t) * 11 * quad_count; // Rewind
                FileStream_readBytes(s, &e->render->quadPrims[11 * quad_count], sizeof(uint32_t) * 11 * quad_count); // 2x for double-buffering


                break;
            default:
                // Unsupported Type
                r->entities[ent_i] = NULL;
                break;
        }
    }

    r->loaded = true;
}


